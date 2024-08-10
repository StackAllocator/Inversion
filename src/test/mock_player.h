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
#include "./mock_level.h"

#include <array>
#include <gtest/gtest.h>

namespace Inversion {

// ----------------------------------------------------------------------------------------------------
enum class MockActorStates { IDLE, RUN, JUMP_START, JUMP_UP, FALL };
enum class MockEmotionStates { HAPPY, SAD, FEAR };

// ----------------------------------------------------------------------------------------------------
// Class that manages a player object. It handles movement and display.
class MockPlayer {
public:
  MockPlayer();

  // Move the player based on input keystrokes (left, right, jump).
  void move();

  // Set the player position on the screen.
  void set_rect(Vector2 position, Vector2 size);

  void set_position(Vector2 position);
  // Retrieve current player position.
  Vector2 get_position();

private:
  // Handles collision between the player and the environment.
  void handle_collision(std::vector<Rectangle> level, Vector2 &new_pos,
                        bool &on_ground);
  FRIEND_TEST(PlayerTest, player_test);

  // Use plain vector for environment testing.
  std::vector<Rectangle> m_Level;

  // Make the player happy initially.
  MockEmotionStates m_EmotionState = MockEmotionStates::HAPPY;

  // Define player rectangle with positional and size attributes.
  Rectangle m_Player;
  Color m_Color;
  Vector2 m_Start_Pos;
  // Checks if player is flipped.
  bool m_Flipped = false;

  // Start with an idle animation.
  MockActorStates m_MovementState = MockActorStates::IDLE;

  // Defines the player velocity.
  float m_Speed = 200.f;

  // Define the gravity for the player.
  float m_Gravity = 300.f;

  bool hitSide = false;
  bool hitBottom = false;
  bool hitTop = false;

  bool space_pressed = false;
  bool key_right_pressed = false;
  bool key_left_pressed = false;

  // Accelerate player when jumping.
  float m_jumpAcceleration = -450;

  // Damping factor for jump.
  float m_jumpVelocityDampen = 1.125f;

  // Horizontal / vertical velocity.
  Vector2 m_Velocity = {0, 0};

  // Define the player acceleration.
  float m_Acceleration = 0.f;
};
} // namespace Inversion
