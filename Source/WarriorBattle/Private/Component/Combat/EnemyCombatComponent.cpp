// Fillipe Romero - All Rights Reserved

#include "Component/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WBFunctionLibrary.h"
#include "WBGameplayTags.h"
#include "Character/WBEnemyCharacter.h"
#include "Components/BoxComponent.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	Super::OnHitTargetActor(HitActor);

	// Make sure we only damage this Actor once
	if (OverlappedActors.Contains(HitActor)) return;

	OverlappedActors.AddUnique(HitActor);
	
	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = UWBFunctionLibrary::NativeDoesActorHaveTag(HitActor, WBGameplayTags::Player_Status_Blocking);
	const bool bIsAttackUnblockable = UWBFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), WBGameplayTags::Enemy_Status_Unblockable);

	if (bIsPlayerBlocking && !bIsAttackUnblockable)
	{
		bIsValidBlock = UWBFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}
	
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, WBGameplayTags::Player_Event_SuccessfulBlock, EventData);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), WBGameplayTags::Shared_Event_MeleeHit, EventData);
	}
}

void UEnemyCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}

void UEnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bEnable, EToggleDamageType ToggleDamageType)
{
	AWBEnemyCharacter* OwningEnemyCharacter = GetOwningPawn<AWBEnemyCharacter>();

	check(OwningEnemyCharacter)

	UBoxComponent* LeftHandCollisionBox = OwningEnemyCharacter->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = OwningEnemyCharacter->GetRightHandCollisionBox();

	check(LeftHandCollisionBox && RightHandCollisionBox)
	
	switch (ToggleDamageType) {
	case EToggleDamageType::LeftHand:
		LeftHandCollisionBox->SetCollisionEnabled(bEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::RightHand:
		RightHandCollisionBox->SetCollisionEnabled(bEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	default:
		break;
	}

	if (!bEnable)
	{
		OverlappedActors.Empty();
	}
}
