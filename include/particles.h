#ifndef PARTICLES_H
#define PARTICLES_H

#include "raylib.h"

#define MAX_PARTICLES 200

typedef enum {
    PARTICLE_BUBBLE,
    PARTICLE_SNOW
} ParticleType;

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float life;
    float size;
    Color color;
    ParticleType type;
    bool active;
} Particle;

void InitParticles();
void UpdateParticles(float dt);
void DrawParticles();
void SpawnParticle(Vector2 pos, ParticleType type);

#endif
