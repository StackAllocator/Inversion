//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#pragma once

#include <array>

#include "./asset_manager.h"
#include "./level.h"
#include "./menu.h"

namespace Inversion {
// ----------------------------------------------------------------------------------------------------
// MainMenu class handles drawing / input in the main game menu.
class MainMenu : public Menu {
public:
  MainMenu();
  // ----------------------------------------------------------------------------------------------------
  // Draw the menu based on initialized menu rects.
  void draw_menu() override;
  // ----------------------------------------------------------------------------------------------------
  // Handle click of buttons in main menu.
  void handle_input() override;
  // ----------------------------------------------------------------------------------------------------
  // Draws balls and connects them with a bezier curve.
  void draw_balls();
  // ----------------------------------------------------------------------------------------------------
  // Updates the balls positions and restricts them to screen dimensions.
  void update_balls();

  // ----------------------------------------------------------------------------------------------------
  bool m_ShouldResume = false;
  // ----------------------------------------------------------------------------------------------------
  bool m_ShouldLevelSelect = false;
  // Used to signal to the game that it should quit.
  bool m_ShouldQuit = false;

private:
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
};

// ----------------------------------------------------------------------------------------------------
// Class that handles the level selection menu.
class LevelSelection : public Menu {
public:
  LevelSelection(LevelManager *level);

  void draw_menu() override;
  void handle_input() override;

  bool mouse_pressed = false;

private:
  // Defines offset for the menu boxes.
  Vector2 m_Offset = {0, 0};

  LevelManager *m_Level;

  // Color m_BoxColor;
  // std::array<bool, 16> m_Activated;
};
} // namespace Inversion
