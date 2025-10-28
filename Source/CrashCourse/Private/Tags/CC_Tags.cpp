#include "Tags/CC_Tags.h"

namespace CCTags
{
	namespace CCAbilities
	{
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(PrimaryAbility, "CCTags.CCAbilities.Player.Primary", "Gameplay tag to identify the player's primary UGameplayAbility")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(SecondaryAbility, "CCTags.CCAbilities.Player.Secondary", "Gameplay tag to identify the player's Secondary UGameplayAbility")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TertiaryAbility, "CCTags.CCAbilities.Player.Tertiary", "Gameplay tag to identify the player's Tertiary UGameplayAbility")
		}

		namespace Enemy
		{
			
		}
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "CCTags.CCAbilities.ActivateOnGiven", "Any gameplay ability which has this tag will be activated immediately after it's given")
	}

	namespace CCEvents
	{
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(EnemyHitReact, "CCTags.CCEvents.Enemy.HitReact", "Tag for the event published for enemies to perform their HitReact ability")
		}
	}
}
