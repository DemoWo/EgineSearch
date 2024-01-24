#include <vector>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H

class ConverterJSON {
public:
    ConverterJSON() = default;
/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json
*/
    static std::vector<std::string> GetTextDocuments();
/**
* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return
*/
    static int GetResponsesLimit();
/**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
    static std::vector<std::string> GetRequests();
/**
* Положить в файл answers.json результаты поисковых запросов
*/
    static void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
};
#endif //SEARCH_ENGINE_CONVERTERJSON_H