// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"

class UWBUserWidgetBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARRIORBATTLE_API UEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(UWBUserWidgetBase* InWidgetToRegister);
	
	UFUNCTION(BlueprintCallable)
	bool RemoveEnemyDrawnWidget();

private:
	UPROPERTY()
	TArray<UWBUserWidgetBase*> EnemyDrawnWidgets;
};
