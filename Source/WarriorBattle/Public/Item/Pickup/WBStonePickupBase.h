// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WBPickupBase.h"
#include "WBStonePickupBase.generated.h"

class UGameplayEffect;
class UWBAbilitySystemComponent;

UCLASS()
class WARRIORBATTLE_API AWBStonePickupBase : public AWBPickupBase
{
	GENERATED_BODY()

public:
	void Consume(UWBAbilitySystemComponent* ASC, int32 ApplyLevel);

protected:
	virtual void OnPickupCollisionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On Stone Consumed"))
	void BP_OnStoneConsumed();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> EffectClassToApply;	
};
