// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Hao_PropsFell.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"



// Sets default values
AHao_PropsFell::AHao_PropsFell()
{


	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;
	/*碰撞: 阻挡动态/静态场景, 重叠pawn , 忽略其他 */
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	BoxComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	BoxComp->SetSimulatePhysics(true);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	ParticleSystemCompo = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleCompo"));
	ParticleSystemCompo->SetupAttachment(RootComponent);
	ProjectileMovementCompo = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementCompo"));
	ProjectileMovementCompo->InitialSpeed = 500.0f;
	ProjectileMovementCompo->Velocity = FVector(1.0f, 0.0f, 1.0f);

}

// Called when the game starts or when spawned
void AHao_PropsFell::BeginPlay()
{
	Super::BeginPlay();
	/*开始游戏两秒后去绑定重叠事件*/
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, 
		&AHao_PropsFell::HTimer , 1.0f , false);
	/*超时销毁*/
	if (DestroyTime > 0.0f)
	{
		GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, 
			&AHao_PropsFell::DestroySelf,DestroyTime, false);
	}
	
}

void AHao_PropsFell::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}



/*重叠事件*/
void AHao_PropsFell::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AHao_PropsFell::HTimer()
{
	/*清除定时器*/
	GetWorldTimerManager().ClearTimer(CountdownTimerHandle);

	

	/*绑定重叠事件*/
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AHao_PropsFell::HandleOverlap);
	
	
	

}

void AHao_PropsFell::DestroySelf()
{	
	/*清空死亡倒计时句柄*/
	GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
	/*销毁自身*/
	this->Destroy(true);

}

