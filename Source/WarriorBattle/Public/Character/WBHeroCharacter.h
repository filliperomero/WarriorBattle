// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WBBaseCharacter.h"
#include "WBHeroCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class WARRIORBATTLE_API AWBHeroCharacter : public AWBBaseCharacter
{
	GENERATED_BODY()

public:
	AWBHeroCharacter();

protected:
	virtual void BeginPlay() override;

private:
	
#pragma region Components
	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<UCameraComponent> FollowCamera;

#pragma endregion 
};
