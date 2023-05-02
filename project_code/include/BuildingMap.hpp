#ifndef BUILDINGMAP_HPP
#define BUILDINGMAP_HPP

// Represents a building composed of cubes as a 2D array of height values.
class BuildingMap {
public:
    // Creates a default building map
    BuildingMap();

    // Creates a building map with the given x and z lengths
    BuildingMap(int x, int z);

    // Destructor
    ~BuildingMap();

    // Fills in the building map. Requires top corner of new section, length of each side, and the height of the section
    void addSegment(unsigned int x, unsigned int z, unsigned int xSize, unsigned int zSize, int height);

    // Creates a random building with a specified number of sections, as well as minimum and maximum heights. Does not prevent a section from being completely overwritten
    void generateRandom(int sections, int minY, int maxY, int minX, int minZ);

    // Returns the size of the map's x dimension.
    int getXSize();

    // Returns the size of the map's z dimension.
    int getZSize();

    int* m_building;
private:
    int m_xSize;
    int m_zSize;
    

};

#endif