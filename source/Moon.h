#pragma once
#include "CTimer.h"
#include "plugin.h"
#include "CTimeCycle.h"
class CMoon
{
public:
	static void Render(void);
	static CVector& GetSunDirection(void) { return CTimeCycle::m_VectorToSun[CTimeCycle::m_CurrentStoredValue]; }
};