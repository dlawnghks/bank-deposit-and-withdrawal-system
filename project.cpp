#include <mysql.h>
#include <iostream>

int main() {
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    conn = mysql_init(nullptr);

    if (!mysql_real_connect(conn, "localhost", "root", "", "test_db", 3306, NULL, 0)) {
        std::cerr << "MySQL connection failed: " << mysql_error(conn) << std::endl;
        return 1;
    }

    const char* insert_query =
        "INSERT INTO users (name, email) VALUES('Alice', 'alice@example.com')";

    if (mysql_query(conn, insert_query)) {
        std::cerr << "INSERT failed: " << mysql_error(conn) << std::endl;
    }
    else {
        std::cout << "Insert successful!" << std::endl;
    }

    if (mysql_query(conn, "SELECT id, name, email FROM users")) {
        std::cerr << "SELECT failed: " << mysql_error(conn) << std::endl;
    }
    else {
        res = mysql_store_result(conn);
        if (res) {
            while ((row = mysql_fetch_row(res)) != NULL) {
                std::cout << "ID: " << row[0]
                    << ", Name: " << row[1]
                    << ", Email: " << row[2] << std::endl;
            }
            mysql_free_result(res);
        }
    }

    mysql_close(conn);
    return 0;
}
