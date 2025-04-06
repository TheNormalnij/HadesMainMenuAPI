//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#pragma once

#include "FunctionHook.h"
#include "interface/MainMenuScreen.h"

class MainMenuHandler {
  public:
    MainMenuHandler();

    void AddGamemode(const char *name) { gamemodes.push_back(name); }
    void InitializeCustomButtons();

private:
    FunctionHook<"sgg::MainMenuScreen::MainMenuScreen", SGG::MainMenuScreen *, SGG::MainMenuScreen *, void *, void *>
        funHook;

    SGG::MainMenuScreen *mainMenuScreen = nullptr;

    std::vector<std::string> gamemodes;
};
