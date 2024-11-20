#include <chrono>
#include <ctime>

struct Bullet {
    float x;
    float y;

    float dx;
    float dy;

    bool destroy = false;
};

struct Zombie {
    float x;
    float y;

    int w = 100;
    int h = 100;

    float dx = -200;

    int health = 2;

    bool destroy = false;
};

struct GameScene : Scene {
    sf::SoundBuffer buffer;
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

	float x = 100;
	float y = 0;

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

        if (!buffer.loadFromFile("res/Sounds/explosion.wav")) {
            return;
        }

        sound.setBuffer(buffer);

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

        float dt = std::chrono::duration_cast<std::chrono::microseconds>(current_time - last_time).count() / 1000000.0f;
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

        std::vector<int> destroy_bullets;
        std::vector<int> destroy_zombies;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && time_till_shoot <= 0.0f) {
            Bullet bullet;
            bullet.x = x;
            bullet.y = y;
            bullet.dx = 500; // bullet speed in pixles
            bullets.push_back(bullet);

            time_till_shoot = 0.2f; // time between shots
        }

        // update game objects here

        for (int i = 0; i < bullets.size(); i++) {
            bullets[i].x += bullets[i].dx * dt;

            if (bullets[i].x > 1600) {
                if (std::find(destroy_bullets.begin(), destroy_bullets.end(), i) == destroy_bullets.end()) destroy_bullets.push_back(i);
            }
        }

        for (int i = 0; i < zombies.size(); i++) {
            zombies[i].x += zombies[i].dx * dt;

            // destroy zombies here later
            if (zombies[i].x < -zombies[i].w) {
                // zombie is past

                if (std::find(destroy_zombies.begin(), destroy_zombies.end(), i) == destroy_zombies.end()) destroy_zombies.push_back(i);
            }

            // if zombie passes player, player base loses health
            // if zombie touches player, player loses a life
        }

        // bullets intersect with zombies
        for (int bi = 0; bi < bullets.size(); bi++) {
            Bullet& bullet = bullets[bi];

            for (int zi = 0; zi < zombies.size(); zi++) {
                Zombie& zombie = zombies[zi];

                if (Physics::AABB(bullet.x, bullet.y, 50, 50, zombie.x, zombie.y, zombie.w, zombie.h)) {
                    if(std::find(destroy_bullets.begin(), destroy_bullets.end(), bi) == destroy_bullets.end()) destroy_bullets.push_back(bi);

                    zombie.health--;

                    if (zombie.health <= 0) {
                        if (std::find(destroy_zombies.begin(), destroy_zombies.end(), zi) == destroy_zombies.end()) destroy_zombies.push_back(zi);
                    }
                }
            }
        }

        // destroy things here
        std::sort(destroy_bullets.begin(), destroy_bullets.end());
        std::sort(destroy_zombies.begin(), destroy_zombies.end());

        for (int i = 0; i < destroy_bullets.size(); i++) {
            bullets.erase(bullets.begin() + destroy_bullets[i] - i);

            sound.play();
        }

        for (int i = 0; i < destroy_zombies.size(); i++) {
            zombies.erase(zombies.begin() + destroy_zombies[i] - i);
        }

        // draw stuff here

        main_window->Draw(background);

        for (sf::Vector2f& pos : grass) {
            grass_piece.setPosition(pos);
            main_window->Draw(grass_piece);
        }

        player.setPosition(sf::Vector2f(100, y));
        main_window->Draw(player);

        for (Bullet& bullet : bullets) {
            bullet_sprite.setPosition(sf::Vector2f(bullet.x, bullet.y));
            main_window->Draw(bullet_sprite);
        }

        for (Zombie& zombie : zombies) {
            player.setPosition(sf::Vector2f(zombie.x, zombie.y));
            main_window->Draw(player);
        }
	}
};