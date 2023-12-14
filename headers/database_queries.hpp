#ifndef DB_QUERIES_H_NAME
#define DB_QUERIES_H_NAME

#include <iostream>
#include <cppconn/statement.h>
#include <cppconn/exception.h>

#include "input_validations.hpp"

namespace DB_Queries {
    void query_database(sql::Statement *stmt) {
        sql::ResultSet *res;

        constexpr std::string_view exit_value{"0"};

        std::string query{};
        while (query.compare(exit_value) != 0) {
            std::cout << "What you want to query (0 to exit)?\n";
            std::cout << "Query: ";

            Inpt_validations::check_if_cin_is_correct_and_clear();
            getline(std::cin, query);

            if (!query.compare(exit_value)) {
                break;
            }

            try {
                res = stmt->executeQuery(query);
                int qtdColumns{res->getMetaData()->getColumnCount()};
                while (res->next()) {
                    for (size_t i = 1; i <= qtdColumns; i++) {
                        std::cout << res->getMetaData()->getColumnName(i) << "= ";
                        std::cout << res->getString(i) << '\n';
                    }
                    std::cout << '\n';
                }
            }
            catch (sql::SQLException &e) {
                std::cout << "\n#InvalidArgumentException\n";
                std::cout << "#ERR: " << e.what() << '\n';
                std::cout << "#CODE: " << e.getErrorCode() << '\n';
                std::cout << "#SQLState: " << e.getSQLState() << '\n';
                std::cout << "#SQLStateCStr: " << e.getSQLStateCStr() << '\n';
            }
        }
        std::cout << '\n';
    }

}

#endif