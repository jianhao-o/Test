// Fill out your copyright notice in the Description page of Project Settings.


#include "HCharacter_Base.h"
#include "HBlueprintFunctionLibrary.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "AIController.h"
#include "HAIController_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Hao_Struct.h"

// Sets default values
AHCharacter_Base::AHCharacter_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*初始化组件*/
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("HPawnSensingComponent"));
	

}
// Called when the game starts or when spawned
void AHCharacter_Base::BeginPlay()
{
	Super::BeginPlay();
	/*动态绑定
	*AddDynamic添加动态函数*/
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AHCharacter_Base::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AHCharacter_Base::OnNoiseHeard);
	OnTakeAnyDamage.AddDynamic(this, &AHCharacter_Base::OnTakeRadialDamage);
	CreateDynamicMaterialInstanceToSkeletal();
	
}
// Called every frame
void AHCharacter_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// Called to bind functionality to input
void AHCharacter_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//构造脚本
void AHCharacter_Base::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	HP_Current = HP_Max;
}



/*创建动态材质实例 , 填入数组*/
void AHCharacter_Base::CreateDynamicMaterialInstanceToSkeletal()
{
	//变量初始化
	HMaterialInstanceDynamic.Empty();
	
	//逻辑实现
	if (GetMesh() && GetMesh()->GetMaterial(0))
	{
		for (int32 Index = 0; Index < GetMesh()->GetNumMaterials(); ++Index)
		{
			//创建并设置动态材质实例
			HMaterialInstanceDynamic.Add(GetMesh()->CreateAndSetMaterialInstanceDynamic(Index));
		}
	}
}

/*用于动态绑定
*实现看见pawn*/
void AHCharacter_Base::OnPawnSeen(APawn* SeePawn)
{
	if (SeePawn == nullptr)
	{
		return;
	}
	AHCharacter_Base * CharacterTemp = Cast<AHCharacter_Base>(SeePawn);
	if (CharacterTemp && HTeam == CharacterTemp->HTeam)
	{
		return;//类相同且阵营相同时退出
	}
	/*传递敌人到黑板*/
	HSetEnemy(SeePawn);
	HTarget = SeePawn;
	//DrawDebugSphere(GetWorld(), SeePawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
}

/*实现听见声音*/
void AHCharacter_Base::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	UE_LOG(LogTemp, Warning, TEXT("heardyou"));
	//DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);
}

/*制造声音*/
void AHCharacter_Base::HMakeNoise(bool EnableMakeNoise)
{
}

/*传递感知到的对象*/
void AHCharacter_Base::HSetEnemy(APawn* HPawn)
{	/*最好做一下有效性判断 , 很难保证攻击对象是不是中途就死了*/
	if (HPawn == nullptr){return;}

	/*判断自身的控制器是否是 自定义的ai控制器 , 如果是 , 获得黑板并传入参数
	*未来有可能要由其他控制器接管这个类*/
	AHAIController_Base* ControllerTemp = Cast<AHAIController_Base>(GetController());
	if (ControllerTemp)
	{
		ControllerTemp->HBlackBoard->SetValueAsObject(FName("AttackTarget"),HPawn);
	}
}

void AHCharacter_Base::HPReduce(float Damage, bool PlayHitColor)
{
	HP_Current -= Damage;
	if (PlayHitColor){PlayHitColorTimeline();}
}

void AHCharacter_Base::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{	
	/*扣血*/
	HP_Current -= Damage;
	/*受击变色*/
	PlayHitColorTimeline();
	if (HP_Current <= 0)
	{	/*进入死亡倒计时*/
		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AHCharacter_Base::DestroySelf, 1.0f, true);
		PlayDieColorTimeline();
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor(0, 255, 255), TEXT("%d"), HP_Current);
}

void AHCharacter_Base::DestroySelf()
{	
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	this->Destroy(true);
}



