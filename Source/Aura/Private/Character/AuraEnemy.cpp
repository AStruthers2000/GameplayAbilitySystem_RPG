


#include "Character/AuraEnemy.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
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
