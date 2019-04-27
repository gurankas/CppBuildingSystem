// Fill out your copyright notice in the Description page of Project Settings.

#include "BPC_PlayerStatManager.h"


UBPC_PlayerStatManager::UBPC_PlayerStatManager()
{
	//Super();
	FCpp_StatValue shield;
	shield.CurrentValue = 0;
	shield.MinValue = 0;
	shield.MaxValue = 100;
	Stats.Add(ECpp_Stats::Shield, shield);

	FCpp_StatValue health;
	health.CurrentValue = 100;
	health.MinValue = 0;
	health.MaxValue = 100;
	Stats.Add(ECpp_Stats::Health, health);
}

UWBP_StatBar * UBPC_PlayerStatManager::GetBarForStat(ECpp_Stats Stat)
{
	if (PlayerRef != nullptr)
	{
		if (Stat == ECpp_Stats::BackSlash)
		{
			return nullptr;
		}
		else if (Stat == ECpp_Stats::Health)
		{
			return PlayerRef->MainUIReference->HealthBar;
		}
		else
		{
			return PlayerRef->MainUIReference->ShieldBar;
		}
	}
	return nullptr;
}

void UBPC_PlayerStatManager::InitializeManager(AShinbiBase * PlayerReference)
{
	PlayerRef = PlayerReference;
	SetUpStats();
}

void UBPC_PlayerStatManager::OnStatsSetUp()
{
	TArray<ECpp_Stats> keys;
	Stats.GetKeys(keys);
	int i = 0;
	while (i < keys.Num())
	{
		int32 Cw;
		FCpp_StatValue statValue;
		GetStat(keys[i], Cw, statValue);
		GetBarForStat(keys[i])->InitializeBar(statValue);
		++i;
	}
}

void UBPC_PlayerStatManager::UpdateStat(ECpp_Stats stat)
{
	int32 Cw;
	FCpp_StatValue statValue;
	GetStat(stat, Cw, statValue);
	GetBarForStat(stat)->UpdateStat(Cw);
}
