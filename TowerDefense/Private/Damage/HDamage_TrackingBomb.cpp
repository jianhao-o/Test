// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/HDamage_TrackingBomb.h"
#include "HCharacter_Base.h"
#include "HBlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Damage/HDamage_Base.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

void AHDamage_TrackingBomb::BeginPlay()
{
	Super::BeginPlay();
	/*此行成立时 , 说明攻击对象有初始值 , 直接减少一次弹射*/
	if (Enemies){ CatapultNum--; }
	/*启用定时器, 开始弹射*/
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AHDamage_TrackingBomb::UpdateLocation,
		1.0f / HFrame, true);

}

/*事件开始重叠*/
void AHDamage_TrackingBomb::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Super::HandleOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (HIgnoreDamage.Contains(OtherActor)) { return; }
	AHCharacter_Base* OtherActorTemp = Cast<AHCharacter_Base>(OtherActor);
	if (OtherActorTemp && OtherActorTemp->HTeam != Team_Actor && OtherActorTemp->HP_Current > 0)
	{
		//伤害函数 , 发起伤害
		UGameplayStatics::ApplyDamage(OtherActor, HDamage, OwnerController, this, nullptr);
		HIgnoreDamage.Emplace(OtherActor);
	}
}

/*计时器调用的函数*/
void AHDamage_TrackingBomb::UpdateLocation()
{
	i++;
	//UE_LOG(LogTemp, Warning, TEXT("%d"),i%60);
	/*自动索敌*/
	if ( Enemies == nullptr ||
		Enemies && UKismetMathLibrary::VSize(Enemies->GetActorLocation() - this->GetActorLocation()) < 50.0f)
	{
		Enemies = nullptr;
		UHBlueprintFunctionLibrary::HGetEnemiesInRange(this, Team_Actor, HNearest, SearchRadius,
			ObjectTypes, HIgnore, Enemies);
		AHDamage_Base::HIgnore.Emplace(Enemies);
		if (CatapultNum <= 0 || Enemies == nullptr)
		{
			/*弹射全部完成 , 根据句柄清空定时器*/
			GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
			/*头部特效直接销毁*/
			EmitterComp->DestroyComponent(true);
			/*自身延迟销毁*/
			AHDamage_Base::HDelayDestroy(0.2f);
			return;
		}
		CatapultNum--;
	}
	/*位移*/
	this->SetActorLocation(UKismetMathLibrary::VInterpTo(this->GetActorLocation(), Enemies->GetActorLocation(),
		1.0f / HFrame, MoveSpeed));

}
