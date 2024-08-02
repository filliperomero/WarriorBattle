// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WBFunctionLibrary.generated.h"

struct FGameplayTag;
class UWBAbilitySystemComponent;

UENUM()
enum class EWBConfirmType : uint8
{
	Yes,
	No
};

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
};
 