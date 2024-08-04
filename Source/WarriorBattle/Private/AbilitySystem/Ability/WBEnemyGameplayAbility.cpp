// Fillipe Romero - All Rights Reserved

#include "AbilitySystem/Ability/WBEnemyGameplayAbility.h"

#include "Character/WBEnemyCharacter.h"

AWBEnemyCharacter* UWBEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedWBEnemyCharacter.IsValid())
	{
		CachedWBEnemyCharacter = Cast<AWBEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedWBEnemyCharacter.IsValid() ? CachedWBEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UWBEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	if (!IsValid(GetEnemyCharacterFromActorInfo())) return nullptr;
	
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
