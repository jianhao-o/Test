// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/HDamage_TrackingBomb.h"
#include "HCharacter_Base.h"
#include "HBlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Damage/HDamage_Base.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AHDamage_TrackingBomb::AHDamage_TrackingBomb()
{	/*组件注册*/
	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	/*初始化速度*/
	ProjectileComp->InitialSpeed = HInitialSpeed;
}

void AHDamage_TrackingBomb::BeginPlay()
{
	Super::BeginPlay();
	if (Enemies)
	{
		ProjectileComp->DestroyComponent();
		CatapultNum--;
		HIgnore.Emplace(Enemies);
		/*启用定时器, 开始弹射*/
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AHDamage_TrackingBomb::UpdateLocation,
			1.0f / HFrame, true);
	}
}

void AHDamage_TrackingBomb::OnConstruction(const FTransform& Transform)
{	
	Super::OnConstruction(Transform);
	/*用户修改时 , 初始化速度*/
	ProjectileComp->InitialSpeed = HInitialSpeed;
	/*旋转跟随速度方向*/
	ProjectileComp->bRotationFollowsVelocity = HRotationFollowsVelocity;
	/*锁定平面*/
	ProjectileComp->bConstrainToPlane = HConstrainToPlane;
	ProjectileComp->SetPlaneConstraintNormal(FVector(0.0f, 0.0f, 1.0f));
}

/*事件开始重叠*/
void AHDamage_TrackingBomb::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	//Super::HandleOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (HIgnoreDamage.Contains(OtherActor)) {return;}
	HIgnoreDamage.Emplace(OtherActor);
	HIgnore.Emplace(OtherActor);
	AHCharacter_Base* OtherActorTemp = Cast<AHCharacter_Base>(OtherActor);
	if (OtherActorTemp && OtherActorTemp->CharacterAttributes.HTeam != Team_Actor && OtherActorTemp->HP_Current > 0)
	{
		//伤害函数 , 发起伤害
		UGameplayStatics::ApplyDamage(OtherActor, HDamage, OwnerController, this, nullptr);
	}
	/*判断是否包含抛射物组件*/
	if (ProjectileComp)
	{
		ProjectileComp->DestroyComponent();
		/*启用定时器, 开始弹射*/
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AHDamage_TrackingBomb::UpdateLocation,
			1.0f / HFrame, true);
	}
}

/*计时器调用的函数*/
void AHDamage_TrackingBomb::UpdateLocation()
{
	//i++;
	/*自动索敌
	*敌人为空 或 双方距离小于50 , 才会索敌*/
	if (Enemies == nullptr ||
		Enemies && UKismetMathLibrary::VSize(Enemies->GetActorLocation() - this->GetActorLocation()) < HRadiu)
	{	
		/*为条件2:距离50 , 成立时清空*/
		Enemies = nullptr;
		UHBlueprintFunctionLibrary::HGetEnemiesInRange(this, Team_Actor, HNearest, SearchRadius,
			ObjectTypes, HIgnore, Enemies);	
		HIgnore.Emplace(Enemies);
		if (CatapultNum <= 0 || Enemies == nullptr)
		{
			/*弹射全部完成 , 根据句柄清空定时器*/
			GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
			/*头部特效直接销毁*/
			EmitterComp->DestroyComponent();
			/*碰撞体销毁*/
			SphereComp->DestroyComponent();
			/*自身延迟销毁*/
			AHDamage_Base::HDelayDestroy(0.2f);
			return;
		}
		CatapultNum--;
		UE_LOG(LogTemp, Warning, TEXT("找到敌人"));
		
	}
	/*位移*/
	this->SetActorLocation(UKismetMathLibrary::VInterpTo(this->GetActorLocation(), Enemies->GetActorLocation(),
		1.0f / HFrame, MoveSpeed));

}
