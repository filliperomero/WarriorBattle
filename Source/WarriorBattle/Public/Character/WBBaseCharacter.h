// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interface/PawnCombatInterface.h"
#include "Interface/PawnUIInterface.h"
#include "WBBaseCharacter.generated.h"

class UDataAsset_BaseStartUpData;
class UWBAttributeSet;
class UWBAbilitySystemComponent;

UCLASS()
class WARRIORBATTLE_API AWBBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	AWBBaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	/** PawnCombat Interface*/
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	/** End PawnCombat Interface*/
	
	/** PawnUI Interface*/
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	/** End IPawnUI Interface*/

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, Category = "Ability System")
	TObjectPtr<UWBAbilitySystemComponent> WBAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Ability System")
	TObjectPtr<UWBAttributeSet> WBAttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Character Data")
	TSoftObjectPtr<UDataAsset_BaseStartUpData> CharacterStartUpData;

public:
	FORCEINLINE UWBAbilitySystemComponent* GetWBAbilitySystemComponent() const { return WBAbilitySystemComponent; }
	FORCEINLINE UWBAttributeSet* GetWBAttributeSet() const { return WBAttributeSet; }
};
