// Fillipe Romero - All Rights Reserved

#include "DataAsset/StartUpData/DataAsset_EnemyStartUpData.h"

#include "AbilitySystem/WBAbilitySystemComponent.h"
#include "AbilitySystem/Ability/WBEnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UWBAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if (EnemyCombatAbilities.IsEmpty()) return;

	for (const auto& AbilityClass : EnemyCombatAbilities)
	{
		if (!AbilityClass) continue;

		FGameplayAbilitySpec AbilitySpec(AbilityClass);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
