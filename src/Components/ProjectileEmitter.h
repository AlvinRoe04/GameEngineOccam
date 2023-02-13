#pragma once

#include "../../libs/glm/glm.hpp"
#include "../EntityManager.h"
#include "../Components/Transform.h"

class ProjectileEmitter: public Component {
    private:
        Transform *transform;
        glm::vec2 origin;
        int speed;
        int range;
        float angleRad;
        bool shouldLoop;

    public:
        ProjectileEmitter(int speed, int angleDeg, int range, bool shouldLoop) {
            this->speed = speed;
            this->range = range;
            this->shouldLoop = shouldLoop;
            this->angleRad = glm::radians(static_cast<float>(angleDeg));
        }

        void Initialize() override {
            transform = owner->GetComponent<Transform>();
            origin = glm::vec2(transform->position.x, transform->position.y);
            transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed); 
        }

        void Update(float deltaTime) override {
            if (glm::distance(transform->position, origin) > range) {
                if (shouldLoop) {
                    transform->position.x = origin.x;
                    transform->position.y = origin.y;
                } else {
                    owner->Destroy();
                }
            } 
        }
};
