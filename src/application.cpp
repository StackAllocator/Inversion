//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#include <iostream>

#include "raylib.h"

#include "./application.h"
#include "./asset_manager.h"
#include "./game.h"

namespace Inversion::Application {
// ----------------------------------------------------------------------------------------------------
// Specifies important properties of the application.
struct ApplicationSpecification {
  // Specify screen width and height of the window.
  const int screen_width = 1920;
  const int screen_height = 1080;

  // Specify the window title.
  std::string title = "Inversion";
};

// Define instances of the game for the application handle.
static ApplicationSpecification specification;
static Game game;

// ----------------------------------------------------------------------------------------------------
// Initialize the game.
// ----------------------------------------------------------------------------------------------------
void init() {
  // Make window resizable and enable anti-aliasing.
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);

  InitWindow(specification.screen_width, specification.screen_height,
             specification.title.c_str());

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

  game.init_game();
}

void run() {
  // ----------------------------------------------------------------------------------------------------
  // Main game loop.
  // ----------------------------------------------------------------------------------------------------
  while (!WindowShouldClose() && !game.m_Quit) {
    Loop();
  }
}

// ----------------------------------------------------------------------------------------------------
void Loop() {
  OnUpdate();
  OnRender();
}

// ----------------------------------------------------------------------------------------------------
void OnUpdate() { game.update_game(); }

void OnRender() {
  // ----------------------------------------------------------------------------------------------------
  // Draw
  BeginDrawing();

  game.draw_game();

  EndDrawing();
  // ----------------------------------------------------------------------------------------------------
}

void cleanup() {
  // De-Initialization
  // ----------------------------------------------------------------------------------------------------
  AssetManager::unload_textures(); // Unload loaded data (textures)
  AssetManager::unload_sounds();   // Unload loaded data (sounds, music)
  AssetManager::unload_fonts();    // Unload loaded data (fonts)
  AssetManager::unload_music();    // Unload loaded data (music)

  CloseAudioDevice(); // Close audio device (music streaming is automatically
                      // stopped)
  CloseWindow();      // Close window and OpenGL context
  // ----------------------------------------------------------------------------------------------------
}
} // namespace Inversion::Application
