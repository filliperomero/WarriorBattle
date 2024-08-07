// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WBBaseCharacter.h"
#include "WBEnemyCharacter.generated.h"

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

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, Category = Combat)
	TObjectPtr<UEnemyCombatComponent> EnemyCombatComponent;

private:
	void InitEnemyStartupData();
	
public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};
