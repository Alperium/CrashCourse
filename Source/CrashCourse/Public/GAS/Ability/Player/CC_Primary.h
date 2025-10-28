// Copyright Alperium 2025

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/CC_GameplayAbility.h"
#include "CC_Primary.generated.h"

/**
 * 
 */
UCLASS()
class CRASHCOURSE_API UCC_Primary : public UCC_GameplayAbility
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable, Category = "Crash|Ability")
	TArray<AActor*> HitBoxOverlapTest();

	UFUNCTION(BlueprintCallable, Category = "Crash|Ability")
	void SendHitReactEventToActors(const TArray<AActor*>& Actors);

private:
	
	void DebugOverlap(const TArray<FOverlapResult>& OverlapResults, const FVector& OverlapCenterLocation) const;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Ability|Hitbox")
	float HitBoxRadius = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Ability|Hitbox")
	float HitBoxForwardOffset = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Crash|Ability|Hitbox")
	float HitBoxElevationOffset = 20.f;
};
