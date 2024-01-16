// 8.1-2.cpp : c++17


#include <iostream>
#include <map>
#include <vector>

struct Query {
    std::string column;
    std::string from;
    std::string where;
    std::map<std::string, std::string> where_map;
};

class SqlSelectQueryBuilder {
public:
    explicit SqlSelectQueryBuilder() {
    }

    std::string BuildQuery() noexcept {
        std::string query_string;
        if (query.column.empty()) query_string += "SELECT *";
        else query_string += query.column;
        query_string += query.from;
        query_string += query.where;
        query_string += ";";
        return query_string;
    }

    SqlSelectQueryBuilder& AddColumn(const std::string& col) {
        if (query.column.empty()) query.column = "SELECT " + col;
        else query.column += ", " + col;
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        for (std::string var : columns)
        {
            if (query.column.empty()) query.column = "SELECT " + var;
            else query.column += ", " + var;
        }
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& from_add) {
        query.from = " FROM " + from_add;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& variable, const std::string& value) {
        if (query.where.empty()) query.where = " WHERE " + variable + " = " + value;
        else query.where += " AND " + variable + " = " + value;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        for (const auto& [variable, value] : kv) {
            if (query.where.empty()) query.where = " WHERE " + variable + " = " + value;
            else query.where += " AND " + variable + " = " + value;
        }
        return *this;
    }

private:
    Query query;
};



int main() {
    std::map<std::string, std::string> where_map;
    where_map["id"] = "42";
    where_map["name"] = "John";

    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumns({ "name","phone" });
    query_builder.AddFrom("students");
    query_builder.AddWhere(where_map);

    std::cout << query_builder.BuildQuery();
}