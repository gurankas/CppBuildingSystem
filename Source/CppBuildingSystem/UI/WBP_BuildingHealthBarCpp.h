// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProgressBar.h"
#include "TextBlock.h"
#include "StructsAndEnums.h"
#include "WBP_BuildingHealthBarCpp.generated.h"

/**
 * 
 */
UCLASS()
class CPPBUILDINGSYSTEM_API UWBP_BuildingHealthBarCpp : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* HealthText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		ECpp_BuildingData State;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 MaxHealth =1;

	//functions
	UFUNCTION(BlueprintCallable)
	void UpdateHealth(int32 NewValue);

	UFUNCTION(BlueprintCallable)
	void SetState(ECpp_BuildingData NewValue);

	UFUNCTION(BlueprintCallable)
		void InitializeBar(int32 NewMaxHealth);
};
