# Zadanie 8 – cvičenie 9 – Databázy

## Čo je cieľ zadania

V Ubuntu používať databázu MySQL. Vytvoriť **jednu databázu** s **jednou tabuľkou** `Hodnoty`, ktorá má iba dva stĺpce:

- `ID` – celé číslo, primárny kľúč, automaticky sa zvyšuje (`AUTO_INCREMENT`).
- `hodnota` – celé číslo vygenerované v C++ funkciou `rand()`.

Program vygeneruje **10 náhodných čísel**, vypíše ich, uloží do MySQL, načíta ich zoradené **vzostupne** a vypíše ich na konzolu.

## 1. Čo je v jednotlivých súboroch

| Súbor | Úloha |
| --- | --- |
| `testdb.cpp` | Hlavný C++ program – vygenerovanie, výpis, uloženie, načítanie a zoradenie čísel. |
| `databaza.sql` | Vytvorí tabuľku `Hodnoty` s `ID` a `hodnota`. |
| `setup.sh` | Nainštaluje potrebné balíky (ak chýbajú), spustí MySQL, vytvorí databázu a používateľa, skompiluje a spustí program. |
| `.github/workflows/run.yml` | Nastavenie automatického spúšťania na GitHube cez Actions. |
| `README.md` | Tento návod. |

Tabuľku netreba vyplniť ručne: `INSERT` príkazy vykonáva C++ program.

## 2. Najjednoduchšie spustenie – GitHub Codespaces

Codespaces je online vývojové prostredie s terminálom podobné VS Code. Do svojho počítača nemusíš nič inštalovať.

1. Otvor https://github.com/parzival2199/zadanie8
2. Klikni na zelené **Code**.
3. Vyber **Codespaces** → **Create codespace on main** (alebo otvor už existujúci Codespace).
4. V dolnej časti otvor kartu **Terminal**.
5. V adresári `/workspaces/zadanie8` spusti:

```bash
bash setup.sh
```

Pri prvom použití sa nainštaluje MySQL server, klient, knižnice na komunikáciu s MySQL a C++ kompilátor. Skript potom vytvorí databázu, tabuľku a spustí program.

**Ak si upravil súbory cez webový GitHub a Codespaces má ešte staršiu verziu**, najprv v termináli zadaj:

```bash
git pull
```

Potom `bash setup.sh`.

### Ako vygenerovať ďalších 10 náhodných čísel

Keď je program už skompilovaný a databáza funguje, **netreba znova inštalovať ani kompilovať**. Stačí:

```bash
DB_HOST=127.0.0.1 ./testdb
```

Hneď sa vypíšu nové náhodné čísla a tie isté čísla zoradené vzostupne. Príkaz `DB_HOST=127.0.0.1` nastaví pripojenie cez TCP, aby nevznikal problém so socketom v Codespaces.

**Ak zmeníš súbor `testdb.cpp`**, treba ho najprv znovu skompilovať:

```bash
g++ -std=c++11 testdb.cpp -o testdb $(mysql_config --cflags --libs)
DB_HOST=127.0.0.1 ./testdb
```

## 3. Prihlásenie do MySQL a zobrazenie tabuľky

Prístupové údaje pre tento školský projekt:

| Údaj | Hodnota |
| --- | --- |
| Server | `127.0.0.1` |
| Používateľ | `student` |
| Heslo | `1234` |
| Databáza | `cvicenie9` |
| Tabuľka | `Hodnoty` |

V Codespaces zadaj **do bežného terminálu**:

```bash
mysql -h 127.0.0.1 -u student -p
```

Zobrazí sa výzva na heslo. Napíš `1234` a stlač Enter. Pri písaní sa znaky hesla nezobrazujú.

Keď sa zobrazí `mysql>`, si prihlásený. Postupne môžeš použiť tieto **SQL príkazy**:

```sql
SHOW DATABASES;
USE cvicenie9;
SHOW TABLES;
SELECT * FROM Hodnoty;
```

Výpis tabuľky má stĺpce `ID` a `hodnota`. Zoradenie hodnôt vzostupne:

```sql
SELECT * FROM Hodnoty ORDER BY hodnota ASC;
```

Odhlásenie z MySQL:

```sql
EXIT;
```

**Rozdiel:** Príkazy ako `./testdb` sa píšu do bežného terminálu (napr. znak `$`). Príkazy `SELECT` a `USE` sa píšu po prihlásení za `mysql>`.

Ak chceš tabuľku zobraziť bez interaktívneho prihlasovania, môžeš v bežnom termináli použiť:

```bash
mysql -h 127.0.0.1 -u student -p cvicenie9 -e "SELECT * FROM Hodnoty;"
```

## 4. Čo sa deje v tabuľke

Súbor `databaza.sql` obsahuje:

```sql
CREATE TABLE IF NOT EXISTS Hodnoty (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    hodnota INT
);
```

- `ID` sa doplní automaticky.
- `hodnota` obsahuje číslo z C++ programu.
- `testdb.cpp` pred každým spustením vymaže **staré riadky** príkazom `DELETE FROM Hodnoty`, potom vloží presne 10 nových.
- Preto tabuľka obsahuje 10 čísel z posledného spustenia.
- ID sa však po `DELETE` **nezačína automaticky od 1**. Môžeš vidieť ID napr. 51 až 60 – je to správne.

V programe sa používa:

```sql
INSERT INTO Hodnoty (hodnota) VALUES (42);
SELECT hodnota FROM Hodnoty ORDER BY hodnota ASC;
```

Prvý príkaz je len príklad vloženia jedného čísla. Skutočný program vkladá vygenerované hodnoty automaticky.

## 5. Spustenie cez GitHub Actions (bez Codespaces)

1. Otvor https://github.com/parzival2199/zadanie8/actions
2. Vľavo klikni **Databazy - Zadanie 8**.
3. Klikni **Run workflow** a potvrď.
4. Otvor vytvorené spustenie označené zelenou fajkou.
5. Vľavo vyber **spustenie**.
6. Rozbaľ šípkou riadok **Compile and run**.
7. Uvidíš vypísaných 10 náhodných a následne 10 zoradených čísel.

Ak si už na detailoch predchádzajúceho spustenia, môžeš vpravo hore stlačiť **Re-run all jobs**. Program sa tým spustí znova a vygeneruje nové čísla.

**Pozor:** GitHub Actions pripravuje nové prostredie s MySQL pri každom behu, preto trvá dlhšie (často približne minútu). Databáza v Actions je dočasná a po skončení behu sa vypne. Na rýchle opakované spúšťanie je vhodnejší Codespaces.

Zelené **Success** znamená, že automatický proces prebehol úspešne. Žlté upozornenie o Node.js v akcii checkout nie je chyba C++ programu.

## 6. Riešenie častých problémov

### `ERROR 2002 ... Can't connect to local MySQL server`

MySQL nemusí byť spustené alebo sa klient pokúša použiť lokálny socket. V termináli Codespaces skús:

```bash
sudo service mysql start
```

Potom použi pripojenie cez `-h 127.0.0.1` a program spúšťaj cez `DB_HOST=127.0.0.1 ./testdb`. Ak stále nefunguje, spusti `bash setup.sh` a skontroluj chybové hlásenie.

### `./testdb: No such file or directory`

Program ešte nebol skompilovaný, alebo nie si v adresári projektu. V `/workspaces/zadanie8` spusti:

```bash
bash setup.sh
```

### MySQL sa pýta na heslo

Pri `mysql -h 127.0.0.1 -u student -p` zadaj heslo `1234`. Znaky pri písaní nevidno – to je normálne.

### Čísla v tabuľke majú ID väčšie ako 10

Je to normálne: `DELETE` vymaže riadky, ale počítadlo `AUTO_INCREMENT` pokračuje.

## 7. Stiahnutie celého projektu ako ZIP

1. Otvor https://github.com/parzival2199/zadanie8
2. Klikni **Code** → **Download ZIP**.
3. Stiahne sa `zadanie8-main.zip`.

ZIP obsahuje zdrojové súbory a návod. **Neobsahuje bežiaci MySQL server ani samotné uložené dáta** z Codespaces či Actions. Ak potrebuješ dôkaz výsledku, odfoť výstup z **Compile and run** alebo z terminálu Codespaces.

## 8. Čo odovzdať

Základom sú `testdb.cpp` a `databaza.sql`. Celý ZIP navyše obsahuje `setup.sh`, GitHub workflow a tento návod na spustenie. Ak vyučujúci vyžaduje konkrétny spôsob odovzdania, riaď sa jeho pokynmi.

**Poznámka k bezpečnosti:** Meno `student` a heslo `1234` sú jednoduché testovacie údaje pre školské prostredie. Nepoužívaj ich na skutočnom verejne prístupnom databázovom serveri.
