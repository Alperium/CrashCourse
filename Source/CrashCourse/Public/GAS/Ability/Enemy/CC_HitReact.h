// Copyright Alperium 2025

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/CC_GameplayAbility.h"
#include "CC_HitReact.generated.h"

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCC_HitReact : public UCC_GameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Crash|Ability")
	void CacheHitDirectionVectors(const AActor* Instigator);
	
	UPROPERTY(BlueprintReadOnly, Category = "Crash|Ability")
	FVector AvatarForward;

	UPROPERTY(BlueprintReadOnly, Category = "Crash|Ability")
	FVector ToInstigatorNormalized;
};
