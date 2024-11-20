#include <chrono>

struct Bullet {
    float x;
    float y;

    float dx;
    float dy;
};

struct GameScene : Scene {
	sf::Sound sound;

	sf::Texture player_texture;
	sf::Sprite player;

    sf::Texture bullet_texture;
    sf::Sprite bullet_sprite;

    std::vector<Bullet> bullets;

	int x = 100;
	int y = 0;

    float time_till_shoot = 0.2f;

    // Time stuff
    std::chrono::steady_clock::time_point last_time;

	virtual void Init() {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("res/Sounds/explosion.wav")) {
            return;
        }

        sound.setBuffer(buffer);

        sound.play();

        // load image

        if (!player_texture.loadFromFile("res/Textures/mario.jpg")) {
            return;
        }

        player.setTexture(player_texture);
        player.setPosition(0, 0);
        player.setScale(sf::Vector2f(1.0f / player_texture.getSize().x * 100, 1.0f / player_texture.getSize().y * 100));

        if (!bullet_texture.loadFromFile("res/Textures/fireball.png")) {
            return;
        }

        bullet_sprite.setTexture(bullet_texture);
        bullet_sprite.setScale(sf::Vector2f(1.0f / bullet_texture.getSize().x * 50, 1.0f / bullet_texture.getSize().y * 50));
	}

	virtual void Start() {
		// lol!

        x = 100;
        y = 0;

        last_time = std::chrono::high_resolution_clock::now();
	}

	virtual void Update() {
        auto current_time = std::chrono::high_resolution_clock::now();

        float dt = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time).count() / 1000.0f;
        last_time = current_time;

        time_till_shoot -= dt;

        // get input here

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            y -= 500 * dt;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            y += 500 * dt;
        }
        if (y < 0) y = 0;
        else if (y > 900 - 100) y = 900 - 100;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && time_till_shoot <= 0.0f) {
            Bullet bullet;
            bullet.x = x;
            bullet.y = y;
            bullet.dx = 500; // bullet speed in pixles
            bullets.push_back(bullet);

            time_till_shoot = 0.2f; // time between shots
        }

        // update game objects here

        int destroy_count = 0;
        for (int i = 0; i < bullets.size(); i++) {
            bullets[i].x += bullets[i].dx * dt;

            if (bullets[i].x > 1600) {
                destroy_count++;
            }
        }

        for (int i = 0; i < destroy_count; i++) {
            bullets.erase(bullets.begin());
        }

        // draw stuff here

        player.setPosition(sf::Vector2f(100, y));
        main_window->Draw(player);

        for (Bullet bullet : bullets) {
            bullet_sprite.setPosition(sf::Vector2f(bullet.x, bullet.y));
            main_window->Draw(bullet_sprite);
        }
	}
};