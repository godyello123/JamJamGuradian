// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Beholder.h"
#include "AIController.h"
#include "../../Animation/Monster/Anim_Beholder.h"
#include "../../NormalActor/DemonGate.h"


AMonster_Beholder::AMonster_Beholder()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/RPGMonsterWave2PBR/Mesh/Beholder/BeholderSK.BeholderSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_Beholder, AnimAsset,"AnimBlueprint'/Game/02Monster/01Beholder/Beholder_Anim.Beholder_Anim_C'");

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));

	GetMesh()->SetCollisionProfileName(TEXT("Monster"));

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -70.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	fMPRecovery = 0;
	fDistance = 1000.f;
	SetMonsterState(5, 5, 5, 100, 1);

	//Test
	P0 = nullptr;
	P1 = nullptr;
	P2 = nullptr;
	fTime = 0;
	//Test
}

void AMonster_Beholder::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_Beholder>(GetMesh()->GetAnimInstance());
}

void AMonster_Beholder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector vLoc = GetActorLocation();

	if (fTime < 1)
	{
		if (IsValid(P1) && IsValid(P0) && IsValid(P2))
		{
			fTime += DeltaTime;
			FVector P0_Point = P0->GetActorLocation();
			FVector P1_Point = P1->GetActorLocation();
			FVector P2_Point = P2->GetActorLocation();

			float Bezier1x = (1 - fTime) * (1 - fTime) * P0_Point.X;
			float Bezier2x = 2 * fTime * (1 - fTime) * P1_Point.X;
			float Bezier3x = fTime * fTime * P2_Point.X;

			float Bezier1y = (1 - fTime) * (1 - fTime) * P0_Point.Y;
			float Bezier2y = 2 * fTime * (1 - fTime) * P1_Point.Y;
			float Bezier3y = fTime * fTime * P2_Point.Y;

			float BezierX = Bezier1x + Bezier2x + Bezier3x;
			float BezierY = Bezier1y + Bezier2y + Bezier3y;
			FVector vBezier = FVector(BezierX, BezierY, vLoc.Z);

			FVector vDir = vBezier-vLoc;
			vDir.Normalize();

			SetActorRotation(FRotator(0.f, vDir.Rotation().Yaw, 0.f));
			SetActorLocation(vBezier);
		}
	}
}

void AMonster_Beholder::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMonster_Beholder::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	State.iHP -= DamageAmount;
	if (State.iHP <= 0)
	{
		State.iHP = 0;
		//Á×ÀÌ±â
		if (Animation)
		{
			Animation->ChangeAnimType(EMonsterAnimType::MAT_Die);
		}
	}

	return State.iHP;
}

void AMonster_Beholder::ChangeAnim(EMonsterAnimType eType)
{
	if (Animation)
		Animation->ChangeAnimType(eType);
}

void AMonster_Beholder::Skill()
{
}
