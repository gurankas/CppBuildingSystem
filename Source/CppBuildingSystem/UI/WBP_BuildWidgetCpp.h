// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TextBlock.h"
#include "StructsAndEnums.h"
#include "BP_Master_Resource.h"
#include "WBP_BuildWidgetCpp.generated.h"

/**
 * 
 */
UCLASS()
class CPPBUILDINGSYSTEM_API UWBP_BuildWidgetCpp : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HealthText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ResourceAmountText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* ResourceIcon;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool CanBeBuilt = true;


	UFUNCTION(BlueprintCallable)
	void Update(FCpp_BuildingResourceVersion VersionInfo, TSubclassOf<ABP_Master_Resource> Resource);

	UFUNCTION(BlueprintCallable)
	void SetCanBeBuilt(bool newValue);

};
