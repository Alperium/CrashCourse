// Copyright Alperium 2025


#include "UI/CC_AttributeWidget.h"

void UCC_AttributeWidget::OnAttributeChange(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, UCC_Attributes* Attributes)
{
	const float AttributeValue = Pair.Key.GetNumericValue(Attributes);
	const float MaxAttributeValue = Pair.Value.GetNumericValue(Attributes);

	BP_OnAttributeChange(AttributeValue, MaxAttributeValue);
}

bool UCC_AttributeWidget::MatchesAttribute(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	return Attribute == Pair.Key && MaxAttribute == Pair.Value;
}
