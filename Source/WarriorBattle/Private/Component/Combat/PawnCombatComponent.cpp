// Fillipe Romero - All Rights Reserved

#include "Component/Combat/PawnCombatComponent.h"

#include "Components/BoxComponent.h"
#include "Item/Weapon/WBBaseWeapon.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWBBaseWeapon* InWeaponToRegister, const bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A Tag named %s has already been added as a carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister)

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);

	if (bRegisterAsEquippedWeapon) CurrentEquippedWeaponTag = InWeaponTagToRegister;
}

AWBBaseWeapon* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (!CharacterCarriedWeaponMap.Contains(InWeaponTagToGet)) return nullptr;

	if (AWBBaseWeapon* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
	{
		return *FoundWeapon;
	}

	return nullptr;
}

AWBBaseWeapon* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid()) return nullptr;

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bEnable, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		ToggleCurrentEquippedWeaponCollision(bEnable);
	}
	else
	{
		ToggleBodyCollisionBoxCollision(bEnable, ToggleDamageType);
	}
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor) {}

void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor) {}

void UPawnCombatComponent::ToggleCurrentEquippedWeaponCollision(bool bEnable)
{
	const AWBBaseWeapon* WeaponToToggle = GetCharacterCurrentEquippedWeapon();

	check(WeaponToToggle);
		
	WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(bEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
	if(!bEnable) OverlappedActors.Empty();
}

void UPawnCombatComponent::ToggleBodyCollisionBoxCollision(bool bEnable, EToggleDamageType ToggleDamageType)
{
}
