#pragma once

#include "components/simple_scene.h"
#include "components/text_renderer.h"

#define PI 3.1415926535897932384626433832795
#define BIRD_SPEED 300
#define INCREMENT_SPEED 200
#define SPAWN_BIRD_X 640
#define SPAWN_BIRD_Y 80
#define CENTER_BIRD_X 0
#define CENTER_BIRD_Y 0
#define CENTER_LEFT_WING_X 0
#define CENTER_LEFT_WING_Y 32.5
#define CENTER_RIGHT_WING_X 0
#define CENTER_RIGHT_WING_Y -30
#define SCREEN_LIMIT_X 1280
#define SCREEN_LIMIT_Y 720
#define SCREEN_OFFSET 60
#define GRASS_LIMIT_Y 170 // LIMITA DE JOS
#define INITIAL_SCOREBAR_CENTER_X 1070
#define INITIAL_SCOREBAR_CENTER_Y 675
#define TIME_TO_LIVE 500  // 5-6 secunde sta pe ecran rata
#define NUMBER_LIVES 3
#define NUMBER_BULLETS 3
#define HEAD_CENTER_X 60
#define HEAD_CENTER_Y 0
#define HEAD_RADIUS 20
#define BIRD_FRAME_LENGTH 130.0
#define BIRD_FRAME_WIDTH 80.0
#define INCREMENT_SCORE 0.3
#define MAX_SCORE 10.0


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void RenderHUD(glm::mat3 modelMatrixScoreBar);
        void RenderBirdMovement(glm::mat3 modelMatrixBird, glm::mat3 modelMatrixHead,
            glm::mat3 modelMatrixLeftWing, glm::mat3 modelMatrixRightWing, float deltaTimeSeconds);

    protected:
        glm::mat3 modelMatrix, modelMatrixGrass, modelMatrixBird, modelMatrixLeftWing,
            modelMatrixRightWing, modelMatrixHead, modelMatrixScoreBar;
        float translateX, translateY, translateXScoreBar;

    };
}   // namespace m1
