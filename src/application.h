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
#include <string>

#include "./game.h"

namespace Inversion {
// ----------------------------------------------------------------------------------------------------
// Specifies important properties of the application.
struct ApplicationSpecification {
  // Specify screen width and height of the window.
  const int screen_width = 1920;
  const int screen_height = 1080;

  // Specify the window title.
  std::string title = "Inversion";
};

// ----------------------------------------------------------------------------------------------------
// Handles the entire application.
class Application {
public:
  // Run the entire application.
  void run();

  // This function is for cleanup. Closes window and OpenGL context.
  void cleanup() const;

private:
  // Instance of the application specification that specifies window properties.
  ApplicationSpecification m_Specification;

  Game m_Game;

  // Code of the loop function is executed every frame.
  void Loop();

  // Update the game loop.
  void OnUpdate();

  // Render the current game loop.
  void OnRender();
};
} // namespace Inversion
