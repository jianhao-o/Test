// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HWeapon_Base.generated.h"

UCLASS()
class TOWERDEFENSE_API AHWeapon_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHWeapon_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Component")
	USkeletalMesh* WeaponSkeletalMesh;
	UPROPERTY(EditAnywhere, Category = "Component")
	UStaticMesh* WeaponStaticMesh;

	virtual void StartFire();
	virtual void EndFire();
};
