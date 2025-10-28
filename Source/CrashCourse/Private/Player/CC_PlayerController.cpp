// Copyright Alperium 2025


#include "CrashCourse/Public/Player/CC_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Tags/CC_Tags.h"

void ACC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubsystem)) return;

	for (TObjectPtr<UInputMappingContext> Context : InputContexts)
	{
		InputSubsystem->AddMappingContext(Context, 0);
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::StartJump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJump);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	
	EnhancedInputComponent->BindAction(PrimaryAbilityAction, ETriggerEvent::Triggered, this, &ThisClass::PrimaryAbility);
	EnhancedInputComponent->BindAction(SecondaryAbilityAction, ETriggerEvent::Started, this, &ThisClass::SecondaryAbility);
	EnhancedInputComponent->BindAction(TertiaryAbilityAction, ETriggerEvent::Started, this, &ThisClass::TertiaryAbility);
}

void ACC_PlayerController::ActivateAbility(const FGameplayTag& AbilityTag) const
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (!IsValid(ASC)) return;

	ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
}

void ACC_PlayerController::StartJump()
{
	if (!IsValid(GetCharacter())) return;

	GetCharacter()->Jump();
}

void ACC_PlayerController::StopJump()
{
	if (!IsValid(GetCharacter())) return;

	GetCharacter()->StopJumping();
}

void ACC_PlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn())) return;
	
	const FVector2D MoveInput = Value.Get<FVector2D>();

	// Find which way is forward
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.0f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(ForwardDirection, MoveInput.X);
	GetPawn()->AddMovementInput(RightDirection, MoveInput.Y);
}

void ACC_PlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookInput = Value.Get<FVector2D>();

	AddYawInput(LookInput.X);
	AddPitchInput(LookInput.Y);
}

void ACC_PlayerController::PrimaryAbility()
{
	ActivateAbility(CCTags::CCAbilities::Player::PrimaryAbility);
}

void ACC_PlayerController::SecondaryAbility()
{
	ActivateAbility(CCTags::CCAbilities::Player::SecondaryAbility);
}

void ACC_PlayerController::TertiaryAbility()
{
	ActivateAbility(CCTags::CCAbilities::Player::TertiaryAbility);
}
