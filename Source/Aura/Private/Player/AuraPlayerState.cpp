


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraPlayerState::AAuraPlayerState()
{
	/**
	 * Since the ability system component might contain information that we want to
	 * have persist beyond one life of a player, we need to attach the player's ability
	 * system component to something more persistent than the player class itself. If
	 * we just had it on the player class itself, when the player died or respawned, or
	 * otherwise needed to be reinstanciated, the ability system component would reset, and
	 * any desired persistent information would be cleared. Since the player state is
	 * persistent throughout the entire gameplay, storing the ability system component for
	 * the player here is a much better idea. 
	*/

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	/**
	 *		+------------------+-------------------+-------------------------------+
	 *		| Replication Mode | Use Case	       | Description				   |
	 *		+------------------+-------------------+-------------------------------+
	 *		| Full			   | Single Player     | Gameplay Effects are		   |
	 *		|				   |			       | replicated to all clients	   |
	 *		+------------------+-------------------+-------------------------------+
	 *		| Mixed			   | Multiplayer,	   | Gameplay Effects are		   |
	 *		|				   | Player-Controlled | replicated to the owning      |
	 *		|				   |				   | client only. Gameplay Cues    |
	 *		|				   |				   | and Gameplay Tags replicated. |
	 *		|				   |				   | to all clients.			   |
	 *		+------------------+-------------------+-------------------------------+
	 *		| Minimal		   | Multiplayer,	   | Gameplay Effects are		   |
	 *		|				   | AI-Controlled	   | NOT replicated. Gameplay	   |
	 *		|				   |				   | Cues and Gameplay Tags		   |
	 *		|				   |				   | replicated to all clients	   |
	 *		+------------------+-------------------+-------------------------------+
	 */
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	
	//how often will the server try and update clients
	//as changes happen on the server for the player state, the server sends updates to all clients
	//any replicated variables will be updated at an attempted rate of NetUpdateFrequency
	//Lyra and Fortnite player state (with ability system component on player state) updates at ~100
	NetUpdateFrequency = 100.f;

	
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
