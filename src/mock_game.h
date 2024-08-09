//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#pragma once

#include <gtest/gtest.h>

#include "./game.h"
#include "./level.h"
#include "./menu.h"

namespace Inversion {
// ----------------------------------------------------------------------------------------------------
// MainMenu class handles drawing / input in the main game menu.
class MockMainMenu : public Menu {
public:
  MockMainMenu();
  // ----------------------------------------------------------------------------------------------------
  // Empty function for mock.
  void draw_menu() override;
  // ----------------------------------------------------------------------------------------------------
  // Handle click of buttons in main menu.
  void handle_input() override;
  // ----------------------------------------------------------------------------------------------------
  // Draws balls and connects them with a bezier spline.
  void draw_balls();
  // ----------------------------------------------------------------------------------------------------
  // Updates the balls positions and restricts them to screen dimensions.
  void update_balls();

private:
  FRIEND_TEST(gameTest, MockMainMenu);
  // Coordinates for the first ball in the animation.
  Vector2 first_ball;
  // Coordinates for the second ball in the animation.
  Vector2 second_ball;
  // Coordinates for the third (rotating) ball in the animation.
  Vector2 third_ball;

  // Controls upward movement of balls.
  bool first_up;
  // Ball speed determines the actual speed of the ball.
  float ball_speed;
  // Radius of the ball.
  float radius;

  bool IS_MOUSE_PRESSED;
};

class MockGame {
  // Define the three major game states.
  // ----------------------------------------------------------------------------------------------------
public:
  MockGame();
  ~MockGame();

  // Use this public variable to simulate an ESC-key press by raylib.
  bool ESCAPE_PRESSED = false;
  bool ANY_KEY_PRESSED = false;

  // ----------------------------------------------------------------------------------------------------
  void update_game();

private:
  FRIEND_TEST(gameTest, MockGame);

  GameState m_GameState;
  Level m_Level;
  Player m_player;
  MockMainMenu m_MockMainMenu;
};

class MockPlayer {
public:
  void move();
private:
  void handle_collision();
};
} // namespace Inversion
