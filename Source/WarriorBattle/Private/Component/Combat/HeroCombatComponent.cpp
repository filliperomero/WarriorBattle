// Fillipe Romero - All Rights Reserved

#include "Component/Combat/HeroCombatComponent.h"

#include "Item/Weapon/WBHeroWeapon.h"

AWBHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AWBHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
