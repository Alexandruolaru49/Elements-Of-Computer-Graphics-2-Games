#include "object2D.h"
#include "tema1.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


//Mesh* object2D::CreateSquare(
//    const std::string& name,
//    glm::vec3 leftBottomCorner,
//    float length,
//    glm::vec3 color,
//    bool fill)
//{
//    glm::vec3 corner = leftBottomCorner;
//
//    std::vector<VertexFormat> vertices =
//    {
//        VertexFormat(corner, color),
//        VertexFormat(corner + glm::vec3(length, 0, 0), color),
//        VertexFormat(corner + glm::vec3(length, length, 0), color),
//        VertexFormat(corner + glm::vec3(0, length, 0), color)
//    };
//
//    Mesh* square = new Mesh(name);
//    std::vector<unsigned int> indices = { 0, 1, 2, 3 };
//
//    if (!fill) {
//        square->SetDrawMode(GL_LINE_LOOP);
//    }
//    else {
//        // Draw 2 triangles. Add the remaining 2 indices
//        indices.push_back(0);
//        indices.push_back(2);
//    }
//
//    square->InitFromData(vertices, indices);
//    return square;
//}


Mesh* object2D::CreateRectangle(
    const std::string& name,
    float length1,
    float length2,
    float leftButtomCornerX,
    float leftButtomCornerY,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(leftButtomCornerX, leftButtomCornerY, 0), color),
        VertexFormat(glm::vec3(leftButtomCornerX, leftButtomCornerY + length2, 0), color),
        VertexFormat(glm::vec3(leftButtomCornerX + length1, leftButtomCornerY + length2, 0), color),
        VertexFormat(glm::vec3(leftButtomCornerX + length1, leftButtomCornerY, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}


Mesh* object2D::CreateBird(
    const std::string& name,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        //// CORP MARE
        //-----------------------------------------------------------------------
        VertexFormat(glm::vec3(-50, 50,  0), glm::vec3(0.5f, 0.35f, 0.05f)),  // A
        VertexFormat(glm::vec3(50, 0,  0), glm::vec3((0.5f, 0.35f, 0.05f))),  // C
        VertexFormat(glm::vec3(-50, -50,  0), glm::vec3(0.5f, 0.35f, 0.05f)),  // B
        //-----------------------------------------------------------------------

       
        //// CIOC
        //-----------------------------------------------------------------------
        VertexFormat(glm::vec3(75, 10,  0), color),   // J
        VertexFormat(glm::vec3(75, -10,  0), color),   // L
        VertexFormat(glm::vec3(95, 0,  0), color),   // K
        //-----------------------------------------------------------------------

        //// PICIOR 1
        //-----------------------------------------------------------------------
        VertexFormat(glm::vec3(-70, 30,  0), color),     // 1
        VertexFormat(glm::vec3(-70, 10,  0), color),     // 2
        VertexFormat(glm::vec3(-50, 20,  0), color),     // 3
        //-----------------------------------------------------------------------
   
        //// PICIOR 2
        //-----------------------------------------------------------------------
        VertexFormat(glm::vec3(-70, -10,  0), color),     // 4
        VertexFormat(glm::vec3(-70, -30,  0), color),     // 5
        VertexFormat(glm::vec3(-50, -20,  0), color)      // 6
        //-----------------------------------------------------------------------
      
    };

    Mesh* bird = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    if (!fill) {
        bird->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    bird->InitFromData(vertices, indices);
    return bird;
}

Mesh* object2D::CreateLeftWing(
    const std::string& name,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        // ARIPA STANGA

        VertexFormat(glm::vec3(10, 5,  0), glm::vec3(0.5f, 0.35f, 0.05f)),  // D
        VertexFormat(glm::vec3(25, 60,  0), glm::vec3(0.5f, 0.35f, 0.05f)),  // F 
        VertexFormat(glm::vec3(-5, 60,  0), glm::vec3(0.5f, 0.35f, 0.05f)),  // E

    };

    Mesh* leftWing = new Mesh("leftWing");
 
    std::vector<unsigned int> indices = { 0, 1, 2};

    if (!fill) {
        leftWing->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    leftWing->InitFromData(vertices, indices);
    return leftWing;
}

Mesh* object2D::CreateRightWing(
    const std::string& name,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        // ARIPA DREAPTA

        VertexFormat(glm::vec3(10, 0,  0), glm::vec3(0.5f, 0.35f, 0.05f)),  // G
        VertexFormat(glm::vec3(25, -60,  0), glm::vec3(0.5f, 0.35f, 0.05f)),  // I
        VertexFormat(glm::vec3(-5, -60,  0), glm::vec3(0.5f, 0.35f, 0.05f)),  // H

    };

    Mesh* rightWing = new Mesh("rightWing");

    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        rightWing->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rightWing->InitFromData(vertices, indices);
    return rightWing;
}


Mesh* object2D::CreateCircle(
    const std::string& name,
    float centerX,
    float centerY,
    float radius,
    glm::vec3 color,
    bool fill)
{
    
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(centerX, centerY,  0), color)
    };

    Mesh* circle = new Mesh(name);

    std::vector<unsigned int> indices = {0};

    circle->SetDrawMode(GL_TRIANGLE_FAN);

    int max = 50;

    for (int i = 1; i < max; i++) {
        float x = centerX + (radius * cos(i * 2.0 * PI / max));
        float y = centerY + (radius * sin(i * 2.0 * PI / max));
        indices.push_back(i);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    
    }

    indices.push_back(1);

    circle->InitFromData(vertices, indices);
    return circle;
}



