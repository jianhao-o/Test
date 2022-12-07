// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStruct.generated.h"

USTRUCT()
//添加BlueprintType才能在蓝图中创建变量
struct FMYStruct                    //必须是F开头
{
	GENERATED_USTRUCT_BODY()
public:
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mantra")
	float Height = 0;
};