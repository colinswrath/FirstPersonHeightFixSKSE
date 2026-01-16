#include "PlayerScalePatch.h"


bool PlayerScalePatch::InstallUpdateHook()
{
    auto& trampoline = SKSE::GetTrampoline();
    _OnUpdate        = trampoline.write_call<5>(PlayerScalePatch::On_Update_Hook.address(), OnUpdate);
    logger::info("Installed update hook");
    return true;
}

std::int32_t PlayerScalePatch::OnUpdate()
{
    UpdatePlayerFirstPersonScale();
    return _OnUpdate();
}

void PlayerScalePatch::UpdatePlayerFirstPersonScale()
{
    auto playerCamera = RE::PlayerCamera::GetSingleton();
    auto ui           = RE::UI::GetSingleton();


    if (playerCamera->IsInFirstPerson() && !ui->GameIsPaused()) {
        auto player    = RE::PlayerCharacter::GetSingleton();

        auto firstPNode = player->Get3D1(true)->AsNode();
        auto thirdPNode = player->Get3D1(false)->AsNode();

        if (firstPNode->local.scale != thirdPNode->local.scale) {
            firstPNode->local.scale = thirdPNode->local.scale;
        }
    }
    
}
