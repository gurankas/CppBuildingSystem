// Fill out your copyright notice in the Description page of Project Settings.

#include "Resource_Wood.h"
#include "ConstructorHelpers.h"

AResource_Wood::AResource_Wood()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> icon(TEXT("/Game/BuildingSystem/Textures/Resources/Icon_Wood"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> mat(TEXT("/Game/BuildingSystem/Materials/M_wood"));
	ResourceData.Name = FText::FromString("Wood");
	ResourceData.Icon = icon.Object;
	ResourceData.GhostBuildingColour = FLinearColor(.172f, .3098f, .145f);
	ResourceData.BuildingMaterial = mat.Object;
}