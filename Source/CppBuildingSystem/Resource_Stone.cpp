// Fill out your copyright notice in the Description page of Project Settings.

#include "Resource_Stone.h"

AResource_Stone::AResource_Stone()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> icon(TEXT("/Game/BuildingSystem/Textures/Resources/Icon_Stone"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> mat(TEXT("/Game/BuildingSystem/Materials/M_Stone"));
	ResourceData.Name = FText::FromString("Stone");
	ResourceData.Icon = icon.Object;
	ResourceData.GhostBuildingColour = FLinearColor(.30196f, .172549f, .090196f);
	ResourceData.BuildingMaterial = mat.Object;
}