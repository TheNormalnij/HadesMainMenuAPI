//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#pragma once

#include "Vector2.h"
#include "TimeSpan.h"
#include "IRectangle.h"

#include "../libs/EASTL-forge1.51/EABase/eabase.h"
#include "../libs/EASTL-forge1.51/string.h"
#include "../libs/EASTL-forge1.51/vector.h"

namespace SGG {
class ScreenManager;
class InputHandler;
enum class ScreenState : uint32_t;
enum class ScreenType : uint32_t;

class GameScreen {
  public:
    virtual void OnExit() = 0;
    virtual void LoadContent() = 0;
    virtual void UnloadContent() = 0;
    virtual void Update(float, const eastl::vector<InputHandler *, eastl::allocator_forge> *) = 0;
    virtual void HandleInput(InputHandler *, float) = 0;
    virtual void HandleNoInput() = 0;
    virtual void Draw(float) = 0;
    virtual bool IsTextComplete(const eastl::basic_string<char8_t, eastl::allocator_forge> *) = 0;
    virtual void ExitScreen() = 0;
    virtual void Clear() = 0;
    virtual void OnControlSchemeChanged(bool) = 0;
    virtual void Init(ScreenManager *, const eastl::basic_string<char8_t, eastl::allocator_forge> *) = 0;
    virtual eastl::vector<IRectangle, eastl::allocator_forge> *
    ComponentBounds(eastl::vector<IRectangle, eastl::allocator_forge> *result) = 0;

    virtual ScreenType GetType() = 0;
    virtual ~GameScreen() = 0;

private:
    bool mTransitionFinished;
    TimeSpan Zero;
    Vectormath::Vector2 mDrawLocation;
    bool mFullscreenSpriteEffect;
    bool mRemoved;
    bool mIsVisible;
    bool mUseFadeTransition;
    bool mBlockLowerInput;
    bool mAllowAllPlayerInput;
    bool mOverPauseMenu;
    bool mAllowDuplicates;
    bool mBlockContentUnload;
    TimeSpan mTransitionOnTime;
    TimeSpan mTransitionOffTime;
    float mTransitionPosition;
    float mUpwardVelocity;
    float mGravity;
    float mBounceMultiplier;
    ScreenState mScreenState;
    bool mIsExiting;
    ScreenManager *mScreenManager;

};
static_assert(sizeof(GameScreen) == 0x60, "Incorrect SGG::GameScreen size");
} // namespace SGG