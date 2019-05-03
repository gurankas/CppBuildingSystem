// Fill out your copyright notice in the Description page of Project Settings.

#include "Building_Wall.h"

ABuilding_Wall::ABuilding_Wall()
{
	BuildingData.Name = FText::FromString(TEXT("Wall"));
	BuildingData.HotKey = FKey("Seven");
	static ConstructorHelpers::FObjectFinder<UTexture2D>CHIcon(TEXT("/Game/BuildingSystem/Textures/Buildings/Icon_Wall"));
	if (CHIcon.Succeeded())
	{
		BuildingData.Icon = CHIcon.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CHMesh(TEXT("/Game/BuildingSystem/Meshes/Wall"));
	if (CHMesh.Succeeded())
	{
		UStaticMesh* actualMesh = CHMesh.Object;
		BuildingMesh->SetStaticMesh(actualMesh);
	}
}