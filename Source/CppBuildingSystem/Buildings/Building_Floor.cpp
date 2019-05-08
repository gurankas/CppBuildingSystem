// Fill out your copyright notice in the Description page of Project Settings.

#include "Building_Floor.h"

#include "ConstructorHelpers.h"
#include "Resource_Metal.h"
#include "Resource_Wood.h"
#include "Resource_Stone.h"

ABuilding_Floor::ABuilding_Floor()
{
	BuildingData.Name = FText::FromString(TEXT("Floor"));
	BuildingData.HotKey = FKey("Six");
	static ConstructorHelpers::FObjectFinder<UTexture2D>CHIcon(TEXT("/Game/BuildingSystem/Textures/Buildings/Icon_Floor"));
	if (CHIcon.Succeeded())
	{
		BuildingData.Icon = CHIcon.Object;
	}
	BuildingWidget->SetRelativeLocation(FVector(200, 200,0));
	WBPHealthBar->SetRelativeLocation(FVector(200, 200, 0));
	FCpp_BuildingResourceVersion* metal = ResourceVersions.Find(AResource_Metal::StaticClass());
	FCpp_BuildingResourceVersion* wood = ResourceVersions.Find(AResource_Wood::StaticClass());
	FCpp_BuildingResourceVersion* stone = ResourceVersions.Find(AResource_Stone::StaticClass());
	wood->AmountRequired = 5;
	wood->BuildingTime = 1.f;
	wood->MaximumHealth = 100;

	stone->AmountRequired = 8;
	stone->BuildingTime = 1.5f;
	stone->MaximumHealth = 150;

	metal->AmountRequired = 10;
	metal->BuildingTime = 2.5f;
	metal->MaximumHealth = 250;
}