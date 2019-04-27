// Fill out your copyright notice in the Description page of Project Settings.

#include "WBP_Resource.h"
#include "SlateColor.h"
#include "Resource_Metal.h"
#include "Resource_Stone.h"
#include "Resource_Wood.h"

void UWBP_Resource::Constructor(TSubclassOf<ABP_Master_Resource> resource)
{
	Resource = resource;
	Construct();
}

void UWBP_Resource::Construct()
{
	Icon->SetBrushFromTexture(Resource.GetDefaultObject()->ResourceData.Icon, true);
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UWBP_Resource::SelectResource(bool select, bool ignoreCheck)
{
	if ((select != Selected) || ignoreCheck)
	{
		Selected = select;
		if (Selected)
		{
			ResourceBorder->SetBrushColor(FLinearColor(0.023529, 0.043137,0.117647,0.6));
			Amount->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f)));
		}
		else
		{
			ResourceBorder->SetBrushColor(FLinearColor(0.f, 0.f, 0.f, 0.3));
			Amount->SetColorAndOpacity(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.8f)));
		}
	}
}
