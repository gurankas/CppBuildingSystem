// Fill out your copyright notice in the Description page of Project Settings.

#include "Resource_Stone.h"

AResource_Stone::AResource_Stone()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> icon(TEXT("/Game/BuildingSystem/Textures/Resources/Icon_Stone"));
	ResourceData.Name = FText::FromString("Stone");
	ResourceData.Icon = icon.Object;
}