// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian.h"
#include "Summoner.h"
#include "Components/WidgetComponent.h"
#include "../../UI/GuardianUI.h"



// Sets default values
AGuardian::AGuardian()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	Summoner = nullptr;

	bCritical = false;

	CriticalChance = 10;
	CriticalRatio = 1.5;
	MPFillTime = 0.f;
	MPFillTimeMax = 1.f;
	m_fDeadTime = 0.f;
	Target = nullptr;
	bTarget = false;

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


}

AActor* AGuardian::GetTarget() const
{
	return Target;
}

void AGuardian::SetFillMP(float iFill)
{
	FillMP = iFill;
}

void AGuardian::SetState(int32 iDmg, int32 HP, int32 MP, float Speed)
{
	State.Damage = iDmg;
	State.iHPMax = HP;
	State.iHP = State.iHPMax;
	State.iMPMax = MP;
	State.iMP = 0;
	State.AttackSpeed = Speed;
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

void AGuardian::FillUpMP(float iValue, float fTime)
{
	MPFillTime += fTime;

	if (MPFillTime >= MPFillTimeMax)
	{
		State.iMP += iValue;

		if (State.iMP >= State.iMPMax)
			State.iMP = State.iMPMax;
		MPFillTime = 0.f;
	}
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

void AGuardian::ShowUI()
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

void AGuardian::Groggy()
{
}

void AGuardian::Victory()
{
}


void AGuardian::LevelUP(ELevelUpType eType)
{

}

void AGuardian::NormalLevelUp()
{
	
}

void AGuardian::FireLevelUp()
{
	
}

void AGuardian::IceLevelUp()
{
	
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
		FillUpMP(FillMP, DeltaTime);
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