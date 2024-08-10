// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WBBaseCharacter.h"
#include "WBEnemyCharacter.generated.h"

class UWidgetComponent;
class UEnemyUIComponent;
class UEnemyCombatComponent;

UCLASS()
class WARRIORBATTLE_API AWBEnemyCharacter : public AWBBaseCharacter
{
	GENERATED_BODY()

public:
	AWBEnemyCharacter();

	/** PawnCombat Interface*/
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	/** End PawnCombat Interface*/
	
	/** PawnUI Interface*/
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
	/** End IPawnUI Interface*/

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Combat)
	TObjectPtr<UEnemyCombatComponent> EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	TObjectPtr<UEnemyUIComponent> EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	TObjectPtr<UWidgetComponent> EnemyHealthWidgetComponent;

private:
	void InitEnemyStartupData();
	
public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
