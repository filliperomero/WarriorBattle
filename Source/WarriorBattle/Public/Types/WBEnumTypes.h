// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WBEnumTypes.generated.h"

UENUM()
enum class EWBConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EWBValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EWBSuccessType : uint8
{
	Successful,
	Failed
};

UENUM()
enum class EWBCountDownActionInput : uint8
{
	Start,
	Cancel
};

UENUM()
enum class EWBCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Canceled
};

