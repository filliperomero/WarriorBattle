// Fillipe Romero - All Rights Reserved

#include "Character/WBEnemyCharacter.h"

#include "Component/Combat/EnemyCombatComponent.h"
#include "Component/UI/EnemyUIComponent.h"
#include "Components/WidgetComponent.h"
#include "DataAsset/StartUpData/DataAsset_EnemyStartUpData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/AssetManager.h"
#include "UI/Widget/WBUserWidgetBase.h"

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
	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));
	
	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthWidgetComponent"));
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());
}

UPawnCombatComponent* AWBEnemyCharacter::GetPawnCombatComponent() const
{
	return GetEnemyCombatComponent();
}

UPawnUIComponent* AWBEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UEnemyUIComponent* AWBEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void AWBEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Initialize our Enemy Widget
	if (UWBUserWidgetBase* HealthWidget = Cast<UWBUserWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
}

void AWBEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Enemy Startup Data Asynchronous
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
				}
			}
		)
	);
}
