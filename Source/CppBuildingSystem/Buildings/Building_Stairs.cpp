// Fill out your copyright notice in the Description page of Project Settings.

#include "Building_Stairs.h"

#include "ConstructorHelpers.h"

ABuilding_Stairs::ABuilding_Stairs()
{
	BuildingData.Name = FText::FromString(TEXT("Stairs"));
	BuildingData.HotKey = FKey("F8");
	static ConstructorHelpers::FObjectFinder<UTexture2D>CHIcon(TEXT("/Game/BuildingSystem/Textures/Buildings/Icon_Stairs"));
	if (CHIcon.Succeeded())
	{
		BuildingData.Icon = CHIcon.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CHMesh(TEXT("/Game/BuildingSystem/Meshes/Stairs_Metal"));
	if (CHMesh.Succeeded())
	{
		UStaticMesh* actualMesh = CHMesh.Object;
		BuildingMesh->SetStaticMesh(actualMesh);
	}
}