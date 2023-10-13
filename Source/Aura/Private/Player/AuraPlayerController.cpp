


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Will halt execution if this condition is false (i.e. AuraContext == nullptr)
	check(AuraContext);
	auto *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	//add the mapping context to the input subsystem
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	//don't hide cursor
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//configure mouse input behavior
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}
