// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Component/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class AWBBaseWeapon;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARRIORBATTLE_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "WarriorBattle|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWBBaseWeapon* InWeaponToRegister, const bool bRegisterAsEquippedWeapon = false);
	
	UFUNCTION(BlueprintCallable, Category = "WarriorBattle|Combat")
	AWBBaseWeapon* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;
	
	UFUNCTION(BlueprintCallable, Category = "WarriorBattle|Combat")
	AWBBaseWeapon* GetCharacterCurrentEquippedWeapon() const;

	UPROPERTY(BlueprintReadWrite, Category = "WarriorBattle|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "WarriorBattle|Combat")
	void ToggleWeaponCollision(bool bEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:
	UPROPERTY()
	TArray<AActor*> OverlappedActors;
	
private:
	UPROPERTY()
	TMap<FGameplayTag, AWBBaseWeapon*> CharacterCarriedWeaponMap;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetCurrentEquippedWeaponTag(FGameplayTag InCurrentEquippedWeaponTag) { CurrentEquippedWeaponTag = InCurrentEquippedWeaponTag; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FGameplayTag GetCurrentEquippedWeaponTag() const { return CurrentEquippedWeaponTag; }
};
