// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WBGameMode.h"
#include "WBSurvivalGameMode.generated.h"

class AWBEnemyCharacter;

UENUM(BlueprintType)
enum class EWBSurvivalGameModeState : uint8
{
	WaitSpawnNewWave,
	SpawningNewWave,
	InProgress,
	WaveCompleted,
	AllWavesCompleted,
	PlayerDied
};

USTRUCT(BlueprintType)
struct FWBEnemyWaveSpawnerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AWBEnemyCharacter> SoftEnemyClassToSpawn;
	
	UPROPERTY(EditAnywhere)
	int32 MinPerSpawnCount = 1;
	
	UPROPERTY(EditAnywhere)
	int32 MaxPerSpawnCount = 3;
};

USTRUCT(BlueprintType)
struct FWBEnemyWaveSpawnerTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FWBEnemyWaveSpawnerInfo> EnemyWaveSpawnerDefinitions;
	
	UPROPERTY(EditAnywhere)
	int32 TotalEnemyToSpawnThisWave = 1;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSurvivalGameModeStateChangedSignature, EWBSurvivalGameModeState, CurrentState);

UCLASS()
class WARRIORBATTLE_API AWBSurvivalGameMode : public AWBGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;	

private:
	void SetCurrentSurvivalGameModeState(EWBSurvivalGameModeState NewState);
	bool HasFinishedAllWaves() const;
	void PreLoadNextWaveEnemies();
	FWBEnemyWaveSpawnerTableRow* GetCurrentWaveSpawnerTableRow() const;
	int32 TrySpawnWaveEnemies();
	bool ShouldKeepSpawningEnemies() const;

	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);
	
	UPROPERTY()
	EWBSurvivalGameModeState CurrentSurvivalGameModeState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSurvivalGameModeStateChangedSignature OnSurvivalGameModeStateChangedDelegate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Definition", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UDataTable> EnemyWaveSpawnerDataTable;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Wave Definition", meta=(AllowPrivateAccess="true"))
	int32 TotalWavesToSpawn;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Wave Definition", meta=(AllowPrivateAccess="true"))
	int32 CurrentWaveCount = 1;

	UPROPERTY()
	int32 CurrentSpawnedEnemiesCounter = 0;

	UPROPERTY()
	int32 TotalSpawnedEnemiesThisWaveCounter = 0;
	
	UPROPERTY()
    TArray<AActor*> TargetPointsArray;

	UPROPERTY()
	float TimePassedSinceStart = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Definition", meta=(AllowPrivateAccess="true"))
	float SpawnNewWaveWaitTime = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wave Definition", meta=(AllowPrivateAccess="true"))
	float SpawnEnemiesDelayTime = 2.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wave Definition", meta=(AllowPrivateAccess="true"))
	float WaveCompletedWaitTime = 5.f;

	UPROPERTY()
	TMap<TSoftClassPtr<AWBEnemyCharacter>, UClass*> PreLoadedEnemyClassMap;

public:
	UFUNCTION(BlueprintCallable)
	void RegisterSpawnedEnemies(const TArray<AWBEnemyCharacter*>& InEnemiesToRegister);
};
