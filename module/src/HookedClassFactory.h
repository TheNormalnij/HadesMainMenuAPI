//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#pragma once

#include "HookTable.h"

class HookedClassFactory {
  public:
    template <typename T, typename... Args> static T *Create(Args... args);

    template <>
    static SGG::GUIComponentButton *Create<SGG::GUIComponentButton>(SGG::MenuScreen *screenManager) {
        auto constructorPos = HookTable::Instance().GUIComponentButton_GUIComponentButton;
        return CreateHooked<SGG::GUIComponentButton>(constructorPos, screenManager);
    }

    template <> static GamemodeScreen *Create<GamemodeScreen>(SGG::ScreenManager *screenMamaner) {
        auto constructorPos = HookTable::Instance().MenuScreen_constructor_ScreenManager;
        auto *instance = CreateHooked<GamemodeScreen>(constructorPos, screenMamaner);
        instance->iherited_constrictor();
        return instance;
    }

  private:
    template <typename T, typename... Args> static T *CreateHooked(uintptr_t constructorPos, Args... args) {
        auto* _aligned_malloc =
            *reinterpret_cast<void *(__cdecl **)(size_t, size_t)>(HookTable::Instance()._aligned_malloc);

        void *pointer = _aligned_malloc(sizeof(T), std::alignment_of<T>::value);
        return reinterpret_cast<T *(*)(void *, Args...)>(constructorPos)(pointer, args...);
    };

};
