#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UDamageTextComponent;
struct FGameplayTag;
class UAuraInputConfig;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class UAuraAbilitySystemComponent;
class USplineComponent;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AAuraPlayerController();

    virtual void PlayerTick(float DeltaTime) override;

    UFUNCTION(Client, Reliable)
    void ClientShowDamageNumber(const float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit);

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    void Move(const struct FInputActionValue& InputActionValue);

    void CursorTrace();

    void AbilityInputTagPressed(FGameplayTag InputTag);
    void AbilityInputTagReleased(FGameplayTag InputTag);
    void AbilityInputTagHeld(FGameplayTag InputTag);

    UAuraAbilitySystemComponent* GetAuraAbilitySystemComponent();

    void AutoRun();

    void ShiftPressed();
    void ShiftReleased();

    bool bShiftKeyDown = false;

    UPROPERTY()
    TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputMappingContext> AuraContext;

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputAction> ShiftAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UAuraInputConfig> InputConfig;

    TScriptInterface<IEnemyInterface> LastActor;
    TScriptInterface<IEnemyInterface> ThisActor;

    FHitResult CursorHit;

    // Movement
    FVector CachedDestination = FVector::ZeroVector;
    float FollowTime = 0.0f;
    float ShortPressThreshold = 0.5f;
    bool bAutoRunning = false;
    bool bTargeting = false;

    UPROPERTY(EditDefaultsOnly)
    float AutoRunAcceptanceRadius = 50.0f;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<USplineComponent> Spline;
    // ~Movement

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
};
