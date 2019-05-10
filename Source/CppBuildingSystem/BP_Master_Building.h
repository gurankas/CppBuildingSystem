// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StructsAndEnums.h"
#include "WidgetComponent.h"
#include "UI/WBP_BuildWidgetCpp.h"
#include "UI/WBP_BuildingHealthBarCpp.h"
#include "BPC_BuildingStats.h"
#include "Components/BoxComponent.h"
#include "BP_Master_Building.generated.h"

UCLASS()
class CPPBUILDINGSYSTEM_API ABP_Master_Building : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABP_Master_Building();

	int32 modifyValue;
	float local2;
	float local1;

	UPROPERTY()
	UWBP_BuildWidgetCpp* WBPBuildWidget;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* Box;

	UPROPERTY()
	UWBP_BuildingHealthBarCpp* WBPHealthWidget;

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

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UWidgetComponent* BuildingWidget;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool CanBeBuilt;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UWidgetComponent* HealthBarWidget;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBPC_BuildingStats* BuildingStatsComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bBuilt;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bInPlayerSight = true;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float BuildingTime = 0.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float interval;

	UPROPERTY()
	FTimerHandle BuildingTimerHandle;

	UPROPERTY()
	FTimerHandle PostBuildingTimerHandle;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TSet<ABP_Master_Building*> OverlappingBuildings;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		bool bOverlapping;

	UFUNCTION(BlueprintCallable)
	void UpdateGhostMaterial();

	UFUNCTION(BlueprintCallable)
	void ChangeResource(TSubclassOf<ABP_Master_Resource> NewResource);

	UFUNCTION(BlueprintCallable)
	void SetCanBeBuilt(bool newValue);

	UFUNCTION(BlueprintCallable)
	void OnBuild(TSubclassOf<ABP_Master_Resource> ResourceSupplied);

	UFUNCTION(BlueprintCallable)
	void BuildingTick();

	UFUNCTION(BlueprintCallable)
	void OnBuildingEnd();

	UFUNCTION(BlueprintCallable)
	void OnEnterPlayerSight();

	UFUNCTION(BlueprintCallable)
	void OnLeavePlayerSight();

	UFUNCTION(BlueprintCallable)
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void OnOverlappingBegin();

	UFUNCTION(BlueprintCallable)
	void OnOverlappingEnd();

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
