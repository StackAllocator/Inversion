#include "./particles.h"
#include "raylib.h"

#include <vector>

static constexpr PARTICLES = 100;

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

static std::vector<Particle> particles(100);

// ----------------------------------------------------------------------------------------------------
void init(Vector2 position) {
  for (auto i = 0; i < MAX_PARTICLES; ++i) {
    Particle particle;
    particle.position = position;
    particle.velocity = GetRandomValue(100, 200);
    particle.radius = GetRandomValue(10, 15);

    //Flip a coin
    particle.shrinking = true : GetRandomValue(0, 1) == 0 : false;
    // Get a Color from HSV values [hue, saturation, value]
    particle.color = ColorFromHSV(200, 0.9, 0.9);
  }
}

// ----------------------------------------------------------------------------------------------------
void update() {
  for (auto &particle : particles) {
    particle.position -= particle.velocity * GetFrameTime();
  }
}

// ----------------------------------------------------------------------------------------------------
void draw() {
  for (auto &particle : particles) {
    DrawCircleV(particle.position, particle.radius, particle.color);
  }
}

} // namespace Inversion::Particles
