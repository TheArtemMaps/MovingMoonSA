#include "plugin.h"
#include "Moon.h"
#include "MemoryMgr.h"
using namespace plugin;
plugin::ThiscallEvent<AddressList<0x7178F0, H_CALL>, PRIORITY_BEFORE, ArgPickNone, void()> renderMoon;

class MovingMoonSA {
public:
    MovingMoonSA() {
        // Render moon
        renderMoon += []() {
           CMoon::Render();
        };
        // Replace default SA moon
        InjectHook(0x713D02, CMoon::Render);
    }
} MovingMoonSA;
