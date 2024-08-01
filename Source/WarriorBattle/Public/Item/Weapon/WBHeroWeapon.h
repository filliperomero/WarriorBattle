// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "WBBaseWeapon.h"
#include "Types/WBStructTypes.h"
#include "WBHeroWeapon.generated.h"

UCLASS()
class WARRIORBATTLE_API AWBHeroWeapon : public AWBBaseWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = WeaponData)
	FWBHeroWeaponData HeroWeaponData;

	UFUNCTION(BlueprintCallable)
	void SetGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
