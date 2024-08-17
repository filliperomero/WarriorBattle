// Fillipe Romero - All Rights Reserved

#include "AbilitySystem/Ability/WBEnemyGameplayAbility.h"

#include "WBGameplayTags.h"
#include "AbilitySystem/WBAbilitySystemComponent.h"
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

FGameplayEffectSpecHandle UWBEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetWBAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetWBAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);
	
	EffectSpecHandle.Data->SetSetByCallerMagnitude(WBGameplayTags::Shared_SetByCaller_BaseDamage, InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel()));
	
	return EffectSpecHandle;
}
