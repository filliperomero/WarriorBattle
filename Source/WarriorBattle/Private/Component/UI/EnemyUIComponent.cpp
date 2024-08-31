// Fillipe Romero - All Rights Reserved

#include "Component/UI/EnemyUIComponent.h"

#include "UI/Widget/WBUserWidgetBase.h"

void UEnemyUIComponent::RegisterEnemyDrawnWidget(UWBUserWidgetBase* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

bool UEnemyUIComponent::RemoveEnemyDrawnWidget()
{
	if (EnemyDrawnWidgets.IsEmpty()) return false;

	for (const auto DrawnWidget : EnemyDrawnWidgets)
	{
		if (!IsValid(DrawnWidget)) continue;
		
		DrawnWidget->RemoveFromParent();
	}

	EnemyDrawnWidgets.Empty();
	
	return true;
}
