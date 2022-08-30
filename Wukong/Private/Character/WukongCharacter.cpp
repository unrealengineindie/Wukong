// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/WukongCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemy/MeleeHitInterface.h"


// Sets default values
AWukongCharacter::AWukongCharacter() :
	DefaultTurnRate(45.f),
	DefaultLookUpRate(45.f),
	WalkSpeed(300.f),
	RunSpeed(600.f)
{
	// Create camera boom
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 400.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	// Create follow camera
	FollowCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	FollowCameraComponent->bUsePawnControlRotation = false;

	// Setup pitch yaw roll
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	// Zero pitch and roll only rotate in yaw directon
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);

	// Jumping
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.1f;

	// Right weapon collision box
	RightWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Weapon Box"));
	RightWeaponCollision->SetupAttachment(GetMesh(), FName("RightWeaponBone"));
}

// Called when the game starts or when spawned
void AWukongCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Bind function to overlap event for weapon box
	RightWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AWukongCharacter::OnRightWeaponOverlap);
	
	// Setup right weapon collision box
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

// Move forward and backward
void AWukongCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.f))
	{
		const FRotator Rotation { Controller->GetControlRotation() };

		const FRotator YawRotation { 0, Rotation.Yaw, 0 };

		const FVector Direction { FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };

		AddMovementInput(Direction, Value);
	}
}

// Move left and right
void AWukongCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.f))
	{
		// create rotators 0 out pitch and roll get vector direction
		const FRotator Rotation { Controller->GetControlRotation() };
		const FRotator YawRotation { 0, Rotation.Yaw, 0 };
		const FVector Direction { FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };

		AddMovementInput(Direction, Value);
	}
}

// Turn rate for character
void AWukongCharacter::TurnRate(float Rate)
{
	// Turning degrees per delta seconds
	AddControllerYawInput(Rate * DefaultTurnRate * GetWorld()->GetDeltaSeconds());
}

// Lookup rate for character
void AWukongCharacter::LookUpRate(float Rate)
{
	// Lookup rate degrees per delta seconds
	AddControllerPitchInput(Rate * DefaultLookUpRate * GetWorld()->GetDeltaSeconds());
}

// Running
void AWukongCharacter::Running()
{
	if (GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.0f)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
}

// Stop Running
void AWukongCharacter::StopRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

// Play recall montage
void AWukongCharacter::Recall()
{
	PlayAnimMontage(RecallMontage, FName("Recall"));
}

// Play anim montage that disables character movement
void AWukongCharacter::PlayAnimMontage(UAnimMontage* MontageToPlay, FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && MontageToPlay)
	{
		// Check to see if the montage is already playing
		if (!AnimInstance->Montage_IsPlaying(MontageToPlay))
		{
			// Disable character movement
			GetCharacterMovement()->DisableMovement();
			
			// Get time it takes to play montage
			int32 const SectionIndex = MontageToPlay->GetSectionIndex(SectionName);
			int32 const SectionLength = MontageToPlay->GetSectionLength(SectionIndex);

			// Play montage and start timer
			AnimInstance->Montage_Play(MontageToPlay);
			AnimInstance->Montage_JumpToSection(SectionName);

			// Setup timer to enable walking after montage stop playing
			GetWorldTimerManager().SetTimer(TimerMovementWalking, this, &AWukongCharacter::EnableWalk, SectionLength);
		}
	}
}

// Enable walking for character
void AWukongCharacter::EnableWalk()
{
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

// Main attack
void AWukongCharacter::MainAttack()
{
	PlayAnimMontage(MainAttackMontage, FName("MainAttack"));
}

void AWukongCharacter::OnRightWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IMeleeHitInterface* MeleeHitInterface = Cast<IMeleeHitInterface>(SweepResult.GetActor());

	if (MeleeHitInterface)
	{
		MeleeHitInterface->MeleeHIt_Implementation(SweepResult);
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Apply damage"));
}

// Called to bind functionality to input
void AWukongCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Make sure component is valid
	check(PlayerInputComponent);

	// Player movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AWukongCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AWukongCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &AWukongCharacter::TurnRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AWukongCharacter::LookUpRate);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Jumping
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Running
	PlayerInputComponent->BindAction("Running", IE_Pressed, this, &AWukongCharacter::Running);
	PlayerInputComponent->BindAction("Running", IE_Released, this, &AWukongCharacter::StopRunning);

	// Combat abilities
	PlayerInputComponent->BindAction("Recall", IE_Pressed, this, &AWukongCharacter::Recall);
	PlayerInputComponent->BindAction("MainAttack", IE_Pressed, this, &AWukongCharacter::MainAttack);
}

void AWukongCharacter::ActivateRightWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Activate weapon"));
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AWukongCharacter::DeactivateRightWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Deactivate weapon"));
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

