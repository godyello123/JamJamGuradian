// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenstPlayerState.h"
#include "DefenseGameMode.h"
#include "../UI/MainUI.h"

ADefenstPlayerState::ADefenstPlayerState()
{

}

void ADefenstPlayerState::AllSetGem(int32 iCount)
{
	m_tGem.iGoldGem = iCount;
	m_tGem.iFireGem = iCount;
	m_tGem.iIceGem = iCount;
	m_pMainUI->SetGoldGemCount(m_tGem.iGoldGem);
	m_pMainUI->SetFireGemCount(m_tGem.iFireGem);
	m_pMainUI->SetIceGemCount(m_tGem.iIceGem);
}

void ADefenstPlayerState::AllAddGem(int32 iCount)
{
	m_tGem.iGoldGem += iCount;
	m_pMainUI->SetGoldGemCount(m_tGem.iGoldGem);

	m_tGem.iFireGem += iCount;
	m_pMainUI->SetFireGemCount(m_tGem.iFireGem);

	m_tGem.iIceGem += iCount;
	m_pMainUI->SetIceGemCount(m_tGem.iIceGem);
}

void ADefenstPlayerState::AllRemoveGem(int32 iCount)
{

	int32 iGoldValue = m_tGem.iGoldGem -= iCount;

	if (iGoldValue >= 0)
	{
		m_tGem.iGoldGem = iGoldValue;
		m_pMainUI->SetGoldGemCount(m_tGem.iGoldGem);
	}
	else
	{
		//*ㅅ*자원부족 UI 만들기
		return;
	}


	int32 iFireValue = m_tGem.iFireGem -= iCount;

	if (iFireValue >= 0)
	{
		m_tGem.iFireGem = iFireValue;
		m_pMainUI->SetFireGemCount(m_tGem.iFireGem);
	}
	else
	{
		//*ㅅ* 자원부족 UI 만들기
		return;
	}

	int32 iIceValue = m_tGem.iIceGem -= iCount;

	if (iIceValue >= 0)
	{
		m_tGem.iIceGem = iIceValue;
		m_pMainUI->SetIceGemCount(m_tGem.iIceGem);
	}
	else
	{
		//*ㅅ* 자원부족 UI 만들기
		return;
	}

}

void ADefenstPlayerState::AddGem(int32 iType, int32 iCount)
{
	if (iType < 0 || iType>2)
		return;

	if (iType == 0)
	{
		m_tGem.iGoldGem += iCount;
		m_pMainUI->SetGoldGemCount(m_tGem.iGoldGem);
	}
	else if (iType == 1)
	{
		m_tGem.iFireGem += iCount;
		m_pMainUI->SetFireGemCount(m_tGem.iFireGem);
	}
	else if (iType == 2)
	{
		m_tGem.iIceGem += iCount;
		m_pMainUI->SetIceGemCount(m_tGem.iIceGem);
	}
}

void ADefenstPlayerState::RemoveGem(int32 iType, int32 iCount)
{
	if (iType < 0 || iType>2 || iCount < 0)
		return;


	if (iType == 0)
	{
		int32 iValue = m_tGem.iGoldGem - iCount;

		if (iValue >= 0)
		{
			m_tGem.iGoldGem = iValue;
			m_pMainUI->SetGoldGemCount(m_tGem.iGoldGem);
		}
		else
		{
			//*ㅅ*자원 부족하다는 ui 노출
			return;
		}

	}
	else if (iType == 1)
	{
		int32 iValue = m_tGem.iFireGem - iCount;

		if (iValue >= 0)
		{
			m_tGem.iFireGem = iValue;
			m_pMainUI->SetFireGemCount(m_tGem.iFireGem);
		}
		else
		{
			//*ㅅ* 자원 부족 하다는 ui 노출
			return;
		}
	}
	else if (iType == 2)
	{
		int32 iValue = m_tGem.iIceGem - iCount;

		if (iValue >= 0)
		{
			m_tGem.iIceGem = iValue;
			m_pMainUI->SetIceGemCount(m_tGem.iIceGem);
		}
		else
		{
			//*ㅅ* 자원부족하다는 ui 노출
			return;
		}
	}
}

int32 ADefenstPlayerState::GetGem(int32 iType) const
{
	if (iType == 0)
	{
		return m_tGem.iGoldGem;
	}
	else if (iType == 1)
	{
		return m_tGem.iFireGem;
	}
	else if (iType == 2)
	{
		return m_tGem.iIceGem;
	}
	else
		return -1;
}

void ADefenstPlayerState::SetMainUI(UMainUI* pUI)
{
	m_pMainUI = pUI;
}

