#pragma once
#include "CTimer.h"
#include "plugin.h"
#include "CTimeCycle.h"
class CMoon
{
public:
	static void __cdecl Render();
	static void renderMoonMask();
	static void setMoonAlphaBlendStates(float x, float y, float z, float halfWidth, float halfHeight,
		unsigned char red, unsigned char green, unsigned char blue, short alpha, float rhw,
		unsigned char intensity, unsigned char udir, unsigned char vdir);
	static void restoreMoonAlphaBlendStates();
	static void Phase();
	static void RenderTEST();
	static void renderPHASE();
	static void SniperPatch();
	static void WeatherUpdate_Patch();
	static bool MoonSizePatch(CPed* shooter, CEntity* victim, CVector* target);
	static CVector& GetSunDirection(void) { return CTimeCycle::m_VectorToSun[CTimeCycle::m_CurrentStoredValue]; }
};
