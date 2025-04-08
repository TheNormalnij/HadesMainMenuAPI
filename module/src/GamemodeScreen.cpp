//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include "pch.h"

#include "GamemodeScreen.h"
#include "../libs/EASTL-forge1.51/string.h"
#include "HookTable.h"
#include "GamemodeManager.h"
#include "HookedClassFactory.h"

static uintptr_t GamemodeScreen_vtb[26];

SGG::ScreenType GamemodeScreen::GetType_VirtImpl(GamemodeScreen*) { return SGG::ScreenType::SettingsMenu; }

void GamemodeScreen::initialize_vft() {
    std::memcpy(GamemodeScreen_vtb, (void *)HookTable::Instance().MenuScreen_vft, sizeof(GamemodeScreen_vtb));
    GamemodeScreen_vtb[13] = reinterpret_cast<uintptr_t>(&GetType_VirtImpl);
}

void GamemodeScreen::iherited_constrictor() {
    *reinterpret_cast<void**>(this) = GamemodeScreen_vtb;
    mBlockLowerInput = true;
    mOverPauseMenu = true;
    CreateComponents();
}

void GamemodeScreen::CreateComponents() {
    CreateBack(0.8);
    eastl::string textureName{""};
    CreateBackground(&textureName);
    CreateTitleText(this);
    CreateCancelButton(this);

    mCancelButton->GetActivateAction().AddCallBack([this]() { Close(); });

    auto *buttonTemplate = HookedClassFactory::Create<SGG::GUIComponentButton, SGG::MenuScreen *>(this);
    buttonTemplate->SetParent(this);
    AddComponent(buttonTemplate);
    GetReflectionHelper().ReflectComponent("mSettingsButton", buttonTemplate);

    Load("GUI/SettingsMenuScreen.sjson");
    buttonTemplate->SetLocation({0.0f, 0.0f});
    buttonTemplate->SetScale(0.0f);

    float offsetY = 0.0f;

    for (auto &gamemode : GamemodeManager::Instance().GetGamemodes()) {
        auto *gamemodeBtn = HookedClassFactory::Create<SGG::GUIComponentButton, SGG::MenuScreen *>(this);
        gamemodeBtn->Load(&buttonTemplate->GetComponentData());

        gamemodeBtn->SetLocation({960.0f, 420.0f + offsetY});
        gamemodeBtn->SetParent(this);
        gamemodeBtn->SetText(gamemode.GetName().c_str());
        AddComponent(gamemodeBtn);

        const eastl::string fontName{"AlegreyaSansSCRegular"};
        gamemodeBtn->SetFont(&fontName);
        gamemodeBtn->SetTextColor(0xFFCCCCCC);

        offsetY += 75.0f;

        gamemodeBtn->GetActivateAction().AddCallBack([&gamemode, this]() {
            Close();
            gamemode.Activate();
        });
    }

    mTitleText->SetText("Gamemode");
}

void GamemodeScreen::Close() {
    ExitScreen();
    // I don't need to do it for another buttons. Why?
    mCancelButton->GetActivateAction().RemoveAll();
}
