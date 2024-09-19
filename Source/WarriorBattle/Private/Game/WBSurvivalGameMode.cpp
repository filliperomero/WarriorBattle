// Fillipe Romero - All Rights Reserved

#include "Game/WBSurvivalGameMode.h"

#include "NavigationSystem.h"
#include "WBFunctionLibrary.h"
#include "Character/WBEnemyCharacter.h"
#include "Engine/AssetManager.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

void AWBSurvivalGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	EGameDifficulty GameDifficulty;
	
	if (UWBFunctionLibrary::TryLoadSavedGameDifficulty(GameDifficulty))
	{
		CurrentGameDifficulty = GameDifficulty;
	}
}

void AWBSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();

	checkf(EnemyWaveSpawnerDataTable, TEXT("Forgot to assign a valid Data Table in Survival Game Mode BP"))

	SetCurrentSurvivalGameModeState(EWBSurvivalGameModeState::WaitSpawnNewWave);

	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();

	PreLoadNextWaveEnemies();
}

void AWBSurvivalGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CurrentSurvivalGameModeState == EWBSurvivalGameModeState::WaitSpawnNewWave)
	{
		TimePassedSinceStart += DeltaSeconds;

		if (TimePassedSinceStart >= SpawnNewWaveWaitTime)
		{
			TimePassedSinceStart = 0.f;

			SetCurrentSurvivalGameModeState(EWBSurvivalGameModeState::SpawningNewWave);
		}
	}

	if (CurrentSurvivalGameModeState == EWBSurvivalGameModeState::SpawningNewWave)
	{
		TimePassedSinceStart += DeltaSeconds;

		if (TimePassedSinceStart >= SpawnEnemiesDelayTime)
		{
			CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();

			TimePassedSinceStart = 0.f;

			SetCurrentSurvivalGameModeState(EWBSurvivalGameModeState::InProgress);
		}
	}

	if (CurrentSurvivalGameModeState == EWBSurvivalGameModeState::WaveCompleted)
	{
		TimePassedSinceStart += DeltaSeconds;

		if (TimePassedSinceStart >= WaveCompletedWaitTime)
		{
			TimePassedSinceStart = 0.f;

			CurrentWaveCount++;

			if (HasFinishedAllWaves())
			{
				SetCurrentSurvivalGameModeState(EWBSurvivalGameModeState::AllWavesCompleted);
			}
			else
			{
				SetCurrentSurvivalGameModeState(EWBSurvivalGameModeState::WaitSpawnNewWave);
				PreLoadNextWaveEnemies();
			}
		}
	}
}

void AWBSurvivalGameMode::SetCurrentSurvivalGameModeState(EWBSurvivalGameModeState NewState)
{
	CurrentSurvivalGameModeState = NewState;

	OnSurvivalGameModeStateChangedDelegate.Broadcast(NewState);
}

bool AWBSurvivalGameMode::HasFinishedAllWaves() const
{
	return CurrentWaveCount > TotalWavesToSpawn;
}

void AWBSurvivalGameMode::PreLoadNextWaveEnemies()
{
	if (HasFinishedAllWaves()) return;

	PreLoadedEnemyClassMap.Empty();

	for (const auto& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;

		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda(
				[SpawnerInfo, this]()
				{
					if (UClass* LoadedEnemyClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
					{
						PreLoadedEnemyClassMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn, LoadedEnemyClass);
					}
				})
		);
	}
}

FWBEnemyWaveSpawnerTableRow* AWBSurvivalGameMode::GetCurrentWaveSpawnerTableRow() const
{
	const FName RowName = FName(TEXT("Wave") + FString::FromInt(CurrentWaveCount));
	FWBEnemyWaveSpawnerTableRow* FoundRow = EnemyWaveSpawnerDataTable->FindRow<FWBEnemyWaveSpawnerTableRow>(RowName, FString());

	checkf(FoundRow, TEXT("Cannot find a valid row under the name %s in the data table"), *RowName.ToString());

	return FoundRow;
}

int32 AWBSurvivalGameMode::TrySpawnWaveEnemies()
{
	if (TargetPointsArray.IsEmpty())
	{
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), TargetPointsArray);
	}

	checkf(!TargetPointsArray.IsEmpty(), TEXT("No valid target point found in level (%s) for spawning enemies"), *GetWorld()->GetName());

	uint32 EnemiesSpawnedThisTime = 0;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (const auto& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;

		const int32 NumToSpawn = FMath::RandRange(SpawnerInfo.MinPerSpawnCount, SpawnerInfo.MaxPerSpawnCount);

		UClass* LoadedEnemyClass = PreLoadedEnemyClassMap.FindChecked(SpawnerInfo.SoftEnemyClassToSpawn);

		for (int32 i = 0; i < NumToSpawn; i++)
		{
			const int32 RandomTargetPointIndex = FMath::RandRange(0, TargetPointsArray.Num() - 1);
			const FVector SpawnOrigin = TargetPointsArray[RandomTargetPointIndex]->GetActorLocation();
			const FRotator SpawnRotation = TargetPointsArray[RandomTargetPointIndex]->GetActorForwardVector().ToOrientationRotator();

			FVector RandomLocation;
			UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(this, SpawnOrigin, RandomLocation, 400.f);

			RandomLocation += FVector(0.f, 0.f, 150.f);
			
			AWBEnemyCharacter* SpawnedEnemy = GetWorld()->SpawnActor<AWBEnemyCharacter>(LoadedEnemyClass, RandomLocation, SpawnRotation, SpawnParameters);

			if (IsValid(SpawnedEnemy))
			{
				SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnEnemyDestroyed);
				
				EnemiesSpawnedThisTime++;
				TotalSpawnedEnemiesThisWaveCounter++;
			}

			if (!ShouldKeepSpawningEnemies())
			{
				return EnemiesSpawnedThisTime;
			}
		}
	}

	return EnemiesSpawnedThisTime;
}

bool AWBSurvivalGameMode::ShouldKeepSpawningEnemies() const
{
	return TotalSpawnedEnemiesThisWaveCounter < GetCurrentWaveSpawnerTableRow()->TotalEnemyToSpawnThisWave;
}

void AWBSurvivalGameMode::OnEnemyDestroyed(AActor* DestroyedActor)
{
	CurrentSpawnedEnemiesCounter--;

	if (ShouldKeepSpawningEnemies())
	{
		CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();
	}
	else if (CurrentSpawnedEnemiesCounter == 0)
	{
		TotalSpawnedEnemiesThisWaveCounter = 0;
		CurrentSpawnedEnemiesCounter = 0;
		SetCurrentSurvivalGameModeState(EWBSurvivalGameModeState::WaveCompleted);
	}
}

void AWBSurvivalGameMode::RegisterSpawnedEnemies(const TArray<AWBEnemyCharacter*>& InEnemiesToRegister)
{
	if (InEnemiesToRegister.IsEmpty()) return;

	for (const auto& SpawnedEnemy : InEnemiesToRegister)
	{
		if (IsValid(SpawnedEnemy))
		{
			CurrentSpawnedEnemiesCounter++;

			SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnEnemyDestroyed);
		}
	}
}
