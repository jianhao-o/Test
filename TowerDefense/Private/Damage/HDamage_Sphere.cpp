// Fill out your copyright notice in the Description page of Project Settings.


#include "Damage/HDamage_Sphere.h"
#include "HCharacter_Base.h"
#include "Kismet/GameplayStatics.h"

/*父类重叠事件重载*/
void AHDamage_Sphere::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::HandleOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (EnableLoop)
	{
		/*启用定时器, 开始循环伤害
		*循环模式我暂时不想做
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AHDamage_Sphere::LoopTakeDamage,
			Interval, true);*/
	}
	else
	{
		AHCharacter_Base* TempActor = Cast<AHCharacter_Base>(OtherActor);
		if(TempActor && TempActor->CharacterAttributes.HTeam != Team_Actor && TempActor->HP_Current > 0)
		{
			UGameplayStatics::ApplyDamage(OtherActor, HDamage, OwnerController, this, nullptr);
		}
		
	}
}
