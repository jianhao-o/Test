// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damage/Weapon/HWeapon_Base.h"
#include "HWeapon_Crossbow.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AHWeapon_Crossbow : public AHWeapon_Base
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void EndFire() override;
	/*发射交给蓝图*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Hao")
	void SpawnAct();
};
