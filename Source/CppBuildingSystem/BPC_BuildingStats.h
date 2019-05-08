// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BPC_Master_StatManager.h"
#include "StructsAndEnums.h"
#include "BPC_BuildingStats.generated.h"

/**
 * 
 */
UCLASS()
class CPPBUILDINGSYSTEM_API UBPC_BuildingStats : public UBPC_Master_StatManager
{
	GENERATED_BODY()
public:
	UBPC_BuildingStats();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class ABP_Master_Building* Building;

	UFUNCTION(BlueprintPure)
	int32 GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	void SetMaxStatValue(ECpp_Stats stat, int32 newValue, bool update);

	UFUNCTION(BlueprintCallable)
	void InitializeManager(class ABP_Master_Building* BuildingSupplied);
};
