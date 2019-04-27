// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "InputCoreTypes.h"
#include "StructsAndEnums.generated.h"

UENUM(BlueprintType)
enum class ECpp_Stats : uint8
{
	BackSlash UMETA(DisplayName = "/"),
	Shield UMETA(DisplayName = "Shield"),
	Health UMETA(DisplayName = "Health")
};

UENUM(BlueprintType)
enum class ECpp_PlayerStates : uint8
{
	Construction UMETA(DisplayName = "Construction"),
	Combat UMETA(DisplayName = "Combat")
};

UENUM(BlueprintType)
enum class ECpp_BuildingData : uint8
{
	Building UMETA(DisplayName = "Building"),
	Built UMETA(DisplayName = "Built")
};

USTRUCT(BlueprintType)
struct FCpp_StatValue
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
		int32 MinValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
		int32 CurrentValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
		int32 MaxValue;
};

USTRUCT(BlueprintType)
struct FCpp_ResourceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	UTexture2D* Icon;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	//FLinearColor GhostBuildingColour;
};

USTRUCT(BlueprintType)
struct FCpp_BuildingData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	FKey HotKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Struct")
	UTexture2D* Icon;
};

/**
 * 
 */
class CPPBUILDINGSYSTEM_API StructsAndEnums
{
public:
	StructsAndEnums();
	~StructsAndEnums();
};
