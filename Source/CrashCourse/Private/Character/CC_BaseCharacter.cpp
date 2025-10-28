// Copyright Alperium 2025


#include "CrashCourse/Public/Character/CC_BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"

ACC_BaseCharacter::ACC_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Tick and refresh bone transforms whether the mesh is rendered or not
	// This allows gameplay mechanics involving anim notifies and dependent on bone positioning at a specific time to work with dedicated server setups
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
}

void ACC_BaseCharacter::GiveStartupAbilities()
{
	if (!HasAuthority()) return;
		
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!IsValid(ASC)) return;
	
	for (const TSubclassOf<UGameplayAbility>& Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		ASC->GiveAbility(AbilitySpec);
	}
}

