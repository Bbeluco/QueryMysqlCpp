#include <stdlib.h>
#include <iostream>
#include <limits>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

void ignore_buffer_remains() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void check_if_cin_is_correct_and_clear() {
  if(std::cin.fail()){
    std::cin.clear();
    ignore_buffer_remains();
  }
}

void query_database(sql::Statement *stmt){
  sql::ResultSet *res;

  constexpr std::string_view exit_value{"0"};

  std::string query{};
  while(query.compare(exit_value) != 0) {
    std::cout << "What you want to query (0 to exit)?\n";
    std::cout << "Query: ";
    
    check_if_cin_is_correct_and_clear();
    getline(std::cin, query);

    if(!query.compare(exit_value)) {
      break;
    }

    try{
      res = stmt->executeQuery(query);
      while(res->next()){
        std::cout << res->~ResultSet() << '\n';
        std::cout << "id="<< res->getInt(1);
        std::cout << ", name="<< res->getString("name");
        std::cout << ", testScore="<< res->getDouble("testScore") << '\n';
      }
    } catch(sql::SQLException& e){
      std::cout << "\n#InvalidArgumentException\n";
      std::cout << "#ERR: " << e.what() << '\n';
      std::cout << "#CODE: " << e.getErrorCode() << '\n';
      std::cout << "#SQLState: " << e.getSQLState() << '\n';
      std::cout << "#SQLStateCStr: " << e.getSQLStateCStr() << '\n';
    }
  }

  std::cout << '\n';
}

int main(void) {
  sql::Driver *driver;
  sql::Connection *conn;
  sql::Statement *stmt;
  

  driver = get_driver_instance();
  conn = driver->connect("tcp://127.0.0.1:3306", "root", "cppPass");

  stmt = conn->createStatement();
  stmt->execute("use cppDb");

  std::cout << "Welcome to Query Mysql\n";

  query_database(stmt);


  delete conn;
  return EXIT_SUCCESS;
}