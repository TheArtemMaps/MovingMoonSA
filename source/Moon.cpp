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
#include "CTxdStore.h"
using namespace plugin;

void
CMoon::Render() {
	float minute = CClock::ms_nGameClockHours * 60 + CClock::ms_nGameClockMinutes + CClock::ms_nGameClockSeconds / 60.0f;
	float moonfadeout;
	float szx, szy;
	RwV3d screenpos;
	const auto z = CDraw::ms_fFarClipZ;
	const auto rhw = 1.f / z;
	RwV3d worldpos;
	if (!CGame::CanSeeOutSideFromCurrArea)
		return;
	CSprite::InitSpriteBuffer();
	RwV3d campos = TheCamera.GetPosition().ToRwV3d();
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
		CVector pos = pos - sunCoors;
		RwV3dAdd(&worldpos, &campos, &pos);
		if (CSprite::CalcScreenCoors(worldpos, &screenpos, &szx, &szy, false, true)) {
			szx /= CDraw::ms_fAspectRatio;
			//szy /= CDraw::ms_fAspectRatio;
			RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RwTextureGetRaster(gpCoronaTexture[2]));
			RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
			RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
			RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);
			szx *= CCoronas::MoonSize * 2.0f + 4.0f;
			szy *= CCoronas::MoonSize * 2.0f + 4.0f;
			CSprite::RenderOneXLUSprite(screenpos.x, screenpos.y, z,
				szx, szy, brightness, brightness, brightness, 255, rhw, 255, 0, 0);
		}
		CSprite::FlushSpriteBuffer();
	}
}