// Fillipe Romero - All Rights Reserved

#include "DataAsset/StartUpData/DataAsset_HeroStartUpData.h"

#include "AbilitySystem/WBAbilitySystemComponent.h"
#include "AbilitySystem/Ability/WBHeroGameplayAbility.h"

void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UWBAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const auto& AbilitySet : HeroStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
