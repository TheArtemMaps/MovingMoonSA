#pragma once
#include "CTimer.h"
#include "plugin.h"
#include "CTimeCycle.h"
class CMoon
{
public:
	static void Render();
	static bool MoonSizePatch(CPed* shooter, CEntity* victim, CVector* target);
	static CVector& GetSunDirection(void) { return CTimeCycle::m_VectorToSun[CTimeCycle::m_CurrentStoredValue]; }
};