// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Types/WBEnumTypes.h"
#include "WBSaveGame.generated.h"

UCLASS()
class WARRIORBATTLE_API UWBSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	EGameDifficulty SavedCurrentGameDifficulty;
};
