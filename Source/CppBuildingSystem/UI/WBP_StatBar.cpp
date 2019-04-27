// Fill out your copyright notice in the Description page of Project Settings.

#include "WBP_StatBar.h"


void UWBP_StatBar::NativePreConstruct()
{
	// Do some custom setup

	// Call the Blueprint "Event Construct" node
	Super::NativePreConstruct();
	UE_LOG(LogTemp, Warning, TEXT("NativeConstruct"));
	Icon->SetBrushFromTexture(IconTexture, true);
	ProgressBar->SetFillColorAndOpacity(Colour);
}

void UWBP_StatBar::InitializeBar(FCpp_StatValue StatValue)
{
	CurrentValue = StatValue.CurrentValue;
	MinimumValue = StatValue.MinValue;
	MaximumValue = StatValue.MaxValue;
	Initialised = true;
	MaxHealthText->SetText(FText::AsNumber(MaximumValue));
	UpdateStat(CurrentValue);
}

void UWBP_StatBar::UpdateStat(int32 value)
{
	if (Initialised)
	{
		CurrentHealthText->SetText(FText::AsNumber(value));
		float percent = (float)(value - MinimumValue) / (float)(MaximumValue - MinimumValue);
		UE_LOG(LogTemp, Warning, TEXT("percent value is %d"), percent);
		ProgressBar->SetPercent(percent);
		return;
	}
	else
	{
		return;
	}
}