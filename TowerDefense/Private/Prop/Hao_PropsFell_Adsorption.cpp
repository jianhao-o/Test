// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/Hao_PropsFell_Adsorption.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"

AHao_PropsFell_Adsorption::AHao_PropsFell_Adsorption()
{	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called every frame
void AHao_PropsFell_Adsorption::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CanMove && HOwner)
	{
		this->SetActorLocation(FMath::VInterpTo(GetActorLocation(), HOwner->GetActorLocation(), DeltaTime, MoveSpeed));
	}
}

void AHao_PropsFell_Adsorption::HTimer()
{	
	Super::HTimer();
	BoxComp->SetSimulatePhysics(false);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	this->DisableComponentsSimulatePhysics();
	/*启用位移*/
	CanMove = true;
}
