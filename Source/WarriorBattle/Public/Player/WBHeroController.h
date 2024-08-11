// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "WBHeroController.generated.h"

UCLASS()
class WARRIORBATTLE_API AWBHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AWBHeroController();

	/** GenericTeamAgent Interface */
	virtual FGenericTeamId GetGenericTeamId() const override;
	/** End GenericTeamAgent Interface */

private:
	FGenericTeamId HeroTeamId;
};
