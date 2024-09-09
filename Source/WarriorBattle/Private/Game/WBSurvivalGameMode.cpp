// Fillipe Romero - All Rights Reserved

#include "Game/WBSurvivalGameMode.h"

void AWBSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();

	checkf(EnemyWaveSpawnerDataTable, TEXT("Forgot to assign a valid Data Table in Survival Game Mode BP"))

	SetCurrentSurvivalGameModeState(EWBSurvivalGameModeState::WaitSpawnNewWave);

	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();
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
			// TODO: Handle Spawn New Enemies

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
