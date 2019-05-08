// Fill out your copyright notice in the Description page of Project Settings.

#include "BPC_BuildingManager.h"
#include "Buildings/Building_Floor.h"
#include "Buildings/Building_Wall.h"
#include "Buildings/Building_Stairs.h"
#include "Buildings/Building_Roof.h"
#include "UI/WBP_BuildingCpp.h"
#include "Kismet/KismetMathLibrary.h"
#include "ShinbiBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UBPC_BuildingManager::UBPC_BuildingManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	Buildings.Add(ABuilding_Floor::StaticClass());
	Buildings.Add(ABuilding_Wall::StaticClass());
	Buildings.Add(ABuilding_Stairs::StaticClass());
	Buildings.Add(ABuilding_Roof::StaticClass());
}


void UBPC_BuildingManager::Initialize(AShinbiBase * player)
{
	if (player)
	{
		PlayerReference = player;
		IsInitializedOrNot = true;
		BuildingWidgets = PlayerReference->MainUIReference->GenerateBuildingWidgets(this);
		switch (PlayerReference->State)
		{
		case ECpp_PlayerStates::Combat:
			break;
		case ECpp_PlayerStates::Construction:
			SelectCurrentBuilding(true);
			break;
		default:
			break;
		}
		component = PlayerReference->GetComponentByClass(UCameraComponent::StaticClass());
		castedCam = Cast<UCameraComponent>(component);
	}
}

UWBP_BuildingCpp * UBPC_BuildingManager::WidgetForBuilding(TSubclassOf<ABP_Master_Building> Building, bool & success)
{
	int32 length = BuildingWidgets.Num();
	for (int32 i = 0; i < length; i++)
	{
		if (BuildingWidgets[i]->Building == Building)
		{
			success = true;
			return BuildingWidgets[i];
		}
	}
	success = false;
	return nullptr;
}

void UBPC_BuildingManager::OnStartBuilding()
{
	if (CurrentlyBuilding)
	{
		ChangeCurrentBuilding();
	}
	else
	{
		StartBuilding();
	}
	CurrentlyBuilding = true;
}

void UBPC_BuildingManager::StartBuilding()
{
	FVector loc;
	FRotator rot;
	GetBuildingPosAndRot(loc, rot);
	UWorld* world = GetWorld();
	if (Buildings[SelectedBuildingIndex] == ABuilding_Floor::StaticClass())
	{
		CurrentBuilding = world->SpawnActorDeferred<ABuilding_Floor>(Buildings[SelectedBuildingIndex], FTransform(rot, loc, FVector(1, 1, 1)));
	}
	if (Buildings[SelectedBuildingIndex] == ABuilding_Roof::StaticClass())
	{
		CurrentBuilding = world->SpawnActorDeferred<ABuilding_Roof>(Buildings[SelectedBuildingIndex], FTransform(rot, loc, FVector(1, 1, 1)));
	}
	if (Buildings[SelectedBuildingIndex] == ABuilding_Stairs::StaticClass())
	{
		CurrentBuilding = world->SpawnActorDeferred<ABuilding_Stairs>(Buildings[SelectedBuildingIndex], FTransform(rot, loc, FVector(1, 1, 1)));
	}
	if (Buildings[SelectedBuildingIndex] == ABuilding_Wall::StaticClass())
	{
		CurrentBuilding = world->SpawnActorDeferred<ABuilding_Wall>(Buildings[SelectedBuildingIndex], FTransform(rot, loc, FVector(1, 1, 1)));
	}
	//GetWorld()->SpawnActorDeferred(Buildings[SelectedBuildingIndex], FTransform(rot,loc,FVector(1,1,1)));
	CurrentBuilding->Resource = PlayerReference->PlayerResourcesComponent->GetSelectedResource();
	UGameplayStatics::FinishSpawningActor(CurrentBuilding, FTransform(rot, loc, FVector(1, 1, 1)));

	//initialize CanBuildBuilding constructor vars
	bool result;
	TSubclassOf<ABP_Master_Resource> ClassVar;
	int32 value;
	CanBuildBuilding(result, ClassVar, value);
	CurrentBuilding->SetCanBeBuilt(result);

	world->GetTimerManager().SetTimer(BuildingTimerHandle, this, &UBPC_BuildingManager::BuildingTick, .03f, true);
}

void UBPC_BuildingManager::ChangeCurrentBuilding()
{
	GetWorld()->GetTimerManager().ClearTimer(BuildingTimerHandle);
	//BuildingTimerHandle.Invalidate();
	CurrentBuilding->Destroy();
	CurrentBuilding = nullptr;
	StartBuilding();
}

void UBPC_BuildingManager::OnStopBuilding()
{
	if (CurrentlyBuilding)
	{
		CurrentlyBuilding = false; 
		SelectCurrentBuilding(false);
		if (CurrentBuilding)
		{
			GetWorld()->GetTimerManager().ClearTimer(BuildingTimerHandle);
			//BuildingTimerHandle.Invalidate();
			CurrentBuilding->Destroy();
			CurrentBuilding = nullptr;
		}
	}
}

FCpp_BuildingData UBPC_BuildingManager::GetCurrentBuildingInfo()
{
	return Buildings[SelectedBuildingIndex].GetDefaultObject()->BuildingData;
}

void UBPC_BuildingManager::SelectCurrentBuilding(bool selected)
{
	bool wasSuccessfulOrNot;
	WidgetForBuilding(Buildings[SelectedBuildingIndex], wasSuccessfulOrNot);
	if (wasSuccessfulOrNot)
	{
		UWBP_BuildingCpp* buildingWidget = WidgetForBuilding(Buildings[SelectedBuildingIndex], wasSuccessfulOrNot);
		buildingWidget->SelectBuilding(selected);
		if (selected)
		{
			OnStartBuilding();
		}
	}
}

void UBPC_BuildingManager::SelectBuildingByIndex(int32 index)
{
	if (UKismetMathLibrary::InRange_IntInt(index, 0, Buildings.Num(), true, true))
	{
		switch (PlayerReference->State)
		{
		case ECpp_PlayerStates::Combat:
			SelectedBuildingIndex = index;
			PlayerReference->ChangeState(ECpp_PlayerStates::Construction);
			break;
		case ECpp_PlayerStates::Construction:
			if (index != SelectedBuildingIndex)
			{
				SelectCurrentBuilding(false);
				SelectedBuildingIndex = index;
				SelectCurrentBuilding(true);
			}
			break;
		default:
			break;
		}
	}
}

FVector UBPC_BuildingManager::ToGridLocation(FVector in)
{
	float X = (float)(UKismetMathLibrary::Round(in.X / (float)XGridSize)*XGridSize);
	float Y = (float)(UKismetMathLibrary::Round(in.Y / (float)YGridSize)*YGridSize);
	float Z = (float)(UKismetMathLibrary::Round(in.Z / (float)ZGridSize)*ZGridSize);
	return FVector(X,Y,Z);
}

int32 UBPC_BuildingManager::ToSnapRotation(float in)
{
	return (UKismetMathLibrary::Round(in / (float)RotationSnap) * RotationSnap);
}

FVector UBPC_BuildingManager::GetPlayerLookAtRotation(int32 ForwardOffset)
{
	return ((castedCam->GetForwardVector()*ForwardOffset) + PlayerReference->GetActorLocation());
}

void UBPC_BuildingManager::GetBuildingPosAndRot(FVector & loc, FRotator & rot)
{
	loc = ToGridLocation(GetPlayerLookAtRotation(ForwardBuildingOffset))+LocationOffset;
	rot = FRotator(0, ToSnapRotation( castedCam->GetComponentRotation().Yaw)+RotationOffset,0);
}

void UBPC_BuildingManager::BuildingTick()
{
	FVector loc;
	FRotator rot;
	GetBuildingPosAndRot(loc, rot);
	CurrentBuilding->SetActorLocationAndRotation(loc, rot);
	//UE_LOG(LogTemp, Warning, TEXT("Bhukh lag rahi hai"));
}

void UBPC_BuildingManager::CanBuildBuilding(bool & out, TSubclassOf<ABP_Master_Resource>& InResource, int32 & Integer)
{
	if (CurrentBuilding)
	{
		 int32 PlayerResource = PlayerReference->PlayerResourcesComponent->GetResource(PlayerReference->PlayerResourcesComponent->GetSelectedResource());
		 int32 ResourcesNeeded = CurrentBuilding->ResourceVersions.Find(PlayerReference->PlayerResourcesComponent->GetSelectedResource())->AmountRequired;
		 out = PlayerResource > ResourcesNeeded;
		 InResource = PlayerReference->PlayerResourcesComponent->GetSelectedResource();
		 Integer = CurrentBuilding->ResourceVersions.Find(PlayerReference->PlayerResourcesComponent->GetSelectedResource())->AmountRequired;
	}
	else
	{
		out = false;
		InResource = nullptr;
		Integer = 0;
	}
}

void UBPC_BuildingManager::OnResourceChanged()
{
	if (CurrentlyBuilding && IsInitializedOrNot)
	{
		if (CurrentBuilding)
		{
			CurrentBuilding->ChangeResource(PlayerReference->PlayerResourcesComponent->GetSelectedResource());

			//initialize CanBuildBuilding constructor vars
			bool result;
			TSubclassOf<ABP_Master_Resource> ClassVar;
			int32 value;
			CanBuildBuilding(result, ClassVar, value);
			CurrentBuilding->SetCanBeBuilt(result);
		}
	}
}

void UBPC_BuildingManager::OnResourceValueModified(TSubclassOf<ABP_Master_Resource> InResource)
{
	if (PlayerReference->PlayerResourcesComponent->GetSelectedResource() == InResource &&
		CurrentlyBuilding && IsInitializedOrNot && InResource)
	{
		if (CurrentBuilding)
		{
			//initialize CanBuildBuilding constructor vars
			bool result;
			TSubclassOf<ABP_Master_Resource> ClassVar;
			int32 value;
			CanBuildBuilding(result, ClassVar, value);
			CurrentBuilding->SetCanBeBuilt(result);
		}
	}
}

// Called when the game starts
void UBPC_BuildingManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBPC_BuildingManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

