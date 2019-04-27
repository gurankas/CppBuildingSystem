// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "Spacer.h"
#include "TextBlock.h"
#include "WBP_BuildingCpp.generated.h"

/**
 * 
 */
UCLASS()
class CPPBUILDINGSYSTEM_API UWBP_BuildingCpp : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Outline;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USpacer* IconSpacer;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HotkeyText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Icon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Selected = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(ExposeOnSpawn="true"))
	TSubclassOf<class ABP_Master_Building> Building;

	UFUNCTION(BlueprintCallable)
	void SelectBuilding(bool Select);

	//since this BP has a expose on spawn property which is utilized in it's OnConstruct event
	//and we cant supply it at the time of spawn, we make a custom function to accept the 
	//variable's value and initialze it
	UFUNCTION(BlueprintCallable)
	void CustomInitialize(TSubclassOf<ABP_Master_Building> resourceSupllied);
	
};
