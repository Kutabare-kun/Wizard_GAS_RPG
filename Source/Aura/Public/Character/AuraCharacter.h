#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UMotionWarpingComponent;

UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
    GENERATED_BODY()

public:
    AAuraCharacter();

    virtual void PossessedBy(AController* NewController) override;

    virtual void OnRep_PlayerState() override;

    // Combat Interface
    virtual int32 GetPlayerLevel() const override;
    // ~Combat Interface

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USpringArmComponent> SpringArmComp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UCameraComponent> CameraComp;

private:
    virtual void InitAbilityActorInfo() override;
};
