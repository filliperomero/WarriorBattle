// Fillipe Romero - All Rights Reserved

#include "AbilitySystem/AbilityTask/ExecuteTaskOnTick.h"

UExecuteTaskOnTick::UExecuteTaskOnTick()
{
	bTickingTask = true;
}

UExecuteTaskOnTick* UExecuteTaskOnTick::ExecuteTaskOnTick(UGameplayAbility* OwningAbility)
{
	UExecuteTaskOnTick* Node = NewAbilityTask<UExecuteTaskOnTick>(OwningAbility);

	return Node;
}

void UExecuteTaskOnTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnAbilityTaskTick.Broadcast(DeltaTime);
	}
	else
	{
		EndTask();
	}
}
