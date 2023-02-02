// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Animation/AnimMontage.h"
#include "Particles/ParticleSystem.h"
#include "Engine/SkeletalMesh.h"
#include "UObject/Object.h"
#include "Math/Vector.h"
#include "Hao_StructLibrary.generated.h"

USTRUCT(BlueprintType)
struct FHao_StructLibrary
{
	GENERATED_USTRUCT_BODY()
public:
	/*当前等级*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "当前等级"))
	int32 Level_Current = 0;

	/*区分团队 , 防止友伤*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "团队"))
	int HTeam = 0;

	/*经验价值 , 当他死亡时 , 会掉落多少经验*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "经验价值"))
	float ExpValue = 10.0f;

	/*死亡时模拟物理 , 类似其他游戏中的布娃娃系统*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "死亡物理"))
	bool DiePy = false;

	/*自定义行为树*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "行为树"))
	UBehaviorTree* HBehaviorTree;

};

/*控制升级的表现*/
USTRUCT(BlueprintType)
struct FLevelCtrl
{
	GENERATED_USTRUCT_BODY()
public:
	/*血量上限*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "最大血量*"))
		float HP_Max = 100.0f;
	/*升级经验, 升级所需的额外经验*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "升级经验*"))
		float Experience = 100.0f;
	/*新的角色模型*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "模型*"))
		USkeletalMesh* SkeletalMesh;
	/*新的动画蓝图*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "动画蓝图*"))
		TSubclassOf<UAnimInstance> AnimInstance;
	/*升级特效*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "升级特效"))
		UParticleSystem* ParticleSys;
	/*升级蒙太奇, 非必要时可以留空*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "升级蒙太奇"))
		UAnimMontage* LevelUpMontage;


	/*攻击蒙太奇*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "攻击蒙太奇"))
		UAnimMontage* AttackMontage;

	/*受击蒙太奇*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "受击蒙太奇"))
		UAnimMontage* HitMontage;
	/*技能蓝图*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "技能蓝图"))
		float Attackbp;
};

/*控制升级的表现*/
USTRUCT(BlueprintType)
struct FDamageTextSet
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "显示伤害数字"))
	bool ShowDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "随机容差"))
	FVector LocalRandomTolerance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "模板"))
	FVector LocalRandomTemp;


};