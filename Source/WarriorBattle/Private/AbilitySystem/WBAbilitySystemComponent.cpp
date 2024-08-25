// Fillipe Romero - All Rights Reserved

#include "AbilitySystem/WBAbilitySystemComponent.h"

#include "WBGameplayTags.h"
#include "AbilitySystem/Ability/WBHeroGameplayAbility.h"

void UWBAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;

		if (InInputTag.MatchesTag(WBGameplayTags::InputTag_Toggleable))
		{
			if (AbilitySpec.IsActive())
			{
				CancelAbilityHandle(AbilitySpec.Handle);
			}
			else
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
		else
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UWBAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid() || !InInputTag.MatchesTag(WBGameplayTags::InputTag_MustBeHeld)) return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
	}
}

void UWBAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FWBHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty()) return;

	for (const auto& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UWBAbilitySystemComponent::RemoveGrantedHeroWeaponAbilities(TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty()) return;

	for (const auto& SpecHandle : InSpecHandlesToRemove)
	{
		if (!SpecHandle.IsValid()) continue;

		ClearAbility(SpecHandle);
	}

	InSpecHandlesToRemove.Empty();
}

bool UWBAbilitySystemComponent::TryActivateAbilityByTag(const FGameplayTag& AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());

	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);

	if (FoundAbilitySpecs.IsEmpty()) return false;

	const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);
	FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];

	check(SpecToActivate);

	if (SpecToActivate->IsActive()) return false;
	
	return TryActivateAbility(SpecToActivate->Handle);
}
