// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_OrientToTargetActor.generated.h"

UCLASS()
class WARRIORBATTLE_API UBTService_OrientToTargetActor : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_OrientToTargetActor();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = Target)
	FBlackboardKeySelector InTargetActorKey;

	UPROPERTY(EditAnywhere, Category = Target)
	float RotationInterpSpeed;
};
