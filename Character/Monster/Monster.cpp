// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../../NormalActor/DemonGate.h"
#include "AIController.h"
#include "../../GameMode/DefenseGameInstance.h"


// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;
	bDead = false;

	GetClassAsset(AActor_Gem, FireGemAsset, "Blueprint'/Game/11Gem/FireGem.FireGem_C'");

	if (FireGemAsset.Succeeded())
		FireGem = FireGemAsset.Class;

	GetClassAsset(AActor_Gem, ICEGemAsset, "Blueprint'/Game/11Gem/ICEGem.ICEGem_C'");

	if (ICEGemAsset.Succeeded())
		ICEGem = ICEGemAsset.Class;

	GetClassAsset(AActor_Gem, HolyGemAsset, "Blueprint'/Game/11Gem/HolyGem.HolyGem_C'");

	if (HolyGemAsset.Succeeded())
		HolyGem = HolyGemAsset.Class;

	Tags.Add("Monster");

	iPathPoint = 0;
	SplineTime = 0.f;

	m_fBurn = 0.f;
	m_fFilter = 1.2f;
	m_fTemperature = 3000.f;
	m_fBurnTime = 2.f;
	bGroggy = false;
	bBurn = false;
}

void AMonster::SetCurMoveSpeed()
{
	m_fCurMoveSpeed = State.MoveSpeed;
}

void AMonster::SlowEvent(float fTime, float fSpeedRate)
{
	m_bSlow = true;
	SetMoveSpeed(fSpeedRate);
	SetSlowEventTime(fSpeedRate);
}

void AMonster::SetMoveSpeed(float fSpeedRate)
{
	SetCurMoveSpeed();
	State.MoveSpeed = State.MoveSpeed*fSpeedRate;
}

void AMonster::SetSlowEventTime(float fTime)
{
	m_fSlowEventTime = fTime;
}

void AMonster::SlowEventEnd()
{
	m_bSlow = false;
	m_fCurSlowEventTime = 0.f;
	m_fSlowEventTime = 0.f;
}

void AMonster::SetGroggyTime(float fTime)
{
	m_fGroggyTime = fTime;
	Groggy();
}

void AMonster::AddCurGroggyTime(float fTime)
{
	m_fCurGroggyTime += fTime;
}

float AMonster::GetCurGroggyTime() const
{
	return m_fCurGroggyTime;
}

float AMonster::GetGroggyTime() const
{
	return m_fGroggyTime;
}

void AMonster::GroggyEnd()
{
	bGroggy = false;
	ChangeAnim(EMonsterAnimType::MAT_Idle);
}

void AMonster::SetSlowRate(float fRate)
{
	State.MoveSpeed *= fRate;
}

void AMonster::AddSplineTime(float fTime)
{
	SplineTime += fTime* State.MoveSpeed;
}

float AMonster::GetSplineTime()
{
	return SplineTime;
}

void AMonster::ClearSplineTime()
{
	SplineTime = 0.f;
}

void AMonster::SetSplice(AActor_Spline* pSpline)
{
	m_pSpline = pSpline;
}

bool AMonster::IsDead()
{
	return bDead;
}

void AMonster::Dead()
{
	bDead = true;
	SetBurnEffectMaterial();
	CreateGem(State.iHPMax);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	GetMesh()->SetCollisionProfileName(TEXT("Pawn"));

	UDefenseGameInstance* pInst = Cast<UDefenseGameInstance>(GetGameInstance());

	if (pInst)
	{
		pInst->EraseMonsterCount();
	}
}

void AMonster::Burn()
{
	bBurn = true;
}

bool AMonster::IsGroggy()
{
	return bGroggy;
}

void AMonster::SetDemonGate(ADemonGate* pGate)
{
	if(IsValid(pGate))
		Gate = pGate;
}

void AMonster::AddPathPoint(AActor* pActor)
{
	PathArray.Add(pActor);
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
	UMaterialInstance* mtrl = LoadObject<UMaterialInstance>(nullptr, TEXT("MaterialInstanceConstant'/Game/07Material/MT_BurnEffect00_Inst.MT_BurnEffect00_Inst'"));

	MaterialDynamicInst = mtrl;
	m_fCurGroggyTime = 0.f;
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_bSlow)
	{
		m_fCurSlowEventTime += DeltaTime;

		if (m_fCurSlowEventTime >= m_fSlowEventTime)
		{
			SlowEventEnd();
		}
	}

	if (bGroggy)
	{
		m_fCurGroggyTime += DeltaTime;

		if (m_fCurGroggyTime >= m_fGroggyTime)
		{
			GroggyEnd();
		}
	}

	if (bDead)
	{
		m_fBurn += DeltaTime / m_fBurnTime;

		SetBurn(m_fBurn);
		if (m_fBurn >= m_fBurnTime)
		{
			Destroy();
		}
	}
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	return 0.0f;
}

void AMonster::ChangeAnim(EMonsterAnimType eType)
{

}

void AMonster::SetMonsterState(int32 iDamage, int32 iHP, int32 iMP, float fATSpeed, float fMoveSpeed)
{
	UDefenseGameInstance* pInst = Cast<UDefenseGameInstance>(GetGameInstance());

	int32 iValue;

	if (pInst)
	{
		iValue = pInst->GetWaveNumber();
	}
	else
	{
		iValue = 1;
	}

	State.Damage = iDamage;
	State.iHPMax = iHP* iValue;
	State.iHP = State.iHPMax;
	State.iMPMax = iMP;
	State.iMP = 0;
	State.MoveSpeed = fMoveSpeed;
	State.AttackSpeed = fATSpeed;
}

FMonsterState AMonster::GetMonsterState() const
{
	return State;
}

void AMonster::CreateGem(int32 iGemCount)
{
	//난수 돌려서 나온거에따라서 해주깅
	int32 iType = FMath::RandRange(0, 2);
	int32 GemCount = FMath::RandRange(iGemCount - 3, iGemCount + 3);

	FVector vPos = GetActorLocation();
	FRotator vRot = GetActorRotation();

	switch (iType)
	{
	case 0:
	{
		FActorSpawnParameters tParams;

		tParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AActor_Gem* pGem = GetWorld()->SpawnActor<AActor_Gem>(HolyGem, vPos, vRot,tParams);
		pGem->SetElementalType(0);
		pGem->SetGemCount(GemCount);
	}
		break;
	case 1:
	{
		FActorSpawnParameters tParams;

		tParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AActor_Gem* pGem = GetWorld()->SpawnActor<AActor_Gem>(FireGem, vPos, vRot, tParams);
		pGem->SetElementalType(1);
		pGem->SetGemCount(GemCount);
	}
		break;
	case 2:
	{
		FActorSpawnParameters tParams;

		tParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AActor_Gem* pGem = GetWorld()->SpawnActor<AActor_Gem>(ICEGem, vPos, vRot, tParams);
		pGem->SetElementalType(2);
		pGem->SetGemCount(GemCount);
	}
		break;
	}
}

void AMonster::SetBurnEffectMaterial()
{
	GetMesh()->SetMaterial(0, MaterialDynamicInst);
}

void AMonster::SetBurn(float fBurn)
{
	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Burn"), fBurn);
}

void AMonster::SetFilter(float fFilter)
{
	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Filter"), fFilter);
}

void AMonster::SetTemperature(float fTemperature)
{
	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Temperature"), fTemperature);
	//GetMesh()->SetVectorParameterValueOnMaterials(TEXT(""))
}

void AMonster::Skill()
{
}

void AMonster::Groggy()
{
	bGroggy = true;
	ChangeAnim(EMonsterAnimType::MAT_Groggy);		
}


