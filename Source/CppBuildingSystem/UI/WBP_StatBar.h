// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "ProgressBar.h"
#include "TextBlock.h"
#include "StructsAndEnums.h"
#include "WBP_StatBar.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CPPBUILDINGSYSTEM_API UWBP_StatBar : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateStat(int32 value);

	void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable)
		void InitializeBar(FCpp_StatValue StatValue);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UImage* Icon;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* ProgressBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* CurrentHealthText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* MaxHealthText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 CurrentValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 MaximumValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 MinimumValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		UTexture2D* IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
		FLinearColor Colour;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool Initialised;

};
