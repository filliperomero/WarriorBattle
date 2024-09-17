// Fillipe Romero - All Rights Reserved

#include "WBFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WBAbilitySystemComponent.h"
#include "Interface/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "WBGameplayTags.h"
#include "Game/WBGameInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Types/WBCountDownAction.h"

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

bool UWBFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);
	
	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());
	
	return DotResult < -0.1f;
}

bool UWBFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UWBAbilitySystemComponent* SourceASC = NativeGetWBASCFromActor(InInstigator);
	UWBAbilitySystemComponent* TargetASC = NativeGetWBASCFromActor(InTargetActor);

	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);

	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UWBFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval,
	float& OutRemainingTime, EWBCountDownActionInput CountDownInput, EWBCountDownActionOutput& CountDownOutput,
	FLatentActionInfo LatentInfo)
{
	UWorld* World = nullptr;

	if (GEngine)
	{
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	}

	if (!World) return;

	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();

	FWBCountDownAction* FoundAction = LatentActionManager.FindExistingAction<FWBCountDownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);
	
	if (CountDownInput == EWBCountDownActionInput::Start)
	{
		if (!FoundAction)
		{
			// The LatentActionManger should be dealing with the "new". It should manage the memory properly and don't cause any leak
			LatentActionManager.AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, new FWBCountDownAction(TotalTime, UpdateInterval, OutRemainingTime, CountDownOutput, LatentInfo));
		}
	}

	if (CountDownInput == EWBCountDownActionInput::Cancel)
	{
		if (FoundAction)
		{
			FoundAction->CancelAction();
		}
	}
}

UWBGameInstance* UWBFunctionLibrary::GetWBGameInstance(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			return World->GetGameInstance<UWBGameInstance>();
		}
	}

	return nullptr;
}

void UWBFunctionLibrary::ToggleInputMode(const UObject* WorldContextObject, EWBInputMode InInputMode)
{
	APlayerController* PlayerController = nullptr;
	
	if (GEngine)
    {
        if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
        {
            PlayerController = World->GetFirstPlayerController();
        }
    }
    
    if (!IsValid(PlayerController)) return;
    
    FInputModeGameOnly GameOnlyMode;
    FInputModeUIOnly UIOnlyMode;
    
    switch (InInputMode)
    {
    case EWBInputMode::GameOnly:
        PlayerController->SetInputMode(GameOnlyMode);
        PlayerController->bShowMouseCursor = false;
        break;
    case EWBInputMode::UIOnly:
        PlayerController->SetInputMode(UIOnlyMode);
        PlayerController->bShowMouseCursor = true;
        break;
    }
}