// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StructsAndEnums.h"
#include "BPC_Master_StatManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPBUILDINGSYSTEM_API UBPC_Master_StatManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBPC_Master_StatManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn = "true"))
		TMap<ECpp_Stats, FCpp_StatValue> Stats;

	UFUNCTION(BlueprintCallable)
	void GetStat(ECpp_Stats Stat, int32& CurrentValue, FCpp_StatValue& StatValue) const;

	virtual void UpdateStat(ECpp_Stats stat);

	void SetStat(ECpp_Stats stat, int32 NewValue, bool Update_DefaultValueIsTrue = true);

	static int32 clampInt(const int32 minValue, const int32 maxValue, const int32 valueToClamp);

	UFUNCTION(BlueprintCallable)
	void ModifyStat(ECpp_Stats stat, int32 ModifyBy);

	void SetUpStats();

	virtual void OnStatsSetUp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
