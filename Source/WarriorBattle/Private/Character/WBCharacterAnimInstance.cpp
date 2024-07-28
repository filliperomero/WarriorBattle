// Fillipe Romero - All Rights Reserved

#include "Character/WBCharacterAnimInstance.h"
#include "Character/WBBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWBCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AWBBaseCharacter>(TryGetPawnOwner());

	if (IsValid(OwningCharacter))
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UWBCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!IsValid(OwningCharacter) || !IsValid(OwningMovementComponent)) return;

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
