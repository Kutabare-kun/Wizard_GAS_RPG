#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widgets/AuraUserWidget.h"

void AAuraHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass))
	{
		Widget->AddToViewport();
	}
}
