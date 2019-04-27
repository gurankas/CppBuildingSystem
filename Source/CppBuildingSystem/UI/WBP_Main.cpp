// Fill out your copyright notice in the Description page of Project Settings.

#include "WBP_Main.h"
#include "HorizontalBoxSlot.h"
#include "BPC_BuildingManager.h"



TArray<UWBP_Resource*> UWBP_Main::GenerateResourceWidgets(UBPC_Master_ResourceManager* Manager)
{
	TArray<TSubclassOf<ABP_Master_Resource>> Keys;
	Manager->Resources.GetKeys(Keys);
	int i = 0;
	while (i < Keys.Num())
	{
		auto SingleResource = CreateWidget<UWBP_Resource>(GetWorld(), ResourceBpVersion);
		SingleResource->Constructor(Keys[i]);
		ResourceWidgets.Add(SingleResource);
		UHorizontalBoxSlot* slot = ResourceBox->AddChildToHorizontalBox(SingleResource);
		if (i > 0)
		{
			slot->SetPadding(FMargin(10.f, 0.f, 0.f, 0.f));
		}
		else
		{
			slot->SetPadding(FMargin(0.f, 0.f, 0.f, 0.f));
		}
		++i;
	}
	return ResourceWidgets;
}

void UWBP_Main::UpdateCurrentResource(UBPC_PlayerResources * PlayerResources)
{
	if (PlayerResources)
	{
		CurrentResourceIcon->SetBrushFromTexture(PlayerResources->GetSelectedResource().GetDefaultObject()->ResourceData.Icon);
		int32 Amount = PlayerResources->GetResource(PlayerResources->GetSelectedResource());
		CurrentResourceAmount->SetText(FText::AsNumber(Amount));
	}
}

void UWBP_Main::ShowCurrentResource(bool shouldShow)
{
	if (shouldShow)
	{
		CurrentResourceBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		CurrentResourceBox->SetVisibility(ESlateVisibility::Hidden);
	}
}

TArray<UWBP_BuildingCpp*> UWBP_Main::GenerateBuildingWidgets(UBPC_BuildingManager * Manager)
{
	int i = 0;
	while (i < Manager->Buildings.Num())
	{
		auto SingleBuilding = CreateWidget<UWBP_BuildingCpp>(GetWorld(), BuildingBpVersion);
		SingleBuilding->CustomInitialize(Manager->Buildings[i]);
		BuildingWidgets.Add(SingleBuilding);
		UHorizontalBoxSlot* slot = BuildingBox->AddChildToHorizontalBox(SingleBuilding);
		if (i > 0)
		{
			slot->SetPadding(FMargin(10.f, 0.f, 0.f, 0.f));
		}
		else
		{
			slot->SetPadding(FMargin(0.f, 0.f, 0.f, 0.f));
		}
		++i;
	}
	return BuildingWidgets;
}
