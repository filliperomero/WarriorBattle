// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WBGameplayAbility.h"
#include "WBHeroGameplayAbility.generated.h"

class UHeroCombatComponent;
class AWBHeroController;
class AWBHeroCharacter;
class UWBAbilitySystemComponent;

UCLASS()
class WARRIORBATTLE_API UWBHeroGameplayAbility : public UWBGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "WarriorBattle|Ability")
	AWBHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "WarriorBattle|Ability")
	AWBHeroController* GetHeroControllerFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "WarriorBattle|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AWBHeroCharacter> CachedHeroCharacter;
	TWeakObjectPtr<AWBHeroController> CachedHeroController;
};
