

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

/**
 * Attribute accessors macro that sets up the getters, setter, and initter for each attribute.
 * We do this so that instead of having to write out each of the four lines in this macro,
 * we can just call this once and it will set up all four functions for us in one line.
 * This macro is included on AttributeSet.h with more comments and information. We can
 * see this by right-clicking on any one of the GAMEPLAYATTRIBUTE_ lines, go to definition
 * or declaration, and then scrolling up a bit to see this macro and more information.
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

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

public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Health Attribute **/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category="Character Attributes|Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData &OldHealth) const;


	/** MaxHealth Attribute **/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category="Character Attributes|Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData &OldMaxHealth) const;

	
	/** Mana Attribute **/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category="Character Attributes|Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData &OldMana) const;

	
	/** MaxMana Attribute **/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category="Character Attributes|Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData &OldMaxMana) const;
};
