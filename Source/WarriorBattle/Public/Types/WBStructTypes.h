// Fillipe Romero - All Rights Reserved

#pragma once

#include "WBStructTypes.generated.h"

class UWBHeroLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FWBHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWBHeroLinkedAnimLayer> WeaponAnimLayerToLink;
};