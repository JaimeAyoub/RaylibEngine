#pragma once
#include "Entity.h"
#include "PhysicsSystem.h"  
#include "include/box2d.h"
#include "raylib.h"
#include <memory>

class Joint : public Entity {
public:
    std::shared_ptr<JointData> jointData;

    Joint(std::shared_ptr<JointData> data)
        : Entity("Joint", "Joint"), jointData(data) {
    }
    void update() override {
    }


    void draw() override {
        if (b2Joint_IsValid(jointData->jointId)) {
            DrawLineV(jointData->pivot->pos, jointData->bola->pos, BLACK);
        }
    }

    bool checkCut(Vector2 lineStart, Vector2 lineEnd) {
        Vector2 collision;
        if (CheckCollisionLines(jointData->pivot->pos, jointData->bola->pos,
            lineStart, lineEnd, &collision))
        {
            if (b2Joint_IsValid(jointData->jointId))
            {
                b2DestroyJoint(jointData->jointId);
                return true;
            }
        }
        return false;
    }
};