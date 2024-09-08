// Fillipe Romero - All Rights Reserved

#include "AbilitySystem/Ability/WBHeroGameplayAbility.h"

#include "WBGameplayTags.h"
#include "AbilitySystem/WBAbilitySystemComponent.h"
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

UHeroUIComponent* UWBHeroGameplayAbility::GetHeroUIComponentFromActorInfo()
{
	if (!IsValid(GetHeroCharacterFromActorInfo())) return nullptr;

	return GetHeroCharacterFromActorInfo()->GetHeroUIComponent();
}

FGameplayEffectSpecHandle UWBHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetWBAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetWBAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(WBGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);

	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}

	return EffectSpecHandle;
}

bool UWBHeroGameplayAbility::GetAbilityRemainingCooldownByTag(const FGameplayTag InCooldownTag, float& OutTotalCooldownTime, float& OutRemainingCooldownTime)
{
	check(InCooldownTag.IsValid());

	const FGameplayEffectQuery CooldownQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTag.GetSingleTagContainer());
	TArray<TTuple<float, float>> TimeRemainingAndDuration = GetAbilitySystemComponentFromActorInfo()->GetActiveEffectsTimeRemainingAndDuration(CooldownQuery);

	if (!TimeRemainingAndDuration.IsEmpty())
	{
		// Should have only one element inside it since we're using specific tags
		OutRemainingCooldownTime = TimeRemainingAndDuration[0].Key;
		OutTotalCooldownTime = TimeRemainingAndDuration[0].Value;
	}

	return OutRemainingCooldownTime > 0.f;
}
