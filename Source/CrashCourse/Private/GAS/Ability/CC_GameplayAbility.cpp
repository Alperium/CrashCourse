// Copyright Alperium 2025


#include "GAS/Ability/CC_GameplayAbility.h"

void UCC_GameplayAbility::ActivateAbility(	const FGameplayAbilitySpecHandle Handle,
											const FGameplayAbilityActorInfo* ActorInfo,
											const FGameplayAbilityActivationInfo ActivationInfo,
											const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
