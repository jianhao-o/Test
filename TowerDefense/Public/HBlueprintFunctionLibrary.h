// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/WidgetComponent.h"
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
	
	/*生成伤害数字*/
	UFUNCTION(BlueprintCallable, DisplayName = "生成伤害数字", Category = "Hao|Tool")
	static void SpawnDamageText(const AActor* Taget, const TSubclassOf<UUserWidget> HWidgetClass , const EWidgetSpace Space , const FVector Location,const FVector2D Size, const FVector2D Pivot);

	/*修改widgetComponent的类 , 在运行时*/
	UFUNCTION(BlueprintCallable, DisplayName = "设置控件组件类", Category = "Hao|Tool")
	static void HSetWidgetClass(UWidgetComponent* Taget,const TSubclassOf<UUserWidget> HClass);
	
	/*范围内随机向量*/
	UFUNCTION(BlueprintCallable,DisplayName = "范围内随机向量", Category = "Hao|Tool", BlueprintPure)
	static void RandomVectorInRange(const FVector Min, const FVector Max, FVector &RetuenValue );

	/*设置容差获得上限和下限
	*±容差*/
	UFUNCTION(BlueprintCallable, DisplayName = "容差", Category = "Hao|Tool", BlueprintPure)
	static void GetTolerance(const float In, const float Tolerance, float& Min , float& Max);

	/*容差内随机浮点
	*±容差*/
	UFUNCTION(BlueprintCallable, DisplayName = "容差内随机浮点", Category = "Hao|Tool", BlueprintPure)
	static void RandomFloatInTolerance(const float In, const float Tolerance, float& ReturnValue);

	/*容差内随机向量
	*±容差*/
	UFUNCTION(BlueprintCallable, DisplayName = "容差内随机向量", Category = "Hao|Tool", BlueprintPure)
		static void RandomVectorInTolerance(const FVector In, const FVector Tolerance, FVector& RetuenValue);


};
