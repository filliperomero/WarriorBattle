// Fillipe Romero - All Rights Reserved

#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "WBGameplayTags.h"
#include "AbilitySystem/WBAttributeSet.h"

struct FWBDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FWBDamageCapture()
	{
		// Source
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWBAttributeSet, AttackPower, Source, false);

		// Target
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWBAttributeSet, DefensePower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWBAttributeSet, DamageTaken, Target, false);
	}
};

static const FWBDamageCapture& GetWBDamageCapture()
{
	static FWBDamageCapture WBDamageCapture;

	return WBDamageCapture;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(GetWBDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetWBDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetWBDamageCapture().DamageTakenDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWBDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);

	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(WBGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
		}

		if (TagMagnitude.Key.MatchesTagExact(WBGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
		}

		if (TagMagnitude.Key.MatchesTagExact(WBGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
		}
	}
	
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWBDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);

	if (UsedLightAttackComboCount != 0)
	{
		const float DamageIncreasedPercentLight = (UsedLightAttackComboCount - 1) * 0.05f + 1.f;
		
		BaseDamage *= DamageIncreasedPercentLight;
	}

	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasedPercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;
		
		BaseDamage *= DamageIncreasedPercentHeavy;
	}

	// TODO: Put some restrains to the AttackPower/DefensePower using FMath::Max
	const float FinalDamage = BaseDamage * SourceAttackPower / TargetDefensePower;

	if (FinalDamage > 0.f)
	{
		const FGameplayModifierEvaluatedData EvaluatedData(GetWBDamageCapture().DamageTakenProperty, EGameplayModOp::Override, FinalDamage);
		OutExecutionOutput.AddOutputModifier(EvaluatedData);
	}
}
