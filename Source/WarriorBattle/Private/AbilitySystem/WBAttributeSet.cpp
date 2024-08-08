// Fillipe Romero - All Rights Reserved

#include "AbilitySystem/WBAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "WBFunctionLibrary.h"
#include "WBGameplayTags.h"

UWBAttributeSet::UWBAttributeSet()
{
	InitHealth(1.f);
	InitMaxHealth(1.f);
	InitRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UWBAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetRageAttribute())
	{
		SetRage(FMath::Clamp(GetRage(), 0.f, GetMaxRage()));
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetHealth();
		const float IncomingDamage = GetDamageTaken();
		SetDamageTaken(0.f);

		// No damage taken
		if (IncomingDamage <= 0.f) return;

		const float NewHealth = FMath::Clamp(OldHealth - IncomingDamage, 0.f, GetMaxHealth());
		SetHealth(NewHealth);

		const bool bIsFatal = NewHealth <= 0.f;

		if (bIsFatal)
		{
			UWBFunctionLibrary::AddGameplayTagToActor(Data.Target.GetAvatarActor(), WBGameplayTags::Shared_Status_Dead);
		}
	}
}
