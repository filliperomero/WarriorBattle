// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WBBaseWeapon.generated.h"

class UBoxComponent;

UCLASS()
class WARRIORBATTLE_API AWBBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWBBaseWeapon();

protected:
	UPROPERTY(VisibleAnywhere, Category = Weapons)
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = Weapons)
	TObjectPtr<UBoxComponent> WeaponCollisionBox;

public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }
};
