// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BPC_BuildingManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPBUILDINGSYSTEM_API UBPC_BuildingManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBPC_BuildingManager();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn="true"))
	TArray<TSubclassOf<class ABP_Master_Building>> Buildings;//list of buildings player can build

	UFUNCTION(BlueprintCallable)
	void Initialize(AShinbiBase* player);

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
