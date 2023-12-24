struct DBConfiguration {
    string_view db_name;
    int db_connection_timeout;
    bool db_allow_exceptions;
    DBLogLevel db_log_level;
};
struct PersonData {
    int min_age;
    int max_age;
    string_view name_filter;
};

DBHandler ConnectDatabase(DBConfiguration config)
{
    DBConnector connector(config.db_allow_exceptions, config.db_log_level);
    DBHandler db;
    if (config.db_name.starts_with("tmp."s)) {
        db = connector.ConnectTmp(config.db_name, config.db_connection_timeout);
    }
    else {
        db = connector.Connect(config.db_name, config.db_connection_timeout);
    }
    if (!config.db_allow_exceptions && !db.IsOK()) {
        return {};
    }
    return db;
}

vector<Person> LoadPersons( PersonData person, DBHandler db) {

    
    ostringstream query_str;
    query_str << "from Persons "s
        << "select Name, Age "s
        << "where Age between "s << person.min_age << " and "s << person.max_age << " "s
        << "and Name like '%"s << db.Quote(person.name_filter) << "%'"s;
    DBQuery query(query_str.str());

    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({ move(name), age });
    }
    return persons;
}
