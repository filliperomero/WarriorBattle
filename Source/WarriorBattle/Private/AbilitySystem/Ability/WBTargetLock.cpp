// Fillipe Romero - All Rights Reserved

#include "AbilitySystem/Ability/WBTargetLock.h"

#include "EnhancedInputSubsystems.h"
#include "WBFunctionLibrary.h"
#include "WBGameplayTags.h"
#include "Character/WBHeroCharacter.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/WBHeroController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/Widget/WBUserWidgetBase.h"

void UWBTargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	TryLockOnTarget();
	InitTargetLockMovement();
	InitTargetLockMappingContext();
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UWBTargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	CleanUp();
	ResetTargetLockMovement();
	ResetTargetLockMappingContext();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UWBTargetLock::OnTargetLockTick(float DeltaTime)
{
	if (!IsValid(CurrentLockedActor)
		|| UWBFunctionLibrary::NativeDoesActorHaveTag(CurrentLockedActor, WBGameplayTags::Shared_Status_Dead)
		|| UWBFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromActorInfo(), WBGameplayTags::Shared_Status_Dead))
	{
		return CancelTargetLockAbility();
	}

	SetTargetLockWidgetPosition();

	const bool bShouldOverrideRotation =
		!UWBFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromActorInfo(), WBGameplayTags::Player_Status_Rolling)
		&& !UWBFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromActorInfo(), WBGameplayTags::Player_Status_Blocking);

	if (bShouldOverrideRotation)
	{
		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetHeroCharacterFromActorInfo()->GetActorLocation(), CurrentLockedActor->GetActorLocation());
		LookAtRot.Pitch -= TargetLockCameraOffsetDistance;

		const FRotator CurrentControlRot = GetHeroControllerFromActorInfo()->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime, TargetLockRotationInterpSpeed);

		GetHeroControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
		GetHeroCharacterFromActorInfo()->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
	}
}

void UWBTargetLock::SwitchTarget(const FGameplayTag& InSwitchDirectionTag)
{
	GetAvailableActorsToLock();

	TArray<AActor*> ActorsOnLeft;
	TArray<AActor*> ActorsOnRight;
	
	GetAvailableActorsAroundTarget(ActorsOnLeft, ActorsOnRight);

	const bool bIsSwitchTargetLeft = InSwitchDirectionTag.MatchesTagExact(WBGameplayTags::Player_Event_SwitchTarget_Left);

	AActor* NewTargetToLock = GetNearestTargetFromAvailableActors(bIsSwitchTargetLeft ? ActorsOnLeft : ActorsOnRight);

	if (IsValid(NewTargetToLock))
	{
		CurrentLockedActor = NewTargetToLock;
	}
}

void UWBTargetLock::TryLockOnTarget()
{
	GetAvailableActorsToLock();

	if (AvailableActorsToLock.IsEmpty()) return CancelTargetLockAbility();

	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);

	if (IsValid(CurrentLockedActor))
	{
		DrawTargetLockWidget();
		SetTargetLockWidgetPosition();
	}
	else
	{
		CancelTargetLockAbility();
	}
}

void UWBTargetLock::GetAvailableActorsToLock()
{
	AvailableActorsToLock.Empty();
	
	TArray<FHitResult> BoxTraceHits;
	
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetAvatarActorFromActorInfo(),
		GetHeroCharacterFromActorInfo()->GetActorLocation(),
		GetHeroCharacterFromActorInfo()->GetActorLocation() + GetHeroCharacterFromActorInfo()->GetActorForwardVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		GetHeroCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);

	for (const auto& TraceHit : BoxTraceHits)
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			if (HitActor != GetHeroCharacterFromActorInfo())
			{
				AvailableActorsToLock.AddUnique(HitActor);
			}
		}
	}
}

AActor* UWBTargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float OutClosestDistance = 0.f;
	return UGameplayStatics::FindNearestActor(GetHeroCharacterFromActorInfo()->GetActorLocation(), InAvailableActors, OutClosestDistance);
}

void UWBTargetLock::GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight)
{
	if (!IsValid(CurrentLockedActor) || AvailableActorsToLock.IsEmpty()) return CancelTargetLockAbility();

	const FVector PlayerLocation = GetHeroCharacterFromActorInfo()->GetActorLocation();
	const FVector PlayerToCurrentNormalized = (CurrentLockedActor->GetActorLocation() - PlayerLocation).GetSafeNormal();

	for (AActor* AvailableActor : AvailableActorsToLock)
	{
		if (!IsValid(AvailableActor) || AvailableActor == CurrentLockedActor) continue;

		const FVector PlayerToAvailableNormalized = (AvailableActor->GetActorLocation() - PlayerLocation).GetSafeNormal();

		const FVector CrossResult = FVector::CrossProduct(PlayerToCurrentNormalized, PlayerToAvailableNormalized);

		if (CrossResult.Z > 0.f) // Pointing Up
		{
			OutActorsOnRight.AddUnique(AvailableActor);
		}
		else
		{
			OutActorsOnLeft.AddUnique(AvailableActor);
		}
	}
}

void UWBTargetLock::DrawTargetLockWidget()
{
	if (IsValid(TargetLockWidget)) return;
	
	checkf(TargetLockWidgetClass, TEXT("Forgot to assign a valid Widget Class in Blueprint"));

	TargetLockWidget = CreateWidget<UWBUserWidgetBase>(GetHeroControllerFromActorInfo(), TargetLockWidgetClass);

	check(TargetLockWidget)

	TargetLockWidget->AddToViewport();
}

void UWBTargetLock::SetTargetLockWidgetPosition()
{
	if (!IsValid(TargetLockWidget) || !IsValid(CurrentLockedActor))
	{
		return CancelTargetLockAbility();
	}
	FVector2D ScreenPosition;

	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		GetHeroControllerFromActorInfo(),
		CurrentLockedActor->GetActorLocation(),
		ScreenPosition,
		true
	);

	if (TargetLockWidgetSize == FVector2D::ZeroVector)
	{
		TargetLockWidget->WidgetTree->ForEachWidget(
		[this](UWidget* FoundWidget)
			{
				if (const USizeBox* SizeBox = Cast<USizeBox>(FoundWidget))
				{
					TargetLockWidgetSize.X = SizeBox->GetWidthOverride();
					TargetLockWidgetSize.Y = SizeBox->GetHeightOverride();
				}
			}
		);
	}

	ScreenPosition -= (TargetLockWidgetSize / 2.f);
	
	TargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}

void UWBTargetLock::InitTargetLockMovement()
{
	CachedDefaultMaxWalkSpeed = GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;
	
	GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetLockMaxWalkSpeed;
}

void UWBTargetLock::InitTargetLockMappingContext()
{
	const ULocalPlayer* LocalPlayer = GetHeroControllerFromActorInfo()->GetLocalPlayer();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	
	check(Subsystem)

	Subsystem->AddMappingContext(TargetLockMappingContext, 3);
}

void UWBTargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UWBTargetLock::CleanUp()
{
	AvailableActorsToLock.Empty();
	CurrentLockedActor = nullptr;
	
	if (IsValid(TargetLockWidget))
	{
		TargetLockWidget->RemoveFromParent();
	}
	
	TargetLockWidget = nullptr;
	TargetLockWidgetSize = FVector2D::ZeroVector;
}

void UWBTargetLock::ResetTargetLockMovement()
{
	if (CachedDefaultMaxWalkSpeed > 0.f)
	{
		GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CachedDefaultMaxWalkSpeed;

		CachedDefaultMaxWalkSpeed = 0.f;
	}
}

void UWBTargetLock::ResetTargetLockMappingContext()
{
	if (!IsValid(GetHeroControllerFromActorInfo())) return;
	
	const ULocalPlayer* LocalPlayer = GetHeroControllerFromActorInfo()->GetLocalPlayer();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	
	check(Subsystem)

	Subsystem->RemoveMappingContext(TargetLockMappingContext);
}
