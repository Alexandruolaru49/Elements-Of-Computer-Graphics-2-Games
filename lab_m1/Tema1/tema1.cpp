#include "lab_m1/Tema1/tema1.h"
#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#include "core/engine.h"
#include "utils/gl_utils.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace m1;


// angle = nr random intre 0 si 1 care va fi inmultit cu PI
float angle;
float birdSpeed = BIRD_SPEED;
float leftWingAngle = 0, rightWingAngle = 0;
float centerBirdX = CENTER_BIRD_X, centerBirdY = CENTER_BIRD_Y;
float centerLeftWingX = CENTER_LEFT_WING_X, centerLeftWingY = CENTER_LEFT_WING_Y;
float centerRightWingX = CENTER_RIGHT_WING_X, centerRightWingY = CENTER_RIGHT_WING_Y;
float initialScoreBarCenterX = INITIAL_SCOREBAR_CENTER_X, initialScoreBarCenterY = INITIAL_SCOREBAR_CENTER_Y;

// Limitele pentru marginile ecranului
float screenLimitX = SCREEN_LIMIT_X, screenLimitY = SCREEN_LIMIT_Y;

// Time to live (5 secunde timp pe ecran per rata)
float ttl = TIME_TO_LIVE;
bool startedFlying = false;
bool deadBird = false;
bool birdOut = false;   // daca rata evadeaza sau deja a murit, nu mai poate fi lovita inca o data

int numberOfBirds = 0;
int numberOfLives = NUMBER_LIVES;
int numberOfBullets = NUMBER_BULLETS;
float score = 1;

float resolutionX;
float resolutionY;




Tema1::Tema1()
{
}                      


Tema1::~Tema1()
{
}


void Tema1::Init()
{

    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float rectangleSide1 = window->GetResolution().x;
    float rectangleSide2 = window->GetResolution().y / 4.23;    // daca pt resY = 720, inaltimea ierbii e 170 -> scalam la resY

    screenLimitX = window->GetResolution().x;
    screenLimitY = window->GetResolution().y;

    float resX = window->GetResolution().x;
    resolutionX = resX;
    float resY = window->GetResolution().y;
    resolutionY = resY;

    initialScoreBarCenterX = resX - 210;
    initialScoreBarCenterY = resY - 45;

    // Generez random unghiul ratei
    // angle = nr random intre 0.1 si 0/9 care va fi inmultit cu PI (primele 2 cadrane trigonometrice)
     
    angle = (0.1 + static_cast<float>(rand()) * static_cast<float>(0.9 - 0.1) / RAND_MAX);
    angle = angle * PI;
    
    translateX = SPAWN_BIRD_X;
    translateY = SPAWN_BIRD_Y;

    Mesh* grass = object2D::CreateRectangle("grass", rectangleSide1, rectangleSide2, 0.0, 0.0, glm::vec3(0, 0.4, 0), true);
    AddMeshToList(grass);

    Mesh* bird = object2D::CreateBird("bird", glm::vec3(1.0, 0.5, 0.0), true);
    AddMeshToList(bird);
    
    Mesh* leftWing = object2D::CreateLeftWing("leftWing", true);
    AddMeshToList(leftWing);

    Mesh* rightWing = object2D::CreateRightWing("rightWing", true);
    AddMeshToList(rightWing);

    Mesh* head = object2D::CreateCircle("head", HEAD_CENTER_X, HEAD_CENTER_Y, HEAD_RADIUS, glm::vec3(0.0, 0.3, 0), true);
    AddMeshToList(head);


    Mesh* life1, * life2, * life3;
    life1 = object2D::CreateCircle("life1", 25, resY - 30, 20, glm::vec3(1, 0, 0), true);
    life2 = object2D::CreateCircle("life2", 75, resY - 30, 20, glm::vec3(1, 0, 0), true);
    life3 = object2D::CreateCircle("life3", 125, resY - 30, 20, glm::vec3(1, 0, 0), true);
    AddMeshToList(life1);
    AddMeshToList(life2);
    AddMeshToList(life3);

    Mesh* bullet1, * bullet2, * bullet3;
    bullet1 = object2D::CreateRectangle("bullet1", 10, 30, 20, resY - 100, glm::vec3(0, 0, 0), true);
    bullet2 = object2D::CreateRectangle("bullet2", 10, 30, 70, resY - 100, glm::vec3(0, 0, 0), true);
    bullet3 = object2D::CreateRectangle("bullet3", 10, 30, 120, resY - 100, glm::vec3(0, 0, 0), true);
    AddMeshToList(bullet1);
    AddMeshToList(bullet2);
    AddMeshToList(bullet3);

    Mesh* scoreFrame = object2D::CreateRectangle("scoreFrame", 200, 50, resX - 230, resY - 70, glm::vec3(0, 0, 0), false);
    AddMeshToList(scoreFrame);

    Mesh* scoreBar = object2D::CreateRectangle("scoreBar", 20 , 50, resX - 230, resY - 70, glm::vec3(0, 0, 1), true);
    AddMeshToList(scoreBar);

}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.0f, 0.5f, 1.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{   
    // Daca jucatorul nu mai are vieti, se reseteaza jocul
    if (numberOfLives == 0) {
        score = 1;
        numberOfBirds = 0;
        numberOfLives = NUMBER_LIVES;
        birdSpeed = BIRD_SPEED;
    }

    
    // Animatie umplere SCORE BAR + afisare vieti si gloante (HUD)
    RenderHUD(modelMatrixScoreBar);

    // se decrementeaza timpul pe care il mai are rata pe ecran
    ttl--;

    // La fiecare 5 pasari care mor/evadeaza, se mareste viteza lor
    // si apare o pasare speciala (de alta culoare) care iti da o viata
    // (doar daca nu ai deja nr maxim de vieti, adica 3)
    if (numberOfBirds == 5) {
        birdSpeed += INCREMENT_SPEED;
        numberOfBirds = 0;
    }
    
    // Rendering GRASS
    modelMatrixGrass = glm::mat3(1);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrixGrass);

    // DACA RATA A FOST IMPUSCATA
    if (deadBird == true) {
        // rata va cadea vertical in jos
        angle = (3.0 / 2.0) * PI;
        birdOut = true;

        // Dupa ce rata a murit si iese din ecran
        if (translateY < 0) {
            birdOut = false;
            // Numarul de pasari de pana acum
            numberOfBirds++;
            // SE RESETEAZA VARIABILELE
            deadBird = false;
            numberOfBullets = NUMBER_BULLETS;   // se reseteaza gloantele
            translateX = SPAWN_BIRD_X;
            translateY = SPAWN_BIRD_Y;
            ttl = TIME_TO_LIVE;
            startedFlying = false;
            // Generez random unghiul urmatoarei rate
            angle = (0.1 + static_cast<float>(rand()) * static_cast<float>(0.9 - 0.1) / RAND_MAX);
            angle = angle * PI;
        }

    }
    // DACA RATA NU A FOST INCA IMPUSCATA
    else {
        // DACA RATA LOVESTE MARGINEA ECRANULUI
        if (ttl > 0) {
            // Rata loveste marginea din dreapta a ecranului
            if (translateX > screenLimitX - SCREEN_OFFSET) {
                angle = PI - angle;
                startedFlying = true;
            }
            // Rata loveste marginea din stanga a ecranului
            if (translateX < SCREEN_OFFSET) {
                angle = PI - angle;
                startedFlying = true;
            }
            // Rata loveste marginea de sus a ecranului
            if (translateY > screenLimitY - SCREEN_OFFSET) {
                angle = 2 * PI - angle;
                startedFlying = true;
            }
            // Rata loveste marginea de jos a ecranului
            if (translateY < GRASS_LIMIT_Y && startedFlying == true) {
                angle = 2 * PI - angle;
                startedFlying = true;
            }
        }
        else {

            // Rata va zbura vertical in sus cand evadeaza
            angle = (1.0 / 2.0) * PI;
            birdOut = true;

            // Dupa ce rata evadeaza, una noua va aparea pe ecran
            if (translateY > screenLimitY) {
                birdOut = false;
                // Numarul de pasari de pana acum
                numberOfBirds++;
                // Se pierde o viata
                numberOfLives--;
                // SE RESETEAZA VARIABILELE
                numberOfBullets = NUMBER_BULLETS;   // se reseteaza gloantele
                translateX = SPAWN_BIRD_X;
                translateY = SPAWN_BIRD_Y;
                ttl = TIME_TO_LIVE;
                startedFlying = false;
                // Generez random unghiul urmatoarei rate
                angle = (0.1 + static_cast<float>(rand()) * static_cast<float>(0.9 - 0.1) / RAND_MAX);
                angle = angle * PI;
            }
        }
    }


    // Initializare model matrices
    modelMatrixBird = glm::mat3(1);
    modelMatrixLeftWing = glm::mat3(1);
    modelMatrixRightWing = glm::mat3(1);
    modelMatrixHead = glm::mat3(1);

    // Miscarea ratei + animatii aripi
    RenderBirdMovement(modelMatrixBird, modelMatrixHead, modelMatrixLeftWing,
        modelMatrixRightWing, deltaTimeSeconds);
    
}

void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    /*cout << "MOUSE X: " << mouseX << "  " << "MOUSE Y:" << (720 - mouseY) << endl;
    cout << "TX: " << translateX << "  " << "TY: " << translateY << endl;*/
    
    if (window->MouseHold(GLFW_MOUSE_BUTTON_1)) {
        if (numberOfBullets > 0) {
            numberOfBullets--;
            // "Creez" un dreptunghi imaginar in jurul ratei cu L = 130 si l = 80, in interiorul caruia daca dau click,
            // se considera ca ating rata
            if ((abs(mouseX - translateX) < BIRD_FRAME_LENGTH)
                && (abs(resolutionY - mouseY - translateY) < BIRD_FRAME_WIDTH) && (birdOut == false)) {
                deadBird = true;
                // SCOR MAXIM - 30
                if (score < MAX_SCORE) {
                    score += INCREMENT_SCORE;
                }
                cout << "HIT" << endl;
            }
            else {
                cout << "MISS" << endl;
            }
        }
         
    }
    
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}

void Tema1::RenderHUD(glm::mat3 modelMatrixScoreBar) {
    modelMatrixScoreBar = glm::mat3(1);
    modelMatrixScoreBar *= transform2D::Translate(initialScoreBarCenterX - 20, initialScoreBarCenterY);
    modelMatrixScoreBar *= transform2D::Scale(-score, 1);
    modelMatrixScoreBar *= transform2D::Translate(-initialScoreBarCenterX, -initialScoreBarCenterY);

    RenderMesh2D(meshes["scoreFrame"], shaders["VertexColor"], glm::mat3(1));
    RenderMesh2D(meshes["scoreBar"], shaders["VertexColor"], modelMatrixScoreBar);

    switch (numberOfBullets)
    {
    case 3:
        RenderMesh2D(meshes["bullet1"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["bullet2"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["bullet3"], shaders["VertexColor"], glm::mat3(1));
        break;

    case 2:
        RenderMesh2D(meshes["bullet1"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["bullet2"], shaders["VertexColor"], glm::mat3(1));
        break;

    case 1:
        RenderMesh2D(meshes["bullet1"], shaders["VertexColor"], glm::mat3(1));
        break;

    default:
        break;
    }


    // Afisare Vieti
    switch (numberOfLives)
    {

    case 3:
        RenderMesh2D(meshes["life1"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["life2"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["life3"], shaders["VertexColor"], glm::mat3(1));
        break;

    case 2:
        RenderMesh2D(meshes["life1"], shaders["VertexColor"], glm::mat3(1));
        RenderMesh2D(meshes["life2"], shaders["VertexColor"], glm::mat3(1));
        break;

    case 1:
        RenderMesh2D(meshes["life1"], shaders["VertexColor"], glm::mat3(1));
        break;

    default:
        break;
    }
}


void Tema1::RenderBirdMovement(glm::mat3 modelMatrixBird, glm::mat3 modelMatrixHead,
                        glm::mat3 modelMatrixLeftWing, glm::mat3 modelMatrixRightWing,
                        float deltaTimeSeconds) {

    // Miscarea ratei
    // translateX si translateY se calculeaza dupa urmatoarele formule trigonometrice
    translateX += birdSpeed * cos(angle) * deltaTimeSeconds;
    translateY += birdSpeed * sin(angle) * deltaTimeSeconds;

    // Am orientat pasarea cu ciocul in directia in care va zbura
    modelMatrixBird *= transform2D::Translate(translateX, translateY);
    modelMatrixBird *= transform2D::Translate(centerBirdX, centerBirdY);
    modelMatrixBird *= transform2D::Rotate(angle); // unghiul (angle) - care va fi random
    modelMatrixBird *= transform2D::Translate(-centerBirdX, -centerBirdY); // centrul pasarii

    // CAP
    modelMatrixHead *= transform2D::Translate(translateX, translateY);
    modelMatrixHead *= transform2D::Translate(centerBirdX, centerBirdY);
    modelMatrixHead *= transform2D::Rotate(angle);
    modelMatrixHead *= transform2D::Translate(-centerBirdX, -centerBirdY);

    // Calcularea unghiurilor pentru animatiile aripilor
    if (leftWingAngle < 1) {
        leftWingAngle += 0.05;
    }
    else {
        leftWingAngle = 0;
    }

    if (rightWingAngle > -1) {
        rightWingAngle -= 0.05;
    }
    else {
        rightWingAngle = 0;
    }

    // ALINIERE ARIPI LANGA CORP
    modelMatrixLeftWing *= transform2D::Translate(translateX, translateY);
    modelMatrixLeftWing *= transform2D::Translate(centerBirdX, centerBirdY);
    modelMatrixLeftWing *= transform2D::Rotate(angle);
    modelMatrixLeftWing *= transform2D::Translate(-centerBirdX, -centerBirdY);

    modelMatrixRightWing *= transform2D::Translate(translateX, translateY);
    modelMatrixRightWing *= transform2D::Translate(centerBirdX, centerBirdY);
    modelMatrixRightWing *= transform2D::Rotate(angle);
    modelMatrixRightWing *= transform2D::Translate(-centerBirdX, -centerBirdY);

    // ANIMATIE ARIPI
    // translatam aripile la -centrul lor
    // rotatie aripi, apoi translatam la loc

    // LEFT
    modelMatrixLeftWing *= transform2D::Translate(centerLeftWingX, centerLeftWingY);
    modelMatrixLeftWing *= transform2D::Rotate(leftWingAngle);
    modelMatrixLeftWing *= transform2D::Translate(-centerLeftWingX, -centerLeftWingY);

    // RIGHT 
    modelMatrixRightWing *= transform2D::Translate(centerRightWingX, centerRightWingY);
    modelMatrixRightWing *= transform2D::Rotate(rightWingAngle);
    modelMatrixRightWing *= transform2D::Translate(-centerRightWingX, -centerRightWingY);

    // Render Meshes
    RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrixHead);
    RenderMesh2D(meshes["bird"], shaders["VertexColor"], modelMatrixBird);
    RenderMesh2D(meshes["leftWing"], shaders["VertexColor"], modelMatrixLeftWing);
    RenderMesh2D(meshes["rightWing"], shaders["VertexColor"], modelMatrixRightWing);

}