// Fillipe Romero - All Rights Reserved

#include "Player/WBHeroController.h"

AWBHeroController::AWBHeroController()
{
	HeroTeamId = FGenericTeamId(0);
}

FGenericTeamId AWBHeroController::GetGenericTeamId() const
{
	return HeroTeamId;
}
