// Fill out your copyright notice in the Description page of Project Settings.

#include "Building_Roof.h"
#include "ConstructorHelpers.h"

ABuilding_Roof::ABuilding_Roof()
{
	BuildingData.Name = FText::FromString(TEXT("Roof"));
	BuildingData.HotKey = FKey("Nine");
	static ConstructorHelpers::FObjectFinder<UTexture2D>CHIcon(TEXT("/Game/BuildingSystem/Textures/Buildings/Icon_Floor"));
	if (CHIcon.Succeeded())
	{
		BuildingData.Icon = CHIcon.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CHMesh(TEXT("/Game/BuildingSystem/Meshes/Roof_Full"));
	if (CHMesh.Succeeded())
	{
		UStaticMesh* actualMesh = CHMesh.Object;
		BuildingMesh->SetStaticMesh(actualMesh);
	}
}

