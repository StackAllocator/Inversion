//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#pragma once

#include "raylib.h"
#include <string>
#include <vector>

namespace Inversion {
// ----------------------------------------------------------------------------------------------------
// MainMenu and LevelMenu definition based on abstract interface (Menu).
// ----------------------------------------------------------------------------------------------------
// Draw and store state about the rectangles in the game menu.
class Menu {
public:
  // Pure virtual functions for implementation that is required.
  virtual void draw_menu() = 0;
  virtual void handle_input() = 0;

private:
  struct MenuRectangle {
    Rectangle m_Rect;
    Color m_Color;      // Store the color of the rectangle.
    int m_Id;           // Store unique id of rectangle
    std::string m_Text; // Specify a message for the rectangle.
  };

protected:
  std::vector<MenuRectangle> m_Menu;
};
} // namespace Inversion
