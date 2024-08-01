// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"


class AWBHeroWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARRIORBATTLE_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="WarriorBattle|Combat")
	AWBHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;
};
