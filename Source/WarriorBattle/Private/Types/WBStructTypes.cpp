// Fillipe Romero - All Rights Reserved

#include "Types/WBStructTypes.h"

#include "AbilitySystem/Ability/WBGameplayAbility.h"
#include "AbilitySystem/Ability/WBHeroGameplayAbility.h"

bool FWBHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
