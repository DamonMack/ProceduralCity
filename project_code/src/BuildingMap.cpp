#include "BuildingMap.hpp"
#include <algorithm>
#include <iostream>

BuildingMap::BuildingMap() {
    m_xSize = 10;
    m_zSize = 10;

    m_building = new int[m_xSize * m_zSize];
    for(int i = 0; i < m_xSize * m_zSize; i++) {
        m_building[i] = 0;
    }
}

BuildingMap::BuildingMap(int x, int z) {
    m_xSize = x;
    m_zSize = z;

    m_building = new int[m_xSize * m_zSize];
    for(int i = 0; i < m_xSize * m_zSize; i++) {
        m_building[i] = 0;
    }
}

BuildingMap::~BuildingMap() {
    delete[] m_building;
}

void BuildingMap::addSegment(unsigned int x, unsigned int z, unsigned int xSize, unsigned int zSize, int height) {
    // Fails silently if the parameters are bad
    if(height < 0 || x + xSize > m_xSize || z + zSize > m_zSize) {
        return;
    }

    for (int row = z; row < z + zSize; row++) {
        for (int col = x; col < x + xSize; col++) {
            // Replaces the current value if the new one is higher
            m_building[row * m_xSize + col] = std::max(m_building[row * m_xSize + col], height);
        }
    }
}

void BuildingMap::generateRandom(int sections, int minY, int maxY, int minX, int minZ) {
    for(int i = 0; i < sections; i++) {
        // Randomly decide section parameters
        int height = minY + rand() % (maxY - minY);
        int x = rand() % (m_xSize - minX);
        int z = rand() % (m_zSize - minX);
        int xSize = minX + rand() % (m_xSize - x - minX);
        int zSize = minZ + rand() % (m_zSize - z - minZ);
        std::cout << "height: " << height << " x: " << x << " z: " << z << " xSize: " << xSize << " zSize: " << zSize << std::endl;

        // Add segment to map
        addSegment(x, z, xSize, zSize, height);
    }
}


int BuildingMap::getXSize() {
    return m_xSize;
}


int BuildingMap::getZSize() {
    return m_zSize;
}