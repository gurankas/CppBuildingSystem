// Fill out your copyright notice in the Description page of Project Settings.

#include "WBP_BuildWidgetCpp.h"
#define LOCTEXT_NAMESPACE "UWBP_BuildWidgetCpp"
void UWBP_BuildWidgetCpp::Update(FCpp_BuildingResourceVersion VersionInfo, TSubclassOf<ABP_Master_Resource> Resource)
{
	HealthText->SetText(FText::FormatNamed(LOCTEXT("HealthText", "{hp} HP"), TEXT("hp"), FText::AsNumber(VersionInfo.AmountRequired)));
	ResourceAmountText->SetText(FText::AsNumber(VersionInfo.AmountRequired));
	ResourceIcon->SetBrushFromTexture(Resource.GetDefaultObject()->ResourceData.Icon, true);
}

void UWBP_BuildWidgetCpp:: SetCanBeBuilt(bool newValue)
{
	if (newValue != CanBeBuilt)
	{
		CanBeBuilt = newValue;
		if (CanBeBuilt)
		{
			ResourceIcon->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
			ResourceAmountText->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f)));
		}
		else
		{
			ResourceIcon->SetColorAndOpacity(FLinearColor(1.f, .2235f, .247f, 1.f));
			ResourceAmountText->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, .2235f, .247f, .9f)));
		}
	}
}
#undef LOCTEXT_NAMESPACE