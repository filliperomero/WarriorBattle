﻿// Fillipe Romero - All Rights Reserved

#include "Character/WBHeroCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "WBGameplayTags.h"
#include "AbilitySystem/WBAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Component/Combat/HeroCombatComponent.h"
#include "Component/Input/WBInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "DataAsset/StartUpData/DataAsset_BaseStartUpData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AWBHeroCharacter::AWBHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
}

UPawnCombatComponent* AWBHeroCharacter::GetPawnCombatComponent() const
{
	return GetHeroCombatComponent();
}

void AWBHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("InputConfigDataAsset Uninitialized, fill variable inside Hero Character"))
	
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
	{
		Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
		UWBInputComponent* InputComp = CastChecked<UWBInputComponent>(PlayerInputComponent);

		InputComp->BindNativeInputAction(InputConfigDataAsset, WBGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		InputComp->BindNativeInputAction(InputConfigDataAsset, WBGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

		InputComp->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
	}
}

void AWBHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWBHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// We need to use IsNull in this case since it's a soft pointer
	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_BaseStartUpData* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(WBAbilitySystemComponent);
		}
	}
}

void AWBHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
	const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AWBHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AWBHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	WBAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AWBHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	WBAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}
