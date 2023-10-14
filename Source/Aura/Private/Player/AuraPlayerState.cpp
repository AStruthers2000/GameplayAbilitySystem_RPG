


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
	 *
	 *	Notes:
	 *		- For Mixed replication mode:
	 *			- The OwnerActor's Owner must be the Controller. For Pawns,
	 *			  this is set automatically in PossessedBy().
	 *			- The PlayerState's Owner is automatically set to the Controller
	 *			- Therefore, if your OwnerActor is not the PlayerState, and you use Mixed
	 *			  Replication Mode, you must call SetOwner() on the OwnerActor to set its owner
	 *			  to the Controller.
	 */
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	/**
	 * InitAbilityActorInfo
	 * 1. Calling InitAbilityActorInfo must be done after possession (aka the Controller has been set for the Pawn)
	 *		1a.	For a player controlled character, where the ASC lives on the Pawn itself (not like our case),
	 *			we could call this from PossessedBy on the pawn (server) and AcknowledgePossession (client)
	 *		1b. For player controlled character, where the ASC lives on the player state (like our case),
	 *			we could call PossessedBy on the pawn (server) and OnRep_PlayerState (client).
	 *			OnRep means this function is a rep-notify, a function that is called as a result
	 *			of something being replicated. In this case, the player state will be set on the server,
	 *			which is replicated, which will trigger the OnRep_PlayerState rep-notify, so the client
	 *			can be sure that the player state has been set and PlayerState is a valid pointer.
	 * 2. AI controlled character
	 *		2a. ASC lives on the pawn, we know the ASC is valid as is the controller, so we can call
	 *			this on BeginPlay
	 */
	
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
