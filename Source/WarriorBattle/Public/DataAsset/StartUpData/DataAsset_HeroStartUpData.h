// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_BaseStartUpData.h"
#include "Types/WBStructTypes.h"
#include "DataAsset_HeroStartUpData.generated.h"

UCLASS()
class WARRIORBATTLE_API UDataAsset_HeroStartUpData : public UDataAsset_BaseStartUpData
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWBAbilitySystemComponent* InASCToGive, int32 ApplyLevel) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = StartUpData, meta=(TitleProperty="InputTag"))
	TArray<FWBHeroAbilitySet> HeroStartUpAbilitySets;
};
