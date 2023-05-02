#ifndef RANDOMCITY_HPP
#define RANDOMCITY_HPP

#include "Camera.hpp"
#include "Renderer.hpp"
#include "Building.hpp"

// Represents a randomly generated city
class RandomCity {
public:
    // Generates a random city with the given dimensions
    RandomCity(unsigned int ScreenW, unsigned int ScreenH,
                        int xBuildings, int zBuildings,
                        int xSize, int zSize, int maxHeight);

    // Destructor
    ~RandomCity();

    // Generates the city.
    void Init();

    // Update the Scene
    void Update();

    // Render the scene
    void Render();

    // Returns the camera at the given index
    Camera*& GetCamera(unsigned int index);

private:
    int m_xBuildings;
    int m_zBuildings;

    int m_xSize;
    int m_zSize;
    int m_maxHeight;

    Renderer* m_renderer;

};

#endif