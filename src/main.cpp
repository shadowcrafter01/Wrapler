#include "init.hpp"
#include <SDL3/SDL_main.h>
#include <Windows.h>
#include <Psapi.h>

#include "game.hpp"

#include <random>
std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);

GameObject test;

int frame = 0;

void onMouseUpR()
{
    // AUD::boom.Play();
}
void onMouseDownL()
{
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    ENG::console.LogDebug(pmc.WorkingSetSize / 1024);
}
void onSecond()
{
    frame++;
}

int main(int argc, char *argv[])
{
    ENG::Init("Wrapler", "0.0", "com.wrapler.engine");

    WIN::primary.SetIcon("data/textures/billGates.bmp");

    ENG::console.LogInfo("test");
    ENG::console.LogDebug(ENG::timer.now_ns());

    // ENG::input.RegisterMouseUp_R(onMouseUpR);
    // ENG::input.RegisterMouseDown_L(onMouseDownL);

    float test_number;
    bool test_bool;
    JSON::test.readProperty<float>("test_number", &test_number, 0);
    JSON::test.readProperty<bool>("test_bool", &test_bool, false);

    double averageFPS = 0;
    double averageFPS_old;
    double averageFPS_best;
    JSON::test.readProperty("average_fps", &averageFPS_old, 0.0);
    JSON::test.readProperty("average_fps_best", &averageFPS_best, 0.0);

    test.AssignCamera(&CAM::primary);
    test.AssignTexture(&TEX::test);
    test.AssignTimer(&ENG::timer);
    test.damping = 0.5;
    test.fenceToWindow = true;
    test.AssignClickEvent_L(&onMouseDownL);
    test.position = {100, 0};

    ENG_CollisionShape tempShape;
    tempShape.radius = 20;
    test.AssignCollisionShape(&tempShape);

    // ENG_CollisionShape temp;
    // test.collisionShape = &temp;

    ENG_Pen testPen = ENG_Pen(&CAM::primary);

    ENG_Atlas atlas(&WIN::primary, "data/textures/billGates.bmp");
    atlas.rect.x = 0;
    atlas.rect.y = 0;
    atlas.rect.w = 64;
    atlas.rect.h = 64;

    ENG_Atlas fire(&WIN::primary, "data/textures/fire.png");

    ENG_AnimatedTexture testAnim(&fire, {8, 8}, 1);

    StopwatchAsync second(onSecond, 20);

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, -10.0f};
    b2WorldId worldId = b2CreateWorld(&worldDef);

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = (b2Vec2){0.0f, -100.0f};
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(500.0f, 10.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = (b2Vec2){0.0f, 400.0f};
    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);
    b2Polygon dynamicBox = b2MakeBox(10.0f, 10.0f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.1f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    const float timeStep = 1.0f / 60.0f;
    const int subStepCount = 4;

    while (ENG::Update())
    {
        averageFPS = ENG_Math::Lerp(averageFPS, ENG::timer.FPS, 0.1);
        mainTick();
        controls();

        b2World_Step(worldId, timeStep, subStepCount);
        b2Vec2 position = b2Body_GetPosition(bodyId);
        b2Rot rotation = b2Body_GetRotation(bodyId);

        //ENG::draw.DrawTexture(&CAM::primary, &TEX::billGates, {b2Body_GetTransform(bodyId).p.x, b2Body_GetTransform(bodyId).p.y});

        
        
        testPen.Up();
        b2Vec2 p = b2TransformPoint(b2Body_GetTransform(groundId),groundBox.vertices[0]);
        b2Vec2 p0 = p;
        for (int i = 0; i < groundBox.count; i++)
        {
            p = b2TransformPoint(b2Body_GetTransform(groundId),groundBox.vertices[i]);

            testPen.GoTo({p.x,p.y});
            testPen.Down();

        }
        testPen.GoTo({p0.x,p0.y});
        testPen.Up();

        testPen.Up();
        p = b2TransformPoint(b2Body_GetTransform(bodyId),dynamicBox.vertices[0]);
        p0 = p;
        for (int i = 0; i < dynamicBox.count; i++)
        {
            p = b2TransformPoint(b2Body_GetTransform(bodyId),dynamicBox.vertices[i]);

            testPen.GoTo({p.x,p.y});
            testPen.Down();

        }
        testPen.GoTo({p0.x,p0.y});
        testPen.Up();




        if (ENG::input.GetMouseState(SDL_BUTTON_LEFT))
        {
            b2Body_ApplyForce(bodyId, (ENG::input.GetMouseWorldPos(&CAM::primary) - Vector2<double>(b2Body_GetTransform(bodyId).p.x, b2Body_GetTransform(bodyId).p.y)).Scale(10, true), b2Body_GetTransform(bodyId).p, true);
        }

        // ENG::draw.DrawAtlas(&CAM::primary, &atlas, {0, 0});
        // atlas.rect.x = ENG::input.GetMouseWorldPos(&CAM::primary).x / 10; // 10 * cos(ENG::timer.now_s() * 15);
        // atlas.rect.y = ENG::input.GetMouseWorldPos(&CAM::primary).y / 10; // 10 * sin(ENG::timer.now_s() * 15);

        // ENG::draw.DrawAnimatedTexture(&CAM::primary, &testAnim, {0, 0}, frame, 10);
        // ENG::draw.DrawAnimatedTexture(&CAM::primary, &testAnim, {0, -100}, (int)((double)frame / 4.0), 10);

        // test.ApplyForce((ENG::input.GetMouseWorldPos(&CAM::primary, true) - test.position).Scale(1, true));

        // ENG::draw.DrawLine(&CAM::primary,{0,0},ENG::input.GetMouseWorldPos(&CAM::primary));
        // ENG::draw.DrawTri(&CAM::primary,{-100,-100},{100,-100},ENG::input.GetMouseWorldPos(&CAM::primary),colorRGBA(128,10,200,255));

        // testPen.GoTo({0,0});
        // testPen.Down();
        // testPen.GoTo({100,100});
        // testPen.GoTo(ENG::input.GetMouseWorldPos(&CAM::primary));
        // testPen.GoTo({-100,0});
        // testPen.Up();

        if (ENG::input.keyState(SDL_SCANCODE_SPACE))
        {
            SDL_Delay(100); //(dist(rng));
        }
    }

    JSON::test.writeProperty<double>("average_fps", averageFPS);

    if (averageFPS > averageFPS_best)
    {
        JSON::test.writeProperty<double>("average_fps_best", averageFPS);
    }

    b2DestroyWorld(worldId);

    ENG::Shutdown();
    return 0;
}
