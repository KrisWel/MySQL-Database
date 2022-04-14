#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.cpp"
#include "SQLConnector.cpp"


class LoginPanel {
private:

	sf::Font font;
	sf::RectangleShape login, regist;
	sf::RectangleShape lname, lpassword, rname, rpassword;
	std::vector<sf::Text> texts;
	sf::RenderWindow* window;
	SQLConnector* connection;
	Button lButton, rButton;

	bool lName, lPass, rName, rPass;
	bool changeGUI, changeAdmin;
	std::string slName, slPass, srName, srPass;

public:

	LoginPanel(sf::RenderWindow* window, SQLConnector* connection) : lButton("Login", window, sf::Vector2f(100.f, 600.f), 40.f), rButton("Register", window, sf::Vector2f(600.f, 600.f), 40.f) {
		if (!font.loadFromFile("external/arial.ttf"))	std::cout << "Font failed" << std::endl;

		login.setSize(sf::Vector2f(500.f, 1000.f));
		login.setPosition(sf::Vector2f(0.f, 0.f));
		login.setFillColor(sf::Color(200, 200, 200));
		regist.setSize(sf::Vector2f(500.f, 1000.f));
		regist.setPosition(sf::Vector2f(500.f, 0.f));
		regist.setFillColor(sf::Color(100, 100, 160));

		lname.setSize(sf::Vector2f(200.f, 50.f));
		lpassword.setSize(sf::Vector2f(200.f, 50.f));
		lname.setPosition(sf::Vector2f(150.f, 150.f));
		lpassword.setPosition(sf::Vector2f(150.f, 250.f));

		rname.setSize(sf::Vector2f(200.f, 50.f));
		rpassword.setSize(sf::Vector2f(200.f, 50.f));
		rname.setPosition(sf::Vector2f(650.f, 150.f));
		rpassword.setPosition(sf::Vector2f(650.f, 250.f));

		texts.push_back(sf::Text("Login", font, 50));
		texts[0].setPosition(sf::Vector2f(150.f, 50.f));
		texts.push_back(sf::Text("Register", font, 50));
		texts[1].setPosition(sf::Vector2f(650.f, 50.f));
		texts.push_back(sf::Text("", font, 20));
		texts[2].setPosition(sf::Vector2f(150.f, 160.f));
		texts.push_back(sf::Text("", font, 20));
		texts[3].setPosition(sf::Vector2f(150.f, 260.f));
		texts.push_back(sf::Text("", font, 20));
		texts[4].setPosition(sf::Vector2f(650.f, 160.f));
		texts.push_back(sf::Text("", font, 20));
		texts[5].setPosition(sf::Vector2f(650.f, 260.f));
		for (auto& text : texts) {
			text.setFillColor(sf::Color::Red);
		}


		lName = false;
		rName = false;
		lPass = false;
		rPass = false;
		slName = "";
		srName = "";
		slPass = "";
		srPass = "";

		changeGUI = false;
		changeAdmin = false;

		this->window = window;
		this->connection = connection;
	}

	void update() {
		if (lname.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window))
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			lName = true;
			rName = false;
			lPass = false;
			rPass = false;
		}
		if (lpassword.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window))
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			lName = false;
			rName = false;
			lPass = true;
			rPass = false;
		}
		if (rname.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window))
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			lName = false;
			rName = true;
			lPass = false;
			rPass = false;
		}
		if (rpassword.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(*window))
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			lName = false;
			rName = false;
			lPass = false;
			rPass = true;
		}

		if (lButton.ifPressed()) {
			if (connection->login(slName, slPass)) {
				changeGUI = true;
			}
			else {
				if (slName == "Admin" && slPass == "Admin") {
					changeAdmin = true;
					changeGUI = true;
				}
				slName = "";
				slPass = "";
				texts[2].setString(slName);
				texts[3].setString(slPass);
			}
			lButton.ofPressed();
		}
		if (rButton.ifPressed()) {
			if (srName != "Admin") {
				if (connection->registration(srName, srPass)) {
					srName = "";
					srPass = "";
					texts[4].setString("");
					texts[5].setString("");
				}
			}
			rButton.ofPressed();
		}

		window->draw(login);
		window->draw(regist);
		window->draw(lname);
		window->draw(lpassword);
		window->draw(rname);
		window->draw(rpassword);

		for (auto& text : texts) {
			window->draw(text);
		}

		lButton.update();
		rButton.update();
	}
	
	void setTexts(char t, int box) {
		if (box == 0) {
			if (t == '-' && !slName.empty()) {
				slName.pop_back();
				texts[2].setString(slName);
			}
			else {
				slName += t;
				texts[2].setString(slName);
			}
		}
		else if (box == 1) {
			if (t == '-' && !slPass.empty()) {
				slPass.pop_back();
				std::string stars = "";
				for (int i = 0; i < slPass.size(); i++) stars += '*';
				texts[3].setString(stars);
			}
			else {
				slPass += t;
				std::string stars = "";
				for (int i = 0; i < slPass.size(); i++) stars += '*';
				texts[3].setString(stars);
			}	
		}
		else if (box == 2) {
			if (t == '-' && !srName.empty()) {
				srName.pop_back();
				texts[4].setString(srName);
			}
			else {
				srName += t;
				texts[4].setString(srName);
			}
		}
		else if (box == 3) {
			if (t == '-' && !srPass.empty()) {
				srPass.pop_back();
				std::string stars = "";
				for (int i = 0; i < srPass.size(); i++) stars += '*';
				texts[5].setString(stars);
			}
			else {
				srPass += t;
				std::string stars = "";
				for (int i = 0; i < srPass.size(); i++) stars += '*';
				texts[5].setString(stars);
			}
		}
	}

	bool ifName() { return lName; }
	bool ifrName() { return rName; }
	bool ifPass() { return lPass; }
	bool ifrPass() { return rPass; }
	bool ifChangeGUI() { return changeGUI; }
	bool ifChangeAdmin() { return changeAdmin; }

	std::string getName() { return slName; }

};