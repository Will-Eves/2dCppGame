#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "Window.h"

#include "Scenes/Scene.h"
#include "Scenes/Game.h"

class Game {
private:
    int scene_index;
    std::vector<Scene*> scenes;
    Scene* current_scene;

    Window window;
public:
    bool IsRunning() {
		return window.IsOpen();
	}

    void LoadScene(int index) {
        if (index < 0 || index >= scenes.size()) return;

        scene_index = index;

        current_scene = scenes[index];

        current_scene->Start();
    }

    void Start() {
        scene_index = 0;

        main_window = &window;

        // Init window
        window.Init(1600, 900, "Zombie Game");

        // Add all the scenes here
        scenes.push_back(new GameScene());

        // Initialize all scenes here
        for (Scene* scene : scenes) {
            scene->Init();
        }

        // Load the first scene
        LoadScene(0);
	}

    void Update() {
        window.PollEvents();

        window.Clear();

        // Update Scene Here
        current_scene->Update();

        window.Display();
	}
};