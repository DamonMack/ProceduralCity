#include "BuildingMap.hpp"
#include <iostream>
#include <time.h>
#include "SDLGraphicsProgram.hpp"

int main(int argc, char** argv){
    srand(time(NULL));

    // BuildingMap map = BuildingMap(20,20);
    // map.generateRandom(5, 2, 20, 5, 5);

    // for(int row = 0; row < 20; row++) {
    //     for (int col = 0; col < 20; col++) {
    //         std::cout << map.m_building[row * 20 + col] << "   ";
    //     }
    //     std::cout << std::endl;
    // }

    SDLGraphicsProgram mySDLGraphicsProgram(1280,720);
    mySDLGraphicsProgram.Loop();

    return 0;
}