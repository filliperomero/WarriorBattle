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

	UFUNCTION(BlueprintPure, Category = "WarriorBattle|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);
	
	UFUNCTION(BlueprintCallable, Category = "WarriorBattle|Ability")
	bool GetAbilityRemainingCooldownByTag(const FGameplayTag InCooldownTag, float& OutTotalCooldownTime, float& OutRemainingCooldownTime);

private:
	TWeakObjectPtr<AWBHeroCharacter> CachedHeroCharacter;
	TWeakObjectPtr<AWBHeroController> CachedHeroController;
};
