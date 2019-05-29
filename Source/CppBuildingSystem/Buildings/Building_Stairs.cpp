// Fill out your copyright notice in the Description page of Project Settings.

#include "Building_Stairs.h"

#include "ConstructorHelpers.h"
#include "Resource_Metal.h"
#include "Resource_Wood.h"
#include "Resource_Stone.h"

ABuilding_Stairs::ABuilding_Stairs()
{
	BuildingData.Name = FText::FromString(TEXT("Stairs"));
	BuildingData.HotKey = FKey("Eight");
	static ConstructorHelpers::FObjectFinder<UTexture2D>CHIcon(TEXT("/Game/BuildingSystem/Textures/Buildings/Icon_Stairs"));
	if (CHIcon.Succeeded())
	{
		BuildingData.Icon = CHIcon.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CHMesh(TEXT("/Game/BuildingSystem/Meshes/Stairs_Concrete_v9"));
	if (CHMesh.Succeeded())
	{
		UStaticMesh* actualMesh = CHMesh.Object;
		BuildingMesh->SetStaticMesh(actualMesh);
	}
	BuildingMesh->SetRelativeRotation(FRotator(0, 0, 0));
	BuildingWidget->SetRelativeLocation(FVector(0, 200, 200));
	HealthBarWidget->SetRelativeLocation(FVector(0, 200, 200));
	FCpp_BuildingResourceVersion* metal = ResourceVersions.Find(AResource_Metal::StaticClass());
	FCpp_BuildingResourceVersion* wood = ResourceVersions.Find(AResource_Wood::StaticClass());
	FCpp_BuildingResourceVersion* stone = ResourceVersions.Find(AResource_Stone::StaticClass());
	wood->AmountRequired = 8;
	wood->BuildingTime = .8f;
	wood->MaximumHealth = 130;

	stone->AmountRequired = 12;
	stone->BuildingTime = 1.2f;
	stone->MaximumHealth = 180;

	metal->AmountRequired = 15;
	metal->BuildingTime = 1.5f;
	metal->MaximumHealth = 250;

	Box->SetRelativeLocation(FVector(200, 200, 120));
	Box->SetBoxExtent(FVector(90, 90, 120));
}