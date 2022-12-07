﻿/*这个类是一个伤害基类, 不具备实现*/
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HDamage_Base.generated.h"

class USphereComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;

UCLASS()
class TOWERDEFENSE_API AHDamage_Base : public AActor
{
	GENERATED_BODY()
public:	
	AHDamage_Base();
protected:
	virtual void BeginPlay() override;
/*以上原始内容*/


//组件区*************************************************************************
public:
	/*碰撞体*/
	UPROPERTY(VisibleAnywhere, Category = "Component")
		USphereComponent* SphereComp;
	/*粒子*/
	UPROPERTY(VisibleAnywhere, Category = "Component")
		UParticleSystemComponent* EmitterComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UProjectileMovementComponent* ProjectileComp;


//变量区*************************************************************************
public:
	/*伤害量*/
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (ExposeOnSpawn = true))
	float HDamage = 0.0f;
	/*队伍 , 实例化对象时传入*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = true))
	int Team_Actor = 0;
	/*控制器 , 实例化对象时传入*/
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn = true))
	AController* OwnerController = nullptr; 
	/*忽略对象(组)*/
	TArray<AActor*> HIgnore;
	/*造成伤害时忽略对象(组)*/
	TArray<AActor*> HIgnoreDamage;
	/*敌人引用,主要是在函数调用时作为返回参数
	除此外 , 我们还能为他设置初始值 , 以指定首个敌人*/
	UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn = true))
	AActor* Enemies;
	/*用于延迟自毁的时间句柄*/
	FTimerHandle TimerHandle;



//函数区*************************************************************************
public:
	/*重叠事件*/
	UFUNCTION()
	virtual void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/*延迟和自毁*/
	UFUNCTION(BlueprintCallable, DisplayName = "延迟销毁", Category = "Hao|Tool")
	void HDelayDestroy(const float Delay);
	/*和上面的函数连用的 , 自毁*/
	void HDestroy();

};
