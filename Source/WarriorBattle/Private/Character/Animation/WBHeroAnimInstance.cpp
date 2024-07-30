// Fillipe Romero - All Rights Reserved

#include "Character/Animation/WBHeroAnimInstance.h"
#include "Character/WBBaseCharacter.h"
#include "Character/WBHeroCharacter.h"

void UWBHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (IsValid(OwningCharacter))
	{
		OwningHeroCharacter = Cast<AWBHeroCharacter>(OwningCharacter);
	}
}

void UWBHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (bHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		if (!bShouldEnterRelaxState)
		{
			IdleElapsedTime += DeltaSeconds;
			bShouldEnterRelaxState = IdleElapsedTime >= EnterRelaxStateThreshold;
		}
	}
}
