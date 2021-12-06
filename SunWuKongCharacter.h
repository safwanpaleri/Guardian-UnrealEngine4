// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SunWuKongCharacter.generated.h"

UCLASS()
class GUARDIAN_API ASunWuKongCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASunWuKongCharacter();

	//Storing references of animations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skeletons")
	USkeletalMesh* Sage_Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skeletons")
	USkeletalMesh* Normal_Mesh;
	UPROPERTY(VisibleDefaultsOnly,Category="Skeletons")
	USkeletalMeshComponent* currentMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Start_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animations")
	UAnimMontage* Recall_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Jump_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Attack_1_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Attack_2_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Attack_3_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Attack_4_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Attack_5_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Taunt_1_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Taunt_2_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Taunt_3_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Taunt_4_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Taunt_5_Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Death_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Hit_Back_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Hit_Front_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Hit_Right_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Hit_Left_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Knock_Back_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Knock_Front_Montage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Stun_Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Animations")
	UAnimMontage* Win_Montage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Bool" )
	bool isAttacking = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Bool" )
	bool doOnce = true;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Bool" )
	bool isFinished = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Bool" )
	bool isTaunting = false;

	int n_combo = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void MoveForward(float Value);
	virtual void MoveSideward(float Value);
	virtual void LookUp(float Value);
	virtual void LookSides(float Value);
	virtual void JumpStart();
	virtual void Attack1();
	virtual void Taunt();
	
	void OnTauntEnd(UAnimMontage* Montage, bool isInterrupted);
	void OnIntroEnd(UAnimMontage* Montage, bool isInterrupted);
	bool AttackCombo();
};
