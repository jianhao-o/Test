#include "Damage/HDamage_Base.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AHDamage_Base::AHDamage_Base()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("HSphereComponent"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetSphereRadius(50.0f);
	RootComponent = SphereComp;
	EmitterComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HParticleComponent"));
	EmitterComp->SetupAttachment(RootComponent);
	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileComp->InitialSpeed = 3000.0f;
}

void AHDamage_Base::BeginPlay()
{
	Super::BeginPlay();
	/*球形碰撞体重叠事件绑定*/
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AHDamage_Base::HandleOverlap);
	/*子弹十秒销毁*/
	HDelayDestroy(10.0f);
}

/*事件开始重叠*/
void AHDamage_Base::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){}

/*延迟调用自毁*/
void AHDamage_Base::HDelayDestroy(float Delay)
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AHDamage_Base::HDestroy,
		Delay, false);
}

/*自毁 , 清空定时器*/
void AHDamage_Base::HDestroy()
{
	GetWorldTimerManager().ClearTimer(TimerHandle);
	UE_LOG(LogTemp, Warning, TEXT("destroy!!"));
	this->Destroy();
}


