DROP DATABASE PROJECT;
CREATE DATABASE PROJECT;
USE PROJECT;


CREATE TABLE SPOLKA_GIER
   (	ID_SPOLKI INT PRIMARY KEY not null, 
	NAZWA VARCHAR(30) not null, 
	SPOLKA VARCHAR(30) not null, 
	ILOSC_PRACOWNIKOW INT not null, 
	DATA_POWSTANIA DATE not null
   );
ALTER TABLE SPOLKA_GIER MODIFY ID_SPOLKI INT NOT NULL AUTO_INCREMENT;  

CREATE TABLE GATUNKI_GIER
   (	ID_GATUNKU INT PRIMARY KEY not null, 
	NAZWA VARCHAR(30) not null
   ) ;
ALTER TABLE GATUNKI_GIER MODIFY ID_GATUNKU INT NOT NULL AUTO_INCREMENT;

CREATE TABLE GRACZE
   (	ID_GRACZA INT PRIMARY KEY not null, 
	NAZWA VARCHAR(30) not null, 
	HASLO VARCHAR(30) not null, 
	DATA_UTWORZENIA_KONTA DATE not null,
	BUDZET FLOAT not null
   ) ;
ALTER TABLE GRACZE MODIFY ID_GRACZA INT NOT NULL AUTO_INCREMENT;

CREATE TABLE PACZKI_GIER
   (	ID_PACZKI INT PRIMARY KEY not null, 
	CENA FLOAT not null, 
	DATA_ROZPOCZECIA DATE not null, 
	DATA_ZAKONCZENIA DATE not null
   ) ;
ALTER TABLE PACZKI_GIER MODIFY ID_PACZKI INT NOT NULL AUTO_INCREMENT;

CREATE TABLE GRY
   (	ID_GRY INT PRIMARY KEY not null, 
	NAZWA VARCHAR(30) not null, 
	CENA FLOAT not null, 
	DATA_WYDANIA DATE not null,
	ID_PACZKI INT null,
	ID_GATUNKU INT null,
	FOREIGN KEY (ID_GATUNKU) REFERENCES GATUNKI_GIER(ID_GATUNKU),
	FOREIGN KEY (ID_PACZKI) REFERENCES PACZKI_GIER(ID_PACZKI)
	ON DELETE CASCADE
   ) ;
ALTER TABLE GRY MODIFY ID_GRY INT NOT NULL AUTO_INCREMENT;

CREATE TABLE OSIAGNIECIA
   (	ID_OSIAGNIECI INT  not null, 
	ID_GRACZA INT not null, 
	NAZWA VARCHAR(30) not null, 
	DATA_ZDOBYCIA DATE not null,
	FOREIGN KEY (ID_GRACZA) REFERENCES GRACZE(ID_GRACZA)
	ON DELETE CASCADE
   ) ;

CREATE TABLE STATYSTYKI
   (	ID_GRY INT not null, 
	ILOSC_GODZIN FLOAT not null, 
	ILOSC_AKTYWNYCH_GRACZY INT not null,
	FOREIGN KEY (ID_GRY) REFERENCES GRY(ID_GRY)
	ON DELETE CASCADE
   ) ;

CREATE TABLE GRA_SPOLKA
   (	ROLA_SPOLKI VARCHAR(30) not null, 
	ID_GRY INT not null, 
	ID_SPOLKI INT not null,
	FOREIGN KEY (ID_GRY) REFERENCES GRY(ID_GRY)
	ON DELETE CASCADE,
	FOREIGN KEY (ID_SPOLKI) REFERENCES SPOLKA_GIER(ID_SPOLKI)
   ) ;

CREATE TABLE POSIADANE_GRY
   (	ID_GRACZA INT not null,
	ID_GRY INT not null, 
	POSIADA_OD DATE not null, 
	ILOSC_SPEDZONYCH_GODZIN FLOAT not null,
	FOREIGN KEY (ID_GRY) REFERENCES GRY(ID_GRY)
	ON DELETE CASCADE,
	FOREIGN KEY (ID_GRACZA) REFERENCES GRACZE(ID_GRACZA)
	ON DELETE CASCADE
   ) ;
   
  CREATE TABLE PRZECENY
   ( 	ID_GRY INT not null, 
	Obnizka_w_procentach FLOAT not null,
	DATA_ROZPOCZECIA DATE not null,
	DATA_ZAKONCZENIA DATE not null,
	FOREIGN KEY (ID_GRY) REFERENCES GRY(ID_GRY)
	ON DELETE CASCADE
   ) ;
   
 
INSERT INTO Gracze (ID_gracza, Nazwa, Haslo, Data_utworzenia_konta, Budzet)
VALUES (NULL, 'User1', '1234', '2022-01-14', 60);
INSERT INTO Gracze (ID_gracza, Nazwa, Haslo, Data_utworzenia_konta, Budzet)
VALUES (NULL, 'User2', '1234', '2022-01-14', 60);
INSERT INTO Gracze (ID_gracza, Nazwa, Haslo, Data_utworzenia_konta, Budzet)
VALUES (NULL, 'User3', '1234', '2022-01-14', 60);
   
INSERT INTO Gatunki_gier (ID_gatunku, Nazwa)
VALUES (NULL, 'RPG');
INSERT INTO Gatunki_gier (ID_gatunku, Nazwa)
VALUES (NULL, 'Przegladarkowa');

INSERT INTO Paczki_gier (ID_paczki, Cena, Data_rozpoczecia, Data_zakonczenia)
VALUES (1, 50, '2022-01-02', '2022-03-02');

INSERT INTO Spolka_gier (ID_spolki, Nazwa, Spolka, Ilosc_pracownikow, Data_powstania)
VALUES (NULL, 'Piranha Bytes', 'Publiczna', 100, '1997-01-02');
INSERT INTO Spolka_gier (ID_spolki, Nazwa, Spolka, Ilosc_pracownikow, Data_powstania)
VALUES (NULL, 'CD Projekt Red', 'SA', 1000, '2002-01-02');
INSERT INTO Spolka_gier (ID_spolki, Nazwa, Spolka, Ilosc_pracownikow, Data_powstania)
VALUES (NULL, 'Louissi', 'Prywatna', 2, '2007-01-02');

INSERT INTO Gry (ID_gry, Nazwa, Cena, Data_wydania, ID_paczki, ID_Gatunku)
VALUES (NULL, 'Gothic 1', 20, '2001-03-16', 1, 1);
INSERT INTO Gry (ID_gry, Nazwa, Cena, Data_wydania, ID_paczki, ID_Gatunku)
VALUES (NULL, 'Gothic 2', 30, '2002-11-30', 1, 1);
INSERT INTO Gry (ID_gry, Nazwa, Cena, Data_wydania, ID_paczki, ID_Gatunku)
VALUES (NULL, 'Gothic 3', 40, '2006-10-14', 1, 1);
INSERT INTO Gry (ID_gry, Nazwa, Cena, Data_wydania, ID_paczki, ID_Gatunku)
VALUES (NULL, 'Wiedzmin 3', 50, '2015-05-19', NULL, 1);
INSERT INTO Gry (ID_gry, Nazwa, Cena, Data_wydania, ID_paczki, ID_Gatunku)
VALUES (NULL, 'Age of War', 0, '2007-01-02', NULL, 2);

INSERT INTO Statystyki(ID_gry, Ilosc_godzin, Ilosc_aktywnych_graczy)
VALUES (1, 10, 2);
INSERT INTO Statystyki (ID_gry, Ilosc_godzin, Ilosc_aktywnych_graczy)
VALUES (2, 80, 20);
INSERT INTO Statystyki (ID_gry, Ilosc_godzin, Ilosc_aktywnych_graczy)
VALUES (3, 30, 9);
INSERT INTO Statystyki (ID_gry, Ilosc_godzin, Ilosc_aktywnych_graczy)
VALUES (4, 100, 30);
INSERT INTO Statystyki (ID_gry, Ilosc_godzin, Ilosc_aktywnych_graczy)
VALUES (5, 5, 1);

INSERT INTO Gra_spolka (Rola_spolki, ID_gry, ID_spolki)
VALUES ('Deweloper', 1, 1);
INSERT INTO Gra_spolka (Rola_spolki, ID_gry, ID_spolki)
VALUES ('Deweloper', 2, 1);
INSERT INTO Gra_spolka (Rola_spolki, ID_gry, ID_spolki)
VALUES ('Deweloper', 3, 1);
INSERT INTO Gra_spolka (Rola_spolki, ID_gry, ID_spolki)
VALUES ('Deweloper', 4, 2);
INSERT INTO Gra_spolka (Rola_spolki, ID_gry, ID_spolki)
VALUES ('Deweloper', 5, 3);

INSERT INTO Przeceny (ID_gry, Obnizka_w_procentach, Data_rozpoczecia, Data_zakonczenia)
VALUES (4, 20, '2022-01-14', '2022-03-02');




delimiter //
CREATE PROCEDURE oblicz_czas_wszystkich_graczy(OUT czas INT)
BEGIN
	SELECT SUM(Ilosc_spedzonych_godzin) INTO czas FROM Posiadane_gry;
END //

 CREATE PROCEDURE nazwy_gier_w_paczce(IN nrPaczki INT, OUT gra VARCHAR(30), OUT gra2 VARCHAR(30), OUT gra3 VARCHAR(30), OUT pcena FLOAT)
BEGIN
    DECLARE counter INT DEFAULT 1;
	DEClARE cGra CURSOR FOR 
		SELECT Nazwa FROM Gry WHERE ID_Paczki = nrPaczki;
		
	SELECT Cena INTO pcena FROM Paczki_gier WHERE ID_Paczki = nrPaczki;
	OPEN cGra;
	WHILE counter <= 3 DO
		IF counter = 1 THEN
			FETCH cGra INTO gra;
		ELSEIF counter = 2 THEN
			FETCH cGra INTO gra2;
		ELSE
			FETCH cGra INTO gra3;
		END IF;
		SET counter = counter +1;
	END WHILE;
	CLOSE cGra;

END //
delimiter ;

call nazwy_gier_w_paczce(1, @gra1, @gra2, @gra3, @cena);
SELECT @gra1, @gra2, @gra3, @cena;
SELECT * FROM GRACZE;
SELECT * FROM PRZECENY;
SELECT * FROM GRA_SPOLKA;
SELECT * FROM SPOLKA_GIER;
SELECT * FROM STATYSTYKI;
SELECT * FROM PACZKI_GIER;
SELECT * FROM GATUNKI_GIER;
SELECT * FROM GRY;

