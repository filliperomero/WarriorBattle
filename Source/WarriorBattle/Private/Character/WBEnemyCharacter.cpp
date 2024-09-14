// Fillipe Romero - All Rights Reserved

#include "Character/WBEnemyCharacter.h"

#include "WBFunctionLibrary.h"
#include "Component/Combat/EnemyCombatComponent.h"
#include "Component/UI/EnemyUIComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "DataAsset/StartUpData/DataAsset_EnemyStartUpData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/AssetManager.h"
#include "Game/WBGameMode.h"
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

	LeftHandCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftHandCollisionBox"));
	LeftHandCollisionBox->SetupAttachment(GetMesh());
	LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	RightHandCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("RightHandCollisionBox"));
	RightHandCollisionBox->SetupAttachment(GetMesh());
	RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

	LeftHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
	RightHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
}

void AWBEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Enemy Startup Data Asynchronous
	InitEnemyStartupData();
}

#if WITH_EDITOR
void AWBEnemyCharacter::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftHandCollisionBoxAttachBoneName))
	{
		LeftHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftHandCollisionBoxAttachBoneName);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightHandCollisionBoxAttachBoneName))
	{
		RightHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandCollisionBoxAttachBoneName);
	}
}
#endif

void AWBEnemyCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UWBFunctionLibrary::IsTargetPawnHostile(this, HitPawn))
		{
			EnemyCombatComponent->OnHitTargetActor(HitPawn);
		}
	}
}

void AWBEnemyCharacter::InitEnemyStartupData()
{
	if (CharacterStartUpData.IsNull()) return;
	
	int32 AbilityApplyLevel = 1;
			
	if (AWBGameMode* GameMode = GetWorld()->GetAuthGameMode<AWBGameMode>())
	{
		switch (GameMode->GetCurrentGameDifficulty()) {
		case EGameDifficulty::Easy:
			AbilityApplyLevel = 1;
			break;
		case EGameDifficulty::Normal:
			AbilityApplyLevel = 2;
			break;
		case EGameDifficulty::Hard:
			AbilityApplyLevel = 3;
			break;
		case EGameDifficulty::VeryHard:
			AbilityApplyLevel = 4;
			break;
		}
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[AbilityApplyLevel, this]()
			{
				if (UDataAsset_BaseStartUpData* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(WBAbilitySystemComponent, AbilityApplyLevel);
				}
			}
		)
	);
}
