

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"



/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	
	/** override from IEnemyInterface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	virtual void ToggleHighlightActor() override;
	/** end IEnemyInterface */

protected:
	virtual void BeginPlay() override;
	
private:
	void ToggleRenderDepth(USkeletalMeshComponent *HoveredSkeletalMesh);
};
