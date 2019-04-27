// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BPC_Master_StatManager.h"
#include "ShinbiBase.h"
#include "UI/WBP_StatBar.h"
#include "BPC_PlayerStatManager.generated.h"

/**
 * 
 */
UCLASS()
class CPPBUILDINGSYSTEM_API UBPC_PlayerStatManager : public UBPC_Master_StatManager
{
	GENERATED_BODY()
public:
	UBPC_PlayerStatManager();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		AShinbiBase* PlayerRef;

	UFUNCTION(BlueprintPure)
		UWBP_StatBar* GetBarForStat(ECpp_Stats Stat);

	UFUNCTION(BlueprintCallable)
		void InitializeManager(AShinbiBase* PlayerReference);

	UFUNCTION(BlueprintCallable)
		void OnStatsSetUp() override;

	UFUNCTION(BlueprintCallable)
		void UpdateStat(ECpp_Stats stat) override;
};
