// Fill out your copyright notice in the Description page of Project Settings.


#include "SunWuKongCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values	
ASunWuKongCharacter::ASunWuKongCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
// Called when the game starts or when spawned
void ASunWuKongCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Playing Intro Scene and restricting all movements untill it completes.
	PlayAnimMontage(Start_Montage);
	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &ASunWuKongCharacter::OnIntroEnd);
	GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(EndDelegate);
	doOnce = true;
}

// Called every frame
void ASunWuKongCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//A helper in combo attacking system
	isAttacking = AttackCombo();	
}

// Called to bind functionality to input
void ASunWuKongCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Move Forward"),this,&ASunWuKongCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Move Sideward"),this,&ASunWuKongCharacter::MoveSideward);
	PlayerInputComponent->BindAxis(TEXT("Look Up"),this,&ASunWuKongCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Look Sides"),this,&ASunWuKongCharacter::LookSides);

	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed,this,&ASunWuKongCharacter::JumpStart);
	PlayerInputComponent->BindAction(TEXT("Attack1"),EInputEvent::IE_Pressed,this,&ASunWuKongCharacter::Attack1);
	PlayerInputComponent->BindAction(TEXT("Taunt"),EInputEvent::IE_Pressed,this,&ASunWuKongCharacter::Taunt);
}

//Call this Function when MoveForward Keys are pressed.
void ASunWuKongCharacter::MoveForward(float Value)
{
	//restricting Forward movement in some sequences.
	if(!doOnce && !isTaunting)
	{
		AddMovementInput(GetActorForwardVector() * Value);
	}
}

//Call this Function when MoveSideward Keys are pressed.
void ASunWuKongCharacter::MoveSideward(float Value)
{
	//restricting Side movement in some sequences.
	if(!doOnce && !isTaunting)
	{
		AddMovementInput(GetActorRightVector() * Value);
	}
}

//Call this Function when LookUp axis changes.
void ASunWuKongCharacter::LookUp(float Value)
{
	//restricting looking Up and Down at intro sequence
	if(!doOnce)
	{
		AddControllerPitchInput(Value);
	}
}

//Call this Function when LookSide axis changes.
void ASunWuKongCharacter::LookSides(float Value)
{
	//restricting looking side at some animation sequences
	if(!doOnce && !isTaunting)
	{
		AddControllerYawInput(Value);
	}
}

//Call this Function when jump key is pressed
void ASunWuKongCharacter::JumpStart()
{
	if(!doOnce && !isTaunting)
	{
		PlayAnimMontage(Jump_Montage,0.75f);
	}
}

//Attacking Combo system
void ASunWuKongCharacter::Attack1()
{
	//restricting attacks in some animation sequence
	if(!doOnce && !isFinished)
	{
		//Combo Attack system with 5 attacks.
		if(isAttacking && n_combo == 1)
		{
			PlayAnimMontage(Attack_2_Montage,0.75f);
			n_combo++;
			isAttacking = GetMesh()->GetAnimInstance()->Montage_IsPlaying(Attack_2_Montage);
		}
		else if(isAttacking && n_combo == 2)
		{
			PlayAnimMontage(Attack_3_Montage,0.75f);
			n_combo++;
			isAttacking = GetMesh()->GetAnimInstance()->Montage_IsPlaying(Attack_3_Montage);
		}
		else if(isAttacking && n_combo == 3)
		{
			PlayAnimMontage(Attack_4_Montage,0.75f);
			n_combo++ ;
			isAttacking = GetMesh()->GetAnimInstance()->Montage_IsPlaying(Attack_4_Montage);
		}
		else if(isAttacking && n_combo == 4)
		{
			PlayAnimMontage(Attack_5_Montage,0.75f);
			n_combo=0;
		}
		else
		{
			PlayAnimMontage(Attack_1_Montage,0.75f);
			n_combo = 1;
			isAttacking= true;
		}
	}
}

//Palying Emotes to Taunt other player/enemy.
void ASunWuKongCharacter::Taunt()
{		
		//playing randomly (just for fun)
		int random = FMath::RandRange(1,5);
		if(random == 1)
		{
			PlayAnimMontage(Taunt_1_Montage);
		}
		else if(random == 2)
		{
			PlayAnimMontage(Taunt_2_Montage);
		}
		else if(random == 3)
		{
			PlayAnimMontage(Taunt_3_Montage);
		}
		else if(random == 4)
		{
			PlayAnimMontage(Taunt_4_Montage);
		}
		else if(random == 5)
		{
			PlayAnimMontage(Taunt_5_Montage);
		}
		//To remove restriction or any other parameters after the animation is played. Calls a Function
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &ASunWuKongCharacter::OnTauntEnd);
		GetMesh()->GetAnimInstance()->Montage_SetEndDelegate(EndDelegate);
}

//Code to activate after playing emote animation
void ASunWuKongCharacter::OnTauntEnd(UAnimMontage* Montage, bool isInteppted)
{
	isTaunting = false;
}

//code to activate after playing intro sequence
void ASunWuKongCharacter::OnIntroEnd(UAnimMontage* Montage, bool isInteppted)
{
	doOnce = false;
}

//code to reset combo attack system.
bool ASunWuKongCharacter::AttackCombo()
{
	if(GetMesh()->GetAnimInstance()->Montage_IsPlaying(Attack_1_Montage) || GetMesh()->GetAnimInstance()->Montage_IsPlaying(Attack_2_Montage) ||
	   GetMesh()->GetAnimInstance()->Montage_IsPlaying(Attack_3_Montage) || GetMesh()->GetAnimInstance()->Montage_IsPlaying(Attack_4_Montage) ||
	   GetMesh()->GetAnimInstance()->Montage_IsPlaying(Attack_5_Montage))
	   {
		   return true;
	   }
	   else
	   {
		   return false;
	   }
}