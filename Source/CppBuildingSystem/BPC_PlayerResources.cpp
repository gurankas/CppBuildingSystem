// Fill out your copyright notice in the Description page of Project Settings.

#include "BPC_PlayerResources.h"
#include "ShinbiBase.h"
#include "Resource_Metal.h"
#include "Resource_Stone.h"
#include "Resource_Wood.h"

UBPC_PlayerResources::UBPC_PlayerResources()
{
	Resources.Add(AResource_Metal::StaticClass(),0);
	Resources.Add(AResource_Wood::StaticClass(),0);
	Resources.Add(AResource_Stone::StaticClass(),0);
}

int32 UBPC_PlayerResources::GetSelectedIndex()
{
	return SelectedResourceIndex;
}

TSubclassOf<ABP_Master_Resource> UBPC_PlayerResources::GetSelectedResource()
{
	TArray<TSubclassOf< ABP_Master_Resource>> Keys;
	Resources.GetKeys(Keys);
	return Keys[SelectedResourceIndex];
}

UWBP_Resource* UBPC_PlayerResources::GetWidgetForResource(TSubclassOf< ABP_Master_Resource> Resource, bool & success)
{
	int32 length = ResourceWidgets.Num();
	for (int32 i = 0; i < length; i++)
	{
		if (ResourceWidgets[i]->Resource == Resource)
		{
			success = true;
			return ResourceWidgets[i];
		}
	}
	success = false;
	return nullptr;
}

UWBP_Resource * UBPC_PlayerResources::CurrentlySelectedWidget()
{
	bool success;
	UWBP_Resource* ResourceWidget= GetWidgetForResource(GetSelectedResource(), success);;
	return ResourceWidget;
}

void UBPC_PlayerResources::SelectCurrentResource()
{
	CurrentlySelectedWidget()->SelectResource(true, false);
}

void UBPC_PlayerResources::OnResourceSwitched()
{
}

void UBPC_PlayerResources::SelectNextResource()
{
	CurrentlySelectedWidget()->SelectResource(false, false);
	TArray<TSubclassOf <ABP_Master_Resource>> Keys;
	Resources.GetKeys(Keys);
	if ((SelectedResourceIndex+1) < Keys.Num())
	{
		SelectedResourceIndex += 1;
	} 
	else
	{
		SelectedResourceIndex = 0;
	}
	SelectCurrentResource();
	PlayerReference->MainUIReference->UpdateCurrentResource(this);
	OnResourceSwitched();
}

void UBPC_PlayerResources::InitializeManager(AShinbiBase * PlayerRef)
{
	if (PlayerRef)
	{
		PlayerReference = PlayerRef;
		Initialized = true;
		ResourceWidgets = PlayerReference->MainUIReference->GenerateResourceWidgets(this);

		TArray<TSubclassOf<ABP_Master_Resource>> Keys;
		Resources.GetKeys(Keys);
		int32 length = Keys.Num();
		for (int32 i = 0; i < length; i++)
		{
			UpdateResourceDisplay(Keys[i]);
		}
		SelectCurrentResource();
	}
}

void UBPC_PlayerResources::UpdateResourceDisplay(TSubclassOf<ABP_Master_Resource> Resource)
{
	if (Initialized)
	{
		bool success;
		UWBP_Resource* ResourceWidget = GetWidgetForResource(Resource, success);;
		if (success)
		{
			if (ResourceWidget)
			{
				ResourceWidget->Amount->SetText(FText::AsNumber(GetResource(Resource)));
				if (GetSelectedResource() == Resource && PlayerReference->State == ECpp_PlayerStates::Construction)
				{
					PlayerReference->MainUIReference->UpdateCurrentResource(this);
				}
			}
		}
	}
}
