// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Hao_PropsFell.h"
#include "Hao_PropsFell_Adsorption.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AHao_PropsFell_Adsorption : public AHao_PropsFell
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = true))
	float MoveSpeed = 10.0f;

	bool CanMove = false;

public:
	// Sets default values for this actor's properties
	AHao_PropsFell_Adsorption();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void HTimer() override;
};
