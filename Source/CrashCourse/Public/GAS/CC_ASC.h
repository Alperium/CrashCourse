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

	UFUNCTION(BlueprintCallable)
	void SetAbilityLevel(const TSubclassOf<UGameplayAbility> AbilityClass, const int32 NewLevel);

	UFUNCTION(BlueprintCallable)
	void IncreaseAbilityLevel(const TSubclassOf<UGameplayAbility> AbilityClass, const int32 IncreaseAmount = 1);

private:

	void HandleAutoActivateAbility(const FGameplayAbilitySpec& AbilitySpec);
};
