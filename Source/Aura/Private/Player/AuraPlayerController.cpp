


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	LastActor = nullptr, CurrentActor = nullptr;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Will halt execution if this condition is false (i.e. AuraContext == nullptr)
	check(AuraContext);

	//add the mapping context to the input subsystem
	if(auto *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	
	//don't hide cursor
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//configure mouse input behavior
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	auto *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(auto *ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if(!CursorHit.bBlockingHit) return;

	LastActor = CurrentActor;
	//if this cast succeeds, then the hit result implements the IEnemyInterface
	//if this cast fails, the result is nullptr
	CurrentActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/**
	 * Line trace from cursor. There are several scenarios:
	 * 1. LastActor is null and CurrentActor is null
	 *		- Do nothing
	 * 2. LastActor is null and CurrentActor is valid
	 *		- Highlight CurrentActor
	 * 3. LastActor is valid and CurrentActor is null
	 *		- Unhighlight LastActor
	 * 4. LastActor is valid and CurrentActor is valid, but LastActor != CurrentActor
	 *		- Unhighlight LastActor
	 *		- Highlight CurrentActor
	 * 5. LastActor is valid and CurrentActor is valid, and LastActor == CurrentActor
	 *		- Do nothing
	 */

	if(CurrentActor != LastActor)
	{
		if(LastActor) LastActor->ToggleHighlightActor();
		if(CurrentActor) CurrentActor->ToggleHighlightActor();
	}
}
