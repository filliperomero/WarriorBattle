// Fillipe Romero - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "WBEnumTypes.h"

class FWBCountDownAction : public FPendingLatentAction
{
public:
	FWBCountDownAction(float InTotalCountDownTime, float InUpdateInterval, float& InOutRemainingTime, EWBCountDownActionOutput& InCountDownOutput, const FLatentActionInfo& LatentInfo)
		: bNeedToCancel(false),
		TotalCountDownTime(InTotalCountDownTime),
		UpdateInterval(InUpdateInterval),
		OutRemainingTime(InOutRemainingTime), 
		CountDownOutput(InCountDownOutput),
		ExecutionFunction(LatentInfo.ExecutionFunction),
		OutputLink(LatentInfo.Linkage),
		CallbackTarget(LatentInfo.CallbackTarget),
		ElapsedInterval(0.f),
		ElapsedTimeSinceStart(0.f)
	{
	}

	void CancelAction();
	virtual void UpdateOperation(FLatentResponse& Response) override;

private:
	bool bNeedToCancel;
	float TotalCountDownTime;
	float UpdateInterval;
	float& OutRemainingTime;
	EWBCountDownActionOutput& CountDownOutput;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStart;
};
