// Fill out your copyright notice in the Description page of Project Settings.

#include "BPC_Master_StatManager.h"

// Sets default values for this component's properties
UBPC_Master_StatManager::UBPC_Master_StatManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UBPC_Master_StatManager::UpdateStat(ECpp_Stats stat)
{
}

void UBPC_Master_StatManager::SetStat(ECpp_Stats stat, int32 NewValue, bool Update_DefaultValueIsTrue)
{
	if (Stats.Contains(stat) && stat != ECpp_Stats::BackSlash)
	{
		//Initializing the variables which get populated via GetStat()
		FCpp_StatValue localStat;
		int32 previousValue;
		GetStat(stat, previousValue, localStat);

		localStat.CurrentValue = clampInt(localStat.MinValue, localStat.MaxValue, NewValue);
		Stats.Add(stat, localStat);
		if (Update_DefaultValueIsTrue)
		{
			UpdateStat(stat);
		}
	}
}

int32 UBPC_Master_StatManager::clampInt(const int32 minValue, const int32 maxValue, const int32 valueToClamp)
{
	if (valueToClamp <= minValue)
	{
		return minValue;
	}
	else if (valueToClamp >= maxValue)
	{
		return maxValue;
	}
	else return valueToClamp;
}

void UBPC_Master_StatManager::ModifyStat(ECpp_Stats stat, int32 ModifyBy)
{
	if (ModifyBy != 0)
	{
		//Initializing the variables which get populated via GetStat()
		FCpp_StatValue localStat;
		int32 previousValue;
		GetStat(stat, previousValue, localStat);

		SetStat(stat, localStat.CurrentValue + ModifyBy, true);
	}
}

void UBPC_Master_StatManager::SetUpStats()
{
	Stats.Remove(ECpp_Stats::BackSlash);
	TArray<ECpp_Stats> keys;
	Stats.GetKeys(keys);
	int i = 0;
	while (i < keys.Num())
	{
		int32 Cw;
		FCpp_StatValue statValue;
		GetStat(keys[i], Cw, statValue);
		SetStat(keys[i], Cw);
		++i;
	}
	/*
	for (auto& iterate : Stats)
	{
		FCpp_StatValue localStat;
		int32 currentValue;
		GetStat(iterate.Key, currentValue, localStat);
		SetStat(iterate.Key, currentValue);
	}*/
	OnStatsSetUp();
}

void UBPC_Master_StatManager::OnStatsSetUp()
{
}

void UBPC_Master_StatManager::GetStat(ECpp_Stats Stat, int32 & CurrentValue, FCpp_StatValue & StatValue) const
{
	CurrentValue = Stats.Find(Stat)->CurrentValue;
	StatValue = *Stats.Find(Stat);
}



// Called when the game starts
void UBPC_Master_StatManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBPC_Master_StatManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

