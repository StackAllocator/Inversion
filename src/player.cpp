//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#include "raylib.h"
#include <iostream>
#include <memory>

#include "./asset_manager.h"
#include "./level.h"
#include "./player.h"

namespace Inversion {

// ----------------------------------------------------------------------------------------------------
Player::Player(Level *level) : m_Color(WHITE), m_Level(level) {}

// ----------------------------------------------------------------------------------------------------
void Player::set_rect(Vector2 position, Vector2 size) {

  // Set player position and initial starting position of the level.
  m_Player.x = m_Start_Pos.x = position.x;
  m_Player.y = m_Start_Pos.y = position.y;

  m_Player.width = size.x;
  m_Player.height = size.y;

  // Reset the emotion state to a happy face.
  m_EmotionState = EmotionStates::HAPPY;
}

// ----------------------------------------------------------------------------------------------------
void Player::handle_collision(std::vector<Rectangle> &level, Vector2 &new_pos) {
  bool on_ground = false;

  // Iterate over every obstacle in the level and check for collision.
  for (const Rectangle &obstacle : level) {
    if (CheckCollisionRecs(
            {new_pos.x, new_pos.y, m_Player.width, m_Player.height},
            obstacle)) {
      // Handle collision from the top
      if (!m_Flipped && m_Player.y < obstacle.y &&
          new_pos.y + m_Player.height > obstacle.y) {
        m_Velocity.y = 0;
        new_pos.y = obstacle.y - m_Player.height;
        on_ground = true;
      }
      // Handle collision from the bottom when flipped
      else if (m_Flipped && m_Player.y > obstacle.y &&
               new_pos.y < obstacle.y + obstacle.height) {
        m_Velocity.y = 0;
        new_pos.y = obstacle.y + obstacle.height;
        on_ground = true;
      }
      // Handle collision from the sides
      else if (new_pos.x + m_Player.width > obstacle.x &&
               m_Player.x < obstacle.x) {
        new_pos.x = obstacle.x - m_Player.width;
      } else if (new_pos.x < obstacle.x + obstacle.width &&
                 m_Player.x > obstacle.x) {
        new_pos.x = obstacle.x + obstacle.width;
      }
    }
  }

  if (on_ground) {
    m_MovementState = ActorStates::IDLE;
  }
}

// ----------------------------------------------------------------------------------------------------
void Player::draw() {
  if (!m_Flipped) {
    DrawTexturePro(AssetManager::get_texture("armor"), {0, 0, 390, 590},
                   {m_Player.x - 18, m_Player.y + 30, 78, 118}, {0, 0}, 0,
                   WHITE);
    switch (m_EmotionState) {
    case EmotionStates::HAPPY:
      DrawTexture(AssetManager::get_texture("happy"), m_Player.x - 10,
                  m_Player.y - 8, WHITE);
      break;
    case EmotionStates::SAD:
      DrawTexture(AssetManager::get_texture("sad"), m_Player.x - 10,
                  m_Player.y - 8, WHITE);
      break;
    case EmotionStates::FEAR:
      DrawTexture(AssetManager::get_texture("fear"), m_Player.x - 10,
                  m_Player.y - 8, WHITE);
      break;
    default:
      throw std::runtime_error("Emotion state invalid!\n");
      break;
    }
  } else {
    DrawTexturePro(
        AssetManager::get_texture("armor"), {0, 0, 390, 590},
        {m_Player.x + 55, m_Player.y + m_Player.height - 30, 78, 118}, {0, 0},
        180, WHITE);
    switch (m_EmotionState) {
    case EmotionStates::HAPPY:
      DrawTexturePro(
          AssetManager::get_texture("happy"), {0, 0, 64, 64},
          {m_Player.x + 50, m_Player.y + m_Player.height + 10, 64, 64}, {0, 0},
          180, WHITE);
      break;
    case EmotionStates::SAD:
      DrawTexturePro(
          AssetManager::get_texture("sad"), {0, 0, 64, 64},
          {m_Player.x + 50, m_Player.y + m_Player.height + 10, 64, 64}, {0, 0},
          180, WHITE);
      break;
    case EmotionStates::FEAR:
      DrawTexturePro(
          AssetManager::get_texture("fear"), {0, 0, 64, 64},
          {m_Player.x + 50, m_Player.y + m_Player.height + 10, 64, 64}, {0, 0},
          180, WHITE);
      break;
    default:
      throw std::runtime_error("Emotion state invalid!\n");
      break;
    }
  }
}

// ----------------------------------------------------------------------------------------------------
void Player::move() {
  // Compute the delta once.
  float delta = GetFrameTime();

  bool want_jump = IsKeyDown(KEY_SPACE);
  bool want_flip = IsKeyPressed(KEY_G);

  int direction = 0;

  // Figure out direction and use it as a movement scalar.
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    direction += 1;
  }
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    direction -= 1;
  }

  if (m_Player.x <= -m_Player.width || m_Player.x >= 1920 || m_Player.y < 0 ||
      m_Player.y >= 1080) {
    m_Player.x = m_Start_Pos.x;
    m_Player.y = m_Start_Pos.y;
    m_Flipped = false;
    m_Velocity.x = m_Velocity.y = 0;
    // Make gravity positive when resetting the player.
    m_Gravity = std::abs(m_Gravity);
  }

  switch (m_MovementState) {
  case ActorStates::IDLE:
    // Set the player to be happy on idle.
    m_EmotionState = EmotionStates::HAPPY;

    // Player wants to jump.
    if (want_jump) {
      m_MovementState = ActorStates::JUMP_START;
      m_Velocity.y = m_Flipped ? -m_jumpAcceleration : m_jumpAcceleration;
    }

    // Make the player flip
    if (want_flip && m_MovementState == ActorStates::IDLE) {
      m_Flipped = !m_Flipped;
      m_Gravity = -m_Gravity;
    }

    // Player wants to run.
    else if (direction != 0) {
      m_MovementState = ActorStates::RUN;
      m_Velocity.x = direction * m_Speed; // Set horizontal velocity
    } else {
      m_Velocity.x = 0;
    }
    break;

  case ActorStates::RUN:
    // Player pressed Space and wants to jump.
    if (want_jump) {
      m_MovementState = ActorStates::JUMP_START;
      m_Velocity.y = m_Flipped ? -m_jumpAcceleration : m_jumpAcceleration;
      m_Velocity.x *= m_jumpVelocityDampen;
    }
    // Player stops running and wants to stand around again.
    else if (direction == 0) {
      m_MovementState = ActorStates::IDLE;
      m_Velocity.x = 0; // Stop horizontal movement
    }
    // Player is running.
    else {
      m_Velocity.x = direction * m_Speed; // Update horizontal velocity
    }
    break;

  case ActorStates::JUMP_START:
    PlaySound(AssetManager::get_sound("jump"));
    m_MovementState =
        m_Velocity.y <= 0 ? ActorStates::JUMP_UP : ActorStates::FALL;
    break;

  case ActorStates::JUMP_UP:
    m_Velocity.y += 400 * delta;
    if (m_Velocity.y >= 0) {
      m_MovementState = ActorStates::FALL;
    }
    break;

  case ActorStates::FALL:
    m_EmotionState = EmotionStates::FEAR;
    m_Velocity.y += (m_Flipped ? -500 : 500) * m_jumpVelocityDampen * delta;
    break;
  }

  // Apply gravity.
  m_Velocity.y += m_Gravity * delta;

  // Calculate the new position.
  Vector2 new_pos = {m_Player.x + m_Velocity.x * delta,
                     m_Player.y + m_Velocity.y * delta};

  // Handle collision based on level.
  switch (m_Level->m_Id) {
  case 1:
    handle_collision(m_Level->level_1.collision_rects, new_pos);
    if (m_Player.x >= 1790 && m_Player.x <= 1810 && m_Player.y >= 370 &&
        m_Player.y <= 390) {
      // Level transition (example case).
      m_Level->m_Id++;
      m_Player.x = m_Start_Pos.x;
      m_Player.y = m_Start_Pos.y;
      PlaySound(AssetManager::get_sound("win"));
    }
    break;
  case 2:
    handle_collision(m_Level->level_2.collision_rects, new_pos);
    if (m_Player.x >= 1690 && m_Player.x <= 1710 && m_Player.y >= 450 &&
        m_Player.y <= 470) {
      m_Level->m_Id++;
      m_Player.x = m_Start_Pos.x;
      m_Player.y = m_Start_Pos.y;
      PlaySound(AssetManager::get_sound("win"));
    }
    break;
  }

  // Update player's position.
  m_Player.x = new_pos.x;
  m_Player.y = new_pos.y;
}
} // namespace Inversion
