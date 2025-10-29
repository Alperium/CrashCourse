// Copyright Alperium 2025

#pragma once

#include "CoreMinimal.h"
#include "GAS/CC_Attributes.h"
#include "Blueprint/UserWidget.h"
#include "CC_AttributeWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCC_AttributeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crash|Attribute")
	FGameplayAttribute Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crash|Attribute")
	FGameplayAttribute MaxAttribute;

	// @param Attributes is required because the variables above are just identifiers
	// In order to get the real numerical value of any attribute, we need its identity and the attribute set it belongs to
	void OnAttributeChange(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, UCC_Attributes* Attributes);
	bool MatchesAttribute(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Attribute Change"))
	void BP_OnAttributeChange(const float NewValue, const float NewMaxValue);
};
