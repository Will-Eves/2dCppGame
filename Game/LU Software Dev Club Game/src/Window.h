class Window {
public:
	sf::RenderWindow* window;

	void Init(int width=1600, int height=900, std::string name="Window") {
		window = new sf::RenderWindow(sf::VideoMode(width, height), name);
	}

	void PollEvents() {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
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