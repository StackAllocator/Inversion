//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#include "raylib.h"

#include "./application.h"
#include "./asset_manager.h"
#include "./game.h"

namespace Inversion {
void Application::run() {
  // ----------------------------------------------------------------------------------------------------
  // Initialize the game.
  // ----------------------------------------------------------------------------------------------------
  // Make window resizable and enable anti-aliasing.
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);

  InitWindow(m_Specification.screen_width, m_Specification.screen_height,
             m_Specification.title.c_str());

  InitAudioDevice();

  // Check if window initialization succeeded.
  if (!IsWindowReady() || !IsAudioDeviceReady()) {
    std::cerr << "Initilization failed!" << std::endl;
    return;
  }

  // Set the log level of the output dump.
  SetTraceLogLevel(LOG_INFO);

  SetExitKey(KEY_NULL); // Prevent ESC to be default exit key.
  SetTargetFPS(144);

  // Load all game textures, fonts and sounds.
  AssetManager::load_textures();
  AssetManager::load_sounds();
  AssetManager::load_fonts();

  m_Game.init_game();
  // ----------------------------------------------------------------------------------------------------
  // Main game loop.
  // ----------------------------------------------------------------------------------------------------
  while (!WindowShouldClose() && !m_Game.m_Quit) {
    Loop();
  }
  cleanup();
}

// ----------------------------------------------------------------------------------------------------
void Application::Loop() {
  OnUpdate();
  OnRender();
}

// ----------------------------------------------------------------------------------------------------
void Application::OnUpdate() { m_Game.update_game(); }

void Application::OnRender() {
  // ----------------------------------------------------------------------------------------------------
  // Draw
  BeginDrawing();
  ClearBackground(BLACK);

  m_Game.draw_game();

  EndDrawing();
  // ----------------------------------------------------------------------------------------------------
}

void Application::cleanup() const {
  // De-Initialization
  // ----------------------------------------------------------------------------------------------------
  AssetManager::unload_textures(); // Unload loaded data (textures)
  AssetManager::unload_sounds();   // Unload loaded data (sounds)
  AssetManager::unload_fonts();    // Unload loaded data (fonts)
  AssetManager::unload_music();    // Unload loaded data (music)

  CloseAudioDevice(); // Close audio device (music streaming is automatically
                      // stopped)
  CloseWindow();      // Close window and OpenGL context
  // ----------------------------------------------------------------------------------------------------
}
} // namespace Inversion
