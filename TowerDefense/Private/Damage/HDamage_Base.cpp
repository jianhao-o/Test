#include "Damage/HDamage_Base.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Pawn.h"

AHDamage_Base::AHDamage_Base()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("HSphereComponent"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetSphereRadius(HRadiu);
	RootComponent = SphereComp;
	EmitterComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HParticleComponent"));
	EmitterComp->SetupAttachment(RootComponent);

}

void AHDamage_Base::BeginPlay()
{
	Super::BeginPlay();
	/*球形碰撞体重叠事件绑定*/
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AHDamage_Base::HandleOverlap);
	/*子弹十秒销毁*/
	HDelayDestroy(10.0f);
}

void AHDamage_Base::OnConstruction(const FTransform& Transform)
{
	SphereComp->SetSphereRadius(HRadiu);
}

/*事件开始重叠 */
void AHDamage_Base::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*如果用户填入了Owner_Pawn , 使用它的控制器*/
	if (Owner_Pawn){OwnerController = Owner_Pawn->GetController();}
}

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


