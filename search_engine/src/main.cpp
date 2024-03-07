#include <iostream>
#include "converterjson.h"
#include "InvertedIndex.h"

//#include "gtest/gtest.h"
//TEST(sample_test_case, sample_test)
//{
//    EXPECT_EQ(1, 1);
//}

int main() {
    auto converterJSON = ConverterJSON();
    auto invertedIndex = InvertedIndex();

    if(!converterJSON.LoadConfig()){
        return 1;
    }

    if(!converterJSON.LoadRequests()){
        return 1;
    }

    std::cout << converterJSON.cf.config.name << ((converterJSON.cf.config.version.empty())? "" : " version: ") << converterJSON.cf.config.version << std::endl;
    int max_responses = converterJSON.cf.config.max_responses;
    auto texts = converterJSON.GetTextDocuments();
    invertedIndex.UpdateDocumentBase(texts);
    SearchServer srv(invertedIndex);
    auto result = srv.search(converterJSON.GetRequests(), max_responses);
    converterJSON.PutAnswers(result);

    std::cout << "The search has been completed";
    std::cin.get();

    return 0;
}
