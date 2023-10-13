

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

protected:
	virtual void BeginPlay() override;

	/*
	 * TObjectPtr is relatively new. In packaged build, it is the sam as a raw pointer.
	 * But in editor, it has access tracking and optional lazy load features.
	 * Access tracking lets us know how much a pointer is accessed and how often.
	 * Lazy loading will keep the memory unload until it is really needed
	 */
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

};
