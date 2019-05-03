// Fill out your copyright notice in the Description page of Project Settings.

#include "WBP_BuildingCpp.h"
#include "BP_Master_Building.h"

void UWBP_BuildingCpp::SelectBuilding(bool Select)
{
	if (Select != Selected)
	{
		Selected = Select;
		if (Selected)
		{
			Outline->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			IconSpacer->SetSize(FVector2D(1.f, 5.f));
		}
		else
		{
			Outline->SetVisibility(ESlateVisibility::Hidden);
			IconSpacer->SetSize(FVector2D(1.f, 10.f));
		}
	}
}

void UWBP_BuildingCpp::CustomInitialize(TSubclassOf<ABP_Master_Building> resourceSupllied)
{
	HotkeyText->SetText(resourceSupllied.GetDefaultObject()->BuildingData.HotKey.GetDisplayName());
	Icon->SetBrushFromTexture(resourceSupllied.GetDefaultObject()->BuildingData.Icon);
	Building = resourceSupllied;
	SelectBuilding(false);
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}
