// Copyright Alperium 2025


#include "CrashCourse/Public/Character/CC_BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"

ACC_BaseCharacter::ACC_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Tick and refresh bone transforms whether the mesh is rendered or not
	// This allows gameplay mechanics involving anim notifies and dependent on bone positioning at a specific time to work with dedicated server setups
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

void ACC_BaseCharacter::InitializeGAS()
{
	GiveStartupAbilities();
	InitializeAttributes();
	OnGASReady.Broadcast();
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

void ACC_BaseCharacter::InitializeAttributes()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!IsValid(ASC) || !IsValid(InitializeAttributeEffect) || !HasAuthority()) return;

	const FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(InitializeAttributeEffect, 1.f, ContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

