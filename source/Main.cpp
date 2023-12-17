#include "plugin.h"
#include "Moon.h"
#include "MemoryMgr.h"
#include <game_sa/CCam.h>
#include <game_sa/CCamera.h>
#include "CCoronas.h"
#include "Utility.h"
using namespace plugin;
plugin::ThiscallEvent<AddressList<0x7178F0, H_CALL>, PRIORITY_BEFORE, ArgPickNone, void()> renderMoon;
auto& GetActiveCam() { return TheCamera.m_aCams[TheCamera.m_nActiveCam]; }

void __fastcall MoonSizePatch(CWeapon* _this, int, CPed* owner, CVector* vecOrigin, CVector* _vecEffectPosn, CEntity* targetEntity, CVector* vecTarget, CVector* arg_14) {
    int weaponType = _this->m_eWeaponType;
   const CCam& Mode = GetActiveCam();

    if (weaponType == eWeaponType::WEAPON_SNIPERRIFLE && Mode.m_nMode == MODE_SNIPER) {
        ((char(__thiscall*)(CWeapon*, CPed*, CEntity*, CVector*))0x73AAC0)(_this, owner, targetEntity, vecTarget); // FireSniper 
        ((char(__thiscall*)(CWeapon*, CPed*, CVector*, CVector*, CEntity*, CVector*, CVector*))0x742300)(_this, owner, vecOrigin, vecOrigin, targetEntity, vecOrigin, arg_14); // Fire
        if (FindPlayerPed() == owner) {
            switch (Mode.m_nMode) {
            case MODE_M16_1STPERSON:
            case MODE_SNIPER:
            case MODE_CAMERA:
            case MODE_ROCKETLAUNCHER:
            case MODE_ROCKETLAUNCHER_HS:
            case MODE_M16_1STPERSON_RUNABOUT:
            case MODE_SNIPER_RUNABOUT:
            case MODE_ROCKETLAUNCHER_RUNABOUT:
            case MODE_ROCKETLAUNCHER_RUNABOUT_HS:
                break;
            default:
                return;
            }
        }
        CCam* cam = &TheCamera.m_aCams[TheCamera.m_nActiveCam];
        CVector dir = cam->m_vecFront;
        // moving Moon
        CVector moonDirection = moonDirection - CMoon::GetSunDirection();
        if (DotProduct(dir, CVector(moonDirection.x, moonDirection.y, moonDirection.z)) > 0.997f)
            CCoronas::MoonSize = (CCoronas::MoonSize + 1) & 7;
        dir.Normalise();
        dir *= 16.0f;
    }
    else {
        ((char(__thiscall*)(CWeapon*, CPed*, CVector*, CVector*, CEntity*, CVector*, CVector*))0x742300)(_this, owner, vecOrigin, _vecEffectPosn, targetEntity, vecTarget, arg_14); // Fire
    }
}
class MovingMoonSA {
public:
    MovingMoonSA() {
        // Render moon
        renderMoon += []() {
            CMoon::Render();
        };
        // Replace default SA moon
        InjectHook(0x713D02, CMoon::Render);
        // Repair moon size changing with a sniper rifle
        InjectHook(0x61ECCD, MoonSizePatch);
        InjectHook(0x628328, MoonSizePatch);
        InjectHook(0x62B109, MoonSizePatch);
        InjectHook(0x62B12A, MoonSizePatch);
        InjectHook(0x68626D, MoonSizePatch);
        InjectHook(0x686283, MoonSizePatch);
        InjectHook(0x686787, MoonSizePatch);
       // InjectHook(0x713C4C, renderMoonMask, PATCH_JUMP);
    }
} MovingMoonSA;