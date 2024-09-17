// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/WBEnumTypes.h"
#include "WBFunctionLibrary.generated.h"

class UWBGameInstance;
struct FGameplayEffectSpecHandle;
struct FScalableFloat;
class UPawnCombatComponent;
struct FGameplayTag;
class UWBAbilitySystemComponent;

UCLASS()
class WARRIORBATTLE_API UWBFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UWBAbilitySystemComponent* NativeGetWBASCFromActor(AActor* InActor);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category="WarriorBattle|FunctionLibrary")
	static void AddGameplayTagToActor(AActor* InActor, FGameplayTag TagToAdd);
	
	UFUNCTION(BlueprintCallable, Category="WarriorBattle|FunctionLibrary")
	static void RemoveGameplayTagFromActor(AActor* InActor, FGameplayTag TagToRemove);

	UFUNCTION(BlueprintCallable, Category="WarriorBattle|FunctionLibrary", meta=(DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWBConfirmType& OutConfirmType);
	
	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category="WarriorBattle|FunctionLibrary", meta=(DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EWBValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category="WarriorBattle|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category="WarriorBattle|FunctionLibrary", meta=(CompactNodeTitle = "Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, const float InLevel = 1.f);

	UFUNCTION(BlueprintPure, Category="WarriorBattle|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category="WarriorBattle|FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintCallable, Category="WarriorBattle|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category="WarriorBattle|FunctionLibrary", meta=(Latent, WorldContext = "WorldContextObject", LatentInfo="LatentInfo", ExpandEnumAsExecs="CountDownInput|CountDownOutput", TotalTime="1.0", UpdateInterval="0.1"))
	static void CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime, EWBCountDownActionInput CountDownInput, UPARAM(DisplayName="Output") EWBCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintPure, Category="WarriorBattle|FunctionLibrary", meta=(WorldContext = "WorldContextObject"))
	static UWBGameInstance* GetWBGameInstance(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category="WarriorBattle|FunctionLibrary", meta=(WorldContext = "WorldContextObject"))
	static void ToggleInputMode(const UObject* WorldContextObject, EWBInputMode InInputMode);
};
 