//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#include "./mock_game.h"
#include "./menu.h"

namespace Inversion {
// ----------------------------------------------------------------------------------------------------
// MainMenu class handles drawing / input in the main game menu.
MockMainMenu::MockMainMenu() {
  m_Menu.push_back({{200, 400, 265, 100}, WHITE, 1, "RESUME"});
  m_Menu.push_back({{200, 550, 500, 100}, WHITE, 2, "SELECT LEVEL"});
  m_Menu.push_back({{200, 700, 160, 100}, WHITE, 3, "EXIT"});

  // Set ball positions and properties.
  first_ball = {1200, 540};
  second_ball = {1600, 540};
  third_ball = {1400, 540};
  radius = 30.f;
  ball_speed = 1.f;
  first_up = false;
}
// ----------------------------------------------------------------------------------------------------
// Empty function implementation for mock.
void MockMainMenu::draw_menu() {}
// ----------------------------------------------------------------------------------------------------
// Handle click of buttons in main menu.
void MockMainMenu::handle_input() {
  Vector2 current_mouse_pos = GetMousePosition();
  for (auto &menu : m_Menu) {
    // Check if mouse is in menu-box and color it if so.
    if (current_mouse_pos.x >= menu.m_Rect.x &&
        current_mouse_pos.x <= menu.m_Rect.x + menu.m_Rect.width &&
        current_mouse_pos.y >= menu.m_Rect.y &&
        current_mouse_pos.y <= menu.m_Rect.y + menu.m_Rect.height) {
      menu.m_Color = GRAY;

      if (IS_MOUSE_PRESSED) {
      }
    } else {
      menu.m_Color = WHITE;
    }
  }
}

// ----------------------------------------------------------------------------------------------------
// Draws balls and connects them with a bezier spline.
void MockMainMenu::draw_balls() {}
// ----------------------------------------------------------------------------------------------------
// Updates the balls positions and restricts them to screen dimensions.
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

MockGame::MockGame() : m_player(&m_Level) {}
MockGame::~MockGame() {}

// ----------------------------------------------------------------------------------------------------
void MockGame::update_game() {
  // ----------------------------------------------------------------------------------------------------
  // Handle input logic.
  // ----------------------------------------------------------------------------------------------------
  switch (m_GameState) {
  // ----------------------------------------------------------------------------------------------------
  case GameState::TITLE:
    // Update to Menu when ESC is pressed.
    if (ESCAPE_PRESSED) {
      m_GameState = GameState::MENU;
    }
    // Update to the first level if any other key is pressed.
    else if (ANY_KEY_PRESSED) {
      m_GameState = GameState::GAME;
    }
    break;
  // ----------------------------------------------------------------------------------------------------
  case GameState::GAME:
    if (ESCAPE_PRESSED) {
      m_GameState = GameState::MENU;
    }
    m_player.move();
    break;
  // ----------------------------------------------------------------------------------------------------
  case GameState::MENU:
    m_MockMainMenu.handle_input();
    m_MockMainMenu.update_balls();

    break;
  case GameState::LEVEL_SELECTION:
    break;
  }
  // ----------------------------------------------------------------------------------------------------
}
} // namespace Inversion
