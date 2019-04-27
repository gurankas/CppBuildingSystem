// Fill out your copyright notice in the Description page of Project Settings.

#include "Building_Floor.h"

#include "ConstructorHelpers.h"

ABuilding_Floor::ABuilding_Floor()
{
	BuildingData.Name = FText::FromString(TEXT("Floor"));
	BuildingData.HotKey = FKey("F6");
	static ConstructorHelpers::FObjectFinder<UTexture2D>CHIcon(TEXT("/Game/BuildingSystem/Textures/Buildings/Icon_Floor"));
	if (CHIcon.Succeeded())
	{
		BuildingData.Icon = CHIcon.Object;
	}
}