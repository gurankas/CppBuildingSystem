// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BP_Master_Resource.h"
#include "Image.h"
#include "TextBlock.h"
#include "Border.h"
#include "WBP_Resource.generated.h"

/**
 * 
 */
UCLASS()
class CPPBUILDINGSYSTEM_API UWBP_Resource : public UUserWidget
{
	GENERATED_BODY()

public:
	void Constructor(TSubclassOf<ABP_Master_Resource> resource);

	UPROPERTY()
	bool Selected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	TSubclassOf<ABP_Master_Resource> Resource;
	
	void Construct();

	UFUNCTION(BlueprintCallable)
	void SelectResource(bool select, bool ignoreCheck);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* Icon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* ResourceBorder;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Amount;
};
