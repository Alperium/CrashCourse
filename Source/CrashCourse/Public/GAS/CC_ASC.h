// Copyright Alperium 2025

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CC_ASC.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRASHCOURSE_API UCC_ASC : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UCC_ASC();

	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;

	virtual void OnRep_ActivateAbilities() override;

private:

	void HandleAutoActivateAbility(const FGameplayAbilitySpec& AbilitySpec);
};
