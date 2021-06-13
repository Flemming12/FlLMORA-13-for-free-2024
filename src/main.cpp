#include <iostream>

#include "LDtkLoader/World.hpp"
#include "TileMap.hpp"

int main() {
    ldtk::World world;
    try {
        world.loadFromFile("assets/maps/world1.ldtk");
        std::cout << "LDtk World \"" << world.getFilePath() << "\" was loaded successfully." << std::endl;
    }
    catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    TileMap::path = world.getFilePath().directory();
    TileMap tilemap(world.getLevel("Level_0"));

    // create the window and start the game loop
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 450), "LDtkLoader - SFML");
    window.setFramerateLimit(60);

    sf::View view({0, 0, 400, 225});

    sf::Event event{};
    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            view.move(0, -1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            view.move(0, 1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            view.move(-1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            view.move(1, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
            view.zoom(0.95f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
            view.zoom(1.05f);

        window.clear();

        window.setView(view);
        window.draw(tilemap.getLayer("Ground"));
        window.draw(tilemap.getLayer("Trees"));
        window.draw(tilemap.getLayer("Trees_top"));

        window.setView(window.getDefaultView());
        window.display();
    }

    return 0;
}
