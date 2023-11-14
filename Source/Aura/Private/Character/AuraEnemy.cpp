#include "Character/AuraEnemy.h"

void AAuraEnemy::HighlightActor()
{
	bHighlighted = true;

	UE_LOG(LogTemp, Log, TEXT("[%s], Highlighted: %s"), *GetNameSafe(this), bHighlighted ? TEXT("TRUE") : TEXT("FALSE"));
}

void AAuraEnemy::UnHighlightActor()
{
	bHighlighted = false;

	UE_LOG(LogTemp, Log, TEXT("[%s], Highlighted: %s"), *GetNameSafe(this), bHighlighted ? TEXT("TRUE") : TEXT("FALSE"));
}
