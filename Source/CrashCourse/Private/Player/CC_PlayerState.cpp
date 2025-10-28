// Copyright Alperium 2025


#include "CrashCourse/Public/Player/CC_PlayerState.h"
#include "GAS/CC_ASC.h"

ACC_PlayerState::ACC_PlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCC_ASC>("ASC");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	SetNetUpdateFrequency(100.f);
}
