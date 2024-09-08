// Fillipe Romero - All Rights Reserved

#include "Item/Pickup/WBPickupBase.h"

#include "Components/SphereComponent.h"

AWBPickupBase::AWBPickupBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	PickupCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickupCollisionSphere"));
	SetRootComponent(PickupCollisionSphere);
	PickupCollisionSphere->InitSphereRadius(50.f);
}

void AWBPickupBase::BeginPlay()
{
	Super::BeginPlay();

	PickupCollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnPickupCollisionSphereOverlap);
}

void AWBPickupBase::OnPickupCollisionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
