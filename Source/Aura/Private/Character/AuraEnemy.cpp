


#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	//if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Highlighting actor: %s"), *GetActorNameOrLabel()));

	ToggleRenderDepth(GetMesh());
	ToggleRenderDepth(Weapon);
}

void AAuraEnemy::UnHighlightActor()
{
	//if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Unhighlighting actor: %s"), *GetActorNameOrLabel()));

	ToggleRenderDepth(GetMesh());
	ToggleRenderDepth(Weapon);
}

void AAuraEnemy::ToggleHighlightActor()
{
	ToggleRenderDepth(GetMesh());
	ToggleRenderDepth(Weapon);
}

void AAuraEnemy::ToggleRenderDepth(USkeletalMeshComponent* HoveredSkeletalMesh)
{
	const bool bRenderCustom = HoveredSkeletalMesh->bRenderCustomDepth;
	HoveredSkeletalMesh->SetRenderCustomDepth(!bRenderCustom);
	HoveredSkeletalMesh->SetCustomDepthStencilValue(!bRenderCustom ? STENCIL_DEPTH_HIGHLIGHT : STENCIL_DEPTH_BLANK);
}
