struct LoseScreen : Scene {
	sf::RectangleShape background;

	virtual void Init() {
		background.setSize(sf::Vector2f(1600, 900));
		background.setFillColor(sf::Color(75, 75, 75));
	}

	virtual void Start() {

	}

	virtual void Update() {
		// R to restart
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			Game::LoadScene(1);
		}

		// M for main menu
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
			Game::LoadScene(0);
		}

		// Q to quit
		// R to restart
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			Game::Quit();
		}

		// draw here

		main_window->Draw(background);

		UI::DrawText("You Died :(", 800, 10, "Bokor", 150, sf::Color::Black, UI::Align::Center, UI::Align::Top);

		UI::DrawText("Press 'R' To Restart", 800, 325, "SUSE", 75, sf::Color::Black, UI::Align::Center, UI::Align::Top);
		UI::DrawText("Press 'M' For Menu", 800, 425, "SUSE", 75, sf::Color::Black, UI::Align::Center, UI::Align::Top);
		UI::DrawText("Press 'Q' To Quit", 800, 525, "SUSE", 75, sf::Color::Black, UI::Align::Center, UI::Align::Top);
	}
};