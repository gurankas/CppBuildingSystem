// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BPC_Master_ResourceManager.h"
#include "UI/WBP_Resource.h"
#include "BPC_PlayerResources.generated.h"

/**
 * 
 */
UCLASS()
class CPPBUILDINGSYSTEM_API UBPC_PlayerResources : public UBPC_Master_ResourceManager
{
	GENERATED_BODY()

public:
	UBPC_PlayerResources();

	UPROPERTY( BlueprintReadWrite, EditAnywhere)
	class AShinbiBase* PlayerReference;

	UFUNCTION(BlueprintPure)
	int32 GetSelectedIndex();

	UFUNCTION(BlueprintPure)
	TSubclassOf<ABP_Master_Resource> GetSelectedResource();

	UFUNCTION(BlueprintCallable)
	UWBP_Resource* GetWidgetForResource(TSubclassOf< ABP_Master_Resource> Resource, bool & success);

	UFUNCTION(BlueprintPure)
	UWBP_Resource* CurrentlySelectedWidget();

	UFUNCTION(BlueprintCallable)
	void SelectCurrentResource();

	UFUNCTION(BlueprintCallable)
	void OnResourceSwitched();

	UFUNCTION(BlueprintCallable)
	void SelectNextResource();

	UFUNCTION(BlueprintCallable)
	void InitializeManager(AShinbiBase* PlayerRef);

	void UpdateResourceDisplay(TSubclassOf<ABP_Master_Resource> Resource) override;

private:
	UPROPERTY(Editanywhere)
	bool Initialized;

	UPROPERTY(Editanywhere)
	TArray<UWBP_Resource*> ResourceWidgets;

	UPROPERTY(Editanywhere)
	int32 SelectedResourceIndex;
};
