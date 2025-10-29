// Copyright Alperium 2025

#include "UI/CC_WidgetComponent.h"

#include "Blueprint/WidgetTree.h"
#include "Character/CC_BaseCharacter.h"
#include "GAS/CC_ASC.h"
#include "GAS/CC_Attributes.h"
#include "UI/CC_AttributeWidget.h"

UCC_WidgetComponent::UCC_WidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCC_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	InitGASData();

	if (!ASC.IsValid())
	{
		checkf(CrashCharacter.IsValid(), TEXT("Crash character object must be valid here!"))
		CrashCharacter->OnGASReady.AddDynamic(this, &UCC_WidgetComponent::OnGASReady);
	}
	else if (!Attributes.IsValid())
	{
		checkf(CrashCharacter.IsValid(), TEXT("Crash character object must be valid here!"))
		CrashCharacter->OnGASReady.AddDynamic(this, &UCC_WidgetComponent::OnGASReady);
	}
	else
	{
		BindToAttributeChanges();
	}
}

void UCC_WidgetComponent::InitGASData()
{
	CrashCharacter = Cast<ACC_BaseCharacter>(GetOwner());
	ASC = Cast<UCC_ASC>(CrashCharacter->GetAbilitySystemComponent());
	Attributes = Cast<UCC_Attributes>(CrashCharacter->GetAttributeSet());
}

void UCC_WidgetComponent::OnGASReady()
{
	InitGASData();
	BindToAttributeChanges();
}

void UCC_WidgetComponent::BindToAttributeChanges()
{
	if (bAlreadyBoundAttributeChanges) return;
	// Check the UUserWidget object owned by this component, see if it's a CC_AttributeWidget and handle it directly if so
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanges(GetUserWidgetObject(), Pair);

		// Otherwise, loop over all the children on the owned widget too if THEY are a CC_AttributeWidget
		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* InWidget)
		{
			BindWidgetToAttributeChanges(InWidget, Pair);
		});
	}
	bAlreadyBoundAttributeChanges = true;
}

void UCC_WidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair)
{
	UCC_AttributeWidget* AttributeWidget = Cast<UCC_AttributeWidget>(WidgetObject);
	if (!IsValid(AttributeWidget)) return; // We only care about CC_AttributeWidget's
	if (!AttributeWidget->MatchesAttribute(Pair)) return; // Only subscribe for matching Attributes

	AttributeWidget->OnAttributeChange(Pair, Attributes.Get()); // For initial values
	ASC->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([this, AttributeWidget, &Pair](const FOnAttributeChangeData& AttributeChangeData)
	{
		AttributeWidget->OnAttributeChange(Pair, Attributes.Get()); // For runtime value changes
	});
}

