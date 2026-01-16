#include "PlayerScalePatch.h"
#include <stddef.h>


SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
    Init(skse);

    const auto plugin{ SKSE::PluginDeclaration::GetSingleton() };
    const auto name{ plugin->GetName() };
    const auto version{ plugin->GetVersion() };

    logger::init();
    logger::info("{} {} is loading...", name, version);
    SKSE::AllocTrampoline(14);
    if (!PlayerScalePatch::InstallUpdateHook()) {
        logger::error("Hook installation failed.");
    }

    logger::info("{} has finished loading.", name);

    return true;
}
