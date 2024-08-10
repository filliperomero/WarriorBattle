// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnUIInterface.generated.h"

class UEnemyUIComponent;
class UHeroUIComponent;
class UPawnUIComponent;
// This class does not need to be modified.
UINTERFACE()
class UPawnUIInterface : public UInterface
{
	GENERATED_BODY()
};

class WARRIORBATTLE_API IPawnUIInterface
{
	GENERATED_BODY()

public:
	virtual UPawnUIComponent* GetPawnUIComponent() const = 0;
	virtual UHeroUIComponent* GetHeroUIComponent() const;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const;
};
