// Fillipe Romero - All Rights Reserved

#include "AbilitySystem/WBAbilitySystemComponent.h"

void UWBAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UWBAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}
