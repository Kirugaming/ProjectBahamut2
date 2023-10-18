//
// Created by kirut on 10/16/2023.
//

#include "Engine.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"


Engine::Engine() {
    SDL_GetCurrentDisplayMode(0, &displayMode);
    if (initRendering(
            (displayMode.h-50) / 1.1,
            (displayMode.w) / 1.1) != 0) {
        std::cout << "ENGINE_ERROR::INIT_RENDERING" << std::endl;
    }

    // init engine ui
    initEngineUI();

    // init game
    game.camera = Camera(glm::vec3(0.0f, 1.0f, 2.0f));

    auto* model = new GameObject("Raphtalia", Model("raph/raph.obj"));

    game.models.push_back(model);
}

/*
 * Startup SDL rendering and OpenGL rendering
 */
int Engine::initRendering(int winHeight, int winWidth) {
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL FAILED TO INITIALIZE!\n " << SDL_GetError() << std::endl;
        return -1;
    }
    // Create Window
    window = SDL_CreateWindow("ProjectBahamut", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_MAXIMIZED);

    // opengl
    SDL_GL_LoadLibrary(nullptr);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 6 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    glContext = SDL_GL_CreateContext(window);
    // Init Glad
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress))) {
        std::cout << "Glad failed to Initialize!" << std::endl;
        return -1;
    }

    // OpenGL rendering settings
    glViewport(0, 0, winWidth, winHeight);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return 0;
}

void Engine::engineLoop() {
    while(!game.quit){
        // delta time
        auto now = std::chrono::steady_clock::now();
        game.deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - game.lastFrame).count() / 1000.0f;
        game.lastFrame = now;


        // Events
        SDL_PumpEvents();
        eventMonitor(); // query SDL events
        KeyboardInput();




        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(); // Show demo window! :)

        ImGui::Begin("Hello World!");
        ImGui::Text("Hello World!");
        ImGui::End();


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(.2f, .3f, .3f, 1.0f);

        for (GameObject* model : game.models) {
            model->draw(game.camera.getView());
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);
    }
}


void Engine::eventMonitor() {
    while( SDL_PollEvent( event ) ) {
        ImGui_ImplSDL2_ProcessEvent(event); // Forward your event to backend
        switch (event->type) {
            case SDL_QUIT:
                game.quit = true;
                break;
            case SDL_WINDOWEVENT:
                switch (event->window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        glViewport(0, 0, event->window.data1, event->window.data2);
                        break;
                }
                break;
        }
    }
}

Engine::~Engine() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    // cleanup
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow( window );
    SDL_Quit();
}

void Engine::KeyboardInput() { // possible to do this elsewhere but its here for now
    if (keys[SDL_SCANCODE_W]) {
        game.camera.movement(Camera::FORWARD, game.deltaTime);
    }
    if (keys[SDL_SCANCODE_S]) {
        game.camera.movement(Camera::BACKWARD, game.deltaTime);
    }
    if (keys[SDL_SCANCODE_A]) {
        game.camera.movement(Camera::LEFT, game.deltaTime);
    }
    if (keys[SDL_SCANCODE_D]) {
        game.camera.movement(Camera::RIGHT, game.deltaTime);
    }
    if (keys[SDL_SCANCODE_UP]) {
        game.camera.setPitch(1);
    }
    if (keys[SDL_SCANCODE_DOWN]) {
        game.camera.setPitch(-1);
    }
    if (keys[SDL_SCANCODE_LEFT]) {
        game.camera.setYaw(-1);
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        game.camera.setYaw(1);
    }
}

int Engine::initEngineUI() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init();

    return 0;
}
