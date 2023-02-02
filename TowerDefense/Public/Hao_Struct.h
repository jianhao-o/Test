#pragma once

#include "CoreMinimal.h"
#include "Hao_Struct.generated.h"

// class UAnimMontage;
// class UBehaviorTree;


USTRUCT(Blueprintable)
struct FCharacterDetail
{
	GENERATED_USTRUCT_BODY()

		/*血量上限*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "最大血量", NoResetToDefault))
		float HP_Max = 100.0f;

	/*区分团队 , 防止友伤*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "团队", NoResetToDefault))
		int HTeam = 0;

// 	/*自定义行为树*/
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "行为树", NoResetToDefault))
// 		UBehaviorTree* HBehaviorTree;
// 
// 	/*攻击蒙太奇*/
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "攻击蒙太奇", NoResetToDefault))
// 		UAnimMontage* AttackMontage;
// 
// 	/*受击蒙太奇*/
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "受击蒙太奇", NoResetToDefault))
// 		UAnimMontage* HitMontage;
	//     FCharacterDetail() 
	//     {
	//         HP_Max = 100.0f;
	//         HTeam = 0;
	//     }
};
