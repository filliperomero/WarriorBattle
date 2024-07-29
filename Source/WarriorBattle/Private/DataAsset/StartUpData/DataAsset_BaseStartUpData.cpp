// Fillipe Romero - All Rights Reserved

#include "DataAsset/StartUpData/DataAsset_BaseStartUpData.h"

#include "AbilitySystem/Ability/WBGameplayAbility.h"
#include "AbilitySystem/WBAbilitySystemComponent.h"

void UDataAsset_BaseStartUpData::GiveToAbilitySystemComponent(UWBAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	checkf(InASCToGive, TEXT("InASCToGive must be initialized"));
	
	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UDataAsset_BaseStartUpData::GrantAbilities(const TArray<TSubclassOf<UWBGameplayAbility>>& InAbilitiesToGive, UWBAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) return;

	for (const auto& Ability : InAbilitiesToGive)
	{
		if (!IsValid(Ability)) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
