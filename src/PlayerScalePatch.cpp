#include "PlayerScalePatch.h"


bool PlayerScalePatch::InstallUpdateHook()
{
    auto& trampoline = SKSE::GetTrampoline();
    _OnUpdate        = trampoline.write_call<5>(PlayerScalePatch::OnFrame_Update_Hook.address(), OnUpdate);
    logger::info("Installed update hook");
    return true;
}

std::int32_t PlayerScalePatch::OnUpdate(std::int64_t a1)
{
    UpdatePlayerFirstPersonScale();
    return _OnUpdate(a1);
}

void PlayerScalePatch::UpdatePlayerFirstPersonScale()
{
    auto playerCamera = RE::PlayerCamera::GetSingleton();
    auto player    = RE::PlayerCharacter::GetSingleton();
    if (!AreMenusOpen() && player->Is3DLoaded() && playerCamera && playerCamera->IsInFirstPerson()) {

        auto firstP3d = player->Get3D(true);
        auto thirdP3d = player->Get3D(false);
        if (firstP3d && thirdP3d) {
            if (firstP3d->local.scale != thirdP3d->local.scale) {
                firstP3d->local.scale = thirdP3d->local.scale;
            }
        }
    }
}

bool PlayerScalePatch::AreMenusOpen()
{
    auto ui = RE::UI::GetSingleton();

    return ui->GameIsPaused() || ui->IsMenuOpen("Main Menu") || ui->IsMenuOpen("loading Menu") || ui->IsMenuOpen("MapMenu");
}
