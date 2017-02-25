// Copyright by GameDream.

#pragma once

#include "AIController.h"
#include "TacAIController.generated.h"

/**
 * 
 */
UCLASS()
class TAC_API ATacAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius;

private:
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

public:
	ATacAIController();
	


};
