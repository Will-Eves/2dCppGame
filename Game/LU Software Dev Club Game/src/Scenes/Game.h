struct GameScene : Scene {
	sf::RectangleShape rect1;
	sf::CircleShape circ1;
	sf::Sound sound;

	sf::Texture texture;
	sf::Sprite sprite;

	int x = 100;
	int y = 0;

	virtual void Init() {
        rect1 = sf::RectangleShape(sf::Vector2f(100, 100));

        circ1 = sf::CircleShape(50);

        circ1.setPosition(sf::Vector2f(200, 200));
        circ1.setFillColor(sf::Color(255, 0, 0));

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

	virtual void Start() {
		// lol!

        x = 100;
        y = 0;
	}

	virtual void Update() {
        // get input here

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            y -= 10;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            y += 10;
        }
        if (y < 0) y = 0;
        else if (y > 900 - 100) y = 900 - 100;

        // draw stuff here

        rect1.setPosition(sf::Vector2f(100, y));
        main_window->Draw(rect1);

        main_window->Draw(circ1);

        main_window->Draw(sprite);
	}
};