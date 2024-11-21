struct MainMenu : Scene {
    sf::RectangleShape background;

    virtual void Init() {
        background.setSize(sf::Vector2f(1600, 900));
        background.setFillColor(sf::Color(75, 75, 75));
    }

    virtual void Start() {
        
    }

    virtual void Update() {
        // press space to play
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            Game::LoadScene(1);
        }

        // draw here

        main_window->Draw(background);

        UI::DrawText("Zombie Game", 800, 10, "Bokor", 150, sf::Color::Black, UI::Align::Center, UI::Align::Top);

        UI::DrawText("Press 'Space' To Play", 800, 425, "SUSE", 50, sf::Color::Black, UI::Align::Center, UI::Align::Middle);
    }
};