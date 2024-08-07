// Fillipe Romero - All Rights Reserved

#include "Component/Combat/HeroCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WBGameplayTags.h"
#include "Item/Weapon/WBHeroWeapon.h"

AWBHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AWBHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AWBHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AWBHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseData.GetValueAtLevel(InLevel);
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	Super::OnHitTargetActor(HitActor);

	// Make sure we only damage this Actor once
	if (OverlappedActors.Contains(HitActor)) return;

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), WBGameplayTags::Shared_Event_MeleeHit, EventData);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), WBGameplayTags::Player_Event_HitPause, FGameplayEventData());
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	Super::OnWeaponPulledFromTargetActor(InteractedActor);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), WBGameplayTags::Player_Event_HitPause, FGameplayEventData());
}
