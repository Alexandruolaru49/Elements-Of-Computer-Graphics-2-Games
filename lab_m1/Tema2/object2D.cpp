#include "object2D.h"
#include "tema2.h"
#include "camera.h"

#include <vector>
#include <iostream>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateCircuit(
    const std::string& name,
    std::vector<glm::vec3>& treesPositions,
    std::vector<VertexFormat>& vertices,
    std::vector<unsigned int>& indices,
    std::vector<glm::vec3>& points,
    glm::vec3 color,
    bool fill) 
{

    // Introduc toate punctele ce formeaza circuitul intr-un vector 
    // si totodata, creez un vector de pozitii pentru copacei
    float step = 0.01f;
    float a, b;
    

    glm::vec3 P1, P2;

    
    points.push_back(glm::vec3(-16.7, 0, 6.31));    // A
    
    P1 = glm::vec3(-16.7, 0, 6.31);
    P2 = glm::vec3(0.14, 0, 13.04);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(0.14, 0, 13.04));    // B  
    
    P1 = glm::vec3(0.14, 0, 13.04);
    P2 = glm::vec3(20, 0, 20);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(20, 0, 20));         // C
    

    P1 = glm::vec3(20, 0, 20);
    P2 = glm::vec3(46.79, 0, 19.38);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(46.79, 0, 19.38));   // D
    

    P1 = glm::vec3(46.79, 0, 19.38);
    P2 = glm::vec3(65.38, 0, 7.18);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(65.38, 0, 7.18));    // E
    

    P1 = glm::vec3(65.38, 0, 7.18);
    P2 = glm::vec3(82.21, 0, -9.63);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(82.21, 0, -9.63));   // F
    

    P1 = glm::vec3(82.21, 0, -9.63);
    P2 = glm::vec3(103.11, 0, -20.82);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(103.11, 0, -20.82)); // G
    

    P1 = glm::vec3(103.11, 0, -20.82);
    P2 = glm::vec3(130.35, 0, -12.61);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(130.35, 0, -12.61)); // H
    

    P1 = glm::vec3(130.35, 0, -12.61);
    P2 = glm::vec3(138.72, 0, 3.3);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(138.72, 0, 3.3));    // I
    

    P1 = glm::vec3(138.72, 0, 3.3);
    P2 = glm::vec3(125.13, 0, 19.49);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(125.13, 0, 19.49));  // J
    

    P1 = glm::vec3(125.13, 0, 19.49);
    P2 = glm::vec3(107.21, 0, 33.29);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(107.21, 0, 33.29));  // K
    

    P1 = glm::vec3(107.21, 0, 33.29);
    P2 = glm::vec3(115.05, 0, 54.2);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(115.05, 0, 54.2));   // L
    

    P1 = glm::vec3(115.05, 0, 54.2);
    P2 = glm::vec3(141.92, 0, 53.82);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(141.92, 0, 53.82));  // M
    

    P1 = glm::vec3(141.92, 0, 53.82);
    P2 = glm::vec3(167.3, 0, 38.52);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(167.3, 0, 38.52));   // N
    
    P1 = glm::vec3(167.3, 0, 38.52);
    P2 = glm::vec3(180, 0, 20);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(180, 0, 20));        // O
   

    P1 = glm::vec3(180, 0, 20);
    P2 = glm::vec3(180, 0, 0);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(180, 0, 0));         // P
    

    P1 = glm::vec3(180, 0, 0);
    P2 = glm::vec3(185.59, 0, -13.73);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(185.59, 0, -13.73)); // Q
    

    P1 = glm::vec3(185.59, 0, -13.73);
    P2 = glm::vec3(193.67, 0, -32.22);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(193.67, 0, -32.22)); // R
    

    P1 = glm::vec3(193.67, 0, -32.22);
    P2 = glm::vec3(186.26, 0, -48.62);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(186.26, 0, -48.62)); // S
    

    P1 = glm::vec3(186.26, 0, -48.62);
    P2 = glm::vec3(152.56, 0, -55.18);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(152.56, 0, -55.18)); // T
    

    P1 = glm::vec3(152.56, 0, -55.18);
    P2 = glm::vec3(123.28, 0, -54.97);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(123.28, 0, -54.97)); // U
    

    P1 = glm::vec3(123.28, 0, -54.97);
    P2 = glm::vec3(91.53, 0, -48.62);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(91.53, 0, -48.62));  // V
    

    P1 = glm::vec3(91.53, 0, -48.62);
    P2 = glm::vec3(70.36, 0, -60.27);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(70.36, 0, -60.27));  // W
    

    P1 = glm::vec3(70.36, 0, -60.27);
    P2 = glm::vec3(48.99, 0, -70.81);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(48.99, 0, -70.81));  // Z
   

    P1 = glm::vec3(48.99, 0, -70.81);
    P2 = glm::vec3(20.61, 0, -69.26);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(20.61, 0, -69.26));  // A1
   

    P1 = glm::vec3(20.61, 0, -69.26);
    P2 = glm::vec3(17.75, 0, -51.61);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(17.75, 0, -51.61));  // B1
    

    P1 = glm::vec3(17.75, 0, -51.61);
    P2 = glm::vec3(33.37, 0, -39.11);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(33.37, 0, -39.11));  // C1
    

    P1 = glm::vec3(33.37, 0, -39.11);
    P2 = glm::vec3(25.78, 0, -26.16);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(25.78, 0, -26.16));  // F1
 
    P1 = glm::vec3(25.78, 0, -26.16);
    P2 = glm::vec3(10.55, 0, -15.28);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(10.55, 0, -15.28));  // D1
   
    P1 = glm::vec3(10.55, 0, -15.28);
    P2 = glm::vec3(-12.74, 0, -10.52);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    

    points.push_back(glm::vec3(-12.74, 0, -10.52)); // E1
    // de la E1 la A (primul punct)
    
    P1 = glm::vec3(-12.74, 0, -10.52);
    P2 = glm::vec3(-16.7, 0, 6.31);
    for (float i = step; i < 1.0f; i = i + 0.01f) {
        glm::vec3 newPoint = P1 + (P2 - P1) * i;
        points.push_back(newPoint);
    }
    


    glm::vec3 point1, point2;
    glm::vec3 UP = glm::vec3(0, 1, 0);
    float distR = 5.0f;
    float distA = 5.0f;

    std::vector<glm::vec3> pointsR, pointsA;

    for (int i = 0; i < points.size() - 1; i++) {

        point1 = points[i];
        point2 = points[i + 1];
        glm::vec3 D = point2 - point1;
        D = glm::normalize(D);
        glm::vec3 P = glm::cross(D, UP);
        P = glm::normalize(P);

        glm::vec3 pointR = point1 + distR * P;
        glm::vec3 pointA = point1 - distA * P;

        pointsR.push_back(pointR);
        pointsA.push_back(pointA);

        // La fiecare 40 de puncte din geometria traseului, e generat cate un copac pe fiecare margine a drumului
        if (i % 40 == 0) {
            pointA = point1 - 3 * distA * P;
            pointR = point1 + 3 * distR * P;
            treesPositions.push_back(pointR);
            treesPositions.push_back(pointA);
        }

    }

    // Pentru legatura dintre ultimul punct cu primul
    point1 = points[points.size() - 1];
    point2 = points[0];
    glm::vec3 D = point2 - point1;
    D = glm::normalize(D);
    glm::vec3 P = glm::cross(D, UP);
    P = glm::normalize(P);

    glm::vec3 pointR = point1 + distR * P;
    glm::vec3 pointA = point1 - distA * P;

    pointsR.push_back(pointR);
    pointsA.push_back(pointA);

    pointA = point1 - 3 * distA * P;
    pointR = point1 + 3 * distR * P;
    treesPositions.push_back(pointR);
    treesPositions.push_back(pointA);

    // Introduc toate nodurile in "vertices"

    for (int i = 0; i < pointsR.size(); i++) {
        vertices.push_back(VertexFormat(pointsR[i], color));
    }
    for (int i = 0; i < pointsA.size(); i++) {
        vertices.push_back(VertexFormat(pointsA[i], color));
    }


    for (int i = 0; i < pointsR.size() - 1; i++) {

        // Primul triunghi din "patrat"
        indices.push_back(i);
        indices.push_back(i + pointsR.size());
        indices.push_back(i + pointsR.size() + 1);

        // Al doilea triunghi din "patrat"
        indices.push_back(i);
        indices.push_back(i + pointsR.size() + 1);
        indices.push_back(i + 1);

    }

    // Introduc si pentru ultimul "patrat"
    
    // Primul triunghi
    int i = pointsR.size() - 1;
    indices.push_back(i);
    indices.push_back(i + pointsR.size());
    indices.push_back(pointsR.size());

    // Al doiea triunghi
    indices.push_back(i);
    indices.push_back(pointsR.size());
    indices.push_back(0);



    Mesh* circuit = new Mesh(name);
  
    circuit->InitFromData(vertices, indices);
    return circuit;
}


Mesh* object2D::CreateCar(
    const std::string& name,
    glm::vec3 color,
    bool fill)
{
    
    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(-1.0f, 0, -2.0f), color),
        VertexFormat(glm::vec3(1.0f, 0, -2.0f), color),
        VertexFormat(glm::vec3(1.0f, 0, 2.0f), color),
        VertexFormat(glm::vec3(-1.0f, 0, 2.0f), color),
        VertexFormat(glm::vec3(-1.0f, 1.0f, -2.0f), color),
        VertexFormat(glm::vec3(1.0f, 1.0f, -2.0f), color),
        VertexFormat(glm::vec3(1.0f, 1.0f, 2.0f), color),
        VertexFormat(glm::vec3(-1.0f, 1.0f, 2.0f), color),
    };

    std::vector<unsigned int> indices =
    {
       0, 3, 1,
       1, 3, 2,
       0, 1, 4,
       1, 5, 4,
       4, 5, 6,
       4, 6, 7,
       1, 6, 5,
       1, 2, 6,
       7, 6, 3,
       6, 2, 3,
       4, 3, 7,
       0, 4, 3,
    };

    Mesh* car = new Mesh(name);

    car->InitFromData(vertices, indices);
    return car;
}