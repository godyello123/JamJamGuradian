// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "../Character/Guardian/Guardian.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	m_pOwner = Cast<AGuardian>(GetOwner());
	Target = m_pOwner->GetTarget();
	if (m_pOwner)
	{
		m_fSpeed = m_pOwner->GetState().AttackSpeed;
	}

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::CollisionBeginOverlap);

}

void AProjectile::SetTarget(AActor* _Target)
{
	Target = _Target;
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target)
	{
		FVector vPos = GetActorLocation();

		FVector vTarget = Target->GetActorLocation();

		FVector vDir = vTarget - vPos;

		vPos = vPos + (vDir * 2*(m_fSpeed)* DeltaTime);

		SetActorLocation(vPos);

		float fDist = 0;
		fDist= FVector::Distance(vPos, Target->GetActorLocation());

		if (fDist <= 2.f)
		{
			FDamageEvent DmgEvent;

			Target->TakeDamage(m_pOwner->GetState().Damage, DmgEvent, m_pOwner->GetController(), this);

			Destroy();

		}
	}

}

void AProjectile::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor!=Target)||
		!Target)
	{
		return;
	}

	FDamageEvent DmgEvent;

	OtherActor->TakeDamage(m_pOwner->GetState().Damage, DmgEvent, m_pOwner->GetController(), this);
	
	Destroy();

}

