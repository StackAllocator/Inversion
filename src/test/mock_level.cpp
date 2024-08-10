//   ___                         _
//  |_ _|_ ____   _____ _ __ ___(_) ___  _ __
//   | ||  _ \ \ / / _ \  __/ __| |/ _ \|  __ \
//   | || | | \ V /  __/ |  \__ \ | (_) | | | |
//  |___|_| |_|\_/ \___|_|  |___/_|\___/|_| |_|
//
// Copyright (C) 2024
// Author: Johannes Elsing <je305@students.uni-freiburg.de>

#include "json.hpp"
#include "raylib.h"

#include "./mock_level.h"

namespace Inversion {

MockLevelManager::MockLevelManager() {}
MockLevelManager::~MockLevelManager() {}

void MockLevelManager::set_level(int level_id) {
  m_Id = level_id;
}
} // namespace Inversion
