#pragma once

#include "raylib.h"

class Enemy {
public:
  Enemy();
  void draw_enemy();
  void update_enemy();

private:
  bool idle;
  Vector2 position;
};
