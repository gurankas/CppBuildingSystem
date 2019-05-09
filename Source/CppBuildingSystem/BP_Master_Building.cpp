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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CHMesh(TEXT("/Game/BuildingSystem/Meshes/Floor_v2"));
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

	static ConstructorHelpers::FClassFinder<UUserWidget> bp(TEXT("/Game/BuildingSystem/UI/WBP_BuildWidget"));

	//adding a widget component
	BuildingWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BuildWidget"));
	BuildingWidget->SetWidgetSpace(EWidgetSpace::Screen);
	BuildingWidget->SetWidgetClass(bp.Class);
	BuildingWidget->SetDrawSize(FVector2D(380, 140));
	BuildingWidget->SetVisibility(false);

	static ConstructorHelpers::FClassFinder<UUserWidget> healthbp(TEXT("/Game/BuildingSystem/UI/WBP_Bu"));
	
	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidget->SetWidgetClass(healthbp.Class);
	HealthBarWidget->SetDrawSize(FVector2D(360, 32));
	HealthBarWidget->SetVisibility(false);

	//set up hierarchy
	SetRootComponent(BuildingMesh);
	BuildingWidget->SetupAttachment(GetRootComponent());
	BuildingWidget->SetRelativeLocation(FVector(0,0,0));

	HealthBarWidget->SetupAttachment(GetRootComponent());
	HealthBarWidget->SetRelativeLocation(FVector(0, 0, 0));


	BuildingStatsComponent = CreateDefaultSubobject<UBPC_BuildingStats>(TEXT("BuildingStatsComponent"));


}

void ABP_Master_Building::UpdateGhostMaterial()
{
	DynamicBuildingMaterial->SetVectorParameterValue("Colour", Resource.GetDefaultObject()->ResourceData.GhostBuildingColour);
}

void ABP_Master_Building::OnBuild(TSubclassOf<ABP_Master_Resource> ResourceSupplied)
{
	if (ResourceSupplied)
	{
		bBuilt = true;
		BuildingMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		BuildingMesh->SetMaterial(0, Resource.GetDefaultObject()->ResourceData.BuildingMaterial);
		BuildingWidget->DestroyComponent();
		BuildingStatsComponent->SetMaxStatValue(ECpp_Stats::Health, ResourceVersions.Find(Resource)->MaximumHealth, false);
		BuildingStatsComponent->SetStat(ECpp_Stats::Health, 0, false);
		BuildingTime = ResourceVersions.Find(Resource)->BuildingTime;
		WBPHealthWidget->InitializeBar(BuildingStatsComponent->GetMaxHealth());
		HealthBarWidget->SetVisibility(true);
	}
}
void ABP_Master_Building::ChangeResource(TSubclassOf<ABP_Master_Resource> NewResource)
{
	if (NewResource && Resource!= NewResource)
	{
		Resource = NewResource;
		UpdateGhostMaterial();
		WBPBuildWidget->Update(*ResourceVersions.Find(Resource),Resource);
	}
}

void ABP_Master_Building::SetCanBeBuilt(bool newValue)
{
	CanBeBuilt = newValue;
	WBPBuildWidget->SetCanBeBuilt(CanBeBuilt);
}

// Called when the game starts or when spawned
void ABP_Master_Building::BeginPlay()
{
	Super::BeginPlay();

	if (BuildingMesh)
	{
		DynamicBuildingMaterial = BuildingMesh->CreateDynamicMaterialInstance(0, BuildingMaterial);
		UpdateGhostMaterial();
		WBPBuildWidget = Cast<UWBP_BuildWidgetCpp>(BuildingWidget->GetUserWidgetObject());
		WBPHealthWidget = Cast<UWBP_BuildingHealthBarCpp>(HealthBarWidget->GetUserWidgetObject());
		WBPBuildWidget->Update(*ResourceVersions.Find(Resource), Resource);
		BuildingStatsComponent->InitializeManager(this);
		BuildingWidget->SetVisibility(true);
	}
}

// Called every frame
void ABP_Master_Building::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

