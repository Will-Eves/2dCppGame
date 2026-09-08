class Window {
public:
	sf::RenderWindow* window;

	void Init(int width=1600, int height=900, std::string name="Window") {
		window = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(width, height)), name);
	}

	void PollEvents() {
		while (const std::optional event = window->pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window->close();
			}
		}
	}

	void Clear() {
		window->clear();
	}

	void Draw(sf::Drawable& draw) {
		window->draw(draw);
	}

	void Display() {
		window->display();
	}

	bool IsOpen() {
		return window->isOpen();
	}
};

Window* main_window;