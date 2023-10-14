


#include "Character/AuraCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

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
void AAuraCharacter::InitAbilityActorInfo()
{
	auto *AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AttributeSet = AuraPlayerState->GetAttributeSet();
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Init ability actor info for the server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init ability actor info for the client
	InitAbilityActorInfo();
}

