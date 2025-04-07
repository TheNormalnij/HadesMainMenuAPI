//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include "pch.h"

#include "GamemodeScreen.h"
#include "../libs/EASTL-forge1.51/string.h"
#include "HookTable.h"

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

    mCancelButton->GetActivateAction().AddCallBack([this]() { ExitScreen(); });

    Load("GUI/SettingsMenuScreen.sjson");
    mTitleText->SetText("Gamemode");
}