
#pragma once
#include "CTimer.h"
#include "plugin.h"
#include "CTimeCycle.h"
class CMoon
{
public:
	static void Render();
	static void renderMoonMask();
	static void setMoonAlphaBlendStates(float x, float y, float z, float halfWidth, float halfHeight,
		unsigned char red, unsigned char green, unsigned char blue, short alpha, float rhw,
		unsigned char intensity, unsigned char udir, unsigned char vdir);
	static void restoreMoonAlphaBlendStates();
	static void Phase();
	//static void Init();
	static bool MoonSizePatch(CPed* shooter, CEntity* victim, CVector* target);
	static CVector& GetSunDirection(void) { return CTimeCycle::m_VectorToSun[CTimeCycle::m_CurrentStoredValue]; }
};