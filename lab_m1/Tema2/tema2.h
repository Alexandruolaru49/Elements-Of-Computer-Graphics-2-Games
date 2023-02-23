#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/camera.h"
#include "lab_m1/Tema2/transform3D.h"
#include "lab_m1/Tema2/object2D.h"

#define PI 3.1415926535897932384626433832795


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        Tema2();
        ~Tema2();

        void Init() override;
        

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;

        void MyRenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::vec3 color);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        

        void RenderScene(float deltaTimeSeconds);
        float triangleArea(glm::vec3 A, glm::vec3 B, glm::vec3 C);
        bool isInsideCircuit(glm::vec3 point, std::vector<VertexFormat> vertices, std::vector<unsigned int> indices);
        bool isColliding();
        

    protected:
        glm::mat4 modelMatrixCar, modelMatrixCircuit, modelMatrixTree,
                modelMatrixCar2, modelMatrixCar3, modelMatrixCar4, modelMatrixGrass;

        // Pentru masina "condusa" de mine
        float translateX, translateY, translateZ;
        // Pentru celelalte masini
        int index2, index3, index4;
        float tx2, ty2, tz2, tx3, ty3, tz3, tx4, ty4, tz4;
        std::vector<glm::vec3> car2Positions;
        std::vector<glm::vec3> car3Positions;
        std::vector<glm::vec3> car4Positions;

        // variabila ce va fi mai mare decat 0 (un numar la alegere) atunci cand masina
        // jucatorului se va lovi de o alta masina de pe traseu, iar acesta nu se mai
        // poate misca o perioada de timp
        int carStunned = 0;
        
        float scaleX, scaleY, scaleZ;
        float angularStepOX, angularStepOY, angularStepOZ;
        float cameraMiniMapX = 20.0f, cameraMiniMapZ = -20.0f;
        //float orthoLeft = -8.0f, orthoRight = 8.0f, orthoUp = 4.5f, orthoDown = -4.5;
        GLenum polygonMode;
        ViewportArea miniViewportArea;
        mycamera::MyCamera *camera, *cameraMiniMap, *currentCamera;
        glm::mat4 projectionMatrix, projectionMatrixMiniMap;
        std::vector<glm::vec3> treesPositions;
        std::vector<glm::vec3> points;
        std::vector<unsigned int> indices;
        std::vector<VertexFormat> vertices;
    };
}   // namespace m1