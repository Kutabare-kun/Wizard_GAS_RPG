#include "Character/AuraEnemy.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/Widgets/AuraUserWidget.h"

AAuraEnemy::AAuraEnemy()
{
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("AttributeSet"));

    HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
    HealthBarWidget->SetupAttachment(GetRootComponent());
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
    if (!SkeletalMeshComp) return;

    SkeletalMeshComp->SetRenderCustomDepth(bHighlighted);
    SkeletalMeshComp->SetCustomDepthStencilValue(Value);
}

int32 AAuraEnemy::GetPlayerLevel() const
{
    return Level;
}

void AAuraEnemy::Die()
{
    SetLifeSpan(LifeSpan);

    Super::Die();
}

void AAuraEnemy::InitHealthBar()
{
    if (UAuraUserWidget* AuraUserWidget = Cast<UAuraUserWidget>(HealthBarWidget->GetUserWidgetObject()))
    {
        AuraUserWidget->SetWidgetController(this);
    }

    if (const UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AttributeSet))
    {
        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(
            [this](const FOnAttributeChangeData& Data)
            {
                OnHealthChanged.Broadcast(Data.NewValue);
            }
        );

        AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(
            [this](const FOnAttributeChangeData& Data)
            {
                OnMaxHealthChanged.Broadcast(Data.NewValue);
            }
        );

        OnHealthChanged.Broadcast(AuraAS->GetHealth());
        OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
    }
}

void AAuraEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
    bHitReacting = NewCount > 0;
    GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.0f : BaseWalkSpeed;
}

void AAuraEnemy::BeginPlay()
{
    Super::BeginPlay();

    GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;

    UAuraAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);

    InitAbilityActorInfo();
    InitHealthBar();

    AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Effects_HitReact,
                                                     EGameplayTagEventType::NewOrRemoved).AddUObject(
        this, &AAuraEnemy::HitReactTagChanged
    );
}

void AAuraEnemy::InitAbilityActorInfo()
{
    AbilitySystemComponent->InitAbilityActorInfo(this, this);
    Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

    InitializeDefaultAttributes();
}

void AAuraEnemy::InitializeDefaultAttributes() const
{
    UAuraAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
