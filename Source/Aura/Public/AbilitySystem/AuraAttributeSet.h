

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

/**
 * We could have multiple AttributeSets that each have different Attributes,
 * but if we did this we would need a new class for each AttributeSet.
 * It is perfectly acceptable to contain all Attributes on one AttributeSet.
 * Attributes take up negligible memory, so we could share one AttributeSet
 * across ALL classes in our project, and simply just use the Attributes we
 * need in each class.
 *
 * Attributes are numerical quantities associated with player information.
 * All Attributes are floats, and they're all of type FGameplayAttributeData.
 * The AttributeSet manages all Attributes. We can directly change the value of
 * Attributes, but GameplayEffects are made specifically to "properly" update
 * Attribute values.
 *
 * We can also use Prediction with GameplayEffects. Prediction means that the client
 * doesn't need to wait for the server's permission to change a value. The value can
 * change immediately client-side, and the server is informed of the change. The server
 * can roll back changes that are invalid.
 *
 * Attributes contain two values, a Base Value and a Current Value. The Current Value
 * is the Base Value with any temporary buffs and debuffs added. Thinking about the Base
 * Value as the "max" value is wrong. We should, instead, have a separate Attribute that
 * stores the "max" value of that Attribute. 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
};
