// Fillipe Romero - All Rights Reserved

#include "Character/WBHeroCharacter.h"
#include "WBDebugHelper.h"

AWBHeroCharacter::AWBHeroCharacter()
{
}

void AWBHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	Debug::Print(TEXT("Hero Character Working"));
}
