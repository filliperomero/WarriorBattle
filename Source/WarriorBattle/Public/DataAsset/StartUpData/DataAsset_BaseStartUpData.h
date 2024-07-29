// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_BaseStartUpData.generated.h"

class UWBAbilitySystemComponent;
class UWBGameplayAbility;

UCLASS()
class WARRIORBATTLE_API UDataAsset_BaseStartUpData : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWBAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UWBGameplayAbility>> ActivateOnGivenAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UWBGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UWBGameplayAbility>>& InAbilitiesToGive, UWBAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
