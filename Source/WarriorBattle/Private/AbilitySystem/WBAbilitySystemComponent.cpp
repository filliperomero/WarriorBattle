// Fillipe Romero - All Rights Reserved

#include "AbilitySystem/WBAbilitySystemComponent.h"

UWBAbilitySystemComponent::UWBAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWBAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWBAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

