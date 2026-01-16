#pragma once

class PlayerScalePatch
{
public:
    inline static REL::Relocation<std::uintptr_t> On_Update_Hook{ REL::RelocationID(35565, 36564), REL::Relocate(0x748, 0xC26) };
    static bool InstallUpdateHook();

protected:

    static void                                       UpdatePlayerFirstPersonScale();
    inline static std::int32_t                        OnUpdate();
    inline static REL::Relocation<decltype(OnUpdate)> _OnUpdate;
};
