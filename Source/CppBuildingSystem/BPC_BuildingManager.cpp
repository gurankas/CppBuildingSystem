// Fill out your copyright notice in the Description page of Project Settings.

#include "BPC_BuildingManager.h"
#include "Buildings/Building_Floor.h"
#include "Buildings/Building_Wall.h"
#include "Buildings/Building_Stairs.h"
#include "Buildings/Building_Roof.h"
#include "ShinbiBase.h"

// Sets default values for this component's properties
UBPC_BuildingManager::UBPC_BuildingManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	Buildings.Add(ABuilding_Floor::StaticClass());
	Buildings.Add(ABuilding_Wall::StaticClass());
	Buildings.Add(ABuilding_Stairs::StaticClass());
	Buildings.Add(ABuilding_Roof::StaticClass());
}


void UBPC_BuildingManager::Initialize(AShinbiBase * player)
{
	if (player)
	{
		PlayerReference = player;
		IsInitializedOrNot = true;
		BuildingWidgets = PlayerReference->MainUIReference->GenerateBuildingWidgets(this);
	}
}

// Called when the game starts
void UBPC_BuildingManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBPC_BuildingManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

