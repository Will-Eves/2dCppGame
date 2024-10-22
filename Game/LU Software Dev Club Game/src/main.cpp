#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");

    sf::RectangleShape rect1 = sf::RectangleShape(sf::Vector2f(100, 100));

    sf::CircleShape circ1 = sf::CircleShape(50);

    circ1.setPosition(sf::Vector2f(200, 200));
    circ1.setFillColor(sf::Color(255, 0, 0));

    int x = 0;
    int y = 0;

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("res/Sounds/explosion.wav")) {
        return -1;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);

    sound.play();

    // load image

    sf::Texture texture;
    if (!texture.loadFromFile("res/Textures/mario.jpg")) {
        return -1;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(500, 300);
    // sprite.setScale(sf::Vector2f(1.0f / sprite.getScale().x * 100, 1.0f / sprite.getScale().y * 100));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // get input here

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            x -= 10;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            x += 10;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            y -= 10;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            y += 10;
        }

        window.clear();

        // draw stuff here

        window.draw(rect1);

        window.draw(circ1);

        window.draw(sprite);

        window.display();
    }

    return 0;
}