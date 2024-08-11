// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "WBAIController.generated.h"

struct FAIStimulus;
class UAISenseConfig_Sight;

UCLASS()
class WARRIORBATTLE_API AWBAIController : public AAIController
{
	GENERATED_BODY()

public:
	AWBAIController(const FObjectInitializer& ObjectInitializer);

	/** GenericTeamAgent Interface */
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	/** End GenericTeamAgent Interface */

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAIPerceptionComponent> EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAISenseConfig_Sight> AISenseConfig_Sight;

	UFUNCTION()
	void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
