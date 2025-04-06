//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#include "pch.h"

#include "GamemodeScreen.h"

GamemodeScreen *GamemodeScreen::internal_constructor(SGG::ScreenManager *screenManager) {
    void *pointer = _aligned_malloc(sizeof(GamemodeScreen), std::alignment_of<GamemodeScreen>::value);
    GamemodeScreen* self = reinterpret_cast<GamemodeScreen *(*)(void *, SGG::ScreenManager *)>(
        HookTable::Instance().MenuScreen_costructor_ScreenManager)(pointer, screenManager);

    self->Init();
    return self;
}

void GamemodeScreen::Init() {

}