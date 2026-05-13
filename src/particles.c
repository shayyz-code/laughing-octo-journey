#include "particles.h"
#include <stdlib.h>

static Particle particles[MAX_PARTICLES];

void InitParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].active = false;
    }
}

void SpawnParticle(Vector2 pos, ParticleType type) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!particles[i].active) {
            particles[i].active = true;
            particles[i].position = pos;
            particles[i].type = type;
            particles[i].life = 1.0f + (float)rand()/RAND_MAX * 2.0f;
            
            if (type == PARTICLE_BUBBLE) {
                particles[i].velocity = (Vector2){ (float)rand()/RAND_MAX * 20.0f - 10.0f, -40.0f - (float)rand()/RAND_MAX * 40.0f };
                particles[i].size = 2.0f + (float)rand()/RAND_MAX * 4.0f;
                particles[i].color = Fade(WHITE, 0.4f);
            } else {
                particles[i].velocity = (Vector2){ 10.0f + (float)rand()/RAND_MAX * 20.0f, 5.0f + (float)rand()/RAND_MAX * 10.0f };
                particles[i].size = 1.0f + (float)rand()/RAND_MAX * 1.0f;
                particles[i].color = Fade(LIGHTGRAY, 0.3f);
            }
            break;
        }
    }
}

void UpdateParticles(float dt) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].active) {
            particles[i].position.x += particles[i].velocity.x * dt;
            particles[i].position.y += particles[i].velocity.y * dt;
            particles[i].life -= dt;
            
            if (particles[i].life <= 0) particles[i].active = false;
            
            // Screen wrapping for snow
            if (particles[i].type == PARTICLE_SNOW) {
                if (particles[i].position.x > 800) particles[i].position.x = 0;
                if (particles[i].position.y > 600) particles[i].position.y = 0;
            }
        }
    }

    // Random spawns
    if (rand() % 10 == 0) SpawnParticle((Vector2){ (float)(rand() % 800), 600 }, PARTICLE_BUBBLE);
    if (rand() % 5 == 0) SpawnParticle((Vector2){ (float)(rand() % 800), (float)(rand() % 600) }, PARTICLE_SNOW);
}

void DrawParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].active) {
            if (particles[i].type == PARTICLE_BUBBLE) {
                DrawCircleLines(particles[i].position.x, particles[i].position.y, particles[i].size, particles[i].color);
            } else {
                DrawCircleV(particles[i].position, particles[i].size, particles[i].color);
            }
        }
    }
}
