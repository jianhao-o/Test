// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HAIController_Base.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AHAIController_Base : public AAIController
{
	GENERATED_BODY()

public:
	AHAIController_Base();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/*控制器和行为树直接通讯 , 所以黑板放这里方便中转*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "黑板")
	UBlackboardComponent* HBlackBoard; 
};
