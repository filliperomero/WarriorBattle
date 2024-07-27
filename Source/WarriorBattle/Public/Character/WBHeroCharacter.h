// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WBBaseCharacter.h"
#include "WBHeroCharacter.generated.h"

UCLASS()
class WARRIORBATTLE_API AWBHeroCharacter : public AWBBaseCharacter
{
	GENERATED_BODY()

public:
	AWBHeroCharacter();

protected:
	virtual void BeginPlay() override;
};
