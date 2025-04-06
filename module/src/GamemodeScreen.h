//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#pragma once

#include "interface/MenuScreen.h"

class GamemodeScreen : public SGG::MenuScreen {
  public:
    static GamemodeScreen *internal_constructor(SGG::ScreenManager *screenManager);

    private:
    void Init();
};
