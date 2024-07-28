// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WBAbilitySystemComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARRIORBATTLE_API UWBAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UWBAbilitySystemComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
