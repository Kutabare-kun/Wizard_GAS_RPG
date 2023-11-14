#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	SetDepthAndStencil(GetMesh(), true, CUSTOM_DEPTH_RED);
	SetDepthAndStencil(Weapon, true, CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighlightActor()
{
	SetDepthAndStencil(GetMesh(), false, 0);
	SetDepthAndStencil(Weapon, false, 0);
}

void AAuraEnemy::SetDepthAndStencil(USkeletalMeshComponent* SkeletalMeshComp, bool bHighlighted, int32 Value)
{
	if (SkeletalMeshComp)
	{
		SkeletalMeshComp->SetRenderCustomDepth(bHighlighted);
		SkeletalMeshComp->SetCustomDepthStencilValue(Value);
	}
}
