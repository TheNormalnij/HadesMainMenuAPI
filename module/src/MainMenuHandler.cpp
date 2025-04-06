//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include "pch.h"

#include "MainMenuHandler.h"
#include "HookTable.h"
#include "interface/eastl_string.h"
#include "GamemodeScreen.h"

MainMenuHandler::MainMenuHandler() : funHook{(void *)HookTable::Instance().MainMenuScreen_MainMenuScreen, 12 } {
    funHook.Install();
    funHook.onPostFunction = [this](SGG::MainMenuScreen *mainMenuScreen) {
        this->mainMenuScreen = mainMenuScreen;
        this->InitializeCustomButtons();
        return mainMenuScreen;
    };
}

void MainMenuHandler::InitializeCustomButtons() {
    auto exitBtn = mainMenuScreen->GetExitButton();
    auto exitBtnPos = exitBtn->GetLocation();
    exitBtn->SetLocation({exitBtnPos.mX, exitBtnPos.mY + 90});

    auto *gamemodeBtn = SGG::GUIComponentButton::internal_constructor(mainMenuScreen);
    gamemodeBtn->Load(&exitBtn->GetComponentDara());

    gamemodeBtn->SetLocation(exitBtnPos);
    gamemodeBtn->SetParent(mainMenuScreen);
    gamemodeBtn->SetText("Select  gamemode");
    mainMenuScreen->AddComponent(gamemodeBtn);
    //mainMenuScreen->GetReflectionHelper().ReflectComponent("mGamemode", gamemodeBtn);

    eastl::string gamemodeBtnText{"Credits_AlegreyaSansSCExtraBold"};
    gamemodeBtn->SetFont(&gamemodeBtnText);
    gamemodeBtn->SetTextColor(0xFFCCCCCC);

    auto &clickHandler = gamemodeBtn->GetActivateAction();
    clickHandler.AddCallBack([]() { 
        //GamemodeScreen* gamemodeMenu = GamemodeScreen::internal_constructor();
    });
}

