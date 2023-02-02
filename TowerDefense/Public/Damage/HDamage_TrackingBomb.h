// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damage/HDamage_Base.h"
#include "HDamage_TrackingBomb.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOWERDEFENSE_API AHDamage_TrackingBomb : public AHDamage_Base
{
	GENERATED_BODY()
	
public:
	AHDamage_TrackingBomb();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

//组件区*****************************************************************************
public:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UProjectileMovementComponent* ProjectileComp;


//变量区*****************************************************************************
public:
	/*搜索半径*/
	UPROPERTY(EditAnywhere, meta = (DisplayName = "搜索半径"), Category = "属性设置")
	float SearchRadius = 1000.0f;
	/*弹射次数*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = true, DisplayName = "弹射次数"), Category = "属性设置")
	int32 CatapultNum = 0;
	/*搜索类型 , 比如pawn*/
	UPROPERTY(EditAnywhere, meta = (DisplayName = "搜索类型"), Category = "属性设置")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	/*位移动画帧率
	*位移是逐帧动画的原理 , 每隔一帧位移一次 , 
	*为确保动画流畅 , 请设置大于动画帧率的值 */
	UPROPERTY(EditAnywhere, meta = (DisplayName = "位移动画帧率"), Category = "属性设置")
	float HFrame = 60.0f;
	/*移动速度*/
	UPROPERTY(EditAnywhere,  BlueprintReadOnly, meta = (ExposeOnSpawn = true, DisplayName = "位移速度"), Category = "属性设置")
	float MoveSpeed = 12.0f;
	/*旋转跟随速度方向*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = true, DisplayName = "旋转随速度"), Category = "属性设置")
	bool HRotationFollowsVelocity = true;
	/*锁定到水平面: 有别于禁用重力 , 禁用重力仍然可以向空间弹射
	*这个只在发射时有效 , 弹射不奏效*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = true, DisplayName = "锁定到水平面"), Category = "属性设置")
	bool HConstrainToPlane = false;
	/*自动选择近处的对象 , 关闭时为随机*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = true, DisplayName = "就近"), Category = "属性设置")
	bool HNearest = false;
	/*初始速度
	*开枪时飞行(脱离枪口)的速度
	* 单位: cm/s
	*/
	UPROPERTY(EditAnywhere, meta = (DisplayName = "始速度"), Category = "属性设置")
	float HInitialSpeed = 3000.0f;
	/*时间管理器中的句柄*/
	FTimerHandle CountdownTimerHandle;
	/*典中典 , 自变量i*/
	int i = 0;




//函数区*************************************************************************
	/*构造函数*/
	virtual void OnConstruction(const FTransform& Transform) override;

	/*重叠事件重载*/
	virtual void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& 
		SweepResult) override;

	/*循环调用的函数*/
	void UpdateLocation();
};
