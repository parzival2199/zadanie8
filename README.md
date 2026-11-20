# 🗄️ Zadanie 8 – cvičenie 9 | Databázy

**C++ + MySQL · Ubuntu · GitHub Codespaces**

> Program vygeneruje **10 náhodných čísel**, vypíše ich, uloží do databázy MySQL a následne ich vypíše **zoradené vzostupne**.

---

## 🚀 Rýchly štart

| Čo chceš urobiť? | Príkaz v termináli Codespaces |
| --- | --- |
| Prvýkrát pripraviť a spustiť projekt | `bash setup.sh` |
| Vygenerovať ďalších 10 čísel | `DB_HOST=127.0.0.1 ./testdb` |
| Načítať najnovšie zmeny z GitHubu | `git pull` |
| Prihlásiť sa do databázy | `mysql -h 127.0.0.1 -u student -p` |

> [!TIP]
> **Najrýchlejší spôsob:** Keď si už raz spustil `bash setup.sh`, ďalšie čísla vytvoríš jediným príkazom `DB_HOST=127.0.0.1 ./testdb`. Nemusíš znovu inštalovať ani kompilovať.

## 📁 Súbory projektu

| Súbor | Na čo slúži |
| --- | --- |
| **[`testdb.cpp`](testdb.cpp)** | Hlavný C++ program – generovanie, ukladanie, načítanie a zoradenie čísel |
| **[`databaza.sql`](databaza.sql)** | Vytvorenie tabuľky `Hodnoty` s dvoma stĺpcami |
| **[`setup.sh`](setup.sh)** | Inštalácia, nastavenie MySQL, kompilácia a spustenie |
| **[`run.yml`](.github/workflows/run.yml)** | Automatické spustenie cez GitHub Actions |
| **`README.md`** | Tento kompletný návod |

---

## 💻 1. Spustenie v GitHub Codespaces

1. Otvor **[projekt na GitHube](https://github.com/parzival2199/zadanie8)**.
2. Klikni na **Code → Codespaces → Create codespace on main** (alebo otvor existujúci Codespace).
3. V spodnej časti otvor kartu **Terminal**.
4. Do terminálu vlož:

```bash
bash setup.sh
```

Skript pripraví MySQL, databázu, tabuľku, skompiluje program a vypíše výsledky.

### 🔄 Nové náhodné čísla

Stačí spustiť:

```bash
DB_HOST=127.0.0.1 ./testdb
```

Program vymaže staré riadky z tabuľky, vloží **10 nových čísel** a vypíše ich aj zoradené.

### ✏️ Ak si zmenil kód

Po zmene `testdb.cpp` ho musíš znovu skompilovať:

```bash
g++ -std=c++11 testdb.cpp -o testdb $(mysql_config --cflags --libs)
DB_HOST=127.0.0.1 ./testdb
```

Ak si súbory upravil priamo na GitHube, v Codespaces si ich najprv aktualizuj:

```bash
git pull
```

---

## 🔐 2. Prihlásenie do MySQL

| Údaj | Hodnota |
| --- | --- |
| **Server** | `127.0.0.1` |
| **Používateľ** | `student` |
| **Heslo** | `1234` |
| **Databáza** | `cvicenie9` |
| **Tabuľka** | `Hodnoty` |

**V bežnom termináli** zadaj:

```bash
mysql -h 127.0.0.1 -u student -p
```

Keď sa zobrazí `Enter password:`, napíš **`1234`** a stlač Enter. Pri písaní hesla sa znaky nezobrazujú.

Po úspešnom prihlásení uvidíš `mysql>`. Teraz môžeš zadávať SQL:

```sql
SHOW DATABASES;
USE cvicenie9;
SHOW TABLES;
SELECT * FROM Hodnoty;
```

**Zoradenie hodnôt vzostupne:**

```sql
SELECT * FROM Hodnoty ORDER BY hodnota ASC;
```

**Odhlásenie:**

```sql
EXIT;
```

> [!IMPORTANT]
> `mysql>` znamená, že si **vo vnútri MySQL** a píšeš SQL príkazy. Príkaz `./testdb` patrí do **bežného terminálu**, nie do MySQL. Najprv zadaj `EXIT;`.

---

## 📊 3. Ako funguje tabuľka

Databáza sa volá **`cvicenie9`** a obsahuje jedinú tabuľku **`Hodnoty`**.

| ID | hodnota |
| ---: | ---: |
| 51 | 35 |
| 52 | 64 |
| 53 | 42 |
| 54 | 80 |
| … | … |

*Ukážka zo spustenia. Skutočné čísla sa menia pri každom spustení.*

**Dva stĺpce:**

- **`ID`** – automaticky pridelené číslo, primárny kľúč (`AUTO_INCREMENT`).
- **`hodnota`** – náhodné číslo z C++ funkcie `rand()`.

**Postup programu:** vygeneruje čísla → vypíše ich → uloží do MySQL (`INSERT`) → načíta zoradené (`SELECT ... ORDER BY`) → vypíše výsledok.

> [!NOTE]
> Po každom spustení sa staré hodnoty vymažú, ale číslovanie `ID` sa **neresetuje**. Preto je normálne, keď máš ID napríklad 51 až 60 namiesto 1 až 10.

<details>
<summary><strong>Zobraziť SQL štruktúru tabuľky</strong></summary>

Súbor `databaza.sql` obsahuje:

```sql
CREATE TABLE IF NOT EXISTS Hodnoty (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    hodnota INT
);
```

Hodnoty vkladá automaticky C++ program. Ručne ich vypĺňať nemusíš.

</details>

---

## ▶️ 4. Spustenie cez GitHub Actions

Ak nechceš otvárať Codespaces, program sa dá spustiť aj priamo cez GitHub:

1. Otvor **[GitHub Actions](https://github.com/parzival2199/zadanie8/actions)**.
2. Vyber **Databazy - Zadanie 8**.
3. Klikni na **Run workflow** a potvrď.
4. Otvor nové spustenie → **spustenie** → rozbaľ **Compile and run**.
5. Uvidíš **10 náhodných čísel** a pod nimi **zoradené hodnoty**.

Ak už máš otvorený výsledok, kliknutím na **Re-run all jobs** spustíš ďalší beh.

> [!TIP]
> GitHub Actions pri každom spustení pripravuje nové prostredie a dočasnú databázu, preto je pomalší. Na opakované generovanie čísel je **Codespaces rýchlejší**.

---

## 🛠️ 5. Časté problémy

<details>
<summary><strong>ERROR 2002 – Can't connect to local MySQL server</strong></summary>

Skontroluj spustenie databázy:

```bash
sudo service mysql start
```

Používaj TCP pripojenie `127.0.0.1` a program spúšťaj takto:

```bash
DB_HOST=127.0.0.1 ./testdb
```

Ak treba, použi znovu `bash setup.sh`.

</details>

<details>
<summary><strong>./testdb: No such file or directory</strong></summary>

Program ešte nemusí byť skompilovaný. V priečinku `/workspaces/zadanie8` zadaj:

```bash
bash setup.sh
```

</details>

<details>
<summary><strong>Pri hesle sa nezobrazujú znaky</strong></summary>

Je to normálne. Napíš `1234` a stlač Enter.

</details>

<details>
<summary><strong>GitHub Actions zobrazuje žlté upozornenie</strong></summary>

Ak má spustenie stav **Success** a upozornenie sa týka Node.js pri `actions/checkout`, nejde o chybu C++ programu.

</details>

---

## 📦 6. Stiahnutie a odovzdanie

1. Otvor **[repozitár zadanie8](https://github.com/parzival2199/zadanie8)**.
2. Klikni **Code → Download ZIP**.
3. Stiahne sa súbor **`zadanie8-main.zip`**.

**Hlavné súbory:** `testdb.cpp` a `databaza.sql`. ZIP obsahuje aj spúšťací skript a tento návod.

> [!NOTE]
> ZIP obsahuje **zdrojové súbory**, nie nainštalovanú databázu ani čísla uložené v MySQL. Ak potrebuješ doložiť výstup, môžeš pridať screenshot z terminálu alebo z **Compile and run**.

---

<sub>Školský testovací projekt. Používateľ `student` a heslo `1234` sú len pre toto cvičenie, nie pre verejný databázový server.</sub>
