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

namespace Inversion::Application {
// ----------------------------------------------------------------------------------------------------
// Handles the entire application.
// Run the entire application.

// Initialization of the application.
void init();

// Run the game until the player signals an interrupt.
void run();

// Close window and OpenGL context.
void cleanup();

// Code of the loop function is executed every frame.
void Loop();

// Update the game loop.
void OnUpdate();

// Render the current game loop.
void OnRender();
} // namespace Inversion::Application
