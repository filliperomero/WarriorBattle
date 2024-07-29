﻿// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WBGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EWarriorBattleAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class WARRIORBATTLE_API UWBGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Warrior Battle Ability")
	EWarriorBattleAbilityActivationPolicy AbilityActivationPolicy = EWarriorBattleAbilityActivationPolicy::OnTriggered;
};
