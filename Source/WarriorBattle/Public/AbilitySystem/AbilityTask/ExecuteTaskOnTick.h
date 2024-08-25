// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "ExecuteTaskOnTick.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityTaskTickSignature, float, DeltaTime);

UCLASS()
class WARRIORBATTLE_API UExecuteTaskOnTick : public UAbilityTask
{
	GENERATED_BODY()

public:
	UExecuteTaskOnTick();
	
	UFUNCTION(BlueprintCallable, Category = "WarrioBattle|AbilityTasks", meta=(HidePin="OwningAbility", DefaultToSelf="OwningAbility", BlueprintInternalUseOnly="true"))
	static UExecuteTaskOnTick* ExecuteTaskOnTick(UGameplayAbility* OwningAbility);

	virtual void TickTask(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityTaskTickSignature OnAbilityTaskTick;
};
