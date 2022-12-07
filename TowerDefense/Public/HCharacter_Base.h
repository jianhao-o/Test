// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HCharacter_Base.generated.h"



class UPawnSensingComponent;
class UBehaviorTree;
struct FHaoStruct;


UCLASS()
class TOWERDEFENSE_API AHCharacter_Base : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AHCharacter_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
	
	
/*以上原始内容*/
//变量区*************************************************************************
protected:
	/*AI感知组件
	*需要在build文件添加模块: "AIModule"*/
	UPROPERTY(VisibleAnywhere, Category = "运行时")
	UPawnSensingComponent *PawnSensingComp;

	/*用于需要一对一的战斗 , 防止扎堆*/
	bool InBattle = false;

public:
	/*结构体测试*/
	FHaoStruct* aa; 
	/*血量上限*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite, DisplayName = "最大血量",Category = "角色属性")
	float HP_Max = 100.0f;

	/*区分团队 , 防止友伤*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "团队", Category = "角色属性")
	int HTeam = 0;

	/*自定义行为树*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "行为树", Category = "角色属性")
	UBehaviorTree* HBehaviorTree;

	/*当前血量*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "当前血量",Category = "运行时")
	float HP_Current ;

	/*游戏开始时 , 能接收到自动生成的动态材质实例数组*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName = "动态材质实例组",Category = "运行时")
	TArray<UMaterialInstanceDynamic*> HMaterialInstanceDynamic;
	
	/*感兴趣的目标 , 会移动向他*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, DisplayName = "兴趣目标", Category = "运行时")
	AActor* HTarget;
	
	/*定时器句柄*/
	FTimerHandle CountdownTimerHandle;
















//函数区*************************************************************************

	
public:
	/*一个依赖蓝图实现的函数
	*可以调用受伤变色*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Hao")
	void PlayHitColorTimeline(); 

	/*一个依赖蓝图实现的函数
	*可以调用受伤变色*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Hao")
	void PlayDieColorTimeline();

	/*一个依赖蓝图实现的函数
	*可以攻击*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Hao")
	void HAttack();

	/*检测伤害 , 用于近战*/
private:
	//构建脚本
	virtual void OnConstruction(const FTransform& Transform) override;

	/*创建动态材质实例 : 自动创建动态材质实例 , 并将材质赋予继承的骨骼
	*返回一个存储动态材质的数组
	*此函数默认在游戏开始时调用
	*return TArray<UMaterialInstanceDynamic*>*/
	void CreateDynamicMaterialInstanceToSkeletal();

protected:
	/*用于动态绑定
	实现看见pawn*/
	UFUNCTION()
	void OnPawnSeen(APawn *SeePawn);

	/*实现听见声音*/
	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	/*制造声音*/
	void HMakeNoise(bool EnableMakeNoise);

	/*传递感知到的对象*/
	void HSetEnemy(APawn* HPawn);

	/*扣血事件*/
	void HPReduce(float Damage , bool PlayHitColor);

	/*任意伤害事件*/
	UFUNCTION()
	void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	/*定时销毁
	*非做不可 , 因为事件绑定需要*/
	void DestroySelf();
};
