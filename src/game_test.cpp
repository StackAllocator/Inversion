//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#include "./mock_game.h"
#include <gtest/gtest.h>

namespace Inversion {
TEST(gameTest, MockMainMenu) {
  MockMainMenu mock_menu;

  ASSERT_FLOAT_EQ(mock_menu.ball_speed, 1);

  // -----------------------------------------
  ASSERT_EQ(mock_menu.first_ball.x, 1200);
  ASSERT_EQ(mock_menu.first_ball.y, 540);

  ASSERT_EQ(mock_menu.second_ball.x, 1600);
  ASSERT_EQ(mock_menu.second_ball.y, 540);

  ASSERT_EQ(mock_menu.third_ball.x, 1400);
  ASSERT_EQ(mock_menu.third_ball.y, 540);

  mock_menu.radius = 20;
  mock_menu.first_ball.y = 10; // 10 < 20

  ASSERT_EQ(mock_menu.first_up, false);

  mock_menu.update_balls();

  ASSERT_EQ(mock_menu.first_up, true);
  ASSERT_FLOAT_EQ(mock_menu.first_ball.y, 9);
  mock_menu.first_up = true;

  mock_menu.update_balls();

  ASSERT_FLOAT_EQ(mock_menu.first_ball.y, 10);
  // -----------------------------------------
}

TEST(gameTest, MockGame) {
  // Instantiate mock_game object.
  MockGame mock_game;

  // Set initial game state.
  mock_game.m_GameState = GameState::TITLE;
  mock_game.ESCAPE_PRESSED = false;

  // Update the game based on current game state.
  mock_game.update_game();
  // ------------------------------------------------
  ASSERT_EQ(mock_game.ESCAPE_PRESSED, false);
  ASSERT_EQ(mock_game.m_GameState, GameState::TITLE);
  // ------------------------------------------------

  mock_game.ESCAPE_PRESSED = true;
  mock_game.update_game();
  // ------------------------------------------------
  ASSERT_EQ(mock_game.ESCAPE_PRESSED, true);
  ASSERT_EQ(mock_game.m_GameState, GameState::MENU);
  // ------------------------------------------------

  mock_game.ESCAPE_PRESSED = false;
  mock_game.update_game();
  // ------------------------------------------------
  ASSERT_EQ(mock_game.ESCAPE_PRESSED, false);
  ASSERT_EQ(mock_game.m_GameState, GameState::MENU);
  // ------------------------------------------------

  mock_game.m_GameState = GameState::TITLE;
  mock_game.ANY_KEY_PRESSED = false;
  mock_game.ESCAPE_PRESSED = false;
  mock_game.update_game();
  // ------------------------------------------------
  ASSERT_EQ(mock_game.ANY_KEY_PRESSED, false);
  ASSERT_EQ(mock_game.ESCAPE_PRESSED, false);
  ASSERT_EQ(mock_game.m_GameState, GameState::TITLE);
  // ------------------------------------------------
  mock_game.ANY_KEY_PRESSED = true;
  mock_game.update_game();
  // ------------------------------------------------
  ASSERT_EQ(mock_game.m_GameState, GameState::GAME);
  // ------------------------------------------------
}
} // namespace Inversion
