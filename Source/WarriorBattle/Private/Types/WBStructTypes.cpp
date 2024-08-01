// Fillipe Romero - All Rights Reserved

#include "Types/WBStructTypes.h"

#include "AbilitySystem/Ability/WBGameplayAbility.h"

bool FWBHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
