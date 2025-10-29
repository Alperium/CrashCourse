// Copyright Alperium 2025

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Components/WidgetComponent.h"
#include "CC_WidgetComponent.generated.h"

class UAbilitySystemComponent;
class UCC_Attributes;
class UCC_ASC;
class ACC_BaseCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRASHCOURSE_API UCC_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UCC_WidgetComponent();

protected:
	virtual void BeginPlay() override;

	// An array of TTuple's is called a TMap
	// List of the attribute and max attributes this widget is responsible with handling
	UPROPERTY(EditAnywhere)
	TMap<FGameplayAttribute, FGameplayAttribute> AttributeMap;

private:

	void InitGASData();

	UFUNCTION()
	void OnGASReady();

	UFUNCTION()
	void BindToAttributeChanges();

	void BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair);

	bool bAlreadyBoundAttributeChanges = false;

	TWeakObjectPtr<ACC_BaseCharacter> CrashCharacter;
	TWeakObjectPtr<UCC_ASC> ASC;
	TWeakObjectPtr<UCC_Attributes> Attributes;
};
