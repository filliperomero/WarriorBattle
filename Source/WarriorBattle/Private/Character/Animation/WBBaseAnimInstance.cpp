// Fillipe Romero - All Rights Reserved

#include "Character/Animation/WBBaseAnimInstance.h"

#include "WBFunctionLibrary.h"

bool UWBBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UWBFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}

	return false;
}
