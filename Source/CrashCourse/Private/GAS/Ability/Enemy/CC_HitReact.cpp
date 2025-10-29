// Copyright Alperium 2025


#include "GAS/Ability/Enemy/CC_HitReact.h"

void UCC_HitReact::CacheHitDirectionVectors(const AActor* Instigator)
{
	AvatarForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	ToInstigatorNormalized = (Instigator->GetActorLocation() - GetAvatarActorFromActorInfo()->GetActorLocation()).GetSafeNormal();
}
