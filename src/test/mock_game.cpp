//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#include "./mock_game.h"
#include "./mock_level.h"

namespace Inversion {
// ----------------------------------------------------------------------------------------------------
// MainMenu class handles drawing / input in the main game menu.

MockGame::MockGame() {}
MockGame::~MockGame() {}

// ----------------------------------------------------------------------------------------------------
void MockGame::update_game() {
  // ----------------------------------------------------------------------------------------------------
  // Handle input logic.
  // ----------------------------------------------------------------------------------------------------
  switch (m_GameState) {
  // ----------------------------------------------------------------------------------------------------
  case MockGameState::TITLE:
    // Update to Menu when ESC is pressed.
    if (ESCAPE_PRESSED) {
      m_GameState = MockGameState::MENU;
    }
    // Update to the first level if any other key is pressed.
    else if (ANY_KEY_PRESSED) {
      m_GameState = MockGameState::GAME;
    }
    break;
  // ----------------------------------------------------------------------------------------------------
  case MockGameState::GAME:
    if (ESCAPE_PRESSED) {
      m_GameState = MockGameState::MENU;
    }
    m_player.move();
    break;
  // ----------------------------------------------------------------------------------------------------
  case MockGameState::MENU:
    m_MockMainMenu.handle_input();
    m_MockMainMenu.update_balls();

    break;
  case MockGameState::LEVEL_SELECTION:
    break;
  }
  // ----------------------------------------------------------------------------------------------------
}
} // namespace Inversion
