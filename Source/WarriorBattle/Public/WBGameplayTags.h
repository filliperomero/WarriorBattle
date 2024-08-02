﻿// Fillipe Romero - All Rights Reserved

#pragma once

#include "NativeGameplayTags.h"

namespace WBGameplayTags
{
	/** Input Tags */
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipAxe)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Axe)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Axe)

	/** Player Tags */
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe)
	
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe)
	
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe)
}
