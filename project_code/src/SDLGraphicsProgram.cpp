#include "SDLGraphicsProgram.hpp"
#include "Camera.hpp"
#include "Building.hpp"
#include "BuildingMap.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h){
	// Initialization flag
	bool success = true;
	// String to hold any errors that occur.
	std::stringstream errorStream;
	// The window we'll be rendering to
	m_window = NULL;

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO)< 0){
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else{
		//Use OpenGL 3.3 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		// We want to request a double buffer for smooth updating.
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		//Create window
		m_window = SDL_CreateWindow( "Lab",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                w,
                                h,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

		// Check if Window did not create.
		if( m_window == NULL ){
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//Create an OpenGL Graphics Context
		m_openGLContext = SDL_GL_CreateContext( m_window );
		if( m_openGLContext == NULL){
			errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		// Initialize GLAD Library
		if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
			errorStream << "Failed to iniitalize GLAD\n";
			success = false;
		}

		//Initialize OpenGL
		if(!InitGL()){
			errorStream << "Unable to initialize OpenGL!\n";
			success = false;
		}
  	}

    // If initialization did not work, then print out a list of errors in the constructor.
    if(!success){
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors=errorStream.str();
        SDL_Log("%s\n",errors.c_str());
    }else{
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }

	// SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN); // Uncomment to enable extra debug support!
	GetOpenGLVersionInfo();


    // Setup our Renderer
    m_random = new RandomCity(w,h,10,10,10,10,20);
    //m_random = new RandomCity(w,h,1,1,10,10,10);
}


// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    if(m_random!=nullptr){
        delete m_random;
    }


    //Destroy window
	SDL_DestroyWindow( m_window );
	// Point m_window to NULL to ensure it points to nothing.
	m_window = nullptr;
	//Quit SDL subsystems
	SDL_Quit();
}


// Initialize OpenGL
// Setup any of our shaders here.
bool SDLGraphicsProgram::InitGL(){
	//Success flag
	bool success = true;

	return success;
}







// ====================== Create the planets =============

//Loops forever!
void SDLGraphicsProgram::Loop(){
    
    //BuildingMap map = BuildingMap(10,10);
    // map.addSegment(0,0,3,3,6);
    // map.addSegment(2,2,2,2,3);
    // map.addSegment(0,0,5,5,1);
    //map.generateRandom(5, 2, 10, 3, 3);

    
    // ================== Initialize the planets ===============
    static float rotate = 0.0f;
    static float rotatePlanet = 0.0f;

    //Building* BuildingObject;
    //SceneNode* BuildingNode;
    
    //Object* temp = new Object;
	//temp->MakeTexturedQuad("brick.ppm");
    //SceneNode* tempQuad = new SceneNode(temp);
    // Create new geometry for Earth's Moon
    //BuildingObject = new Building(map);
    //BuildingObject->LoadTexture("brick.ppm");

    //BuildingNode = new SceneNode(BuildingObject);

    // Render our scene starting from the sun.
    //m_renderer->setRoot(BuildingNode);

    // Set a default position for our camera
    m_random->GetCamera(0)->SetCameraEyePosition(0.0f,5.0f,20.0f);

    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();

    // Set the camera speed for how fast we move.
    float cameraSpeed = 0.5f;
    
    // While application is running
    while(!quit){

        //Handle events on queue
        while(SDL_PollEvent( &e ) != 0){
            // User posts an event to quit
            // An example is hitting the "x" in the corner of the window.
            if(e.type == SDL_QUIT){
                quit = true;
            }
            // Handle keyboard input for the camera class
            if(e.type==SDL_MOUSEMOTION){
                // Handle mouse movements
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
                m_random->GetCamera(0)->MouseLook(mouseX, mouseY);
            }
            switch(e.type){
                // Handle keyboard presses
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case SDLK_LEFT:
                            m_random->GetCamera(0)->MoveLeft(cameraSpeed);
                            break;
                        case SDLK_RIGHT:
                            m_random->GetCamera(0)->MoveRight(cameraSpeed);
                            break;
                        case SDLK_UP:
                            m_random->GetCamera(0)->MoveForward(cameraSpeed);
                            break;
                        case SDLK_DOWN:
                            m_random->GetCamera(0)->MoveBackward(cameraSpeed);
                            break;
                        case SDLK_RSHIFT:
                            m_random->GetCamera(0)->MoveUp(cameraSpeed);
                            break;
                        case SDLK_RCTRL:
                            m_random->GetCamera(0)->MoveDown(cameraSpeed);
                            break;
                    }
                break;
            }
        } // End SDL_PollEvent loop.
        // ================== Use the planets ===============
        // TODO:
        //      After the planets have been created, and the hierarchy
        //      has been made, you can transform them.
        //      Note, you'll need to setup the scene graph world/local
        //      transformation correctly first before the planets are shown.
        //      
        //      The 'Sun' for example will be the only object shown initially
        //      since the rest of the planets are children (or grandchildren)
        //      of the Sun.
        rotate += 0.1;
        rotatePlanet += 0.13;
        if (rotatePlanet > 360) rotatePlanet = 0;
        if (rotate > 360) rotate = 0;
        // BuildingNode->GetLocalTransform().LoadIdentity();
        // BuildingNode->GetLocalTransform().Translate(0.0f,0.0f,2.0f);
        // BuildingNode->GetLocalTransform().Scale(1.0f,1.0f,1.0f);

        // tempQuad->GetLocalTransform().LoadIdentity();
        // tempQuad->GetLocalTransform().Translate(0.0f,0.0f,-8.0f);
        // ... transform the Sun

        // Moon->GetLocalTransform().LoadIdentity();
        // Moon->GetLocalTransform().Translate(0, 0, 3);
        // Moon->GetLocalTransform().Scale(.5, .5, .5);

        // Moon2->GetLocalTransform().LoadIdentity();
        // Moon2->GetLocalTransform().Translate(2, 0, 0);
        // Moon2->GetLocalTransform().Scale(.5, .5, .5);

        // Moon3->GetLocalTransform().LoadIdentity();
        // Moon3->GetLocalTransform().Translate(0, 0, 3);
        // Moon3->GetLocalTransform().Scale(.5, .5, .5);

        // Moon4->GetLocalTransform().LoadIdentity();
        // Moon4->GetLocalTransform().Translate(2, 0, 0);
        // Moon4->GetLocalTransform().Scale(.5, .5, .5);

        // Moon5->GetLocalTransform().LoadIdentity();
        // Moon5->GetLocalTransform().Translate(0, 0, 3);
        // Moon5->GetLocalTransform().Scale(.5, .5, .5);

        // Moon6->GetLocalTransform().LoadIdentity();
        // Moon6->GetLocalTransform().Translate(2, 0, 0);
        // Moon6->GetLocalTransform().Scale(.5, .5, .5);

        // // ... transform the Moon

        // Earth->GetLocalTransform().LoadIdentity();
        // Earth->GetLocalTransform().Translate(9.0, 0, 0);
        // Earth->GetLocalTransform().Rotate(rotatePlanet, 0, 1, 0);

        // Earth2->GetLocalTransform().LoadIdentity();
        // Earth2->GetLocalTransform().Translate(-5.0, 0, 2.0);
        // Earth2->GetLocalTransform().Rotate(rotatePlanet, 0, 1, 0);

        // Earth3->GetLocalTransform().LoadIdentity();
        // Earth3->GetLocalTransform().Translate(0, 0, -5.0);
        // Earth3->GetLocalTransform().Rotate(rotatePlanet, 0, 1, 0);
        // ... transform the Earth        

        // Update our scene through our renderer
        m_random->Update();
        // Render our scene using our selected renderer
        m_random->Render();
        // Delay to slow things down just a bit!
        SDL_Delay(25);  // TODO: You can change this or implement a frame
                        // independent movement method if you like.
      	//Update screen of our specified window
      	SDL_GL_SwapWindow(GetSDLWindow());
	}
    //Disable text input
    SDL_StopTextInput();
}


// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::GetSDLWindow(){
  return m_window;
}

// Helper Function to get OpenGL Version Information
void SDLGraphicsProgram::GetOpenGLVersionInfo(){
	SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
	SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
	SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
	SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
	SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}
