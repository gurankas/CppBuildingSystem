// Fill out your copyright notice in the Description page of Project Settings.

#include "Resource_Wood.h"
#include "ConstructorHelpers.h"

AResource_Wood::AResource_Wood()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> icon(TEXT("/Game/BuildingSystem/Textures/Resources/Icon_Wood"));
	ResourceData.Name = FText::FromString("Wood");
	ResourceData.Icon = icon.Object;
}