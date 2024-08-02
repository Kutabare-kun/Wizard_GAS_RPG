#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UMotionWarpingComponent;
class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAnimMontage;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase
    : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
    GENERATED_BODY()

public:
    AAuraCharacterBase();

    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    UAttributeSet* GetAttributeSet() const { return AttributeSet; }

    // Combat Interface
    virtual UAnimMontage* GetHitReactMontage_Implementation() override;
    virtual void Die() override;
    // ~Combat Interface

    UFUNCTION(NetMulticast, Reliable)
    virtual void MulticastHandleDeath();

protected:
    virtual void BeginPlay() override;

    virtual void InitAbilityActorInfo();

    void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

    virtual void InitializeDefaultAttributes() const;

    void AddCharacterAbilities();

    // Combat Interface
    virtual FVector GetCombatSocketLocation() const override;

    virtual void UpdateFacingTarget_Implementation(const FVector& Target) override;
    // ~Combat Interface

    // Dissolve Effects
    void Dissolve();

    UFUNCTION(BlueprintImplementableEvent)
    void StartMeshDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

    UFUNCTION(BlueprintImplementableEvent)
    void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);
    // ~Dissolve Effects

    UPROPERTY(EditAnywhere, Category = "Combat")
    FName WeaponTipSocketName;

    UPROPERTY(EditAnywhere, Category = "Combat")
    TObjectPtr<USkeletalMeshComponent> Weapon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UMotionWarpingComponent> MotionWarpingComp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Motion Warping")
    FName WarpTargetName;

    UPROPERTY()
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
    TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
    TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
    TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

    // Dissolve Effects
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dissolve")
    TObjectPtr<UMaterialInstance> MeshDissolveMaterialInstance;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dissolve")
    TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;
    // ~Dissolve Effects

private:
    UPROPERTY(EditAnywhere, Category = "Abilities")
    TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

    UPROPERTY(EditAnywhere, Category = "Combat")
    TObjectPtr<UAnimMontage> HitReactMontage;
};
