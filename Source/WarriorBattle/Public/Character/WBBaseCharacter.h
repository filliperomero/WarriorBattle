// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "WBBaseCharacter.generated.h"

class UWBAttributeSet;
class UWBAbilitySystemComponent;

UCLASS()
class WARRIORBATTLE_API AWBBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWBBaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, Category = "Ability System")
	TObjectPtr<UWBAbilitySystemComponent> WBAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Ability System")
	TObjectPtr<UWBAttributeSet> WBAttributeSet;

public:
	FORCEINLINE UWBAbilitySystemComponent* GetWBAbilitySystemComponent() const { return WBAbilitySystemComponent; }
	FORCEINLINE UWBAttributeSet* GetWBAttributeSet() const { return WBAttributeSet; }
};
