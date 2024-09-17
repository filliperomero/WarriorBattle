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
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Roll)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SwitchTarget)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SpecialWeaponAbility_Light)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SpecialWeaponAbility_Heavy)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Pickup_Stones)

	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld_Block)

	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_TargetLock)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_Rage)

	/** Player Tags */
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Roll)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Block)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_TargetLock)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Rage)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_SpecialWeaponAbility_Light)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_SpecialWeaponAbility_Heavy)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Pickup_Stones)
	
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Cooldown_SpecialWeaponAbility_Light)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Cooldown_SpecialWeaponAbility_Heavy)
	
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe)
	
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SuccessfulBlock)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Left)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Right)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_ActivateRage)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_AOE)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_ConsumeStones)

	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rolling)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Blocking)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_TargetLocking)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Activating)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Active)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Full)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_None)
	
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy)

	/** Enemy Tags */
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon)

	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_SummonEnemies)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_SpawnStone)

	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Event_SummonEnemies)

	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_UnderAttack)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Unblockable)

	/** Shared Tags*/
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_SpawnProjectile)

	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death)
	
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage)
	
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Dead)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Front)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Back)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Right)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Left)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Invincible)

	/** GameplayCue */
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_MeleeHit_Axe)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_MeleeHit_Stick)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Death_Guardian)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Death_FrostGiant)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Effects_MagicShield)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Effects_MagicShield_SuccessfulBlock)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Effects_MagicShield_PerfectBlock)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Effects_UnblockableWarning)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayCue_Effects_Rage_Activating)

	/** Game Data Tags */
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameData_Level_SurvivalGameModeMap)
	WARRIORBATTLE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameData_Level_MainMenuMap)
}
