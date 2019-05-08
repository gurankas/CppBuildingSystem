// Fill out your copyright notice in the Description page of Project Settings.

#include "Building_Wall.h"
#include "Resource_Metal.h"
#include "Resource_Wood.h"
#include "Resource_Stone.h"

ABuilding_Wall::ABuilding_Wall()
{
	BuildingData.Name = FText::FromString(TEXT("Wall"));
	BuildingData.HotKey = FKey("Seven");
	static ConstructorHelpers::FObjectFinder<UTexture2D>CHIcon(TEXT("/Game/BuildingSystem/Textures/Buildings/Icon_Wall"));
	if (CHIcon.Succeeded())
	{
		BuildingData.Icon = CHIcon.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CHMesh(TEXT("/Game/BuildingSystem/Meshes/Wall_v2"));
	if (CHMesh.Succeeded())
	{
		UStaticMesh* actualMesh = CHMesh.Object;
		BuildingMesh->SetStaticMesh(actualMesh);
	}
	BuildingMesh->SetRelativeRotation(FRotator(0, 90, 0));
	BuildingWidget->SetRelativeLocation(FVector(0, 200, 200));
	FCpp_BuildingResourceVersion* metal = ResourceVersions.Find(AResource_Metal::StaticClass());
	FCpp_BuildingResourceVersion* wood = ResourceVersions.Find(AResource_Wood::StaticClass());
	FCpp_BuildingResourceVersion* stone = ResourceVersions.Find(AResource_Stone::StaticClass());
	wood->AmountRequired = 10;
	wood->BuildingTime = 1.4f;
	wood->MaximumHealth = 200;

	stone->AmountRequired = 15;
	stone->BuildingTime = 2.f;
	stone->MaximumHealth = 300;

	metal->AmountRequired = 20;
	metal->BuildingTime = 3.f;
	metal->MaximumHealth = 500;
}