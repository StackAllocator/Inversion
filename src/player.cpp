//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <memory>

#include "./asset_manager.h"
#include "./level.h"
#include "./player.h"

namespace Inversion {

// ----------------------------------------------------------------------------------------------------
Player::Player(LevelManager *level) : m_Color(WHITE), m_Level(level) {}

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
void Player::handle_collision(std::vector<Rectangle> &level, Vector2 &new_pos,
                              bool &on_ground) {

  for (const Rectangle &obstacle : level) {

    if (new_pos.x + m_Player.width > obstacle.x &&
        new_pos.x < obstacle.x + obstacle.width &&
        new_pos.y + m_Player.height > obstacle.y &&
        new_pos.y < obstacle.y + obstacle.height) {

      float delta_x =
          (new_pos.x + m_Player.width / 2) - (obstacle.x + obstacle.width / 2);
      float delta_y = (new_pos.y + m_Player.height / 2) -
                      (obstacle.y + obstacle.height / 2);

      // Compute the intersection spots.
      float intersect_x =
          abs(delta_x) - (m_Player.width / 2 + obstacle.width / 2);
      float intersect_y =
          abs(delta_y) - (m_Player.height / 2 + obstacle.height / 2);

      if (intersect_x < 0.0f && intersect_y < 0.0f) {
        if (intersect_y > intersect_x) {
          // Vertical collision resolution
          if (delta_y > 0.0f) {
            // Collision on the bottom (normal gravity) or top (flipped gravity)
            new_pos.y = obstacle.y + obstacle.height;
            m_Velocity.y = 0;
            if (m_Flipped)
              on_ground = true;
          } else {
            // Collision on the top (normal gravity) or bottom (flipped gravity)
            new_pos.y = obstacle.y - m_Player.height;
            m_Velocity.y = 0;
            if (!m_Flipped)
              on_ground = true;
          }
        } else {
          // Horizontal collision resolution
          if (delta_x > 0.0f) {
            // Collision on the left
            new_pos.x = obstacle.x + obstacle.width;
          } else {
            // Collision on the right
            new_pos.x = obstacle.x - m_Player.width;
          }
          m_Velocity.x = 0;
        }
      }
    }
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
  }
  // Flip the sprites and adjust the positions.
  else {
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

void Player::set_position(Vector2 position) {
  m_Player.x = m_Start_Pos.x = position.x;
  m_Player.y = m_Start_Pos.y = position.y;
}

// ----------------------------------------------------------------------------------------------------
void Player::move() {

  float delta = GetFrameTime();

  bool want_jump = IsKeyDown(KEY_SPACE);
  bool want_flip = IsKeyPressed(KEY_G);
  int direction = 0;

  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
    direction += 1;
  }
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
    direction -= 1;
  }

  // Reset position if out of bounds
  if (m_Player.x <= -m_Player.width || m_Player.x >= 1920 || m_Player.y < 0 ||
      m_Player.y >= 1080) {
    m_Player.x = m_Start_Pos.x;
    m_Player.y = m_Start_Pos.y;
    m_Flipped = false;
    m_Velocity.x = m_Velocity.y = 0;
    m_Gravity = std::abs(m_Gravity);
  }

  // Determine if the player is on the ground before processing movement and
  // flip
  Vector2 new_pos = {m_Player.x + m_Velocity.x * delta,
                     m_Player.y + m_Velocity.y * delta};
  bool on_ground = false;
  handle_collision(m_Level->current_level.collision_rects, new_pos, on_ground);

  // Gravity flipping
  if (want_flip &&
      (m_MovementState == ActorStates::IDLE ||
       m_MovementState == ActorStates::RUN) &&
      on_ground) {
    m_Flipped = !m_Flipped;
    m_Gravity = -m_Gravity;
    m_Velocity.x = 0;
  }

  // Movement state management
  switch (m_MovementState) {
  case ActorStates::IDLE:
    m_EmotionState = EmotionStates::HAPPY;

    if (want_jump && on_ground) {
      m_MovementState = ActorStates::JUMP_START;
      m_Velocity.y = m_Flipped ? -m_jumpAcceleration : m_jumpAcceleration;
    } else if (direction != 0) {
      m_MovementState = ActorStates::RUN;
      m_Velocity.x = direction * m_Speed;
    }
    // Player wants to stay in IDLE state.
    else {
      m_Velocity.x = 0;
    }
    break;

  case ActorStates::RUN:
    if (want_jump && on_ground) {
      m_MovementState = ActorStates::JUMP_START;
      m_Velocity.y = m_Flipped ? -m_jumpAcceleration : m_jumpAcceleration;
      m_Velocity.x *= m_jumpVelocityDampen;
    } else if (direction == 0) {
      m_MovementState = ActorStates::IDLE;
      m_Velocity.x = 0;
    } else {
      m_Velocity.x = direction * m_Speed;
    }
    break;

  case ActorStates::JUMP_START:
    PlaySound(AssetManager::get_sound("jump"));
    m_MovementState =
        (m_Velocity.y <= 0) ? ActorStates::JUMP_UP : ActorStates::FALL;
    break;

  case ActorStates::JUMP_UP:
    m_Velocity.y += (m_Flipped ? -400 : 400) * delta;
    if (m_Velocity.y >= 0) {
      m_MovementState = ActorStates::FALL;
    }
    break;

  case ActorStates::FALL:
    m_EmotionState = EmotionStates::FEAR;
    m_Velocity.y += m_Gravity * delta;
    break;
  }

  m_Velocity.y += m_Gravity * delta;

  // Update player's position after handling collision
  handle_collision(m_Level->current_level.collision_rects, new_pos, on_ground);

  if (m_Player.x >= 1770 && m_Player.x <= 1790 && m_Player.y >= 300 &&
      m_Player.y <= 320) {
    // Reset player to start.
    new_pos.x = m_Player.x = m_Start_Pos.x;
    new_pos.y = m_Player.y = m_Start_Pos.y;

    if (m_Level->m_Id == 15) {
      m_Level->finished = true;
    } else {
      m_Level->m_Id++;
    }
    m_Level->set_level(m_Level->m_Id);
    PlaySound(AssetManager::get_sound("win"));
  }

  if (on_ground) {
    // Reset player to idle state if grounded.
    if (m_MovementState == ActorStates::FALL ||
        m_MovementState == ActorStates::JUMP_UP) {
      m_MovementState = ActorStates::IDLE;
    }
  }
  // Not on ground -> make us fall.
  else if (m_MovementState == ActorStates::IDLE) {
    m_MovementState = ActorStates::FALL;
  }

  // Update the player position by the newly computed position.
  m_Player.x = new_pos.x;
  m_Player.y = new_pos.y;
}
} // namespace Inversion
