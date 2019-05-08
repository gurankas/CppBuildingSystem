// Fill out your copyright notice in the Description page of Project Settings.

#include "WBP_BuildingHealthBarCpp.h"
#include "BPC_Master_StatManager.h"

#define LOCTEXT_NAMESPACE "UWBP_BuildingHealthBarCpp"


void UWBP_BuildingHealthBarCpp::UpdateHealth(int32 NewValue)
{
	CurrentHealth = UBPC_Master_StatManager::clampInt(0, MaxHealth, NewValue);
	HealthBar->SetPercent((float)(CurrentHealth / MaxHealth));
	HealthText->SetText(FText::FormatNamed(LOCTEXT("HealthText", "{Current} | {Max}"), TEXT("Current"), FText::AsNumber(CurrentHealth), TEXT("Max"), FText::AsNumber(MaxHealth)));
}

void UWBP_BuildingHealthBarCpp::SetState(ECpp_BuildingData NewValue)
{
	State = NewValue;
	switch (State)
	{
	case ECpp_BuildingData::Building:
		HealthBar->SetFillColorAndOpacity(FLinearColor(.52549,.282353,.011765));
		break;
	case ECpp_BuildingData::Built:
		HealthBar->SetFillColorAndOpacity(FLinearColor(.137255,.643137,.094118));
		break;
	default:
		break;
	}
}

void UWBP_BuildingHealthBarCpp::InitializeBar(int32 NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
	SetState(ECpp_BuildingData::Building);
	UpdateHealth(0);
}


#undef LOCTEXT_NAMESPACE