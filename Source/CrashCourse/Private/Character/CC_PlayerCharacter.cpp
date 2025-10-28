// Copyright Alperium 2025
#include "CrashCourse/Public/Character/CC_PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/CC_PlayerState.h"

ACC_PlayerCharacter::ACC_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(40.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	UCharacterMovementComponent* CharMov = GetCharacterMovement();
	CharMov->bOrientRotationToMovement = true;
	CharMov->RotationRate = FRotator(0.f, 540.f, 0.f);
	CharMov->JumpZVelocity = 500.f;
	CharMov->AirControl = 0.35f;
	CharMov->MaxWalkSpeed = 500.f;
	CharMov->MinAnalogWalkSpeed = 20.f;
	CharMov->BrakingDecelerationWalking = 2000.f;
	CharMov->BrakingDecelerationFalling = 1500.f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 600.f;
	SpringArm->bUsePawnControlRotation = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
	
}

UAbilitySystemComponent* ACC_PlayerCharacter::GetAbilitySystemComponent() const
{
	const ACC_PlayerState* PS = Cast<ACC_PlayerState>(GetPlayerState());
	if (!IsValid(PS)) return nullptr;

	return PS->GetAbilitySystemComponent();
}

void ACC_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!IsValid(ASC)) return;
	if (!HasAuthority()) return;

	ASC->InitAbilityActorInfo(GetPlayerState(), this);
	GiveStartupAbilities();
}

void ACC_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!IsValid(ASC)) return;

	ASC->InitAbilityActorInfo(GetPlayerState(), this);
}

