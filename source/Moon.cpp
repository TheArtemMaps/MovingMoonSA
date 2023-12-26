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
void __cdecl CMoon::Render()
{
	float minute = CClock::ms_nGameClockHours * 60 + CClock::ms_nGameClockMinutes + CClock::ms_nGameClockSeconds / 60.0f;
	float moonfadeout;
	float szx, szy;
	RwV3d screenpos;
	const auto z = CDraw::ms_fFarClipZ;
	const auto rhw = 1.0f / z;
	RwV3d worldpos;
	if (!CGame::CanSeeOutSideFromCurrArea) return;
	CSprite::InitSpriteBuffer();
	RwV3d campos = TheCamera.GetPosition().ToRwV3d(); // Converting CVector to RwV3d, by using ToRwV3d()
	float smoothBrightnessAdjust = 1.9f;
	if ((int)minute > 1100)
	{
		moonfadeout = fabsf(minute - 1100.0f) / smoothBrightnessAdjust;
	}
	else if ((int)minute < 240)
	{
		moonfadeout = 180.0f;
	}
	else
	{
		moonfadeout = 180.0f - fabsf(minute - 240.0f) * smoothBrightnessAdjust;
	}

	if ((int)moonfadeout > 0.0f && (int)moonfadeout < 340)
	{
		float coverage = fmaxf(CWeather::Foggyness, CWeather::CloudCoverage);
		int brightness = (1.0f - coverage) * ((int)moonfadeout);
		CVector sunCoors = CMoon::GetSunDirection();
		sunCoors *= 150.0f;
		CVector pos = pos - sunCoors;
		// Moon phases (WIP) (help)
	/*RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(NULL));
		RwRenderStateSet(rwRENDERSTATESRCBLEND, RWRSTATE(rwBLENDSRCALPHA));
		RwRenderStateSet(rwRENDERSTATEDESTBLEND, RWRSTATE(rwBLENDZERO));
		RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);

		RwV3dAdd(&worldpos, &campos, &pos);
		if (CSprite::CalcScreenCoors(worldpos, &screenpos, &szx, &szy, false, true))
		{
			szx *= CCoronas::MoonSize * 2.0f + 4.0f;
			szy *= CCoronas::MoonSize * 2.0f + 4.0f;
			CSprite::RenderOneXLUSprite(
				screenpos.x, screenpos.y, z,
				szx, szy,
				0, 0, 0, 255,
				rhw,
				255,
				0,
				0
			);
		}

		//
		// Draw moon's mask
		//
		RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(RwTextureGetRaster(gpMoonMask)));
		RwRenderStateSet(rwRENDERSTATESRCBLEND, RWRSTATE(rwBLENDSRCALPHA));
		RwRenderStateSet(rwRENDERSTATEDESTBLEND, RWRSTATE(rwBLENDZERO));
		RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);

		szx *= CCoronas::MoonSize * 2.0f + 4.0f;
		szy *= CCoronas::MoonSize * 2.0f + 4.0f;
		const auto moonMaskSz = szx * 1.7f;
		RwV3d moonMaskPosScr = RwV3d{
			3.7f,
			9.4f * (((float)CClock::ms_nGameClockDays / 31.f - 3.5f)) // Slowly glide on the X axis according to current game day
		};
		RwV3dAdd(&worldpos, &campos, &pos);
		if (CSprite::CalcScreenCoors(worldpos, &moonMaskPosScr, &szx, &szy, false, true))
		{
			// SilentPatch Start
			int alphaFuncBak;
			RwD3D9SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_ALPHA);
			RwRenderStateGet(rwRENDERSTATEALPHATESTFUNCTION, (void*)&alphaFuncBak);
			RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, (void*)rwALPHATESTFUNCTIONALWAYS);
			RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
			RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDZERO);
			// SilentPatch End

			CSprite::RenderOneXLUSprite(
				moonMaskPosScr.x, moonMaskPosScr.y, moonMaskPosScr.z,
				moonMaskSz, moonMaskSz,
				0, 0, 0, 0,
				rhw,
				255,
				0,
				0
			);

			// SilentPatch Start
			RwD3D9SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
			RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, (void*)alphaFuncBak);
			// SilentPatch End
		}*/
		RwV3dAdd(&worldpos, &campos, &pos);
		if (CSprite::CalcScreenCoors(worldpos, &screenpos, &szx, &szy, false, true)) {
			RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
			RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
			RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
			RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
			RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);
			RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RwTextureGetRaster(gpCoronaTexture[2]));
			szx *= CCoronas::MoonSize * 2.7f + 4.0f;
			szy *= CCoronas::MoonSize * 2.7f + 4.0f;
			CSprite::RenderOneXLUSprite(screenpos.x, screenpos.y, z,
				szx * (1.0f) / CDraw::ms_fAspectRatio, szy * (1.3333334f) / CDraw::ms_fAspectRatio, brightness, brightness, brightness, 255, rhw, 255, 0, 0);
			CSprite::FlushSpriteBuffer();
		}
	}
}