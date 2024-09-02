// Fillipe Romero - All Rights Reserved

#include "AbilitySystem/WBAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "WBFunctionLibrary.h"
#include "WBGameplayTags.h"
#include "Component/UI/HeroUIComponent.h"
#include "Component/UI/PawnUIComponent.h"
#include "Interface/PawnUIInterface.h"

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

	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());
	
	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();
	checkf(PawnUIComponent, TEXT("Couldn't extract a PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel())

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));

		PawnUIComponent->OnHealthChangedDelegate.Broadcast(GetHealth()/GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetRageAttribute())
	{
		SetRage(FMath::Clamp(GetRage(), 0.f, GetMaxRage()));

		if (GetRage() == GetMaxRage())
		{
			UWBFunctionLibrary::AddGameplayTagToActor(Data.Target.GetAvatarActor(), WBGameplayTags::Player_Status_Rage_Full);
		}
		else if (GetRage() <= 0.f)
		{
			UWBFunctionLibrary::AddGameplayTagToActor(Data.Target.GetAvatarActor(), WBGameplayTags::Player_Status_Rage_None);
		}
		else
		{
			UWBFunctionLibrary::RemoveGameplayTagFromActor(Data.Target.GetAvatarActor(), WBGameplayTags::Player_Status_Rage_Full);
			UWBFunctionLibrary::RemoveGameplayTagFromActor(Data.Target.GetAvatarActor(), WBGameplayTags::Player_Status_Rage_None);
		}

		if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnRageChangedDelegate.Broadcast(GetRage()/GetMaxRage());
		}
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

		PawnUIComponent->OnHealthChangedDelegate.Broadcast(NewHealth/GetMaxHealth());

		const bool bIsFatal = NewHealth <= 0.f;

		if (bIsFatal)
		{
			UWBFunctionLibrary::AddGameplayTagToActor(Data.Target.GetAvatarActor(), WBGameplayTags::Shared_Status_Dead);
		}
	}
}
