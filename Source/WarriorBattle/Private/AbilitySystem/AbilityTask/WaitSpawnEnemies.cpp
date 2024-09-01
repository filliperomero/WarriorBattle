// Fillipe Romero - All Rights Reserved

#include "AbilitySystem/AbilityTask/WaitSpawnEnemies.h"

#include "AbilitySystemComponent.h"
#include "NavigationSystem.h"
#include "Character/WBEnemyCharacter.h"
#include "Engine/AssetManager.h"

UWaitSpawnEnemies* UWaitSpawnEnemies::WaitSpawnEnemies(UGameplayAbility* OwningAbility, FGameplayTag EventTag,
                                                       TSoftClassPtr<AWBEnemyCharacter> SoftEnemyClassToSpawn, int32 NumToSpawn, const FVector& SpawnOrigin,
                                                       float RandomSpawnRadius)
{
	UWaitSpawnEnemies* Node = NewAbilityTask<UWaitSpawnEnemies>(OwningAbility);

	Node->CachedEventTag = EventTag;
	Node->CachedSoftEnemyClassToSpawn = SoftEnemyClassToSpawn;
	Node->CachedNumToSpawn = NumToSpawn;
	Node->CachedSpawnOrigin = SpawnOrigin;
	Node->CachedRandomSpawnRadius = RandomSpawnRadius;

	return Node;
}

void UWaitSpawnEnemies::Activate()
{
	// Needs to be a reference, otherwise it'll not work. If we don't use a reference, it'll only get a copy of it. 
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);

	DelegateHandle = Delegate.AddUObject(this, &ThisClass::OnGameplayEventReceived);
}

void UWaitSpawnEnemies::OnDestroy(bool bInOwnerFinished)
{
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);
	Delegate.Remove(DelegateHandle);

	Super::OnDestroy(bInOwnerFinished);
}

void UWaitSpawnEnemies::OnGameplayEventReceived(const FGameplayEventData* InPayload)
{
	if (ensure(!CachedSoftEnemyClassToSpawn.IsNull()))
	{
		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
			CachedSoftEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateUObject(this, &ThisClass::OnEnemyClassLoaded)
		);
	}
	else
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			DidNotSpawn.Broadcast(TArray<AWBEnemyCharacter*>());
		}
		
		EndTask();
	}
}

void UWaitSpawnEnemies::OnEnemyClassLoaded()
{
	UClass* LoadedClass = CachedSoftEnemyClassToSpawn.Get();
	UWorld* World = GetWorld();

	if (!IsValid(LoadedClass) || !IsValid(World))
	{
		if (ShouldBroadcastAbilityTaskDelegates()) DidNotSpawn.Broadcast(TArray<AWBEnemyCharacter*>());
		
		return EndTask();
	}

	TArray<AWBEnemyCharacter*> SpawnedEnemies;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int32 i = 0; i < CachedNumToSpawn; i++)
	{
		FVector RandomLocation;
		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(World, CachedSpawnOrigin, RandomLocation, CachedRandomSpawnRadius);

		// Make sure the Enemy will not be stuck in the ground
		RandomLocation += FVector(0.f, 0.f, 150.f);
		const FRotator SpawnFacingRotation = AbilitySystemComponent->GetAvatarActor()->GetActorForwardVector().ToOrientationRotator();

		AWBEnemyCharacter* SpawnedEnemy = World->SpawnActor<AWBEnemyCharacter>(LoadedClass, RandomLocation, SpawnFacingRotation, SpawnParameters);

		if (IsValid(SpawnedEnemy))
		{
			SpawnedEnemies.Add(SpawnedEnemy);
		}
	}

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if (!SpawnedEnemies.IsEmpty())
		{
			OnSpawnFinished.Broadcast(SpawnedEnemies);
		}
		else
		{
			DidNotSpawn.Broadcast(TArray<AWBEnemyCharacter*>());
		}
	}

	EndTask();
}
