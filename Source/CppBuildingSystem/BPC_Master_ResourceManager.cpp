// Fill out your copyright notice in the Description page of Project Settings.

#include "BPC_Master_ResourceManager.h"
#include "BPC_Master_StatManager.h"

// Sets default values for this component's properties
UBPC_Master_ResourceManager::UBPC_Master_ResourceManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


int32 UBPC_Master_ResourceManager::GetResource(TSubclassOf<ABP_Master_Resource> Resource)
{
	int32* value = Resources.Find(Resource);
	if (value == nullptr)
	{
		return -1;
	}
	return *value;
}

void UBPC_Master_ResourceManager::UpdateResourceDisplay(TSubclassOf<ABP_Master_Resource> Resource)
{
}

void UBPC_Master_ResourceManager::AddResource(TSubclassOf<ABP_Master_Resource> Resource, int32 Amount)
{
	if (Resource.GetDefaultObject() != nullptr && Amount > 0)
	{
		if (Resources.Find(Resource))
		{
			Resources.Add(Resource, UBPC_Master_StatManager::clampInt(0, 999, (*Resources.Find(Resource) + Amount)));
			UpdateResourceDisplay(Resource);
		}
		else
		{
			Resources.Add(Resource, UBPC_Master_StatManager::clampInt(0, 999, Amount));
			UpdateResourceDisplay(Resource);
		}
	}
}

void UBPC_Master_ResourceManager::RemoveResource(TSubclassOf<ABP_Master_Resource> Resource, int32 Amount)
{
	if (Resource.GetDefaultObject() != nullptr && Amount > 0)
	{
		if (Resources.Find(Resource))
		{
			Resources.Add(Resource, UBPC_Master_StatManager::clampInt(0, 999, (*Resources.Find(Resource) - Amount)));
			UpdateResourceDisplay(Resource);
		}
	}
}

// Called when the game starts
void UBPC_Master_ResourceManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBPC_Master_ResourceManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

