﻿// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WBGameplayAbility.h"
#include "WBEnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class AWBEnemyCharacter;

UCLASS()
class WARRIORBATTLE_API UWBEnemyGameplayAbility : public UWBGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "WarrioBattle|Ability")
	AWBEnemyCharacter* GetEnemyCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "WarrioBattle|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AWBEnemyCharacter> CachedWBEnemyCharacter;
};