// Copyright Alperium 2025


#include "GAS/Ability/Player/CC_Primary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Engine/OverlapResult.h"
#include "Tags/CC_Tags.h"

TArray<AActor*> UCC_Primary::HitBoxOverlapTest()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);

	TArray<FOverlapResult> OverlapResults;

	const FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);

	const FVector AvatarLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector AvatarForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector OverlapCenterLocation = AvatarLocation + AvatarForward * HitBoxForwardOffset + FVector(0.f, 0.f, HitBoxElevationOffset);
	
	GetWorld()->OverlapMultiByChannel(OverlapResults, OverlapCenterLocation, FQuat::Identity, ECC_Visibility, Sphere, QueryParams, ResponseParams);
	if (bDebugMode) DebugOverlap(OverlapResults, OverlapCenterLocation);
	
	TArray<AActor*> OverlappedActors;
	for (const FOverlapResult& OverlapResult : OverlapResults)
	{
		if (IsValid(OverlapResult.GetActor())) OverlappedActors.AddUnique(OverlapResult.GetActor());
	}
	return OverlappedActors;
}

void UCC_Primary::SendHitReactEventToActors(const TArray<AActor*>& Actors)
{
	for (AActor* Actor : Actors)
	{
		if (!IsValid(Actor)) continue;
		FGameplayEventData Payload;
		Payload.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Actor, CCTags::CCEvents::Enemy::EnemyHitReact, Payload);
	}
}

void UCC_Primary::DebugOverlap(const TArray<FOverlapResult>& OverlapResults, const FVector& OverlapCenterLocation) const
{
	DrawDebugSphere(GetWorld(), OverlapCenterLocation, HitBoxRadius, 16, FColor::Red, false, 0.5);

	for (const FOverlapResult& OverlapResult : OverlapResults)
	{
		if (!IsValid(OverlapResult.GetActor())) continue;
		const FVector DebugLocation = OverlapResult.GetActor()->GetActorLocation() + FVector(0.f, 0.f, 10);
		DrawDebugSphere(GetWorld(), DebugLocation, 60, 16, FColor::Green, false, 0.5);
	}
}
