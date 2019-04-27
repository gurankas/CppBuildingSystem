// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WBP_StatBar.h"
#include "UI/WBP_Resource.h"
#include "HorizontalBox.h"
#include "BPC_Master_ResourceManager.h"
#include "Blueprint/UserWidget.h"
#include "BPC_PlayerResources.h"
#include "TextBlock.h"
#include "SizeBox.h"
#include "UI/WBP_BuildingCpp.h"
#include "WBP_Main.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CPPBUILDINGSYSTEM_API UWBP_Main : public UUserWidget
{
	GENERATED_BODY()
public:

	//Binding of widgets
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWBP_StatBar* HealthBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UWBP_StatBar* ShieldBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* ResourceBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* CurrentResourceIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentResourceAmount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USizeBox* CurrentResourceBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* CrossHair;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* StateIcon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UHorizontalBox* BuildingBox;

	//UProperties
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray <UWBP_Resource*> ResourceWidgets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UWBP_Resource> ResourceBpVersion;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<class UWBP_BuildingCpp*> BuildingWidgets;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UWBP_BuildingCpp> BuildingBpVersion;

	//functions
	UFUNCTION(BlueprintCallable)
	TArray<UWBP_Resource*> GenerateResourceWidgets(UBPC_Master_ResourceManager* Manager);

	UFUNCTION(BlueprintCallable)
	void UpdateCurrentResource(UBPC_PlayerResources* PlayerResources);

	UFUNCTION(BlueprintCallable)
	void ShowCurrentResource(bool shouldShow);

	UFUNCTION(BlueprintCallable)
	TArray<UWBP_BuildingCpp*> GenerateBuildingWidgets(class UBPC_BuildingManager* Manager);

};
