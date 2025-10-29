// Copyright Alperium 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "CC_PlayerState.generated.h"

class UAttributeSet;
class UCC_ASC;

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API ACC_PlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ACC_PlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return Attributes; }

private:

	UPROPERTY(VisibleAnywhere, Category = "Crash|GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> Attributes;
};
