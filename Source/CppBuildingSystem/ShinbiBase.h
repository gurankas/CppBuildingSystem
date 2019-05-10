// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UI/WBP_Main.h"
#include "StructsAndEnums.h"
#include "ShinbiBase.generated.h"

UCLASS()
class CPPBUILDINGSYSTEM_API AShinbiBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShinbiBase();

	//key binding functions
	void AddShield();
	void DeductShield();
	void AddHealth();
	void DeductHealth();
	void ChangeToWood();
	void ChangeToStone();
	void ChangeToMetal();
	void SelectNextResource();
	void ChangeStateBinding();
	void OnStartBuildingKeyPressed(FKey key);
	void OnPlaceBuilding();

	//Images in project
	UTexture2D* CrossHairCombat;
	UTexture2D* CrossHairConstruction;
	UTexture2D* Icon_Combat;
	UTexture2D* Icon_Construction;

	TSubclassOf<class UUserWidget> mainClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UWBP_Main* MainUIReference;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBPC_PlayerStatManager* PlayerStatsComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBPC_PlayerResources* PlayerResourcesComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBPC_BuildingManager* BuildingManagerComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECpp_PlayerStates State;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		ABP_Master_Building* CurrentlySeenBuilding;

	UFUNCTION(BlueprintCallable)
	void UpdateStateDisplay();

	UFUNCTION(BlueprintCallable)
	void ChangeState(ECpp_PlayerStates suppliedState);

	UFUNCTION(BlueprintCallable)
	void SightTrace();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
