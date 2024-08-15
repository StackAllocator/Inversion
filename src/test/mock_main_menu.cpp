//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#include <array>
#include <iostream>

#include "./mock_main_menu.h"
#include "./mock_level.h"

namespace Inversion {
// ----------------------------------------------------------------------------------------------------
MockMainMenu::MockMainMenu()
  : mouse_pressed(false)
{
  // Add selectable menu items for the menu.
  m_Menu.push_back({{20, 40, 10, 10}, WHITE, 1, "FIRST"});
  m_Menu.push_back({{20, 70, 10, 10}, WHITE, 2, "SECOND"});
  m_Menu.push_back({{20, 90, 10, 10}, WHITE, 3, "THIRD"});

  // Set ball positions and properties.
  first_ball = {1200, 540};
  second_ball = {1600, 540};
  third_ball = {1400, 540};

  radius = 30.f;
  ball_speed = 500.f;
  first_up = false;
}

// ----------------------------------------------------------------------------------------------------
// No implementation for mock.
void MockMainMenu::draw_menu() {}

// ----------------------------------------------------------------------------------------------------
void MockMainMenu::handle_input() {

  // Retrieve the current mouse position.
  for (auto &menu : m_Menu) {

    // Check if the mouse is on menu box and color it gray if that's the case.
    if (current_mouse_pos.x >= menu.m_Rect.x &&
        current_mouse_pos.x <= menu.m_Rect.x + menu.m_Rect.width &&
        current_mouse_pos.y >= menu.m_Rect.y &&
        current_mouse_pos.y <= menu.m_Rect.y + menu.m_Rect.height) {

      menu.m_Color = GRAY;

      // If the left mouse button is pressed, handle action based on selected
      // box.
      if (mouse_pressed) {
        switch (menu.m_Id) {
        case 1:
          m_ShouldResume = true;
          break;
        case 2:
          m_ShouldLevelSelect = true;
          break;
        case 3:
          m_ShouldQuit = true;
          break;
        }
      }
    }
    // Reset the menu-box color to white if it is not currently selected.
    else {
      menu.m_Color = WHITE;
    }
  }
}

// ----------------------------------------------------------------------------------------------------
// Empty impl. for mock.
void MockMainMenu::draw_balls() {}

// ----------------------------------------------------------------------------------------------------
void MockMainMenu::update_balls() {
  // Reset the balls if out of bounds.
  if (first_ball.y < radius || second_ball.y < radius)
    first_up = !first_up;

  // Move in one direction.
  if (first_up) {
    first_ball.y -= ball_speed;
    second_ball.y += ball_speed;
  }
  // Swap direction.
  else {
    first_ball.y += ball_speed;
    second_ball.y -= ball_speed;
  }
}

// ----------------------------------------------------------------------------------------------------
// Class that handles the level selection menu.
MockLevelSelection::MockLevelSelection() {

  for (int i = 0; i < 16; ++i) {
    if (i == 0) {
      m_Offset.y = 120;
    }
    // After fox boxes have been initialized in a row, move to the next lane.
    else if (i % 4 == 0) {
      m_Offset.y += 250;
      m_Offset.x = 0; // Reset offset to start value.
    }

    m_Offset.x += 250;

    // Provide menu the appropriate box properties.
    m_Menu.push_back({{280 + m_Offset.x, m_Offset.y, 100, 100},
                      WHITE,
                      i,
                      std::to_string(i + 1)});
  }
}

// ----------------------------------------------------------------------------------------------------
// No implementation for mock.
void MockLevelSelection::draw_menu() {}

// ----------------------------------------------------------------------------------------------------
void MockLevelSelection::handle_input() {

  for (auto &box : m_Menu) {
    // Check if the mouse is on menu box and color it gray if that's the case.
    if (current_mouse_pos.x >= box.m_Rect.x &&
        current_mouse_pos.x <= box.m_Rect.x + box.m_Rect.width &&
        current_mouse_pos.y >= box.m_Rect.y &&
        current_mouse_pos.y <= box.m_Rect.y + box.m_Rect.height) {

      box.m_Color = GRAY;
      // If the left mouse button is pressed, handle action based on selected
      // box.
    }
    // Reset the menu-box color to white if it is not currently selected.
    else {
      box.m_Color = WHITE;
    }
  }
}
} // namespace Inversion
