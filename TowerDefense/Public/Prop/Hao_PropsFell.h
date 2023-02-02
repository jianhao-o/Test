// Fill out your copyright notice in the Description page of Project Settings.
/*掉落物类*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hao_PropsFell.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponen;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class UBoxComponent;
class USphereComponent;
//class AActor; 

UCLASS()
class TOWERDEFENSE_API AHao_PropsFell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHao_PropsFell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


//***********组件区**********************
public:
	/*掉落物抛射*/
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UProjectileMovementComponent* ProjectileMovementCompo;
	/*粒子*/
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UParticleSystemComponent* ParticleSystemCompo;
	/*box碰撞体 , 用于掉落阻挡*/
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UBoxComponent* BoxComp;
	/*Sphere碰撞体 , 用于事件绑定*/
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent* SphereComp;

//*************变量区*************************
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (ExposeOnSpawn = true))
	float DestroyTime = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = true))
	APawn* HOwner;
	/*时间句柄*/
	FTimerHandle CountdownTimerHandle;
	FTimerHandle DestroyTimerHandle;

	//**********************函数区**************************
public:

	/*构造函数*/
	virtual void OnConstruction(const FTransform& Transform) override;
	/*重叠函数*/
	
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&
		SweepResult);
	/*计时器 , 暂时只负责调用重叠绑定 , 就是说 , 不到时间 , 重叠事件就不会生效*/
	virtual void HTimer();
	/*延迟销毁自身*/
	void DestroySelf();
};
