// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnCombatInterface.generated.h"

class UPawnCombatComponent;

UINTERFACE()
class UPawnCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class WARRIORBATTLE_API IPawnCombatInterface
{
	GENERATED_BODY()

public:
	virtual UPawnCombatComponent* GetPawnCombatComponent() const = 0;
};
