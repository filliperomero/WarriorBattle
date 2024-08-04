﻿// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARRIORBATTLE_API UEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
};
