#include "lab_m1/Tema2/tema2.h"
#include <vector>
#include <string>
#include <iostream>


using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{

    // Pozitia initiala a masinii
    translateX = 0;
    translateY = 0.5f;
    translateZ = 6.5f;

    // Camera 3rd Person 
    camera = new mycamera::MyCamera();
    camera->Set(glm::vec3(0, 2.50f, 10.0f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    // Camera pentru minimap
    cameraMiniMap = new mycamera::MyCamera();
    cameraMiniMap->Set(glm::vec3(translateX, 20.0f, translateZ), glm::vec3(translateX, translateY, translateZ), glm::vec3(1, 0, 0));
    
    // Pointer de tip Camera care pointeaza pe rand la cele 2 camere
    currentCamera = camera;
    

    Mesh* car = object2D::CreateCar("car", glm::vec3(1, 0, 0), true);
    AddMeshToList(car);

    // TREE
    Mesh* tree = new Mesh("tree");

    tree->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "goodTree/source"), "Tree.fbx");
    meshes[tree->GetMeshID()] = tree;

    // GRASS
    Mesh* grass = new Mesh("grass");
    grass->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
    meshes[grass->GetMeshID()] = grass;
    modelMatrixGrass = glm::mat4(1);

    // CIRCUIT
    Mesh* circuit = object2D::CreateCircuit("circuit", treesPositions, vertices, indices, points, glm::vec3(0.3, 0.3, 0.3), true);
    AddMeshToList(circuit);

    // Elimin copacii care sunt pe pista
    for (int i = 0; i < treesPositions.size(); i++) {
        glm::vec3 point = glm::vec3(treesPositions[i].x, treesPositions[i].y, treesPositions[i].z + 20);
        if (isInsideCircuit(point, vertices, indices)) {
            treesPositions.erase(treesPositions.begin() + i);
        }
    }


    Mesh* car2 = object2D::CreateCar("car2", glm::vec3(0, 1, 0), true);
    AddMeshToList(car2);

    Mesh* car3 = object2D::CreateCar("car3", glm::vec3(0, 0, 1), true);
    AddMeshToList(car3);

    Mesh* car4 = object2D::CreateCar("car4", glm::vec3(0.5, 0.5, 0.5), true);
    AddMeshToList(car4);

    // CONSTRUIREA DRUMULUI PREDEFINIT PENTRU CELELALTE MASINI

    // CAR 2
    for (int i = 0; i < points.size(); i++) {
        car2Positions.push_back(glm::vec3(points[i].x, points[i].y, points[i].z + 2.0f));
    }

    // CAR 3
    for (int i = (points.size() / 2); i < points.size(); i++) {
        car3Positions.push_back(glm::vec3(points[i].x, points[i].y, points[i].z + 4.0f));
    }
    for (int i = 0; i < points.size() / 2; i++) {
        car3Positions.push_back(glm::vec3(points[i].x, points[i].y, points[i].z + 4.0f));
    }


    // CAR 4
    for (int i = (3 * points.size() / 4); i <points.size(); i++) {
        car4Positions.push_back(glm::vec3(points[i].x, points[i].y, points[i].z + 3.0f));
    }
    for (int i = 0; i < (3 * points.size() / 4); i++) {
        car4Positions.push_back(glm::vec3(points[i].x, points[i].y, points[i].z + 3.0f));
    }
    

    // Indicii pentru celelalte masini (la ce elem din vectorul de pozitii sunt)

    index2 = 0;
    index3 = 0;
    index4 = 0;

    // Pozitiile initiale ale masinilor
    tx2 = car2Positions[index2].x;
    ty2 = car2Positions[index2].y;
    tz2 = car2Positions[index2].z;

    tx3 = car3Positions[index3].x;
    ty3 = car3Positions[index3].y;
    tz3 = car3Positions[index3].z;

    tx4 = car4Positions[index4].x;
    ty4 = car4Positions[index4].y;
    tz4 = car4Positions[index4].z;
    

    // Initialize angular steps
    angularStepOX = 0;
    angularStepOY = 0;
    angularStepOZ = 0;

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);

    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);



    // DEFINIRE SHADER
    {
        Shader* shader = new Shader("homeworkShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

}

void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.53, 0.81, 0.92, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(currentCamera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();


}

void Tema2::MyRenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, glm::vec3 color) {

    if (!mesh || !shader || !shader->GetProgramID()) {
        return;
    }
    glUseProgram(shader->program);

    int locationModel = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(locationModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    int locationView = glGetUniformLocation(shader->program, "View");
    glm::mat4 viewMatrix = currentCamera->GetViewMatrix();
    glUniformMatrix4fv(locationView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    int locationProjection = glGetUniformLocation(shader->program, "Projection");
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    glUniformMatrix4fv(locationProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    int locationColor = glGetUniformLocation(shader->program, "Color");
    glUniform3fv(locationColor, 1, glm::value_ptr(color));

    int locationCarPosition = glGetUniformLocation(shader->program, "CarPosition");
    glUniform3fv(locationCarPosition, 1, glm::value_ptr(glm::vec3(translateX, translateY, translateZ)));

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


void Tema2::RenderScene(float deltaTimeSeconds) {

    // RENDERING GRASS
    
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            modelMatrixGrass = glm::mat4(1);
            
            modelMatrixGrass *= transform3D::Translate(-1000 + 50 * i, -0.2, -1000 + 50 * j);
            modelMatrixGrass *= transform3D::Scale(2, 2, 2);
            MyRenderMesh(meshes["grass"], shaders["homeworkShader"], modelMatrixGrass, glm::vec3(0, 0.7, 0));
        }
    }

    // RENDERING TREES
    for (int i = 0; i < treesPositions.size(); i++) {
        modelMatrixTree = glm::mat4(1);
        modelMatrixTree *= transform3D::Translate(treesPositions[i].x, -0.2, treesPositions[i].z + 20);
        modelMatrixTree *= transform3D::RotateOX(RADIANS(-90));
        modelMatrixTree *= transform3D::Scale(1, 1, 1);
        MyRenderMesh(meshes["tree"], shaders["homeworkShader"], modelMatrixTree, glm::vec3(0, 0.4, 0));
    }
    
    // RENDERING MY CAR
    modelMatrixCar = glm::mat4(1);
    modelMatrixCar *= transform3D::Translate(translateX, translateY, translateZ);
    modelMatrixCar *= transform3D::RotateOX(angularStepOX);
    modelMatrixCar *= transform3D::RotateOY(angularStepOY);
    modelMatrixCar *= transform3D::RotateOZ(angularStepOZ);
    modelMatrixCar *= transform3D::Scale(0.3, 0.3, 0.3);
    MyRenderMesh(meshes["car"], shaders["homeworkShader"], modelMatrixCar, glm::vec3(1, 0, 0));


    // RENDERING OTHER CARS
    
    // CAR 2
    modelMatrixCar2 = glm::mat4(1);
    modelMatrixCar2 *= transform3D::Translate(tx2, ty2, tz2 + 20);
    int nextIndex2;
    if (index2 == car2Positions.size() - 1) {
        nextIndex2 = 0;
    }
    else {
        nextIndex2 = index2 + 1;
    }
    // Calculez unghiul (panta) dintre punctul la care ma aflu si punctul unde vreau sa ajung
    modelMatrixCar2 *= transform3D::RotateOY(atan((car2Positions[nextIndex2].x - tx2) / (car2Positions[nextIndex2].z - tz2)));
    modelMatrixCar2 *= transform3D::Scale(0.3, 0.3, 0.3);
    MyRenderMesh(meshes["car2"], shaders["homeworkShader"], modelMatrixCar2, glm::vec3(0, 0, 1));

    // Actualizare + conditie terminare circuit
    index2++;
    if (index2 >= car2Positions.size()) {
        index2 = 0;
    }
    tx2 = car2Positions[index2].x;
    ty2 = car2Positions[index2].y;
    tz2 = car2Positions[index2].z;


    // CAR 3
    modelMatrixCar3 = glm::mat4(1);
    modelMatrixCar3 *= transform3D::Translate(tx3, ty3, tz3 + 20);
    int nextIndex3;
    if (index3 == car3Positions.size() - 1) {
        nextIndex3 = 0;
    }
    else {
        nextIndex3 = index3 + 1;
    }
    // Calculez unghiul (panta) dintre punctul la care ma aflu si punctul unde vreau sa ajung
    modelMatrixCar3 *= transform3D::RotateOY(atan((car3Positions[nextIndex3].x - tx3) / (car3Positions[nextIndex3].z - tz3)));
    modelMatrixCar3 *= transform3D::Scale(0.3, 0.3, 0.3);
    MyRenderMesh(meshes["car3"], shaders["homeworkShader"], modelMatrixCar3, glm::vec3(0, 1, 0));

    // Actualizare + conditie terminare circuit
    index3++;
    if (index3 >= car3Positions.size()) {
        index3 = 0;
    }
    tx3 = car3Positions[index3].x;
    ty3 = car3Positions[index3].y;
    tz3 = car3Positions[index3].z;


    // CAR 4
    modelMatrixCar4 = glm::mat4(1);
    modelMatrixCar4 *= transform3D::Translate(tx4, ty4, tz4 + 20);
    int nextIndex4;
    if (index4 == car4Positions.size() - 1) {
        nextIndex4 = 0;
    }
    else {
        nextIndex4 = index4 + 1;
    }
    // Calculez unghiul (panta) dintre punctul la care ma aflu si punctul unde vreau sa ajung
    modelMatrixCar4 *= transform3D::RotateOY(atan((car4Positions[nextIndex4].x - tx4) / (car4Positions[nextIndex4].z - tz4)));
    modelMatrixCar4 *= transform3D::Scale(0.3, 0.3, 0.3);
    MyRenderMesh(meshes["car4"], shaders["homeworkShader"], modelMatrixCar4, glm::vec3(0.5, 0.5, 0.5));

    // Actualizare + conditie terminare circuit
    index4++;
    if (index4 >= car4Positions.size()) {
        index4 = 0;
    }
    tx4 = car4Positions[index4].x;
    ty4 = car4Positions[index4].y;
    tz4 = car4Positions[index4].z;

    
    // RENDERING CIRCUIT
    modelMatrixCircuit = glm::mat4(1);
    modelMatrixCircuit *= transform3D::Translate(0, 0, 20);
    MyRenderMesh(meshes["circuit"], shaders["homeworkShader"], modelMatrixCircuit, glm::vec3(0.3, 0.3, 0.3));
}

void Tema2::Update(float deltaTimeSeconds)
{

    if (carStunned > 0) {
        carStunned--;
    }
    
    currentCamera = camera;
    projectionMatrix = glm::perspective(RADIANS(70), window->props.aspectRatio, 0.01f, 200.0f);
    RenderScene(deltaTimeSeconds);

    // VERIFICARE COLIZIUNE MASINI
    if (isColliding()) {
        carStunned = 50;
    }
    


    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);


    // RENDERING MINIMAP
    
    currentCamera = cameraMiniMap;
    float orthoLeft = -8.0f, orthoRight = 8.0f, orthoUp = 4.5f, orthoDown = -4.5;
    projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
    RenderScene(deltaTimeSeconds);
    

}

void Tema2::FrameEnd()
{
    
}

bool Tema2::isColliding() {

    float distance = sqrt((translateX - tx2) * (translateX - tx2) +
                        (translateY - ty2) * (translateY - ty2) + 
                        (translateZ - tz2 - 20) * (translateZ - tz2 - 20));
    

    if (distance < 1.0f) {
        cout << "COLIZIUNE" << endl;
        return true;
    }

    distance = sqrt((translateX - tx3) * (translateX - tx3) +
        (translateY - ty3) * (translateY - ty3) +
        (translateZ - tz3 - 20) * (translateZ - tz3 - 20));

    if (distance < 1.0f) {
        cout << "COLIZIUNE" << endl;
        return true;
    }

    distance = sqrt((translateX - tx4) * (translateX - tx4) +
        (translateY - ty4) * (translateY - ty4) +
        (translateZ - tz4 - 20) * (translateZ - tz4 - 20));

    if (distance < 1.0f) {
        cout << "COLIZIUNE" << endl;
        return true;
    }

}


float Tema2::triangleArea(glm::vec3 A, glm::vec3 B, glm::vec3 C) {

    // COMPUTING TRIANGLE AREA

    float a = glm::distance(A, B);
    float b = glm::distance(A, C);
    float c = glm::distance(B, C);

    float s = (a + b + c) / 2.0f;

    return sqrt(s * (s - a) * (s - b) * (s - c));
}

bool Tema2::isInsideCircuit(glm::vec3 point, std::vector<VertexFormat> vertices, std::vector<unsigned int> indices) {

    // Pt fiecare triunghi ce formeaza geometria circuitului
    for (int i = 0; i < indices.size(); i = i + 3) {
        // formam triunghiul din punctele A,B,C
        glm::vec3 A = glm::vec3(vertices[indices[i]].position.x, vertices[indices[i]].position.y, vertices[indices[i]].position.z + 20.0f);
        glm::vec3 B = glm::vec3(vertices[indices[i + 1]].position.x, vertices[indices[i + 1]].position.y, vertices[indices[i + 1]].position.z + 20.0f);
        glm::vec3 C = glm::vec3(vertices[indices[i + 2]].position.x, vertices[indices[i + 2]].position.y, vertices[indices[i + 2]].position.z + 20.0f);

        float area = triangleArea(A, B, C);
        float area_sum = 0.0f;
        // verific daca aria triunghiului este aproximativ egala cu suma ariilor triunghiurilor formate din varfurile celui initial si punctul
        // pentru care se face verificarea
        area_sum += triangleArea(A, B, point);
        area_sum += triangleArea(A, C, point);
        area_sum += triangleArea(B, C, point);

        if (abs(area - area_sum) < 0.01f) {
            return true;
        }

    }

    return false;
}



void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    
    // DEPLASAREA MASINII SI A CAMEREI

    if (carStunned == 0) {

        float speed = 20;
        float distanceToTarget = 3.7f;

        float newTZ, newTX;

        if (window->KeyHold(GLFW_KEY_W)) {

            newTZ = translateZ;
            newTX = translateX;

            newTZ -= speed * cos(angularStepOY) * deltaTime;
            newTX -= speed * sin(angularStepOY) * deltaTime;

            if (isInsideCircuit(glm::vec3(newTX, 0, newTZ), vertices, indices)) {
                translateZ -= speed * cos(angularStepOY) * deltaTime;
                translateX -= speed * sin(angularStepOY) * deltaTime;
                camera->MoveForward(speed * deltaTime);
                cameraMiniMap->Set(glm::vec3(translateX, 20.0f, translateZ), glm::vec3(translateX, translateY, translateZ), glm::vec3(1, 0, 0));
                
            }

        }

        if (window->KeyHold(GLFW_KEY_S)) {

            newTZ = translateZ;
            newTX = translateX;

            newTZ += speed * cos(angularStepOY) * deltaTime;
            newTX += speed * sin(angularStepOY) * deltaTime;

            if (isInsideCircuit(glm::vec3(newTX, 0, newTZ), vertices, indices)) {
                translateZ += speed * cos(angularStepOY) * deltaTime;
                translateX += speed * sin(angularStepOY) * deltaTime;
                camera->MoveForward(-speed * deltaTime);
                cameraMiniMap->Set(glm::vec3(translateX, 20.0f, translateZ), glm::vec3(translateX, translateY, translateZ), glm::vec3(1, 0, 0));
                
            }


        }

        if (window->KeyHold(GLFW_KEY_A)) {

            angularStepOY += 1.5f * deltaTime;

            // ROTATE THIRD PERSON OY
            camera->TranslateForward(distanceToTarget);
            camera->RotateFirstPerson_OY(1.5f * deltaTime);
            camera->TranslateForward(-distanceToTarget);

        }
        if (window->KeyHold(GLFW_KEY_D)) {

            angularStepOY -= 1.5f * deltaTime;

            // ROTATE THIRD PERSON OY
            camera->TranslateForward(distanceToTarget);
            camera->RotateFirstPerson_OY(-1.5f * deltaTime);
            camera->TranslateForward(-distanceToTarget);
        }

    }


    // PENTRU TESTARE
    if (window->KeyHold(GLFW_KEY_SPACE)) {
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        camera->TranslateUpward(1);
    }
    if (window->KeyHold(GLFW_KEY_F)) {
        
        camera->TranslateUpward(-1);
    }


}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}



void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

    // PENTRU TESTARE
    // Add mouse move event
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            
            camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
            camera->RotateFirstPerson_OY(-sensivityOY * deltaX);

        }
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}

