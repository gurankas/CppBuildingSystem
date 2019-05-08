// Fill out your copyright notice in the Description page of Project Settings.

#include "BPC_BuildingStats.h"
#include "BP_Master_Building.h"

UBPC_BuildingStats::UBPC_BuildingStats()
{
	FCpp_StatValue StructStats;
	StructStats.CurrentValue = 0;
	Stats.Add(ECpp_Stats::Health, StructStats);	
}

int32 UBPC_BuildingStats::GetMaxHealth()
{
	FCpp_StatValue StructStats;
	int32 currentValue = 0;
	GetStat(ECpp_Stats::Health, currentValue, StructStats);
	return StructStats.MaxValue;
}

void UBPC_BuildingStats::SetMaxStatValue(ECpp_Stats stat, int32 newValue, bool update)
{
	if (Stats.Contains(stat) && stat != ECpp_Stats::BackSlash)
	{
		FCpp_StatValue StructStats;
		int32 currentValue = 0;
		GetStat(ECpp_Stats::Health, currentValue, StructStats);
		
		//making new struct
		FCpp_StatValue newStat;
		newStat.MinValue = StructStats.MinValue;
		newStat.CurrentValue = clampInt(StructStats.MinValue, newValue, currentValue);
		newStat.MaxValue = newValue;
		Stats.Add(stat, newStat);
		if (update)
		{
			UpdateStat(stat);
		}
	}
}

void UBPC_BuildingStats::InitializeManager(ABP_Master_Building* BuildingSupplied)
{
	if (BuildingSupplied)
	{
		Building = BuildingSupplied;
		SetUpStats();
	}
}
