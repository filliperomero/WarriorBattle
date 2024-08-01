// Fillipe Romero - All Rights Reserved

#include "Character/Animation/WBHeroLinkedAnimLayer.h"

#include "Character/Animation/WBHeroAnimInstance.h"

UWBHeroAnimInstance* UWBHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UWBHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
