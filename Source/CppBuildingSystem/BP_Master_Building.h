// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StructsAndEnums.h"
#include "BP_Master_Building.generated.h"

UCLASS()
class CPPBUILDINGSYSTEM_API ABP_Master_Building : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_Master_Building();

	UPROPERTY()
	UMaterialInterface* BuildingMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* BuildingMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FCpp_BuildingData BuildingData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = "true"))
	TSubclassOf<class ABP_Master_Resource> Resource;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<TSubclassOf<ABP_Master_Resource>, FCpp_BuildingResourceVersion> ResourceVersions;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicBuildingMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
