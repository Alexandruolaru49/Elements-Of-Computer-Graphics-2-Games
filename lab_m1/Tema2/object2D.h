#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    Mesh* CreateCircuit(const std::string& name, std::vector<glm::vec3>& treesPositions, std::vector<VertexFormat>& vertices,
        std::vector<unsigned int>& indices, std::vector<glm::vec3>& points, glm::vec3 color, bool fill);
    Mesh* CreateCar(const std::string& name, glm::vec3 color, bool fill);
}
