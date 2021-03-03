// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian.h"
#include "Summoner.h"
#include "Components/WidgetComponent.h"
#include "../../UI/GuardianUI.h"
#include "../../Spell/Spell.h"


// Sets default values
AGuardian::AGuardian()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	Summoner = nullptr;

	bCritical = false;

	CriticalChance = 10;
	CriticalRatio = 1.5;
	m_fDeadTime = 0.f;
	bTarget = false;
	m_eLevel = EGUARDIANLEVEL::GL_LEVEL1;

	fAttackDist = 3000.f;

	//SetActorType(EActorType::AT_Guardian);

	Tags.Add("Guardian");

	m_eElementalType = EElementalType::ET_Normal;

	UIComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));

	UIComponent->SetupAttachment(GetMesh());

	UIComponent->SetWidgetSpace(EWidgetSpace::Screen);
	UIComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	UIComponent->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));


	GetClassAsset(UUserWidget, WidgetClass, "WidgetBlueprint'/Game/10UI/BP_GuardianUI.BP_GuardianUI_C'");

	if (WidgetClass.Succeeded())
		UIComponent->SetWidgetClass(WidgetClass.Class);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Guardian"));

	GetMesh()->SetCollisionProfileName(TEXT("Guardian"));

	GetClassAsset(AEffect_LevelUp, EffectAsset1, "Blueprint'/Game/06Effect/BP_Effect_L_Up.BP_Effect_L_Up_C'");

	if (EffectAsset1.Succeeded())
		LightningLevelUp_EffectAsset = EffectAsset1.Class;

	GetClassAsset(AEffect_LevelUp, EffectAsset2, "Blueprint'/Game/06Effect/BP_L_Up2.BP_L_Up2_C'");

	if (EffectAsset2.Succeeded())
		FireLevelUp_EffectAsset = EffectAsset2.Class;

	GetClassAsset(AEffect_LevelUp, EffectAsset3, "Blueprint'/Game/06Effect/BP_L_Up3.BP_L_Up3_C'");

	if (EffectAsset1.Succeeded())
		IceLevelUp_EffectAsset = EffectAsset3.Class;

	GetClassAsset(AActor_Decal, DecalRed, "Blueprint'/Game/03Decal/RedCircleDecal_BP.RedCircleDecal_BP_C'");

	if (DecalRed.Succeeded())
		RedDecal = DecalRed.Class;

	GetClassAsset(AActor_Decal, DecalBlue, "Blueprint'/Game/03Decal/BlueCircleDecal_BP.BlueCircleDecal_BP_C'");

	if (DecalBlue.Succeeded())
		BlueDecal = DecalBlue.Class;

	GetClassAsset(AActor_Decal, DecalYellow, "Blueprint'/Game/03Decal/YellowCircleDecal_BP.YellowCircleDecal_BP_C'");

	if (DecalYellow.Succeeded())
		YellowDecal = DecalYellow.Class;

	m_fTierGageTimeMax = 0.5f;
}


AActor_Decal * AGuardian::GetDecal() const
{
	return m_pDecal;
}

EGUARDIANLEVEL AGuardian::GetGuardianLevel() const
{
	return m_eLevel;
}

void AGuardian::SetGuardianLevel(EGUARDIANLEVEL eLevel)
{
	m_eLevel = eLevel;
}

void AGuardian::SetElementalType(EElementalType eType)
{
	m_eElementalType = eType;
	SetMeshMaterial(m_eElementalType);
}

EElementalType AGuardian::GetElementalType() const
{
	return m_eElementalType;
}

void AGuardian::RandElementalType()
{
	int32 iType = FMath::RandRange(0, 2);

	if (iType == 0)
		SetElementalType(EElementalType::ET_Normal);
	else if(iType==1)
		SetElementalType(EElementalType::ET_Fire);
	else
		SetElementalType(EElementalType::ET_Ice);
}

AActor* AGuardian::GetTarget() const
{
	return Target;
}

void AGuardian::SetFillTierGage_1(float fGage)
{
	m_fFillTierGage_1 = fGage;
}

void AGuardian::SetFillTierGage_2(float fGage)
{
	m_fFillTierGage_2 = fGage;
}

void AGuardian::SetFillTierGage_3(float fGage)
{
	m_fFillTierGage_3 = fGage;
}


void AGuardian::SetState(int32 iDmg, float fTier1, float fTier2, float fTier3, float fSpeed)
{
	State.iDamage = iDmg;
	State.fTierGageMax_1 = fTier1;
	State.fTierGageMax_2 = fTier2;
	State.fTierGageMax_3 = fTier3;
	State.fAttackSpeed = fSpeed;
}

FGuardianState AGuardian::GetState() const
{
	return State;
}

void AGuardian::SetCriticalChance(int32 iChance)
{
	CriticalChance = iChance;
}

void AGuardian::SetCriticalRatio(float fRatio)
{
	CriticalRatio = fRatio;
}

int32 AGuardian::GetCriticalChance() const
{
	return CriticalChance;
}

float AGuardian::GetCriticalRatio() const
{
	return CriticalRatio;
}

void AGuardian::SetMeshMaterial(EElementalType eType)
{
	UMaterialInstance* mtrl0 = LoadObject<UMaterialInstance>(nullptr,
		TEXT("MaterialInstanceConstant'/Game/07Material/HeadPartsMat_2_Inst.HeadPartsMat_2_Inst'"));
	UMaterialInstance* mtrl1 = LoadObject<UMaterialInstance>(nullptr,
		TEXT("MaterialInstanceConstant'/Game/07Material/BodyPartsMat_2_Inst.BodyPartsMat_2_Inst'"));
	UMaterialInstance* mtrl2 = LoadObject<UMaterialInstance>(nullptr,
		TEXT("MaterialInstanceConstant'/Game/07Material/CostumesMat_2_Inst.CostumesMat_2_Inst'"));

	GetMesh()->SetMaterial(0, mtrl0);
	GetMesh()->SetMaterial(1, mtrl1);
	GetMesh()->SetMaterial(2, mtrl2);

	switch (eType)
	{
	case EElementalType::ET_Normal:
	{
		FVector4 vColor = FVector4(1.f, 1.f, 0.f, 0.f);
		SetMeshMaterialColor(vColor);
	}
		break;
	case EElementalType::ET_Fire:
	{
		FVector4 vColor = FVector4(1.f, 0.f, 0.f, 0.f);
		SetMeshMaterialColor(vColor);
	}
		break;
	case EElementalType::ET_Ice:
	{
		FVector4 vColor = FVector4(0.f, 0.f, 1.f, 0.f);
		SetMeshMaterialColor(vColor);
	}
		break;
	}
}

void AGuardian::SetMeshMaterialColor(FVector4 & vColor)
{
	GetMesh()->SetVectorParameterValueOnMaterials(TEXT("Color"), vColor);
	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Value"), 10.f);
}

void AGuardian::AddCriticalChance()
{
	++CriticalChance;
}

void AGuardian::AddCriticalRatio()
{
	++CriticalRatio;
}

void AGuardian::SetSummoner(ASummoner* Sum)
{
	Summoner = Sum;
}

bool AGuardian::IsSummoner()
{
	if (IsValid(Summoner))
		return true;
	
	return false;
}

void AGuardian::Motion()
{
}

void AGuardian::Attack()
{
}

void AGuardian::Skill()
{
}

void AGuardian::SearchTarget()
{
}

void AGuardian::Targeting(const FVector& vLoc)
{
}

void AGuardian::Ultimate()
{
}

void AGuardian::ShowUI()
{
	if (m_eLevel != EGUARDIANLEVEL::GL_LEVEL3)
	{
		switch (SpawnUI->GetVisibility())
		{
		case ESlateVisibility::Visible:
			SpawnUI->SetVisibility(ESlateVisibility::Collapsed);
			break;
		case ESlateVisibility::Collapsed:
			SpawnUI->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AGuardian::HideUI()
{
	SpawnUI->SetVisibility(ESlateVisibility::Collapsed);
}

void AGuardian::CreateEffectLevelUp(EElementalType eType)
{
	switch (eType)
	{
	case EElementalType::ET_Normal:
	{
		FVector vPos = this->GetActorLocation();
		FRotator vRot = this->GetActorRotation();
		AEffect_LevelUp* pEffect = GetWorld()->SpawnActor<AEffect_LevelUp>(vPos, vRot);
	}
		break;
	case EElementalType::ET_Fire:
	{

	}
		break;
	case EElementalType::ET_Ice:
	{

	}
		break;
	}
}

void AGuardian::AttackEnable(bool bEnable)
{
	bAttack = bEnable;
}

bool AGuardian::IsAttack() const
{
	return bAttack;
}

void AGuardian::FillUpTierGage_1(float iValue, float fTime)
{
	m_fTierGageCurTime_1 += fTime;

	if (m_fTierGageCurTime_1 >= m_fTierGageTimeMax)
	{
		State.fTierGage_1 += iValue;

		if (State.fTierGage_1 >= State.fTierGageMax_1)
		{
			State.fTierGage_1 = State.fTierGageMax_1;
		}
		 
		m_fTierGageCurTime_1 = 0.f;
	}
}

void AGuardian::FillUpTierGage_2(float iValue, float fTime)
{
	m_fTierGageCurTime_2 += fTime;

	if (m_fTierGageCurTime_2 >= m_fTierGageTimeMax)
	{
		State.fTierGage_2 += iValue;

		if (State.fTierGage_2 >= State.fTierGageMax_2)
		{
			State.fTierGage_2 = State.fTierGageMax_2;
		}

		m_fTierGageCurTime_2 = 0.f;
	}
}

void AGuardian::FillUpTierGage_3(float iValue, float fTime)
{
	m_fTierGageCurTime_3 += fTime;

	if (m_fTierGageCurTime_3 >= m_fTierGageTimeMax)
	{
		State.fTierGage_3 += iValue;

		if (State.fTierGage_3 >= State.fTierGageMax_3)
		{
			State.fTierGage_3 = State.fTierGageMax_3;
		}

		m_fTierGageCurTime_3 = 0.f;
	}
}

void AGuardian::Groggy()
{
}

void AGuardian::Victory()
{
}

void AGuardian::LevelUp(EGUARDIANLEVEL eLevel, EElementalType eType)
{
	switch (eLevel)
	{
	case EGUARDIANLEVEL::GL_LEVEL1:
		break;
	case EGUARDIANLEVEL::GL_LEVEL2:
		break;
	case EGUARDIANLEVEL::GL_LEVEL3:
		break;
	}
}

// Called when the game starts or when spawned
void AGuardian::BeginPlay()
{
	Super::BeginPlay();

	SpawnUI = Cast< UGuardianUI>(UIComponent->GetUserWidgetObject());
	SpawnUI->SetOwner(this);
	//SpawnUI->AddToViewport();
	SpawnUI->SetVisibility(ESlateVisibility::Collapsed);

}

// Called every frame
void AGuardian::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_bDead)
	{
		//FillUpTierGage_1(m_fFillTierGage_1, DeltaTime);
	}
	else
	{
		m_fDeadTime += DeltaTime;

		if (m_fDeadTime >= 6.f)
			this->Destroy();
	}
}

// Called to bind functionality to input
void AGuardian::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AGuardian::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void AGuardian::Dead()
{
	m_bDead = true;
	GetMesh()->SetVisibility(false);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnUI->SetVisibility(ESlateVisibility::Collapsed);
}