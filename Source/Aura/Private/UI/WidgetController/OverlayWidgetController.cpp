


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"

/**
 * Scream out into the void, to whoever is listening, that we have these initial attribute values
 */
void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	const auto *AuraAttributes = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributes->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributes->GetMaxHealth());
}
