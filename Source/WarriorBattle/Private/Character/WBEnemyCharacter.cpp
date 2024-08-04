// Fillipe Romero - All Rights Reserved

#include "Character/WBEnemyCharacter.h"

#include "WBDebugHelper.h"
#include "Component/Combat/EnemyCombatComponent.h"
#include "DataAsset/StartUpData/DataAsset_EnemyStartUpData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/AssetManager.h"

AWBEnemyCharacter::AWBEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
}

void AWBEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Enemy Startup Data Assynchronous
	InitEnemyStartupData();
}

void AWBEnemyCharacter::InitEnemyStartupData()
{
	if (CharacterStartUpData.IsNull()) return;

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UDataAsset_BaseStartUpData* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(WBAbilitySystemComponent);
					
					Debug::Print(TEXT("Enemy Start Up Data Loaded"));
				}
			}
		)
	);
}
