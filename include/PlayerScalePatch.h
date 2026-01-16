#pragma once

class PlayerScalePatch
{
public:
    inline static REL::Relocation<std::uintptr_t> OnFrame_Update_Hook{ REL::RelocationID(35565, 36564), REL::Relocate(0x1E, 0x6E) };
    static bool InstallUpdateHook();

protected:

    static void                                       UpdatePlayerFirstPersonScale();
    inline static std::int32_t                        OnUpdate(std::int64_t a1);
    inline static REL::Relocation<decltype(OnUpdate)> _OnUpdate;
    inline static bool                                       AreMenusOpen();
};
