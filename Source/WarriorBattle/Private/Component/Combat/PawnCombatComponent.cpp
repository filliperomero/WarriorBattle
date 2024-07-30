// Fillipe Romero - All Rights Reserved

#include "Component/Combat/PawnCombatComponent.h"

#include "WBDebugHelper.h"
#include "Item/Weapon/WBBaseWeapon.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWBBaseWeapon* InWeaponToRegister, const bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A Tag named %s has already been added as a carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister)

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	if (bRegisterAsEquippedWeapon) CurrentEquippedWeaponTag = InWeaponTagToRegister;

	const FString DebugMessage = FString::Printf(TEXT("A Weapon named: %s has been registered using the tag %s"), *InWeaponToRegister->GetName(), *InWeaponTagToRegister.ToString()); 
	Debug::Print(DebugMessage, FColor::Purple);
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
