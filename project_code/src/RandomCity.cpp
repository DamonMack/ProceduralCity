#include "RandomCity.hpp"
#include "BuildingMap.hpp"
#include "Object.hpp"

RandomCity::RandomCity(unsigned int ScreenW, unsigned int ScreenH,
                        int xBuildings, int zBuildings,
                        int xSize, int zSize, int maxHeight) {
    m_xBuildings = xBuildings;
    m_zBuildings = zBuildings;
    m_xSize = xSize;
    m_zSize = zSize;
    m_maxHeight = maxHeight;

    m_renderer = new Renderer(ScreenW, ScreenH);

    Init();
}

RandomCity::~RandomCity() {
    if(m_renderer!=nullptr){
        delete m_renderer;
    }
}

void RandomCity::Init() {
    // Generate the ground
    int buidlingSpacing =3;

    Object* ground = new Object;
    ground->MakeFloor(-1, m_xBuildings *(m_xSize + buidlingSpacing) + 2,
                     -1, m_zBuildings *(m_zSize + buidlingSpacing) + 2, "grass.ppm");
    SceneNode* groundNode = new SceneNode(ground);
    m_renderer->setRoot(groundNode);

    //Generate the buildings.
    for(int z = 0; z < m_zBuildings; z++) {
        // First building of row
        BuildingMap map = BuildingMap(m_xSize, m_zSize);
        map.generateRandom(5, 2, m_maxHeight, 3, 3);

        Building* building = new Building(map);
        building->LoadTexture("Window.ppm");
        SceneNode* BuildingNode = new SceneNode(building);

        groundNode->AddChild(BuildingNode);
        // Push it down the z axis
        BuildingNode->GetLocalTransform().LoadIdentity();
        BuildingNode->GetLocalTransform().Translate(0.0f, 0.0f, z * (m_zSize + buidlingSpacing));

        for(int x = 1; x < m_xBuildings; x++) {
            BuildingMap mapChild = BuildingMap(m_xSize, m_zSize);
            mapChild.generateRandom(5, 2, m_maxHeight, 3, 3);

            Building* buildingChild = new Building(mapChild);
            buildingChild->LoadTexture("Window.ppm");
            SceneNode* BuildingNodeChild = new SceneNode(buildingChild);

            BuildingNode->AddChild(BuildingNodeChild);
            // Push it down the x axis
            BuildingNodeChild->GetLocalTransform().LoadIdentity();
            BuildingNodeChild->GetLocalTransform().Translate(x * (m_xSize + buidlingSpacing), 0.0f, 0.0f);
        }
    }
}

void RandomCity::Update() {
    m_renderer->Update();
}

void RandomCity::Render() {
    m_renderer->Render();
}

Camera*& RandomCity::GetCamera(unsigned int index) {
    m_renderer->GetCamera(index);
}