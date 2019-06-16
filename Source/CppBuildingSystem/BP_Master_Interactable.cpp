// Fill out your copyright notice in the Description page of Project Settings.

#include "BP_Master_Interactable.h"
#include "BPC_Master_ResourceManager.h"
#include "Resource_Stone.h"
#include "BPC_Master_StatManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "ShinbiBase.h"

ABP_Master_Interactable::ABP_Master_Interactable()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MI(TEXT("/Game/StarterContent/Props/Materials/M_Rock"));
	if (MI.Succeeded())
	{
		BuildingMaterial = MI.Object;
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CHMesh(TEXT("/Game/StarterContent/Props/SM_Rock"));
	if (CHMesh.Succeeded())
	{
		actualMesh = CHMesh.Object;
		BuildingMesh->SetStaticMesh(actualMesh);
		BuildingMesh->SetMaterial(0, BuildingMaterial);
		BuildingMesh->SetCollisionProfileName(FName(TEXT("BlockAll")));
	}

	//static ConstructorHelpers::FClassFinder<UUserWidget> healthbp(TEXT("/Game/BuildingSystem/UI/WBP_BuildingHealthBar"));
	//HealthWidgetRef = healthbp.Class;
	//Cast<HealthWidgetRef>(HealthBarWidget->GetUserWidgetObject());

	Box->SetRelativeLocation(FVector(0, 0, 110));

	ResourcesComponent = CreateDefaultSubobject<UBPC_Master_ResourceManager>(TEXT("ResourcesComponent"));

	ResourcesComponent->Resources.Add(AResource_Stone::StaticClass(), 90);

	ResourceVersions.Empty();
	bBuilt = true;
	bInPlayerSight = false;
}

void ABP_Master_Interactable::BeginPlay()
{
	Super::Super::BeginPlay();
	SetUpOriginalResources();
	BuildingStatsComponent->SetMaxStatValue(ECpp_Stats::Health, MaxHealth, false);
	BuildingStatsComponent->SetStat(ECpp_Stats::Health, MaxHealth, false);
	WBPHealthWidget = Cast<UWBP_BuildingHealthBarCpp>(HealthBarWidget->GetUserWidgetObject());
	if (WBPHealthWidget)
	{
		WBPHealthWidget->InitializeBar(MaxHealth);
		BuildingStatsComponent->InitializeManager(this);
		WBPHealthWidget->SetState(ECpp_BuildingData::Built);
	}
}

void ABP_Master_Interactable::SetUpOriginalResources()
{
	TArray<TSubclassOf<ABP_Master_Resource>> ResourceKeys;
	int32 length = ResourcesComponent->Resources.GetKeys(ResourceKeys);
	for (int32 i = 0; i < length; i++)
	{
		int32 amount = ResourcesComponent->GetResource(ResourceKeys[i]);
		OriginalResources.Add(ResourceKeys[i], amount);
	}
}

void ABP_Master_Interactable::GiveResourcesToPlayer(AShinbiBase * Player, int32 DealthDamage)
{
	if (DealthDamage > 0)
	{
		float localPercentage = (float)DealthDamage / (float)BuildingStatsComponent->GetMaxHealth();
		TArray<TSubclassOf<ABP_Master_Resource>> ResourceKeys;
		int32 length = ResourcesComponent->Resources.GetKeys(ResourceKeys);
		for (int32 i = 0; i < length; i++)
		{
			if (ResourcesComponent->GetResource(ResourceKeys[i]) > 0)
			{
				int32 LocalAmountToAdd = UBPC_Master_StatManager::clampInt(1, ResourcesComponent->GetResource(ResourceKeys[i]), UKismetMathLibrary::FCeil(*OriginalResources.Find(ResourceKeys[i])*localPercentage));
				ResourcesComponent->RemoveResource(ResourceKeys[i], LocalAmountToAdd);
				Player->PlayerResourcesComponent->AddResource(ResourceKeys[i], LocalAmountToAdd);
			}
		}
	}
}
float ABP_Master_Interactable::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 CurrentValue;
	FCpp_StatValue healthStats;
	BuildingStatsComponent->GetStat(ECpp_Stats::Health, CurrentValue, healthStats);
	HealthBefore = CurrentValue;
	BuildingStatsComponent->ModifyStat(ECpp_Stats::Health, UKismetMathLibrary::Round(DamageAmount*-1));
	BuildingStatsComponent->GetStat(ECpp_Stats::Health, CurrentValue, healthStats);
	HealthAfter = CurrentValue;

	AShinbiBase* playerRef = Cast<AShinbiBase>(DamageCauser);
	if (playerRef)
	{
		GiveResourcesToPlayer(playerRef, (HealthBefore - HealthAfter));
	}
	BuildingStatsComponent->GetStat(ECpp_Stats::Health, CurrentValue, healthStats);
	if (CurrentValue <= 0)
	{
		DestroyBuilding();
	}

	return CurrentValue - DamageAmount;
}