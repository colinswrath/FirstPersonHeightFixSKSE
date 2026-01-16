#include "PlayerScalePatch.h"

#include <stddef.h>

void InitListener(SKSE::MessagingInterface::Message* a_msg) noexcept
{
    switch (a_msg->type)
    {
    case SKSE::MessagingInterface::kDataLoaded:
        break;
    case SKSE::MessagingInterface::kPostLoadGame:
        logger::debug("LOAD");
        logger::debug("--------------");
        if (!PlayerScalePatch::InstallUpdateHook()) {
            logger::error("Hook installation failed.");
        }
        break;
    }
}


SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
    Init(skse);

    const auto plugin{ SKSE::PluginDeclaration::GetSingleton() };
    const auto name{ plugin->GetName() };
    const auto version{ plugin->GetVersion() };

    logger::init();
    logger::info("{} {} is loading...", name, version);
    SKSE::AllocTrampoline(14);
    auto messaging = SKSE::GetMessagingInterface();
    if (!messaging->RegisterListener(InitListener)) {
        return false;
    }

    logger::info("{} has finished loading.", name);

    return true;
}
