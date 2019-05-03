// Fill out your copyright notice in the Description page of Project Settings.

#include "BP_Master_Building.h"
#include "ConstructorHelpers.h"
#include "Resource_Metal.h"
#include "Resource_Wood.h"
#include "Resource_Stone.h"

// Sets default values
ABP_Master_Building::ABP_Master_Building()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MI(TEXT("/Game/BuildingSystem/Materials/MI_GhostBuilding"));
	if (MI.Succeeded())
	{
		BuildingMaterial = MI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CHMesh(TEXT("/Game/BuildingSystem/Meshes/Floor"));
	if (CHMesh.Succeeded())
	{
		UStaticMesh* actualMesh = CHMesh.Object;
		BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BuildingMesh"));
		BuildingMesh->SetStaticMesh(actualMesh);
		BuildingMesh->SetMaterial(0, BuildingMaterial);
		BuildingMesh->SetCollisionProfileName(FName(TEXT("OverlapAllDynamic")));
	}
	FCpp_BuildingResourceVersion BRV;
	ResourceVersions.Add(AResource_Wood::StaticClass(), BRV);
	ResourceVersions.Add(AResource_Stone::StaticClass(), BRV);
	ResourceVersions.Add(AResource_Metal::StaticClass(), BRV);
}

// Called when the game starts or when spawned
void ABP_Master_Building::BeginPlay()
{
	Super::BeginPlay();

	if (BuildingMesh)
	{
		DynamicBuildingMaterial = BuildingMesh->CreateDynamicMaterialInstance(0, BuildingMaterial);
	}
}

// Called every frame
void ABP_Master_Building::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

