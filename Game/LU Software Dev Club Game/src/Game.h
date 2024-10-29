#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "Window.h"

#include "Scenes/Scene.h"
#include "Scenes/Game.h"

static class Game {
private:
    static sf::RectangleShape rect1;
    static sf::CircleShape circ1;
    static sf::Sound sound;

    static sf::Texture texture;
    static sf::Sprite sprite;

    static int x;
    static int y;

    static int scene_index;
    static std::vector<Scene*> scenes;
    static Scene* current_scene;
public:
    static bool IsRunning() {
		return Window::IsOpen();
	}

    static void LoadScene(int index) {
        if (index < 0 || index >= scenes.size()) return;

        scene_index = index;

        current_scene = scenes[index];
    }

    static void Start() {
		// lol

        x = 100;
        y = 0;

        // Init window
        Window::Init(1600, 900, "Zombie Game");

        // Add all the scenes here
        scenes.push_back(new GameScene());

        // Load the first scene
        LoadScene(0);

        rect1 = sf::RectangleShape(sf::Vector2f(100, 100));

        circ1 = sf::CircleShape(50);

        circ1.setPosition(sf::Vector2f(200, 200));
        circ1.setFillColor(sf::Color(255, 0, 0));

        int x = 0;
        int y = 0;

        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("res/Sounds/explosion.wav")) {
            return;
        }

        sound.setBuffer(buffer);

        sound.play();

        // load image

        if (!texture.loadFromFile("res/Textures/mario.jpg")) {
            return;
        }

        sprite.setTexture(texture);
        sprite.setPosition(500, 300);
        // sprite.setScale(sf::Vector2f(1.0f / sprite.getScale().x * 100, 1.0f / sprite.getScale().y * 100));
	}

    static void Update() {
        Window::PollEvents();

        // get input here

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            y -= 10;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            y += 10;
        }
        if (y < 0) y = 0;
        else if (y > 900 - 100) y = 900 - 100;

        Window::Clear();

        // draw stuff here

        rect1.setPosition(sf::Vector2f(100, y));
        Window::Draw(rect1);

        Window::Draw(circ1);

        Window::Draw(sprite);

        Window::Display();
	}
};