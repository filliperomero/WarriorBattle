// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/GameInstance.h"
#include "WBGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FWBGameLevelSet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(Categories="GameData.Level"))
	FGameplayTag LevelTag;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Level;

	bool IsValid() const
	{
		return LevelTag.IsValid() && !Level.IsNull();
	}
};

UCLASS()
class WARRIORBATTLE_API UWBGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FWBGameLevelSet> GameLevelSets;

	UFUNCTION()
	virtual void OnPreLoadMap(const FString& MapName);

	UFUNCTION()
	virtual void OnDestinationWorldLoaded(UWorld* LoadedWorld);

public:
	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="GameData.Level"))
	TSoftObjectPtr<UWorld> GetGameLevelByTag(FGameplayTag InTag) const;
};
