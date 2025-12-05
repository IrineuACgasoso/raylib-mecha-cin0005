#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include "ecs/entitymanager.h"
#include "ecs/systems.h"
#include "ecs/types.h"
#include "event_manager.h"
#include "resource_manager.h"
#include "systems.h"
#include "map_loader.h"


#define MAX_CLOUDS 100        
#define CLOUD_AREA 1000.0f    
#define CLOUD_HEIGHT 120.0f



void InitSecondLevelScreen(struct Systems* systems, FirstLevelData* data) {
    InitEntityManager(&systems->entityManager);
    data->camera.position = (Vector3){ 0.0f, 2.5f, 0.0f };
    data->camera.target = (Vector3){ 0.0f, 2.5f, 1.0f };
    data->camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    data->camera.fovy = 60.0f;
    data->camera.projection = CAMERA_PERSPECTIVE;
    MapContext context;
    context.mainCamera = &data->camera;
    // Carregue o mapa do segundo nível
    LoadMapFromText(&systems->entityManager, &systems->resourceManager, "resources/maps/level2.map", context);
    DisableCursor();
}

void UpdateSecondLevelScreen(struct Systems* systems, FirstLevelData* data) {
    systems->delta_time = GetFrameTime();
    // repita os sistemas do primeiro nível
    PlayerControlSystem(systems);
    AIControlSystem(systems);
    LifetimeSystem(systems);
    MissileSystem(systems);
    TrailSystem(systems);
    MovementSystem(systems);
    AttachmentSystem(systems);
    WeaponSystem(systems);
    CollisionSystem(systems);
    HealthSystem(systems);
    PlayerAudioSystem(systems);

    if (IsKeyPressed(systems->configManager.KeyMap.KeyPause)) {
        EnableCursor();
        RequestScreenChange(systems, SCREEN_MAIN_MENU);
    }
    ProcessGameEvents(systems);
}

void DrawSecondLevelScreen(struct Systems* systems, FirstLevelData* data) {
    ClearBackground(SKYBLUE);
    BeginMode3D(data->camera);
    // Chame a função para desenhar o nível (você pode copiar/adaptar do first_level.c)
    EndMode3D();
    DrawHUDSystem(systems);
    DrawCrosshair(systems);
    DrawMinimapSystem(systems, data);
    DrawFPS(10, 10);
}

void DestroySecondLevelScreen(struct Systems* systems, FirstLevelData* data) {
    // Libera recursos se necessário
}