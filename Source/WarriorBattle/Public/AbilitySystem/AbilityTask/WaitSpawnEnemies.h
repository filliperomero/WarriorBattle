// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "WaitSpawnEnemies.generated.h"

class AWBEnemyCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitSpawnEnemiesDelegate, const TArray<AWBEnemyCharacter*>&, SpawnedEnemies);

UCLASS()
class WARRIORBATTLE_API UWaitSpawnEnemies : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="WarrioBattle|AbilityTasks", meta=(DisplayName="Wait Gameplay Event And Spawn Enemies", HidePin="OwningAbility", DefaultToSelf="OwningAbility", BlueprintInternalUseOnly="true", NumToSpawn="1", RandomSpawnRadius="200"))
	static UWaitSpawnEnemies* WaitSpawnEnemies(UGameplayAbility* OwningAbility, FGameplayTag EventTag, TSoftClassPtr<AWBEnemyCharacter> SoftEnemyClassToSpawn, int32 NumToSpawn, const FVector& SpawnOrigin, float RandomSpawnRadius);

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate OnSpawnFinished;

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate DidNotSpawn;

	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

private:
	FGameplayTag CachedEventTag;
	TSoftClassPtr<AWBEnemyCharacter> CachedSoftEnemyClassToSpawn;
	int32 CachedNumToSpawn;
	FVector CachedSpawnOrigin;
	float CachedRandomSpawnRadius;

	FDelegateHandle DelegateHandle;

	void OnGameplayEventReceived(const FGameplayEventData* InPayload);
	void OnEnemyClassLoaded();
};
