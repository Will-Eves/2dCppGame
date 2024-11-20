#include <chrono>
#include <ctime>

struct Bullet {
    float x;
    float y;

    float dx;
    float dy;
};

struct Zombie {
    float x;
    float y;

    int w = 100;
    int h = 100;

    float dx = -200;

    int health = 2;
};

struct GameScene : Scene {
	sf::Sound sound;

    sf::RectangleShape background;
    sf::RectangleShape grass_piece;

    std::vector<sf::Vector2f> grass;

	sf::Texture player_texture;
	sf::Sprite player;

    sf::Texture bullet_texture;
    sf::Sprite bullet_sprite;

    std::vector<Bullet> bullets;

    std::vector<Zombie> zombies;

    float time_till_spawn = 1.0f;

	int x = 100;
	int y = 0;

    int health = 10;

    float time_till_shoot = 0.2f;

    // Time stuff
    std::chrono::steady_clock::time_point last_time;

	virtual void Init() {
        srand(time(0));

        background.setSize(sf::Vector2f(1600, 900));
        background.setFillColor(sf::Color(100, 200, 100));

        grass_piece.setSize(sf::Vector2f(10, 20));
        grass_piece.setFillColor(sf::Color(50, 165, 75));

        for (int i = 0; i < 100; i++) {
            grass.push_back(sf::Vector2f(rand() % 1590, rand() & 880));
        }

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
        time_till_spawn -= dt;

        // get input here

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            y -= 500 * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            y += 500 * dt;
        }

        if (y < 0) y = 0;
        else if (y > 900 - 100) y = 900 - 100;

        if (time_till_spawn <= 0.0f) {
            Zombie zombie;

            zombie.x = 1600;
            zombie.y = rand() % 800;

            zombies.push_back(zombie);

            time_till_spawn = 1.0f;
        }

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

        for (int i = 0; i < zombies.size(); i++) {
            zombies[i].x += zombies[i].dx * dt;

            // destroy zombies here later
        }

        // draw stuff here

        main_window->Draw(background);

        for (sf::Vector2f pos : grass) {
            grass_piece.setPosition(pos);
            main_window->Draw(grass_piece);
        }

        player.setPosition(sf::Vector2f(100, y));
        main_window->Draw(player);

        for (Bullet bullet : bullets) {
            bullet_sprite.setPosition(sf::Vector2f(bullet.x, bullet.y));
            main_window->Draw(bullet_sprite);
        }

        for (Zombie zombie : zombies) {
            player.setPosition(sf::Vector2f(zombie.x, zombie.y));
            main_window->Draw(player);
        }
	}
};