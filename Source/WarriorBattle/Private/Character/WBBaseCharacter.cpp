// Fillipe Romero - All Rights Reserved

#include "Character/WBBaseCharacter.h"
#include "AbilitySystem/WBAbilitySystemComponent.h"
#include "AbilitySystem/WBAttributeSet.h"

AWBBaseCharacter::AWBBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;
	
	WBAbilitySystemComponent = CreateDefaultSubobject<UWBAbilitySystemComponent>(TEXT("WBAbilitySystemComponent"));

	WBAttributeSet = CreateDefaultSubobject<UWBAttributeSet>(TEXT("WBAttributeSet"));
}

UAbilitySystemComponent* AWBBaseCharacter::GetAbilitySystemComponent() const
{
	return GetWBAbilitySystemComponent();
}

UPawnCombatComponent* AWBBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent* AWBBaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

void AWBBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (IsValid(WBAbilitySystemComponent))
	{
		WBAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("StartUp Data not assigned to %s"), *GetName());
	}
}
