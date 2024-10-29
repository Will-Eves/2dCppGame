static class Window {
private:
	static sf::RenderWindow* window;
public:
	static void Init(int width=1600, int height=900, std::string name="Window") {
		window = new sf::RenderWindow(sf::VideoMode(width, height), name);
	}

	static void PollEvents() {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
		}
	}

	static void Clear() {
		window->clear();
	}

	static void Draw(sf::Drawable& draw) {
		window->draw(draw);
	}

	static void Display() {
		window->display();
	}

	static bool IsOpen() {
		return window->isOpen();
	}
};