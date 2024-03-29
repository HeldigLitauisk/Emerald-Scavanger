#include <utility>

//
// Created by Morten Nobel-Jørgensen on 11/3/17.
//

#include "Level.hpp"
#include "EmeraldGame.hpp"
#include "SpriteComponent.hpp"
#include "PhysicsComponent.hpp"
#include "PlatformComponent.hpp"
#include "MovingPlatformComponent.hpp"


std::shared_ptr<Level> Level::createDefaultLevel(EmeraldGame *game,
                                                 std::shared_ptr<sre::SpriteAtlas> spriteAtlas) {
    std::shared_ptr<Level> res = std::shared_ptr<Level>(new Level());

    // todo initialize
    res->game = game;
    res->spriteAtlas = std::move(spriteAtlas);

    return res;
}

void Level::level_01() {
    // start wall
    addWall(0, 0, 2, 51);

    // floor
    addPlatform(1, 0, 2, 100, false);

    addPlatform(105, 0, 2, 100, false);
    // ceil
    addPlatform(1, 50, 2, 204, false);


    auto movingPlatform = addPlatform(10, 3, 2, 5, true);
    auto movingPlatformComponent = movingPlatform->getGameObject()->addComponent<MovingPlatformComponent>();
    movingPlatformComponent->setMovementStart({10, 3});
    movingPlatformComponent->setMovementEnd({10, 10});

    // add some more platforms
    addPlatform(15, 7, 2, 5, true);
    addPlatform(20, 3, 2, 5, true);
    addPlatform(25, 7, 2, 5, true);
    addPlatform(30, 10, 2, 5, true);
    addPlatform(35, 7, 2, 5, true);
    addPlatform(40, 3, 2, 5, true);

    addPlatform(35, 15, 2, 5, true);
    addPlatform(40, 20, 2, 5, true);
    addPlatform(45, 25, 2, 5, true);
    addPlatform(50, 30, 2, 5, true);
    addPlatform(55, 35, 2, 5, true);
    addPlatform(60, 40, 2, 5, true);
    addPlatform(65, 45, 2, 140, true);


    addWall(125, 0, 2, 2);
    // end wall
    addWall(205, 0, 2, 51);
    levelWidth = 206 * tileSize;
    levelHeight = 51 * tileSize;
}

//todo: design levels:
void Level::level_02() {

}

void Level::level_03() {

}

void Level::level_04() {

}

void Level::level_05() {

}

void Level::generateLevel() {
    // start wall
    addWall(-1, 0, 2, 10);

    // floor
    addPlatform(0, 0, 2, 100, false);
    // ceil
    addPlatform(0, 20, 2, 100, false);

    auto movingPlatform = addPlatform(10, 3, 2, 5, true);
    auto movingPlatformComponent = movingPlatform->getGameObject()->addComponent<MovingPlatformComponent>();
    movingPlatform->getPhysicsComponent()->setLinearVelocity({0,100});
    b2Body *body = movingPlatform->getPhysicsComponent()->getBody();
    movingPlatformComponent->setBody(body);
    movingPlatformComponent->setMovementStart({10, 3});
    movingPlatformComponent->setMovementEnd({10, 5});

    //Procedurally generated level
    Procedural_level();
}

//clamps a value with a lower and upper bound
float clamp(float n, float lower, float upper) {
    return std::max(lower, std::min(n, upper));
}

//Procedurally generates a level.
void Level::Procedural_level() {

    glm::vec2 min(0, -3);
    glm::vec2 max(5, 3);

    float floor = 0;
    float ceil = 15;
    float wall_l = 0;
    float wall_r = 500;

    addPlatform(15, 7, 2, 5, true);
    glm::vec2 prev_platform = glm::vec2(15 + 5, 7);

    int i = 0;
    while (i < 100) {
        //int min_y = clamp(min.y, floor, ceil);
        //int max_y = clamp(max.y, floor, ceil);

        int length = 5;
        int rand_x = (rand() % (int) ((max.x - min.x) + 1)) + min.x + prev_platform.x;
        int rand_y = (rand() % (int) ((max.y - min.y) + 1)) + min.y + prev_platform.y;
        addPlatform(rand_x, rand_y, 2, length, true);
        prev_platform = glm::vec2(rand_x + length, clamp(rand_y, floor, ceil));
        i++;
    }

    levelWidth = 206 * tileSize;
    levelHeight = 51 * tileSize;
}

std::shared_ptr<PlatformComponent> Level::addPlatform(int x, int y, int startSpriteId, int length, bool kinematic) {
    auto gameObject = game->createGameObject();
    gameObject->name = "Platform";
    auto res = gameObject->addComponent<PlatformComponent>();
    res->initPlatform(spriteAtlas, x, y, startSpriteId, length, kinematic);
    return res;
}


std::shared_ptr<PlatformComponent> Level::addWall(int x, int y, int startSpriteId, int length) {
    auto gameObject = game->createGameObject();
    gameObject->name = "Wall";
    auto res = gameObject->addComponent<PlatformComponent>();
    res->initWall(spriteAtlas, x, y, startSpriteId, length);
    return res;
}

float Level::getWidth() {
    return this->levelWidth;
}

float Level::getHeight() {
    return this->levelHeight;
}
