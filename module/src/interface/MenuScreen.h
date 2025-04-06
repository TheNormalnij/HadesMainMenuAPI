//
// Copyright (c) Uladzislau Nikalayevich <thenormalnij@gmail.com>. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for details.
//

#pragma once

#include "../libs/EASTL-forge1.51/hash_map.h"
#include "../libs/EASTL-forge1.51/string.h"
#include "../libs/EASTL-forge1.51/vector.h"
#include "GUIComponentReflectionHelper.h"
#include "GameScreen.h"
#include "HookTable.h"
#include "IGUIComponentContainer.h"
#include "IRectangle.h"
#include "Rectangle.h"
#include "ScreenData.h"

namespace SGG {

class GUIComponentAnimation;
class GUIComponentTextBox;
class GUIComponentBox;
class GUIComponentImage;
class GUIComponent;
class GUIComponentButton;

struct MenuScreen_InsertCommand {
    GUIComponent *mToInsert;
    GUIComponent *mLocation;
    bool mIsBefore;
};
static_assert(sizeof(MenuScreen_InsertCommand) == 0x18, "Size of MenuScreen is not 0x4B0");

class MenuScreen : public GameScreen, public IGUIComponentContainer {
  public:
    void AddComponent(GUIComponent *component) {
        reinterpret_cast<void(__fastcall *)(void *, GUIComponent **)>(HookTable::Instance().vector8x8_push)(
            &mComponents, &component);
    }

    GUIComponentReflectionHelper &GetReflectionHelper() { return mReflectionHelper; }

  private:
    using InsertCommand = MenuScreen_InsertCommand;

  private:
    bool mUsingInfoPanel;
    bool mDidDoubleClick;
    float mInfoPanelFadeOut;
    const float GAMEPAD_BUTTON_SCALE;
    const float GAMEPAD_TEXT_OFFSET_X;
    GUIComponent *mRandomUseableComponent;
    Vectormath::Vector2 mPrevSearchDirection;
    eastl::vector<GUIComponent *, eastl::allocator_forge> mPossibleClicks;
    eastl::vector<GUIComponent *, eastl::allocator_forge> mMouseOverChoices;
    eastl::vector<GUIComponent *, eastl::allocator_forge> mPossibleTooltips;
    const Vectormath::Vector2 mZero;
    const IRectangle mIEmptyRect;
    const Rectangle mEmptyRect;
    bool mDrawSelected;
    bool mLoadDefaultComponents;
    bool mPrevGamepadCursorControl;
    bool mSomethingActivated;
    int mCurrentColumn;
    int mCurrentRow;
    float mLastManualSelectionChange;
    float mLastRepeatSelectionChange;
    float mLastSelectionTime;
    float mLastClickTime;
    float mPrevGamepadCursorSpeed;
    float mPrevGamepadCursorSlowSpeed;
    uint8_t mButtonArrangement[4];
    GUIComponent *mLastComponentClicked;
    GUIComponent *mMouseOverComponent;
    eastl::basic_string<char8_t, eastl::allocator_forge> mItemName;
    eastl::vector<GUIComponent *, eastl::allocator_forge> mComponents;
    eastl::vector<GUIComponent *, eastl::allocator_forge> mDrawOnly;
    Vectormath::Vector2 mLocation;
    Vectormath::Vector2 mSize;
    eastl::vector<int, eastl::allocator_forge> mColumnLengths;
    eastl::vector<GUIComponent *, eastl::allocator_forge> mInfoPanelComponents;
    GUIComponentReflectionHelper mReflectionHelper;
    bool mAllowInteractUnder;
    bool mConfirmInfoPanel;
    long double mOpenTime;
    float mTooltipShowTimeRemaining;
    float mTooltipHideTimeRemaining;
    eastl::basic_string<char8_t, eastl::allocator_forge> mTitle;
    eastl::basic_string<char8_t, eastl::allocator_forge> mDataPath;
    GUIComponentBox *mDimBox;
    GUIComponentBox *mBack;
    GUIComponentImage *mBackground;
    GUIComponentAnimation *mAnimatedBackground;
    GUIComponentTextBox *mTitleText;
    GUIComponentImage *mTitleTextBacking;
    GUIComponentTextBox *mTooltippedTextbox;
    int mTooltippedTargetId;
    eastl::vector<eastl::basic_string<char8_t, eastl::allocator_forge>, eastl::allocator_forge> mActiveTooltips;
    eastl::vector<GUIComponentImage *, eastl::allocator_forge> mTooltipBackings;
    eastl::vector<GUIComponentTextBox *, eastl::allocator_forge> mTooltipHeaders;
    eastl::vector<GUIComponentTextBox *, eastl::allocator_forge> mTooltipBodys;
    eastl::hash_map<eastl::basic_string<char8_t, eastl::allocator_forge>, GUIComponent *,
                    eastl::hash<eastl::basic_string<char8_t, eastl::allocator_forge>>,
                    eastl::equal_to<eastl::basic_string<char8_t, eastl::allocator_forge>>, eastl::allocator_forge, 0>
        mReflectionMap;
    GUIComponentButton *mConfirmButton;
    GUIComponentButton *mCancelButton;
    GUIComponentButton *mXButton;
    GUIComponentButton *mYButton;
    GUIComponentAnimation *mTutorialBoxBackGlow;
    GUIComponentAnimation *mTutorialBoxArrow;
    GUIComponentAnimation *mTutorialBoxBack;
    GUIComponentTextBox *mTutorialBoxText;
    GUIComponentAnimation *mInfoPanel;
    GUIComponentTextBox *mInfoText;
    GUIComponent *mSelectedComponent;
    Vectormath::Vector2 mTooltipStartLocation;
    ScreenData mData;
    eastl::vector<MenuScreen::InsertCommand, eastl::allocator_forge> mInsertCommands;
    GUIComponent *mTooltippedComponent;
};
static_assert(sizeof(MenuScreen) == 0x4B0, "Size of MenuScreen is not 0x4B0");
} // namespace SGG