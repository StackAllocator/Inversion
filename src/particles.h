#include "raylib.h"

namespace Inversion::Particles {

// ----------------------------------------------------------------------------------------------------
// Particle structure definition.
struct Particle {
  Vector2 position;
  Vector2 velocity;
  float radius;
  bool shrinking;
  Color color;
};
} // namespace Inversion::Particles
