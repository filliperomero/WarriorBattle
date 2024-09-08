// Fillipe Romero - All Rights Reserved

#include "AbilitySystem/Ability/WBHeroPickupStones.h"

#include "Character/WBHeroCharacter.h"
#include "Item/Pickup/WBStonePickupBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UWBHeroPickupStones::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UWBHeroPickupStones::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UWBHeroPickupStones::CollectStones()
{
	CollectedStones.Empty();
	
	TArray<FHitResult> TraceHits;
	
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetHeroCharacterFromActorInfo(),
		GetHeroCharacterFromActorInfo()->GetActorLocation(),
		GetHeroCharacterFromActorInfo()->GetActorLocation() + -GetHeroCharacterFromActorInfo()->GetActorUpVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		(-GetHeroCharacterFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		StoneTraceChannel,
		false,
		TArray<AActor*>(),
		bShowDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		TraceHits,
		true
	);

	for (const FHitResult& TraceHit : TraceHits)
	{
		if (AWBStonePickupBase* Stone = Cast<AWBStonePickupBase>(TraceHit.GetActor()))
		{
			CollectedStones.AddUnique(Stone);
		}
	}

	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
}

void UWBHeroPickupStones::ConsumeStones()
{
	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}
	
	for (AWBStonePickupBase* CollectedStone : CollectedStones)
	{
		if (IsValid(CollectedStone))
		{
			CollectedStone->Consume(GetWBAbilitySystemComponentFromActorInfo(), GetAbilityLevel());
		}
	}
}
