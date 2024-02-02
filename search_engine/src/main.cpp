#include <iostream>
#include "converterjson.h"

//#include "gtest/gtest.h"
//TEST(sample_test_case, sample_test)
//{
//    EXPECT_EQ(1, 1);
//}

int main() {
    int a = ConverterJSON::GetResponsesLimit();
    std::cout << a << std::endl;
    return 0;
}
