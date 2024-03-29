#include "converterjson.h"

bool ConverterJSON::LoadConfig(){
    auto config_file = std::ifstream("config.json");
    if(!config_file.is_open()){
        config_file = std::ifstream("./examples/config.json");
        if(!config_file.is_open()){
            cf.config.max_responses = 5;
            std::cerr << "config file is missing." << std::endl;
            return false;
        }
    }

    nlohmann::json conf;
    config_file >> conf;
    if(conf["config"].is_null()){
        std::cerr << "config file is empty." << std::endl;
        return false;
    }

    if(!conf["config"]["name"].is_null() && conf["config"]["name"].is_string()){
        cf.config.name = conf["config"]["name"];
    }else{
        cf.config.name = "Undefined";
    }

    if(!conf["config"]["version"].is_null() && conf["config"]["version"].is_string()) {
        cf.config.version = conf["config"]["version"];
    }else{
        cf.config.version = "1.0";
    }

    if(!conf["config"]["max_responses"].is_null() && conf["config"]["max_responses"].is_number()){
        cf.config.max_responses = conf["config"]["max_responses"];
    }else{
        cf.config.max_responses = 5;
    }

    for (const auto& f: conf["files"]) {
        cf.files.push_back(f);
    }
    config_file.close();
    return true;
}

std::vector<std::string> ConverterJSON::GetTextDocuments() const {
    auto response = std::vector<std::string>();

    for (const auto& f: cf.files) {
        auto fl = std::ifstream(f);
        std::stringstream ss;
        ss << fl.rdbuf();
        response.push_back(ss.str());
    }
    return response;
}

int ConverterJSON::GetResponsesLimit() const {
    return cf.config.max_responses;
}

bool ConverterJSON::LoadRequests() {

    auto requests_file = std::ifstream("requests.json");
    if(!requests_file.is_open()){
        requests_file = std::ifstream("./examples/requests.json");
        if(!requests_file.is_open()){
            std::cerr << "requests file is missing." << std::endl;
            return false;
        }
    }

    nlohmann::json requests;
    requests_file >> requests;

    if(requests["requests"].is_null()){
        std::cerr << "requests file is empty." << std::endl;
        return false;
    }

    for (const auto& r: requests["requests"]) {
        req.requests.push_back(r);
    }
    requests_file.close();
    return true;
}

std::vector<std::string> ConverterJSON::GetRequests() const {
    return req.requests;
}

void ConverterJSON::PutAnswers(const std::vector<std::vector<RelativeIndex>>& answers) const {

    nlohmann::json answ;
    int ind = 1;
    auto answers_file = std::ofstream("answers.json",std::ios::trunc);

    if(!answers_file.is_open()){
        std::cerr << "cannot generate a answers.json file." << std::endl;
    }

    for (const auto& a: answers) {
        nlohmann::json request;
        request["result"] = !a.empty();
        for (const auto& p: a) {
            nlohmann::json dict_pair;
            dict_pair["docid"] = p.doc_id;
            dict_pair["rank"] = p.rank;
            request["relevance"].push_back(dict_pair);
        }
        std::string name = "request00" + std::to_string(ind);
        answ[name] = request;
        ind++;
    }

    nlohmann::json file;
    file["answers"] = answ;

    answers_file << file.dump(4);
    answers_file.close();
}