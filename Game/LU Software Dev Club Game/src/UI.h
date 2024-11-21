namespace UI{
	std::map<std::string, sf::Font> fonts;

	sf::Text text;

	namespace Align{
		float Left = 0;
		float Center = -0.5f;
		float Right = -1.0f;

		float Top = 0;
		float Middle = 0.5f;
		float Bottom = 1.0f;
	}

	bool Init() {
		// load Bokor font
		if (!fonts["Bokor"].loadFromFile("res/Fonts/Bokor.ttf")) {
			std::cout << "RES ISSUE : Couldn't Load Font 'Bokor'" << std::endl;
			return false;
		}

		// load Bokor font
		if (!fonts["SUSE"].loadFromFile("res/Fonts/SUSE.ttf")) {
			std::cout << "RES ISSUE : Couldn't Load Font 'SUSE'" << std::endl;
			return false;
		}

		return true;
	}

	void DrawText(std::string txt, int x, int y, std::string font="SUSE", int font_size=24, sf::Color font_color=sf::Color::Black, float align_x=Align::Left, float align_y=Align::Top) {
		text.setFont(fonts[font]);
		text.setString(txt);
		text.setCharacterSize(font_size);
		text.setFillColor(font_color);

		sf::FloatRect bounds = text.getLocalBounds();

		text.setPosition(x + bounds.width * align_x, y + bounds.height * align_y);

		main_window->Draw(text);
	}
}