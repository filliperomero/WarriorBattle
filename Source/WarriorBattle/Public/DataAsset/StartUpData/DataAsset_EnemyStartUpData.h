// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_BaseStartUpData.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class UWBEnemyGameplayAbility;

UCLASS()
class WARRIORBATTLE_API UDataAsset_EnemyStartUpData : public UDataAsset_BaseStartUpData
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWBAbilitySystemComponent* InASCToGive, int32 ApplyLevel) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = StartUpData)
	TArray<TSubclassOf<UWBEnemyGameplayAbility>> EnemyCombatAbilities; 
};
