# Zadanie 8 – cvičenie 9 – Databázy

Jedna databáza **cvicenie9**, jedna tabuľka **Hodnoty** so stĺpcami `ID` (primárny kľúč, AUTO_INCREMENT) a `hodnota`.

C++ program vygeneruje 10 náhodných čísel funkciou `rand()`, vypíše ich, vloží do MySQL, vyberie vzostupne a vypíše. Pred vložením vymaže predchádzajúce hodnoty, aby bol pri každom spustení výstup presne 10 čísel.

## Online automatické spustenie

V GitHube otvor **Actions → Databazy - Zadanie 8 → Run workflow**. Výsledok nájdeš v kroku **Compile and run**. Workflow spúšťa databázu MySQL 8 v kontajneri.

## Spustenie v GitHub Codespaces

Otvor repozitár → **Code → Codespaces → Create codespace on main**.

V jeho termináli stačí jediný príkaz:

```bash
bash setup.sh
```

Nainštaluje MySQL, vytvorí databázu, skompiluje a spustí program. Pri ďalšom spustení stačí `./testdb`.

Prihlasovacie údaje `student` / `1234` sú iba pre tento školský testovací projekt.
