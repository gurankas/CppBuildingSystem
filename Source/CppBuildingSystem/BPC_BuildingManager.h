// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StructsAndEnums.h"
#include "Camera/CameraComponent.h"
#include "BPC_BuildingManager.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPBUILDINGSYSTEM_API UBPC_BuildingManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBPC_BuildingManager();

	UPROPERTY()
		UActorComponent* component;
	UPROPERTY()
		UCameraComponent* castedCam;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn="true"))
	TArray<TSubclassOf<class ABP_Master_Building>> Buildings;//list of buildings player can 

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CurrentlyBuilding;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category="Building Grid")
	int32 XGridSize = 400;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Building Grid")
	int32 YGridSize = 400;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Building Grid")
	int32 ZGridSize = 400;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Building Grid")
	int32 RotationSnap = 90;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Building Grid")
		int32 ForwardBuildingOffset = 350;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Building Grid")
		FVector LocationOffset = FVector(0,0,160);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Building Grid")
		int32 RotationOffset = 90;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AShinbiBase> BPShinbiRef;

	UPROPERTY()
		ABP_Master_Building* CurrentBuilding;

	UPROPERTY()
	FTimerHandle BuildingTimerHandle;

	//functions
	UFUNCTION(BlueprintCallable)
	void Initialize(AShinbiBase* player);

	UFUNCTION(BlueprintCallable)
	UWBP_BuildingCpp* WidgetForBuilding(TSubclassOf< ABP_Master_Building> Building, bool & success);

	UFUNCTION(BlueprintCallable)
	void OnStartBuilding();

	UFUNCTION(BlueprintCallable)
	void StartBuilding();

	UFUNCTION(BlueprintCallable)
	void ChangeCurrentBuilding();

	UFUNCTION(BlueprintCallable)
	void OnStopBuilding();

	UFUNCTION(BlueprintPure)
	FCpp_BuildingData GetCurrentBuildingInfo();

	UFUNCTION(BlueprintCallable)
	void SelectCurrentBuilding(bool selected);

	UFUNCTION(BlueprintCallable)
	void SelectBuildingByIndex(int32 index);

	UFUNCTION(BlueprintPure)
	FVector ToGridLocation(FVector in);

	UFUNCTION(BlueprintPure)
	int32 ToSnapRotation(float in);

	UFUNCTION(BlueprintPure)
	FVector GetPlayerLookAtRotation(int32 ForwardOffset);

	UFUNCTION(BlueprintPure)
	void GetBuildingPosAndRot(FVector & loc, FRotator & rot);

	UFUNCTION(BlueprintCallable)
	void BuildingTick();

	UFUNCTION(BlueprintPure)
	void CanBuildBuilding(bool & out, TSubclassOf<ABP_Master_Resource> & InResource, int32 & Integer);

	UFUNCTION(BlueprintCallable)
	void OnResourceChanged();

	UFUNCTION(BlueprintCallable)
	void OnResourceValueModified(TSubclassOf<ABP_Master_Resource> InResource);


private:
	UPROPERTY(EditAnywhere)
	class AShinbiBase* PlayerReference;

	UPROPERTY(EditAnywhere)
	bool IsInitializedOrNot;

	UPROPERTY(EditAnywhere)
	TArray<class UWBP_BuildingCpp*> BuildingWidgets;//list of building widgets

	UPROPERTY(EditAnywhere)
	int32 SelectedBuildingIndex;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
