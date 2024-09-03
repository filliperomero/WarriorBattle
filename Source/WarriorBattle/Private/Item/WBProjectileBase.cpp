// Fillipe Romero - All Rights Reserved

#include "Item/WBProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "NiagaraComponent.h"
#include "WBFunctionLibrary.h"
#include "WBGameplayTags.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AWBProjectileBase::AWBProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollisionBox"));
	SetRootComponent(ProjectileCollisionBox);
	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileNiagaraComponent"));
	ProjectileNiagaraComponent->SetupAttachment(GetRootComponent());

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 550.f;
	ProjectileMovementComponent->MaxSpeed = 550.f;
	ProjectileMovementComponent->Velocity = FVector(1.f, 0, 0);
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 4.f;
}

void AWBProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if (ProjectileDamagePolicy == EProjectileDamagePolicy::OnBeginOverlap)
	{
		ProjectileCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnBeginOverlap);
		ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
	else
	{
		ProjectileCollisionBox->OnComponentHit.AddDynamic(this, &ThisClass::OnProjectileHit);
	}
}

void AWBProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);
	
	APawn* HitPawn = Cast<APawn>(OtherActor);

	if (!IsValid(HitPawn) || !UWBFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
	{
		Destroy();
		return;
	}

	bool bIsValidBlock = false;
	bool bIsPlayerBlocking = UWBFunctionLibrary::NativeDoesActorHaveTag(HitPawn, WBGameplayTags::Player_Status_Blocking);

	if (bIsPlayerBlocking)
	{
		bIsValidBlock = UWBFunctionLibrary::IsValidBlock(this, HitPawn);
	}

	FGameplayEventData Data;
	Data.Instigator = this;
	Data.Target = HitPawn;

	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitPawn, WBGameplayTags::Player_Event_SuccessfulBlock, Data);
	}
	else
	{
		HandleApplyProjectileDamage(HitPawn, Data);
	}

	Destroy();
}

void AWBProjectileBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedActors.Contains(OtherActor)) return;

	OverlappedActors.AddUnique(OtherActor);
	
	APawn* HitPawn = Cast<APawn>(OtherActor);

	if (!IsValid(HitPawn) || !UWBFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
	{
		return;
	}

	FGameplayEventData Data;
	Data.Instigator = this;
	Data.Target = HitPawn;
	
	HandleApplyProjectileDamage(HitPawn, Data);
}

void AWBProjectileBase::HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InEventData)
{
	checkf(ProjectileDamageSpecHandle.IsValid(), TEXT("Forgot to assign a valid spec handle to the projectile: %s"), *GetActorNameOrLabel());
	
	const bool bWasApplied = UWBFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), InHitPawn, ProjectileDamageSpecHandle);

	if (bWasApplied)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(InHitPawn, WBGameplayTags::Shared_Event_HitReact, InEventData);
	}
}
