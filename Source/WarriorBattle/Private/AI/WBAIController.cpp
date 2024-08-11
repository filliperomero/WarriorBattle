// Fillipe Romero - All Rights Reserved

#include "AI/WBAIController.h"

#include "WBDebugHelper.h"
#include "Navigation/CrowdFollowingComponent.h"

AWBAIController::AWBAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	if (UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		Debug::Print(TEXT("CrowdFollowingComponent valid"), FColor::Green);
	}
}
