// Fill out your copyright notice in the Description page of Project Settings.


#include "HAIController_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HCharacter_Base.h"

AHAIController_Base::AHAIController_Base()
{
	HBlackBoard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("黑板"));
}

void AHAIController_Base::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("RuningController"));
	/*运行行为树*/
	AHCharacter_Base* PawnTemp = Cast<AHCharacter_Base>(GetPawn());
	if (PawnTemp && PawnTemp->HBehaviorTree)
	{
		RunBehaviorTree(PawnTemp->HBehaviorTree);
	}
}


