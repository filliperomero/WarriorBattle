// Fillipe Romero - All Rights Reserved

#include "DataAsset/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const auto& [InputTag, InputAction] : NativeInputActions)
	{
		if (InputTag.MatchesTagExact(InInputTag) && InputAction)
		{
			return InputAction;
		}
	}

	return nullptr;
}
