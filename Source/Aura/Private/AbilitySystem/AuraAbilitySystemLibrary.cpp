#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"


UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
    if (!PC) return nullptr;

    AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
    if (!AuraHUD) return nullptr;

    AAuraPlayerState* PS = Cast<AAuraPlayerState>(PC->PlayerState);
    if (!PS) return nullptr;

    UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
    if (!ASC) return nullptr;

    UAttributeSet* AS = PS->GetAttributeSet();
    if (!AS) return nullptr;

    const FWidgetControllerParams WCParams(PC, PS, ASC, AS);

    return AuraHUD->GetOverlayWidgetController(WCParams);
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
    if (!PC) return nullptr;

    AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
    if (!AuraHUD) return nullptr;

    AAuraPlayerState* PS = Cast<AAuraPlayerState>(PC->PlayerState);
    if (!PS) return nullptr;

    UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
    if (!ASC) return nullptr;

    UAttributeSet* AS = PS->GetAttributeSet();
    if (!AS) return nullptr;

    const FWidgetControllerParams WCParams(PC, PS, ASC, AS);

    return AuraHUD->GetAttributeMenuWidgetController(WCParams);
}
