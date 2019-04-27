// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BP_Master_Resource.h"
#include "BPC_Master_ResourceManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPBUILDINGSYSTEM_API UBPC_Master_ResourceManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBPC_Master_ResourceManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (ExposeOnSpawn = "true"))
	TMap<TSubclassOf<ABP_Master_Resource>, int32> Resources;

	UFUNCTION(BlueprintPure)
	int32 GetResource(TSubclassOf<ABP_Master_Resource> Resource);

	UFUNCTION(BlueprintCallable)
	virtual void UpdateResourceDisplay(TSubclassOf<ABP_Master_Resource> Resource);

	UFUNCTION(BlueprintCallable)
	void AddResource(TSubclassOf<ABP_Master_Resource> Resource, int32 Amount);

	UFUNCTION(BlueprintCallable)
	void RemoveResource(TSubclassOf<ABP_Master_Resource> Resource, int32 Amount);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
