// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Types/WBEnumTypes.h"
#include "WBGameplayAbility.generated.h"

class UWBAbilitySystemComponent;
class UPawnCombatComponent;

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
	
	UPROPERTY(EditDefaultsOnly, Category = "WarriorBattle|Ability")
	EWarriorBattleAbilityActivationPolicy AbilityActivationPolicy = EWarriorBattleAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "WarriorBattle|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "WarriorBattle|Ability")
	UWBAbilitySystemComponent* GetWBAbilitySystemComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "WarriorBattle|Ability", meta=(DisplayName = "Apply Gameplay Effect Spec Handle To Target", ExpandEnumAsExecs="OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EWBSuccessType& OutSuccessType);
};
