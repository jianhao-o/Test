// Fill out your copyright notice in the Description page of Project Settings.


#include "HBlueprintFunctionLibrary.h"
#include "HCharacter_Base.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


/*测试两种打印方式*/
void UHBlueprintFunctionLibrary::GetCurrentActorInfo(AActor* Actor)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor(0, 255, 255), TEXT("Function Called"));
	}

	UE_LOG(LogTemp, Warning, TEXT("Called Function"));
}

/*用于动画蓝图获取变量*/
void UHBlueprintFunctionLibrary::HGetCharacterValue(const UAnimInstance* Target, bool& IsDie, float& SpeedScale)
{	//获得动画的持有者 , 一般是character类
	AHCharacter_Base* HCharacter = Cast<AHCharacter_Base>(Target->TryGetPawnOwner());
	if (HCharacter)
	{	//判断死活
		IsDie = HCharacter->HP_Current > 0.0f ? false : true;
		/*获得当前速度 : HCharacter->GetVelocity().Size();
		*获得最大速度 : HCharacter->GetCharacterMovement()->MaxWalkSpeed;
		*	首先需要获得 MovementComponent, 有两种函数:
		*	GetMovementComponent() return:UPawnMovementComponent
		*	GetCharacterMovement() return:UCharacterMovementComponent
		*	获得的PawnMovementComponent可以类转后再获得最大行走速度;因为这个变量来自Character,如下
		*	UCharacterMovementComponent* Movement = Cast<UCharacterMovementComponent>(HCharacter->GetMovementComponent());
		*获得速度比例 : CurrentWalkSpeed/HMaxWolkSpeed*100;*/
		SpeedScale = HCharacter->GetVelocity().Size()
			/ HCharacter->GetCharacterMovement()->MaxWalkSpeed
			* 100;
	}
}

/*获取范围内的敌人
*Taget 搜索中心
*Nearest true:选择最近的 ; false:随机
*Radius 搜索半径 cm
*Object Types 被搜索的对象类型
*Actor Class Filter 被搜索的类 , 建议留空 , 如果使用自定义的类则不区分团队
*Ignore 忽略的对象 , 默认忽略自身
*/
void UHBlueprintFunctionLibrary::HGetEnemiesInRange(AActor* Taget, const int Team, const bool Nearest, 
	const float Radius,const TArray<TEnumAsByte<EObjectTypeQuery> >& ObjectTypes, TArray<AActor*> &ActorsToIgnore,AActor* & Enemies)
{	/*检查输入*/
	if (Taget == nullptr) { return; }

	/*临时接收的数组,临时的敌队阵容
	*因为需要暂存这些敌队对象 , 使用遍历不建议随意操作数组数据*/
	TArray<AActor*> OutActors, TempActor;

	/*忽略自身*/
	ActorsToIgnore.Emplace(Taget);

	/*球体重叠Actor
	*执行后得到OutActors*/
	UKismetSystemLibrary::SphereOverlapActors(Taget->GetWorld(), Taget->GetActorLocation(), Radius, ObjectTypes,
		AHCharacter_Base::StaticClass(), ActorsToIgnore, OutActors);

	/*暂存OutActors中的敌队对象*/
	for (int32 Index = 0; Index < OutActors.Num(); ++Index)
	{
		/*检查是否同队*/
		if (Team != Cast<AHCharacter_Base>(OutActors[Index])->HTeam)
		{
			TempActor.Emplace(OutActors[Index]);
		}
	}

	/*找到的敌人数量*/
	int objnum = TempActor.Num();
	/*为0时退出*/
	if (objnum <= 0){return;}
	if (Nearest)
	{
		float distance;//只存不用
		Enemies = UGameplayStatics::FindNearestActor(Taget->GetActorLocation(), TempActor, distance);
	}
	else
	{
		Enemies = TempActor[UKismetMathLibrary::RandomIntegerInRange(0, objnum-1)];
	}
}

