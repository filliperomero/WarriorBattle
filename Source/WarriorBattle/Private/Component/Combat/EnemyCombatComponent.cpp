// Fillipe Romero - All Rights Reserved

#include "Component/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WBGameplayTags.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	Super::OnHitTargetActor(HitActor);

	// Make sure we only damage this Actor once
	if (OverlappedActors.Contains(HitActor)) return;

	OverlappedActors.AddUnique(HitActor);

	// TODO: Implement block checks
	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = false;
	const bool bIsAttackUnblockable = false;

	if (bIsPlayerBlocking && !bIsAttackUnblockable)
	{
		// TODO: if the block is valid
	}
	
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock)
	{
		// TODO: Handle successful block
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), WBGameplayTags::Shared_Event_MeleeHit, EventData);
	}
}

void UEnemyCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}
