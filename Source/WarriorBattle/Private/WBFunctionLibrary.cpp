// Fillipe Romero - All Rights Reserved

#include "WBFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WBAbilitySystemComponent.h"
#include "Interface/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "WBGameplayTags.h"
#include "Kismet/KismetMathLibrary.h"

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

bool UWBFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn);
	check(TargetPawn);
	
	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	
	return false;
}

float UWBFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, const float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UWBFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	// Convert back to degrees
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);
	
	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}

	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return WBGameplayTags::Shared_Status_HitReact_Front;
	}
	if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
	{
		return WBGameplayTags::Shared_Status_HitReact_Left;
	}
	if (OutAngleDifference < -135.f || OutAngleDifference > 135.f)
	{
		return WBGameplayTags::Shared_Status_HitReact_Back;
	}
	if (OutAngleDifference > 45.f && OutAngleDifference <= 135.f)
	{
		return WBGameplayTags::Shared_Status_HitReact_Right;
	}
	
	return WBGameplayTags::Shared_Status_HitReact_Front;
}
