// Copyright Alperium 2025


#include "Character/CC_EnemyCharacter.h"
#include "GAS/CC_ASC.h"
#include "GAS/CC_Attributes.h"

ACC_EnemyCharacter::ACC_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UCC_ASC>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<UCC_Attributes>("Attributes");
}

void ACC_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(AbilitySystemComponent)) return;

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	if (!HasAuthority()) return;

	InitializeGAS();
}

