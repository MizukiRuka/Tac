// Copyright by GameDream.

#pragma once

#include "WheeledVehicle.h"
#include "TacVehicle.generated.h"

/**
 * Actor one, main pawn, good luck!
 */

class UCameraComponent;
class USpringArmComponent;
class UInputComponent;

UCLASS()
class TAC_API ATacVehicle : public AWheeledVehicle
{
	GENERATED_BODY()

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	
public:
	ATacVehicle();
	
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	/** Handle pressing forwards */
	void MoveForward(float val);
	/** Handle pressing right */
	void MoveRight(float val);
	/** Rotate Camera to adjust the view */
	void RotateCamera(float val);
	/** Zoom camera to adjust the view */
	void ZoomCamera(float val);
	/** Boost the vehicle */
	void Boost();
	/** Handle handbrake pressed */
	void OnHandbrakePressed();
	/** Handle handbrake released */
	void OnHandbrakeReleased();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float BoostSpeed;

public:
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
};
