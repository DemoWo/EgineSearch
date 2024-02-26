#ifndef CONVERTERJSON_H
#define CONVERTERJSON_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"
#include "SearchServer.h"

/**
* Структура для хранения параметров из фала config.json
*/
struct config_json {
    struct {
        std::string name;
        std::string version;
        int max_responses;
    } config;
    std::vector<std::string> files;
};

/**
* Структура для хранения параметров из фала request.json
*/
struct request_json {
    std::vector<std::string> requests;
};

/**
* Структура для хранения реливантности документов
*/
struct relevance_json {
    int docid;
    float rank;
};

/**
* Класс для работы с JSON-файлами
*/
class ConverterJSON {
public:
    config_json cf;
    request_json req;

    ConverterJSON() = default;

    /**
    * Метод для проверки загрузки и содержимого файла config.json
    * @return Возвращает значение true или false
    */
    bool LoadConfig();

    /**
    * Метод для проверки загрузки и содержимого файла requests.json
    * @return Возвращает значение true или false
    */
    bool LoadRequests();

    /**
    * Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных
    * в config.json
    */
    std::vector<std::string> GetTextDocuments() const;

    /**
    * Метод считывает поле max_responses для определения предельного
    * количества ответов на один запрос
    * @return
    */
    int GetResponsesLimit() const;

    /**
    * Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json
    */
    std::vector<std::string> GetRequests() const;

    /**
    * Положить в файл answers.json результаты поисковых запросов
    */
    void PutAnswers(const std::vector<std::vector<RelativeIndex>>&
    answers) const;
};

#endif // CONVERTERJSON_H