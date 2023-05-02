#include "Building.hpp"
#include <algorithm>

Building::Building(BuildingMap& map) {
    // Copy in the data of the provided map
    m_xSize = map.getXSize();
    m_zSize = map.getZSize();

    m_building = new int[m_xSize * m_zSize];

    for(int i = 0; i < m_xSize * m_zSize; i++) {
        // Set any negative values to 0
        m_building[i] = std::max(0, map.m_building[i]);
    }

    Init();
}

Building::~Building() {
    if(m_building != nullptr) {
        delete[] m_building;
    }
}

void Building::Init() {
    unsigned int index = 0;
    // Creating each cube of the building
    for(unsigned int z = 0; z < m_zSize; z++) {
        for(unsigned int x = 0; x < m_xSize; x++) {
            int ySize = m_building[z * m_xSize + x];
            // Should skip if ySize is 0
            // Starting at the floor, stacking cubes upwards
            for(unsigned int y = 0; y < ySize; y++) {
                // First Face
                m_geometry.AddVertex(x, y, z, 0.5f, 0.0f); // bottom left
                m_geometry.AddVertex(x+1 , y, z, 1.0f, 0.0f); // bottom right
                m_geometry.AddVertex(x+1, y+1, z, 1.0f, 1.0f); // top right
                m_geometry.AddVertex(x, y+1, z, 0.5f, 1.0f); // top left

                m_geometry.MakeTriangle(index, index + 1, index + 2);
                m_geometry.MakeTriangle(index + 2, index + 3, index);
                index += 4;

                // Second Face
                m_geometry.AddVertex(x+1, y, z, 0.5f, 0.0f); // bottom left
                m_geometry.AddVertex(x+1, y, z+1, 1.0f, 0.0f); // bottom right
                m_geometry.AddVertex(x+1, y+1, z+1, 1.0f, 1.0f); // top right
                m_geometry.AddVertex(x+1, y+1, z, 0.5f, 1.0f); // top left

                m_geometry.MakeTriangle(index, index + 1, index + 2);
                m_geometry.MakeTriangle(index + 2, index + 3, index + 0);
                index += 4;


                // Third Face
                m_geometry.AddVertex(x+1, y, z+1, 0.5f, 0.0f); // bottom left
                m_geometry.AddVertex(x, y, z+1, 1.0f, 0.0f); // bottom right
                m_geometry.AddVertex(x, y+1, z+1, 1.0f, 1.0f); // top right
                m_geometry.AddVertex(x+1, y+1, z+1, 0.5f, 1.0f); // top left

                m_geometry.MakeTriangle(index, index + 1, index + 2);
                m_geometry.MakeTriangle(index + 2, index + 3, index + 0);
                index += 4;

                // Fourth Face
                m_geometry.AddVertex(x, y, z+1, 0.5f, 0.0f); // bottom left
                m_geometry.AddVertex(x, y, z, 1.0f, 0.0f); // bottom right
                m_geometry.AddVertex(x, y+1, z, 1.0f, 1.0f); // top right
                m_geometry.AddVertex(x, y+1, z+1, 0.5f, 1.0f); // top left

                m_geometry.MakeTriangle(index, index + 1, index + 2);
                m_geometry.MakeTriangle(index + 2, index + 3, index + 0);
                index += 4;

                // Top face
                m_geometry.AddVertex(x, y+1, z, 0.0f, 0.0f); // bottom left
                m_geometry.AddVertex(x+1, y+1, z, 0.5f, 0.0f); // bottom right
                m_geometry.AddVertex(x+1, y+1, z+1, 0.5f, 1.0f); // top right
                m_geometry.AddVertex(x, y+1, z+1, 0.0f, 1.0f); // top left

                m_geometry.MakeTriangle(index, index + 1, index + 2);
                m_geometry.MakeTriangle(index + 2, index + 3, index + 0);
                index += 4;
            }
        }
    }
    m_geometry.Gen();

    m_vertexBufferLayout.CreateNormalBufferLayout(m_geometry.GetBufferDataSize(),
                                        m_geometry.GetIndicesSize(),
                                        m_geometry.GetBufferDataPtr(),
                                        m_geometry.GetIndicesDataPtr());
}