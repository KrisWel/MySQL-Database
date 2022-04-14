#pragma once
#define NOMINMAX
#include "SQLConnector.cpp"
#include "LoginPanel.cpp"
#include "UserPanel.cpp"
#include "DiagramPanel.cpp"
#include "adminPanel.cpp"


int main() {

	SQLConnector connection;
	connection.Connect();

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
	LoginPanel lPanel(&window, &connection);
	UserPanel uPanel(&window, &connection);
	DiagramPanel dPanel(&window, &connection, &uPanel);
	AdminPanel aPanel(&window, &connection);

	sf::RectangleShape shape(sf::Vector2f(100.f, 100.f));


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::TextEntered) {
				if (lPanel.ifName()) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
						lPanel.setTexts('-', 0);
					else
						lPanel.setTexts((char)event.text.unicode, 0);
				}
				if (lPanel.ifPass()) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
						lPanel.setTexts('-', 1);
					else
						lPanel.setTexts((char)event.text.unicode, 1);
				}
				if (lPanel.ifrName()) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
						lPanel.setTexts('-', 2);
					else
						lPanel.setTexts((char)event.text.unicode, 2);
				}
				if (lPanel.ifrPass()) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
						lPanel.setTexts('-', 3);
					else
						lPanel.setTexts((char)event.text.unicode, 3);
				}

				if (uPanel.iflSearch()) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
						uPanel.setTexts('-', 0);
					else
						uPanel.setTexts((char)event.text.unicode, 0);
				}
				if (uPanel.ifrSearch()) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
						uPanel.setTexts('-', 1);
					else
						uPanel.setTexts((char)event.text.unicode, 1);
				}

				int nr = aPanel.whichWrite();
				if (nr != 100) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
						aPanel.setTexts('-', nr);
					else
						aPanel.setTexts((char)event.text.unicode, nr);
				}
			}
		}

		window.clear();
		
		if (!lPanel.ifChangeGUI()) lPanel.update();
		else if (lPanel.ifChangeAdmin()) aPanel.update();
		else if (!uPanel.ifChangeGUI()) {
			if (!uPanel.ifGetUserName()) uPanel.setUserName(lPanel.getName());
			uPanel.update();
		}
		else {
			dPanel.update();
			if (dPanel.getBack()) {
				uPanel.setGUI(false);
				dPanel.setBack(false);
			}
		}
		

		//window.draw(shape);

		window.display();
	}

	return 0;
}