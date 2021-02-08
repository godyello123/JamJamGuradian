// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Spline.h"

// Sets default values
AActor_Spline::AActor_Spline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_pSpline = CreateDefaultSubobject< USplineComponent>(TEXT("Spline"));
	SetRootComponent(m_pSpline);

	m_iCurPoint = 0;
	m_iMaxPoint = 0;
}

// Called when the game starts or when spawned
void AActor_Spline::BeginPlay()
{
	Super::BeginPlay();
	//Spline->bShouldVisualizeScale(true);
	m_pSpline->Duration = 50.f;

	m_iMaxPoint = m_pSpline->GetNumberOfSplinePoints();
}

// Called every frame
void AActor_Spline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AActor_Spline::GetPathLocation(float fTime)
{	
	/*int32 iSize = m_Spline->GetNumberOfSplinePoints();
	FVector vLoc = m_Spline->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Type::World);
	return vLoc;
	*/

	return m_pSpline->GetLocationAtTime(fTime, ESplineCoordinateSpace::Type::World,true);
	//return m_pSpline->Get
}

FVector AActor_Spline::GetPathLocation()
{
	return m_pSpline->GetLocationAtSplinePoint(m_iCurPoint, ESplineCoordinateSpace::World);
}

int32 AActor_Spline::GetPathPoint() const
{
	return m_iCurPoint;
}

void AActor_Spline::AddPathPoint()
{
	++m_iCurPoint;

	if (m_iCurPoint > m_iMaxPoint)
		m_iCurPoint = 0;
}

void AActor_Spline::ClearPathPoint()
{
	m_iCurPoint = 0;
}

void AActor_Spline::SetSplineDurationTime(float fTime)
{
	m_pSpline->Duration = fTime;
}

float AActor_Spline::GetSplineDurationTime() const
{
	return m_pSpline->Duration;
}

