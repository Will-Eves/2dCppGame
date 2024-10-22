#include <SFML/Graphics.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");

    sf::RectangleShape rect1 = sf::RectangleShape(sf::Vector2f(100, 100));

    sf::CircleShape circ1 = sf::CircleShape(50);

    circ1.setPosition(sf::Vector2f(200, 200));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // draw stuff here

        window.draw(rect1);

        window.draw(circ1);

        window.display();
    }

    return 0;
}