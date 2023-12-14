#include "plugin.h"

#include "CGame.h"
#include "CWeather.h"
#include "CCamera.h"
#include "CVector.h"
#include "Moon.h"
#include "Utility.h"
#include "CCoronas.h"
#include "CClock.h"
#include "CSprite.h"
#include "CClouds.h"
using namespace plugin;
#define RwV3dAddMacro(o, a, b)                                  \
MACRO_START                                                     \
{                                                               \
    (o)->x = (((a)->x) + ( (b)->x));                            \
    (o)->y = (((a)->y) + ( (b)->y));                            \
    (o)->z = (((a)->z) + ( (b)->z));                            \
}                                                               \
MACRO_STOP                               
#define RwV3dAdd(o, a, b) RwV3dAddMacro(o, a, b)
void 
CMoon::Render(void) {
	float szx, szy;
	RwV3d screenpos;
	RwV3d worldpos;
	float minute = CClock::ms_nGameClockHours * 60 + CClock::ms_nGameClockMinutes + CClock::ms_nGameClockSeconds / 60.0f;
	RwV3d campos = TheCamera.GetPosition().ToRwV3d();
	float moonfadeout;

	float smoothBrightnessAdjust = 1.9f;
	if ((int)minute > 1100)
		moonfadeout = abs(minute - 1100.0f) / smoothBrightnessAdjust;
	else if ((int)minute < 240)
		moonfadeout = 180.0f;
	else
		moonfadeout = 180.0f - abs(minute - 240.0f) * smoothBrightnessAdjust;

	if ((int)moonfadeout > 0.0f && (int)moonfadeout < 340) {
		float coverage = max(CWeather::Foggyness, CWeather::CloudCoverage);
		int brightness = (1.0f - coverage) * ((int)moonfadeout);
		CVector sunCoors = CMoon::GetSunDirection();
		sunCoors *= 150.0f;
		CVector pos = pos-sunCoors;
		RwV3dAdd(&worldpos, &campos, &pos);
		if (CSprite::CalcScreenCoors(worldpos, &screenpos, &szx, &szy, false, false)) {
			RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RwTextureGetRaster(gpCoronaTexture[2]));
			RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
			RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
			RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);
			szx *= CCoronas::MoonSize * 2.0f + 4.0f;
			szy *= CCoronas::MoonSize * 2.0f + 4.0f;
			CSprite::RenderOneXLUSprite(screenpos.x, screenpos.y, screenpos.z,
				szx, szy, brightness, brightness, brightness, 255, 1.0f / screenpos.z, 255, 0, 0);
		}
	}
}