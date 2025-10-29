// Copyright Alperium 2025

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CC_BaseCharacter.generated.h"

class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGASReady);

UCLASS(Abstract) // Keyword Abstract implies this class will not be directly instantiated from the game or the editor
class CRASHCOURSE_API ACC_BaseCharacter : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACC_BaseCharacter();

	// This interface override is overriden here to make both player and npc classes be able to override it in their own way
	// Since it's expected for those classes to override this, we return nullptr here
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return nullptr; }

	virtual UAttributeSet* GetAttributeSet() const { return nullptr; }

	FGASReady OnGASReady;

protected:

	virtual void InitializeGAS();

	void GiveStartupAbilities();
	void InitializeAttributes();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
	TSubclassOf<UGameplayEffect> InitializeAttributeEffect;
};
