// Fillipe Romero - All Rights Reserved

#include "Item/Pickup/WBStonePickupBase.h"

#include "WBGameplayTags.h"
#include "AbilitySystem/WBAbilitySystemComponent.h"
#include "Character/WBHeroCharacter.h"

void AWBStonePickupBase::Consume(UWBAbilitySystemComponent* ASC, int32 ApplyLevel)
{
	check(EffectClassToApply);

	const UGameplayEffect* EffectCDO = EffectClassToApply->GetDefaultObject<UGameplayEffect>();
	
	ASC->ApplyGameplayEffectToSelf(EffectCDO, ApplyLevel, ASC->MakeEffectContext());

	BP_OnStoneConsumed();
}

void AWBStonePickupBase::OnPickupCollisionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Use an interface for this
	if (const AWBHeroCharacter* OverlappedHeroCharacter = Cast<AWBHeroCharacter>(OtherActor))
	{
		OverlappedHeroCharacter->GetWBAbilitySystemComponent()->TryActivateAbilityByTag(WBGameplayTags::Player_Ability_Pickup_Stones);
	}
}
