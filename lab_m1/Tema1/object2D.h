#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    //Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string& name, float length1, float length2, float leftButtomCornerX,
        float leftButtomCornerY, glm::vec3 color, bool fill = false);
    Mesh* CreateBird(const std::string& name, glm::vec3 color, bool fill);
    Mesh* CreateLeftWing(const std::string& name, bool fill);
    Mesh* CreateRightWing(const std::string& name, bool fill);
    Mesh* CreateCircle(const std::string& name, float centerX, float centerY, float radius, glm::vec3 color, bool fill);
}
