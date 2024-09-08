// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WBHeroGameplayAbility.h"
#include "WBHeroPickupStones.generated.h"

class AWBStonePickupBase;

UCLASS()
class WARRIORBATTLE_API UWBHeroPickupStones : public UWBHeroGameplayAbility
{
	GENERATED_BODY()

public:

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable)
	void CollectStones();

	UFUNCTION(BlueprintCallable)
	void ConsumeStones();

private:
	UPROPERTY(EditDefaultsOnly)
	float BoxTraceDistance = 50.f;
	
	UPROPERTY(EditDefaultsOnly)
	FVector TraceBoxSize = FVector(100.f);

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> StoneTraceChannel;
	
	UPROPERTY(EditDefaultsOnly)
	bool bShowDebugShape = false;

	UPROPERTY()
	TArray<AWBStonePickupBase*> CollectedStones;
};
