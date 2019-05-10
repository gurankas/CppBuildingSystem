// Fill out your copyright notice in the Description page of Project Settings.

#include "ShinbiBase.h"
#include "ConstructorHelpers.h"
#include "BPC_PlayerStatManager.h"
#include "Resource_Metal.h"
#include "Resource_Stone.h"
#include "Resource_Wood.h"
#include "BPC_BuildingManager.h"
#include "BP_Master_Building.h"

// Sets default values
AShinbiBase::AShinbiBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UTexture2D> CHCombat(TEXT("/Game/BuildingSystem/Textures/Crosshairs/Crosshair_Combat"));
	if (CHCombat.Succeeded())
	{
		CrossHairCombat = CHCombat.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> CHConstruction(TEXT("/Game/BuildingSystem/Textures/Crosshairs/Crosshair_Construction"));
	if (CHConstruction.Succeeded())
	{
		CrossHairConstruction = CHConstruction.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> ICombat(TEXT("/Game/BuildingSystem/Textures/States/Icon_Combat"));
	if (ICombat.Succeeded())
	{
		Icon_Combat = ICombat.Object;
	}
	static ConstructorHelpers::FObjectFinder<UTexture2D> IConstruction(TEXT("/Game/BuildingSystem/Textures/States/Icon_Construction"));
	if (IConstruction.Succeeded())
	{
		Icon_Construction = IConstruction.Object;
	}

	PlayerStatsComponent = CreateDefaultSubobject<UBPC_PlayerStatManager>(TEXT("PlayerStatsComponent"));
	PlayerResourcesComponent = CreateDefaultSubobject<UBPC_PlayerResources>(TEXT("PlayerResourcesComponent"));
	BuildingManagerComponent = CreateDefaultSubobject<UBPC_BuildingManager>(TEXT("BuildingManagerComponent"));
	
	static ConstructorHelpers::FClassFinder<UWBP_Main> WidgetClassAsset(TEXT("/Game/BuildingSystem/UI/WBP_Main"));
	if (WidgetClassAsset.Succeeded())
	{
		MainUIReference = Cast<UWBP_Main>(CreateWidget(GetWorld(), WidgetClassAsset.Class, "HUD"));
	}
}


void AShinbiBase::UpdateStateDisplay()
{
	switch (State)
	{
	case ECpp_PlayerStates::Construction:
		MainUIReference->CrossHair->SetBrushFromTexture(CrossHairConstruction,true);
		MainUIReference->StateIcon->SetBrushFromTexture(Icon_Construction,true);
		MainUIReference->BuildingBox->SetRenderOpacity(1.f);
		MainUIReference->BuildingBox->SetRenderScale(FVector2D(1.f, 1.f));
		BuildingManagerComponent->SelectCurrentBuilding(true);
		MainUIReference->UpdateCurrentResource(PlayerResourcesComponent);
		MainUIReference->ShowCurrentResource(true);
		break;
	case ECpp_PlayerStates::Combat:
		MainUIReference->CrossHair->SetBrushFromTexture(CrossHairCombat,true);
		MainUIReference->StateIcon->SetBrushFromTexture(Icon_Combat,true);
		MainUIReference->BuildingBox->SetRenderOpacity(0.8f);
		MainUIReference->BuildingBox->SetRenderScale(FVector2D(0.8f, 0.8f));
		BuildingManagerComponent->OnStopBuilding();
		MainUIReference->ShowCurrentResource(false);
		break;
	default:
		break;
	}
}

void AShinbiBase::ChangeState(ECpp_PlayerStates suppliedState)
{
	if (State != suppliedState)
	{
		State = suppliedState;
		UpdateStateDisplay();
	}
}

void AShinbiBase::SightTrace()
{
	FHitResult Hit;
	FVector Start = GetActorLocation() + BuildingManagerComponent->LocationOffset;
	FVector End = BuildingManagerComponent->LocationOffset + BuildingManagerComponent->ToGridLocation(BuildingManagerComponent->GetPlayerLookAtRotation(BuildingManagerComponent->ForwardBuildingOffset * 3));
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility);
	ABP_Master_Building* building = Cast<ABP_Master_Building>(Hit.Actor);
	if (building)
	{
		if (CurrentlySeenBuilding)
		{
			if (CurrentlySeenBuilding != Hit.Actor)
			{
				CurrentlySeenBuilding->OnLeavePlayerSight();
				CurrentlySeenBuilding = building;
				CurrentlySeenBuilding->OnEnterPlayerSight();
			}
		}
		else
		{
			CurrentlySeenBuilding = building;
			CurrentlySeenBuilding->OnEnterPlayerSight();
		}
	}
	else
	{
		if (CurrentlySeenBuilding)
		{
			CurrentlySeenBuilding->OnLeavePlayerSight();
			CurrentlySeenBuilding = nullptr;
		}
	}
}

// Called when the game starts or when spawned
void AShinbiBase::BeginPlay()
{
	Super::BeginPlay();

	if (MainUIReference)
	{
		State = ECpp_PlayerStates::Combat;
		UpdateStateDisplay();
		PlayerStatsComponent->InitializeManager(this);
		PlayerResourcesComponent->InitializeManager(this);
		BuildingManagerComponent->Initialize(this);
		MainUIReference->AddToViewport();
	}
}

// Called every frame
void AShinbiBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShinbiBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("AddShield", IE_Pressed, this, &AShinbiBase::AddShield);
	PlayerInputComponent->BindAction("DeductShield", IE_Pressed, this, &AShinbiBase::DeductShield);
	PlayerInputComponent->BindAction("AddHealth", IE_Pressed, this, &AShinbiBase::AddHealth);
	PlayerInputComponent->BindAction("DeductHealth", IE_Pressed, this, &AShinbiBase::DeductHealth);
	PlayerInputComponent->BindAction("AddWood", IE_Pressed, this, &AShinbiBase::ChangeToWood);
	PlayerInputComponent->BindAction("AddStone", IE_Pressed, this, &AShinbiBase::ChangeToStone);
	PlayerInputComponent->BindAction("AddMetal", IE_Pressed, this, &AShinbiBase::ChangeToMetal);
	PlayerInputComponent->BindAction("SelectNextResource", IE_Pressed, this, &AShinbiBase::SelectNextResource);
	PlayerInputComponent->BindAction("ChangeState", IE_Pressed, this, &AShinbiBase::ChangeStateBinding);
	PlayerInputComponent->BindAction("StartBuilding", IE_Pressed, this, &AShinbiBase::OnStartBuildingKeyPressed);
	PlayerInputComponent->BindAction("PlaceBuilding", IE_Pressed, this, &AShinbiBase::OnPlaceBuilding);
}

void AShinbiBase::AddShield()
{
	UE_LOG(LogTemp, Warning, TEXT("AddShieldCalled"));
	PlayerStatsComponent->ModifyStat(ECpp_Stats::Shield, 30);
}

void AShinbiBase::DeductShield()
{
	PlayerStatsComponent->ModifyStat(ECpp_Stats::Shield, -30);
}

void AShinbiBase::AddHealth()
{
	PlayerStatsComponent->ModifyStat(ECpp_Stats::Health, 30);
}

void AShinbiBase::DeductHealth()
{
	PlayerStatsComponent->ModifyStat(ECpp_Stats::Health, -30);
}

void AShinbiBase::ChangeToWood()
{
	PlayerResourcesComponent->AddResource(AResource_Wood::StaticClass(), 150);
}

void AShinbiBase::ChangeToStone()
{
	PlayerResourcesComponent->AddResource(AResource_Stone::StaticClass(), 150);
}

void AShinbiBase::ChangeToMetal()
{
	PlayerResourcesComponent->AddResource(AResource_Metal::StaticClass(), 150);
}

void AShinbiBase::SelectNextResource()
{
	switch (State)
	{
	case ECpp_PlayerStates::Construction:
		PlayerResourcesComponent->SelectNextResource();
		break;
	case ECpp_PlayerStates::Combat:
		break;
	default:
		break;
	}
}
//executed when Q is pressed
void AShinbiBase::ChangeStateBinding()
{
	switch (State)
	{
	case ECpp_PlayerStates::Construction:
		ChangeState(ECpp_PlayerStates::Combat);
		break;
	case ECpp_PlayerStates::Combat:
		ChangeState(ECpp_PlayerStates::Construction);
		break;
	default:
		break;
	}
}

void AShinbiBase::OnStartBuildingKeyPressed(FKey key)
{
	int32 length = BuildingManagerComponent->Buildings.Num();
	for (int32 i = 0; i < length; i++)
	{
		if (BuildingManagerComponent->Buildings[i].GetDefaultObject()->BuildingData.HotKey == key)
		{
			BuildingManagerComponent->SelectBuildingByIndex(i);
			break;
		}
		
	}
	
}

void AShinbiBase::OnPlaceBuilding()
{
	switch (State)
	{
	case ECpp_PlayerStates::Construction:
		BuildingManagerComponent->PlaceCurrentBuilding();
		break;
	case ECpp_PlayerStates::Combat:
		break;
	default:
		break;
	}
}
