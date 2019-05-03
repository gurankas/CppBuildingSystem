// Fill out your copyright notice in the Description page of Project Settings.

#include "Resource_Metal.h"

AResource_Metal::AResource_Metal()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> icon(TEXT("/Game/BuildingSystem/Textures/Resources/Icon_Metal"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> mat(TEXT("/Game/BuildingSystem/Materials/M_Metal"));
	ResourceData.Name = FText::FromString("Metal");
	ResourceData.Icon = icon.Object;
	ResourceData.GhostBuildingColour = FLinearColor(.070588f, .501961f, 1.f);
	ResourceData.BuildingMaterial = mat.Object;
}