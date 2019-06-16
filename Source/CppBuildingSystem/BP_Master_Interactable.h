// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BP_Master_Building.h"
#include "BP_Master_Interactable.generated.h"

/**
 * 
 */
UCLASS()
class CPPBUILDINGSYSTEM_API ABP_Master_Interactable : public ABP_Master_Building
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

public:
	ABP_Master_Interactable();

	TSubclassOf<UWBP_BuildingHealthBarCpp> HealthWidgetRef;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBPC_Master_ResourceManager* ResourcesComponent;

	UPROPERTY(Editanywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	int32 MaxHealth = 250;

	UPROPERTY(Editanywhere, BlueprintReadWrite)
	TMap<TSubclassOf<class ABP_Master_Resource>,int32> OriginalResources;

	UPROPERTY(Editanywhere, BlueprintReadOnly)
	int32 HealthBefore;

	UPROPERTY(Editanywhere, BlueprintReadOnly)
	int32 HealthAfter;

	UPROPERTY(Editanywhere, BlueprintReadOnly)
		UUserWidget* BP_HealthBar;

	UFUNCTION(BlueprintCallable)
	void SetUpOriginalResources();

	UFUNCTION(BlueprintCallable)
	void GiveResourcesToPlayer(class AShinbiBase* Player, int32 DealthDamage);

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
