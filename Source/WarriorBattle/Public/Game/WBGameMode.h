// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Types/WBEnumTypes.h"
#include "WBGameMode.generated.h"

UCLASS()
class WARRIORBATTLE_API AWBGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AWBGameMode();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Settings")
	EGameDifficulty CurrentGameDifficulty;

public:
	FORCEINLINE EGameDifficulty GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
	
};
