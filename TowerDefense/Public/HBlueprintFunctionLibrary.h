// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UHBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// 测试函数，主要用来测试
	UFUNCTION(BlueprintCallable, Category = "Hao|Tool")
	static void GetCurrentActorInfo(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Hao|Tool")
	static void HGetCharacterValue(const UAnimInstance* Target, bool& IsDie, float& SpeedScale);

	/*球体寻敌*/
	UFUNCTION(BlueprintCallable, DisplayName = "球体寻敌", Category = "Hao|Tool")
	static void HGetEnemiesInRange(AActor* Taget, const int Team, const bool Nearest, const float Radius,
		const TArray<TEnumAsByte<EObjectTypeQuery> >& ObjectTypes, TArray<AActor*>& ActorsToIgnore, AActor*& Enemies);
	

};
