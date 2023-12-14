#ifndef DATABASE_CONNECTION_H_NAME
#define DATABASE_CONNECTION_H_NAME

#include <cppconn/statement.h>
#include <cppconn/driver.h>

namespace DB_Conn {
    sql::Statement* connect_to_database() {
        sql::Statement *stmt;
        sql::Driver *driver;
        sql::Connection *conn;
        driver = get_driver_instance();
        conn = driver->connect("tcp://127.0.0.1:3306", "root", "cppPass");

        stmt = conn->createStatement();
        stmt->execute("use cppDb");

        return stmt;
    } 
}

#endif