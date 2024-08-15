//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#include "./game.h"
#include "./asset_manager.h"
#include "./menu.h"

#include <string>
#include <vector>

namespace Inversion {

static int frames_counter = 0;
// Forward declaration for firework.
static void draw_fireworks();

// ----------------------------------------------------------------------------------------------------
// Inject the dependencies into the object. [Dependency injection]
Game::Game() : level_selection(&m_Level), m_Player(&m_Level) {}

// ----------------------------------------------------------------------------------------------------
void Game::init_game() {
  // ----------------------------------------------------------------------------------------------------
  // Get game main music and make it loop.
  m_Music = AssetManager::get_music("main");
  m_Music.looping = true;
  SetMusicVolume(m_Music, 0.5f);
  // Play this music when the game starts.
  PlayMusicStream(m_Music);
  // ----------------------------------------------------------------------------------------------------

  // Set player and level properties.
  m_Player.set_rect({200, 820}, {40, 140});
  m_Level.set_level(0);
  m_Level.set_texture();
}

// ----------------------------------------------------------------------------------------------------
void Game::update_game() {

  // Constantly update the music stream and loop if music finished.
  UpdateMusicStream(m_Music);

  // ----------------------------------------------------------------------------------------------------
  // Handle input logic.
  // ----------------------------------------------------------------------------------------------------
  switch (m_GameState) {
  // ----------------------------------------------------------------------------------------------------
  case GameState::TITLE:
    // Update to Menu when ESC is pressed.
    if (IsKeyPressed(KEY_ESCAPE)) {
      m_GameState = GameState::MENU;
    }
    // Update to the first level if any other key is pressed.
    else if (GetKeyPressed()) {
      m_GameState = GameState::GAME;
    }
    break;
  // ----------------------------------------------------------------------------------------------------
  case GameState::GAME:
    if (IsKeyPressed(KEY_ESCAPE)) {
      m_GameState = GameState::MENU;
    }
    m_Player.move();
    if (m_Level.finished) {
      m_GameState = GameState::END;
    }
    break;
  // ----------------------------------------------------------------------------------------------------
  case GameState::MENU:

    // Update the main menu.
    main_menu.handle_input();
    main_menu.update_balls();

    // Proceed with the game.
    if (main_menu.m_ShouldResume) {
      main_menu.m_ShouldResume = false;
      m_GameState = GameState::GAME;
    }

    // Move in the level selection state.
    else if (main_menu.m_ShouldLevelSelect) {
      m_GameState = GameState::LEVEL_SELECTION;
    }

    // Quit the application if the user signals it.
    else if (main_menu.m_ShouldQuit) {
      m_Quit = true;
    }
    break;

  // ----------------------------------------------------------------------------------------------------
  case GameState::LEVEL_SELECTION:

    // Go back to menu if ESCAPE key has been pressed.
    if (IsKeyPressed(KEY_ESCAPE)) {
      m_GameState = GameState::MENU;
      main_menu.m_ShouldLevelSelect = false;
    }

    level_selection.handle_input();
    if (level_selection.mouse_pressed) {
      level_selection.mouse_pressed = false;
      m_Player.set_position({200, 820});
      main_menu.m_ShouldLevelSelect = false;
      m_GameState = GameState::GAME;
    }
    break;
  // ----------------------------------------------------------------------------------------------------
  case GameState::END:
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_Q)) {
      m_Quit = true;
    }
    break;
  }
  // ----------------------------------------------------------------------------------------------------
}

// ----------------------------------------------------------------------------------------------------
void Game::draw_game() {
  // ----------------------------------------------------------------------------------------------------
  // Handle draw calls.
  // ----------------------------------------------------------------------------------------------------
  switch (m_GameState) {
  // ----------------------------------------------------------------------------------------------------
  // Draw the title screen.
  case GameState::TITLE:

    // Draw text with custom font.
    ClearBackground(BLACK);
    DrawTextEx(AssetManager::get_font("dejavu"), "INVERSION", {220, 300}, 200,
               20, WHITE);
    DrawTextEx(AssetManager::get_font("dejavu"), "PRESS ANY BUTTON",
               {800, 1000}, 30, 5, WHITE);
    DrawText("by Johannes Elsing", 1170, 500, 20, WHITE);
    break;
  // ----------------------------------------------------------------------------------------------------
  // Draw the game main menu.
  case GameState::MENU:
    ClearBackground(BLACK);
    main_menu.draw_menu();
    main_menu.draw_balls();
    break;
  case GameState::LEVEL_SELECTION:
    ClearBackground(BLACK);
    level_selection.draw_menu();
    break;
  // ----------------------------------------------------------------------------------------------------
  // Draw the current level and player.
  case GameState::GAME:
    ClearBackground(BLACK);
    m_Level.draw_level();
    m_Player.draw();
    break;
  // ----------------------------------------------------------------------------------------------------
  case GameState::END:
    ClearBackground(BLUE);
    draw_fireworks();
    DrawText("The end. Thanks for playing!", 690, 500, 40, BLACK);
    break;
  }
}

// Draw fireworks for the end screen.
void draw_fireworks() {
  if (frames_counter < 10) {
    DrawTexture(AssetManager::get_texture("firework_1"), 600, 200, WHITE);
    DrawTexture(AssetManager::get_texture("firework_1"), 1100, 200, WHITE);
  } else if (frames_counter < 20 && frames_counter <= 30) {
    DrawTexture(AssetManager::get_texture("firework_2"), 600, 200, WHITE);
    DrawTexture(AssetManager::get_texture("firework_2"), 1100, 200, WHITE);
  } else if (frames_counter < 30 && frames_counter <= 40) {
    DrawTexture(AssetManager::get_texture("firework_3"), 600, 200, WHITE);
    DrawTexture(AssetManager::get_texture("firework_3"), 1100, 200, WHITE);
  } else if (frames_counter < 40 && frames_counter <= 50) {
    DrawTexture(AssetManager::get_texture("firework_4"), 600, 200, WHITE);
    DrawTexture(AssetManager::get_texture("firework_4"), 1100, 200, WHITE);
  } else if (frames_counter < 50 && frames_counter <= 60) {
    DrawTexture(AssetManager::get_texture("firework_5"), 600, 200, WHITE);
    DrawTexture(AssetManager::get_texture("firework_5"), 1100, 200, WHITE);
  } else if (frames_counter < 60 && frames_counter <= 70) {
    DrawTexture(AssetManager::get_texture("firework_6"), 600, 200, WHITE);
    DrawTexture(AssetManager::get_texture("firework_6"), 1100, 200, WHITE);
  }
  frames_counter++;
  // Reset frame counter to see animation periodically
  if (frames_counter > 100)
    frames_counter = 0;
}
} // namespace Inversion
