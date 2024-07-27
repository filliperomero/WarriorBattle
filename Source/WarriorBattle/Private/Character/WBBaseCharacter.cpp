// Fillipe Romero - All Rights Reserved

#include "Character/WBBaseCharacter.h"

AWBBaseCharacter::AWBBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;
}
