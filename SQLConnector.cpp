#pragma once
#include <mysql.h>
#include <iostream>
#include <string>
#include <vector>

class SQLConnector {
private:

	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	int qstate;

public:

	SQLConnector() {
		qstate = 0;
		conn = mysql_init(0);
	}

	void Connect() {
		conn = mysql_real_connect(conn, "localhost", "root", "1234", "Project", 3306, NULL, 0);
		if (conn) std::cout <<"Successful connection to database!" << std::endl;
		else std::cout << "Failed connection to database!" << std::endl;
	}

	bool login(std::string name, std::string password) {
		std::string query = "SELECT NAZWA, HASLO FROM GRACZE;";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
				if ((std::string)row[0] == name && (std::string)row[1] == password) return true;

			return false;
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
			return false;
		}
	}

	bool registration(std::string name, std::string password) {
		if (!name.empty() || !password.empty()) {

			std::string query3 = "INSERT INTO Gracze (ID_gracza, Nazwa, Haslo, Data_utworzenia_konta, Budzet) VALUES(NULL, '" + name + "', '" + password + "', (SELECT NOW() FROM DUAL), 60); ";
			const char* q3 = query3.c_str();
			qstate = mysql_query(conn, q3);
			if (!qstate) {
				return true;
			}
			else {
				std::cout << "Query failed: " << mysql_error(conn) << std::endl;
				return false;
			}
		}
		else return false;
	}


	std::vector<std::string> userGames(std::string name) {
		std::vector<std::string> games;
		std::string all = "";
		std::string query = "SELECT ID_gry FROM Posiadane_gry WHERE ID_Gracza = (SELECT ID_Gracza FROM Gracze WHERE Nazwa = '"+name+"');";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) {
				all += (std::string)row[0]+',';
			}
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}
		if (!all.empty()) {
			all.pop_back();

			std::string query1 = "SELECT Nazwa FROM Gry WHERE ID_Gry IN(" + all + ");";
			const char* q1 = query1.c_str();
			qstate = mysql_query(conn, q1);
			if (!qstate) {
				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res)) {
					games.push_back(row[0]);
				}
			}
			else {
				std::cout << "Query failed: " << mysql_error(conn) << std::endl;
			}
		}

		return games;
	}
	float userBudget(std::string name) {
		std::string query = "SELECT BUDZET FROM GRACZE WHERE NAZWA = '"+name+"'; ";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			float result = std::stof(row[0]);
			return result;
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
			return -1.f;
		}
	}
	std::vector<std::string> allGames() {
		std::vector<std::string> games;
		std::string query = "SELECT NAZWA FROM GRY;";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
				games.push_back(row[0]);
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}

		return games;
	}
	std::vector<std::string> allPlayers() {
		std::vector<std::string> players;
		std::string query = "SELECT NAZWA FROM GRACZE;";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
				players.push_back(row[0]);
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}

		return players;
	}

	float getPrice(std::string game) {
		float price = 0.f;
		std::string query = "SELECT CENA FROM GRY WHERE NAZWA = '"+game+"'; ";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			price = std::stof(row[0]);
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}

		return price;
	}

	void buyGame(std::string game, std::string userName) {
		std::string query = "INSERT INTO Posiadane_gry(ID_Gracza, ID_Gry, Posiada_od, ILOSC_SPEDZONYCH_GODZIN) ";
		query += "VALUES((SELECT ID_Gracza FROM Gracze WHERE Nazwa = '"+ userName +"'), (SELECT ID_Gry FROM Gry WHERE Nazwa = '" + game + "'), (SELECT NOW() FROM DUAL), 0); ";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (qstate) {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}
	}
	void changeBudget(float price, std::string userName) {
		std::string query = "UPDATE Gracze SET Budzet = "+ std::to_string(price) +"WHERE Nazwa = '"+userName+"';";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (qstate) {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}
	}

	bool addUser(std::string User, std::string Pass, std::string Money) {
		std::string query = "INSERT INTO Gracze (ID_gracza, Nazwa, Haslo, Data_utworzenia_konta, Budzet) VALUES (NULL, '"+User+"', '" + Pass + "', (SELECT NOW() FROM DUAL), " + Money + ");";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			return true;
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << query << std::endl;
			return false;
		}
	}
	bool addGame(std::string Game, std::string Cost, std::string Date, std::string Package, std::string Type) {
		if (Package == "0") Package = "NULL";
		std::string query = "INSERT INTO Gry(ID_gry, Nazwa, Cena, Data_wydania, ID_paczki, ID_gatunku) VALUES(NULL, '" + Game + "', " + Date + ", '" + Cost + "', " + Package + ", " + Type + "); ";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			return true;
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << query << std::endl;
			return false;
		}
	}
	bool addPackage(std::string Cost, std::string DateStart, std::string DateStop) {
		std::string query = "INSERT INTO Paczki_gier (ID_paczki, Cena, Data_rozpoczecia, Data_zakonczenia) VALUES(NULL, " + Cost + ", '" + DateStart + "', '" + DateStop + "'); ";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			return true;
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << query << std::endl;
			return false;
		}
	}
	bool deleteUser(std::string User) {
		std::string query = "DELETE FROM Gracze WHERE Nazwa = '"+User+"';";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			return true;
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << query << std::endl;
			return false;
		}
	}
	bool deleteGame(std::string Game) {
		std::string query = "DELETE FROM Gry WHERE Nazwa = '" + Game + "';";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			return true;
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << query << std::endl;
			return false;
		}
	}
	bool deletePackage(std::string Package) {
		std::string query = "DELETE FROM Paczki_gier WHERE ID_Paczki = " + Package + ";";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			return true;
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << query << std::endl;
			return false;
		}
	}
	bool changeUser(std::string User, std::string Pass, std::string Money) {
		std::string query = "UPDATE Gracze SET Haslo = '"+Pass+"', Budzet = "+Money+" WHERE Nazwa = '"+User+"';";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			return true;
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << query << std::endl;
			return false;
		}
	}
	bool changeGame(std::string Game, std::string Cost, std::string Date, std::string Package) {
		std::string query = "UPDATE Gry SET Cena = " + Cost + ", Data_wydania = '" + Date + "', ID_Paczki = "+Package+" WHERE Nazwa = '" + Game + "';";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			return true;
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << query << std::endl;
			return false;
		}
	}
	bool changePackage(std::string Package, std::string Cost, std::string DateStart, std::string DateStop) {
		std::string query = "UPDATE Paczki_gier SET Cena = '" + Cost + "', Data_rozpoczecia = '" + DateStart + "', Data_zakonczenia = '" + DateStop + "' WHERE ID_Paczki = "+Package + ";";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			return true;
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << query << std::endl;
			return false;
		}
	}

	void addHoursToPlayer(std::string Time, std::string User, std::string Game) {
		std::string query = "UPDATE Posiadane_gry SET Ilosc_spedzonych_godzin = Ilosc_spedzonych_godzin + "+ Time +" WHERE ID_gracza = (SELECT ID_gracza FROM Gracze WHERE Nazwa = '"+ User +"') AND ID_gry = (SELECT ID_gry FROM Gry WHERE Nazwa = '" + Game + "');";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (qstate) {
			std::cout << "Query failed: " << mysql_error(conn) << query << std::endl;
		}
	}
	void addHoursToStatistics(std::string Game) {
		std::string query = "call oblicz_czas_wszystkich_graczy(@czas);";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (qstate) {
			std::cout << "Query failed: " << mysql_error(conn) << query << std::endl;
		}

		std::string query2 = "UPDATE Statystyki SET Ilosc_godzin = Ilosc_godzin + @czas, Ilosc_aktywnych_graczy = Ilosc_aktywnych_graczy + 1 WHERE ID_gry = (SELECT ID_gry FROM Gry WHERE Nazwa = '"+Game+"');";
		const char* q2 = query2.c_str();
		qstate = mysql_query(conn, q2);
		if (qstate) {
			std::cout << "Query failed: " << mysql_error(conn) << query << std::endl;
		}
	}

	std::string getPlayerHours(std::string userName) {
		
		std::string temp;
		std::string query = "SELECT SUM(Ilosc_spedzonych_godzin) FROM Posiadane_gry WHERE ID_gracza = (SELECT ID_gracza FROM Gracze WHERE Nazwa = '"+ userName +"');";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			if (row[0] == "NULL")
				temp = "0";
			else
				temp = row[0];
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}
		return temp;
	}

	std::string getPlayerNrGames(std::string userName) {
		std::string temp;
		std::string query = "SELECT COUNT(*) FROM Posiadane_gry WHERE ID_gracza = (SELECT ID_gracza FROM Gracze WHERE Nazwa = '" + userName + "');";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			std::cout << row[0];
			if (row[0] == "NULL")
				temp = "0";
			else
				temp = row[0];
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}

		return temp;
	}

	std::vector<std::string> selectedGames(std::string selection) {
		std::vector<std::string> games;
		std::string query = "SELECT NAZWA FROM GRY WHERE NAZWA LIKE '"+selection+"%';";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
				games.push_back(row[0]);
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}

		return games;
	}
	std::vector<std::string> selectedPlayers(std::string selection) {
		std::vector<std::string> players;
		std::string query = "SELECT NAZWA FROM GRACZE WHERE NAZWA LIKE '" + selection + "%';";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
				players.push_back(row[0]);
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}

		return players;
	}

	std::vector<std::string> allStatyistics() {
		std::vector<std::string> all;
		std::string query = "SELECT Nazwa, Ilosc_godzin, Ilosc_aktywnych_graczy FROM Statystyki INNER JOIN Gry on gry.ID_gry = statystyki.ID_gry;";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) {
				std::string temp = "";
				temp += row[0];
				temp += " ";
				temp += "Ilosc godzin: ";
				temp += row[1];
				temp += " ";
				temp += "Ilosc aktywnych graczy: ";
				temp += row[2];
				all.push_back(temp);
			}
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}

		return all;
	}
	std::string buyedGames() {
		std::string temp = "";
		std::string query = "SELECT COUNT(*) FROM Posiadane_gry;";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			temp += "Ilosc wszystkich kupionych egzemplarzy gier: ";
			temp += row[0];
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}

		return temp;
	}
	std::vector<std::string> Packages() {
		std::vector<std::string> temp;
		std::string countS;
		std::string query = "SELECT COUNT(*) FROM Paczki_gier;";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			countS = row[0];
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}

		int count = std::stoi(countS);
		for (int i = 1; i <= count; i++) {
			std::string temp2;
			std::string query2 = "call nazwy_gier_w_paczce("+std::to_string(i)+", @gra1, @gra2, @gra3, @cena);";
			const char* q2 = query2.c_str();
			qstate = mysql_query(conn, q2);
			if (!qstate) {
				std::string temp3 = "";
				std::string query3 = "SELECT @gra1, @gra2, @gra3, @cena;";
				const char* q3 = query3.c_str();
				qstate = mysql_query(conn, q3);
				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res)) {
					temp3 += "Paczka nr ";
					temp3 += std::to_string(i);
					temp3 += ": ";
					temp3 += row[0];
					temp3 += ", ";
					temp3 += row[1];
					temp3 += ", ";
					temp3 += row[2];
					temp3 += " cena: ";
					temp3 += row[3];
				}
				temp.push_back(temp3);
			}
			else {
				std::cout << "Query failed: " << mysql_error(conn) << std::endl;
			}
		}
		return temp;
	}
	std::vector<std::string> Promotions() {
		std::vector<std::string> all;
		std::string query = "select nazwa, cena, obnizka_w_procentach from przeceny inner join gry on gry.id_gry = przeceny.id_gry;";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) {
				std::string tempS = row[0];
				tempS += " stara cena: ";
				tempS += row[1];
				tempS += " nowa cena: ";
				tempS += std::to_string(std::stof(row[1]) - ((std::stof(row[2])/100) * std::stof(row[1])));
				all.push_back(tempS);
			}
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}

		return all;
	}

	bool setFirstAchievment(std::string userName) {
		std::string query = "INSERT INTO Osiagniecia (ID_OSIAGNIECI, ID_GRACZA, NAZWA, DATA_ZDOBYCIA) VALUES (1, (SELECT ID_Gracza FROM Gracze WHERE Nazwa = '"+userName+"'), 'Kup gre', (SELECT NOW() FROM DUAL))";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			return true;
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << query << std::endl;
			return false;
		}
	}

	std::vector<std::string> getPlayerAchivments(std::string userName) {

		std::vector<std::string> temp;
		std::string query = "SELECT Nazwa FROM Osiagniecia WHERE ID_gracza = (SELECT ID_gracza FROM Gracze WHERE Nazwa = '" + userName + "');";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
				temp.push_back(row[0]);
			
		}
		else {
			std::cout << "Query failed: " << mysql_error(conn) << std::endl;
		}
		return temp;
	}
};
