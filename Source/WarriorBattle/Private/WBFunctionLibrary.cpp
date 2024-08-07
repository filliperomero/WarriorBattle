// Fillipe Romero - All Rights Reserved

#include "WBFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WBAbilitySystemComponent.h"
#include "Interface/PawnCombatInterface.h"

UWBAbilitySystemComponent* UWBFunctionLibrary::NativeGetWBASCFromActor(AActor* InActor)
{
	check(InActor);
	
	return CastChecked<UWBAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

bool UWBFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UWBAbilitySystemComponent* ASC = NativeGetWBASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UWBFunctionLibrary::AddGameplayTagToActor(AActor* InActor, FGameplayTag TagToAdd)
{
	UWBAbilitySystemComponent* ASC = NativeGetWBASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UWBFunctionLibrary::RemoveGameplayTagFromActor(AActor* InActor, FGameplayTag TagToRemove)
{
	UWBAbilitySystemComponent* ASC = NativeGetWBASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

void UWBFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWBConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EWBConfirmType::Yes : EWBConfirmType::No;
}

UPawnCombatComponent* UWBFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor)
	
	if (const IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		 return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* UWBFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EWBValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
	OutValidType = CombatComponent ? EWBValidType::Valid : EWBValidType::Invalid;
	
	return CombatComponent;
}
