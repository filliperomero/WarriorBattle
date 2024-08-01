// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WBBaseAnimInstance.h"
#include "WBHeroLinkedAnimLayer.generated.h"

class UWBHeroAnimInstance;

UCLASS()
class WARRIORBATTLE_API UWBHeroLinkedAnimLayer : public UWBBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UWBHeroAnimInstance* GetHeroAnimInstance() const;
};
