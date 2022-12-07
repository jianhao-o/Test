// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damage/HDamage_Base.h"
#include "HDamage_Sphere.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AHDamage_Sphere : public AHDamage_Base
{
	GENERATED_BODY()

public:
	/*重叠事件重载*/
	virtual void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&
		SweepResult) override;

/*以上原始内容*/

//变量区************************************************************************************
public:
	/*启用循环*/
	bool EnableLoop;
	/*循环间隔*/
	float Interval;
	/*时间管理器中的句柄*/
	FTimerHandle CountdownTimerHandle;
	/*典中典 , 自变量i*/
	int i = 0;



//函数区************************************************************************************
	/*定时函数*/
	void LoopTakeDamage();

};
