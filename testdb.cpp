#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <mysql/mysql.h>
using namespace std;

int main() {
    srand(time(0));

    MYSQL* db = mysql_init(NULL);
    const char* host = getenv("DB_HOST");
    if (!host) host = "localhost";

    if (!mysql_real_connect(db, host, "student", "1234", "cvicenie9", 0, NULL, 0)) {
        cerr << "Chyba MySQL: " << mysql_error(db) << endl;
        mysql_close(db);
        return 1;
    }

    if (mysql_query(db, "DELETE FROM Hodnoty")) {
        cerr << mysql_error(db) << endl;
        mysql_close(db);
        return 1;
    }

    cout << "Nahodne hodnoty:" << endl;
    for (int i = 0; i < 10; i++) {
        int x = rand() % 100;
        cout << x << endl;

        string sql = "INSERT INTO Hodnoty (hodnota) VALUES (" + to_string(x) + ")";
        if (mysql_query(db, sql.c_str())) {
            cerr << mysql_error(db) << endl;
            mysql_close(db);
            return 1;
        }
    }

    if (mysql_query(db, "SELECT hodnota FROM Hodnoty ORDER BY hodnota ASC")) {
        cerr << mysql_error(db) << endl;
        mysql_close(db);
        return 1;
    }

    MYSQL_RES* vysledok = mysql_store_result(db);
    if (!vysledok) {
        cerr << mysql_error(db) << endl;
        mysql_close(db);
        return 1;
    }

    MYSQL_ROW riadok;
    cout << "\nZoradene hodnoty:" << endl;
    while ((riadok = mysql_fetch_row(vysledok)))
        cout << riadok[0] << endl;

    mysql_free_result(vysledok);
    mysql_close(db);
    return 0;
}
