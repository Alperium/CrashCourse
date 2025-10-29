// Copyright Alperium 2025

#include "GAS/CC_ASC.h"

#include "Tags/CC_Tags.h"

UCC_ASC::UCC_ASC()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCC_ASC::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);

	if (!IsValid(AbilitySpec.Ability)) return;
	HandleAutoActivateAbility(AbilitySpec);
}

void UCC_ASC::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	FScopedAbilityListLock ActiveScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		HandleAutoActivateAbility(AbilitySpec);
	}
}

void UCC_ASC::SetAbilityLevel(const TSubclassOf<UGameplayAbility> AbilityClass, const int32 NewLevel)
{
	if (IsValid(GetAvatarActor()) && !GetAvatarActor()->HasAuthority()) return;

	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass);
	if (!AbilitySpec) return;

	AbilitySpec->Level = NewLevel;
	MarkAbilitySpecDirty(*AbilitySpec);
}

void UCC_ASC::IncreaseAbilityLevel(const TSubclassOf<UGameplayAbility> AbilityClass, const int32 IncreaseAmount)
{
	if (IsValid(GetAvatarActor()) && !GetAvatarActor()->HasAuthority()) return;

	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass);
	if (!AbilitySpec) return;

	AbilitySpec->Level += IncreaseAmount;
	MarkAbilitySpecDirty(*AbilitySpec);
}

void UCC_ASC::HandleAutoActivateAbility(const FGameplayAbilitySpec& AbilitySpec)
{
	// Similar behaviour could be achieved by giving the ability with GiveAbilityAndActivateOnce too
	// But that function results with ability being removed from ASC when it ends
	if (AbilitySpec.Ability->GetAssetTags().HasTagExact(CCTags::CCAbilities::ActivateOnGiven))
	{
		TryActivateAbility(AbilitySpec.Handle);
	}
}
