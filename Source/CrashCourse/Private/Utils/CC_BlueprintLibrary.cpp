// Copyright Alperium 2025


#include "Utils/CC_BlueprintLibrary.h"

EHitDirection UCC_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigatorNormal)
{
	constexpr float Cos45 = 0.70710678;

	const float ForwardDot = FVector::DotProduct(TargetForward, ToInstigatorNormal);
	
	if (ForwardDot >= Cos45) return EHitDirection::Forward;
	if (ForwardDot <= -Cos45) return EHitDirection::Back;

	const FVector TargetRight = FVector::CrossProduct(TargetForward, FVector::UpVector);
	const float RightDot = FVector::DotProduct(ToInstigatorNormal, TargetRight);

	if (RightDot >= Cos45) return EHitDirection::Right;
	if (RightDot <= -Cos45) return EHitDirection::Left;

	// Function will never reach here
	return EHitDirection::Forward;
}

FName UCC_BlueprintLibrary::GetHitDirectionName(const EHitDirection& HitDirection)
{
	switch (HitDirection)
	{
		case EHitDirection::Forward: return FName("Forward");
		case EHitDirection::Back: return FName("Back");
		case EHitDirection::Right: return FName("Right");
		case EHitDirection::Left: return FName("Left");
		default: return FName("Unknown");
	}
}
