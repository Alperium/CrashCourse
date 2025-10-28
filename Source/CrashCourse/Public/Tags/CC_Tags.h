#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace CCTags
{
	namespace CCAbilities
	{
		namespace Player
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(PrimaryAbility);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(SecondaryAbility);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(TertiaryAbility);
		}

		namespace Enemy
		{
			
		}
		
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ActivateOnGiven);
	}

	namespace CCEvents
	{
		namespace Enemy
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(EnemyHitReact)
		}
	}
}