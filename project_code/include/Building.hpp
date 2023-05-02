#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "Object.hpp"
#include "BuildingMap.hpp"

#include <string>
#include <vector>

class Building : public Object {
public:
    // Creates a building object from a building map and given texture
    Building(BuildingMap& map);

    // Destructor
    ~Building();

    void Init();

private:
    int m_xSize;
    int m_zSize;
    int* m_building;
    std::vector<Texture> m_textures;
};
#endif