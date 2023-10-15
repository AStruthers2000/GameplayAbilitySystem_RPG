


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
 	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	auto *TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	//if we don't have a target with an Ability System Component, fine, whatever
	//now, if we don't have a valid GameplayEffectClass, big crash-y time
	if(TargetASC == nullptr) return;
	check(GameplayEffectClass);
	
	auto ContextHandle = TargetASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	
	const auto SpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, ContextHandle);
	TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

