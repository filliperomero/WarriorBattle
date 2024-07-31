// Fillipe Romero - All Rights Reserved

#include "AbilitySystem/Ability/WBHeroGameplayAbility.h"

#include "Character/WBHeroCharacter.h"
#include "Player/WBHeroController.h"

AWBHeroCharacter* UWBHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedHeroCharacter.IsValid())
	{
		CachedHeroCharacter = Cast<AWBHeroCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedHeroCharacter.IsValid() ? CachedHeroCharacter.Get() : nullptr;
}

AWBHeroController* UWBHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedHeroController.IsValid())
	{
		CachedHeroController = Cast<AWBHeroController>(CurrentActorInfo->PlayerController);
	}

	return CachedHeroController.IsValid() ? CachedHeroController.Get() : nullptr;
}

UHeroCombatComponent* UWBHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	if (!IsValid(GetHeroCharacterFromActorInfo())) return nullptr;
	
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}
