// Fillipe Romero - All Rights Reserved

#include "Game/WBGameInstance.h"

TSoftObjectPtr<UWorld> UWBGameInstance::GetGameLevelByTag(FGameplayTag InTag) const
{
	if (!InTag.IsValid() || GameLevelSets.IsEmpty()) return TSoftObjectPtr<UWorld>();

	for (const auto& GameLevelSet : GameLevelSets)
	{
		if (!GameLevelSet.IsValid()) continue;

		if (GameLevelSet.LevelTag.MatchesTagExact(InTag))
		{
			return GameLevelSet.Level;
		}
	}

	return TSoftObjectPtr<UWorld>();
}
