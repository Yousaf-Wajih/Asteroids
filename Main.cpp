#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Physics.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Asteroids Tutorial",
		sf::Style::Close | sf::Style::Titlebar);
	sf::Clock clock;

	sf::VertexArray poly1(sf::LineStrip);
	sf::VertexArray poly2(sf::LineStrip);

	enum { POLY_1, POLY_2, TEST } state = POLY_1;

	// Game::begin();

	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();
		sf::Event e{};
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			} else if (e.type == sf::Event::MouseButtonPressed &&
				e.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f pos = (sf::Vector2f)sf::Mouse::getPosition(window);
				if (state == POLY_1) {
					poly1.append(sf::Vertex(pos, sf::Color::White));
				} else if (state == POLY_2) {
					poly2.append(sf::Vertex(pos, sf::Color::White));
				}
			} else if (e.type == sf::Event::KeyPressed &&
				e.key.code == sf::Keyboard::Space) {
				if (state == POLY_1 && poly1.getVertexCount() > 0) {
					state = POLY_2;
					poly1.append(poly1[0]);
				} else if (state == POLY_2 && poly2.getVertexCount() > 0) {
					state = TEST;
					poly2.append(poly2[0]);

					if (physics::intersects(poly1, poly2)) {
						printf("intersect!\n");
					} else {
						printf("do not intersect!\n");
					}
				} else if (state == TEST) {
					state = POLY_1;
					poly1.clear();
					poly2.clear();
				}
			}
		}

		// Game::update(window, deltaTime);

		window.clear();

		window.draw(poly1);
		window.draw(poly2);

		window.display();
	}
}
