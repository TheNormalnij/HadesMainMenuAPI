//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#pragma once

#include "interface/MenuScreen.h"

class GamemodeScreen : public SGG::MenuScreen {
  public:
    void iherited_constrictor();
    static void initialize_vft();

  private:
    static SGG::ScreenType GetType_VirtImpl(GamemodeScreen *self);

    void CreateComponents();
};
