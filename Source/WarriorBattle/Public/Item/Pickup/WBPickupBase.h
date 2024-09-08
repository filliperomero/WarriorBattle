// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WBPickupBase.generated.h"

class USphereComponent;

UCLASS()
class WARRIORBATTLE_API AWBPickupBase : public AActor
{
	GENERATED_BODY()

public:
	AWBPickupBase();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pickup Interaction")
	TObjectPtr<USphereComponent> PickupCollisionSphere;

	UFUNCTION()
	virtual void OnPickupCollisionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
};
