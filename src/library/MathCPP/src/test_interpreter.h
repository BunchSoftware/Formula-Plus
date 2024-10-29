#include <iostream>

namespace TestInterpreter 
{
    typedef double numeric_type;
    typedef std::pair<std::string, numeric_type> test_t;

    static const test_t globalTestList[] =
    {
        test_t("1",1.0),
        test_t("2",2.0),
        test_t("3",3.0),
        test_t("4",4.0),
        test_t("5",5.0),
        test_t("6",6.0),
        test_t("7",7.0),
        test_t("8",8.0),
        test_t("9",9.0),
    };


    class Tester {
    public:
        static inline void Test()
        {
            static const std::size_t testListSize = sizeof(globalTestList) / sizeof(test_t);
            for (int i = 0; i < testListSize; i++)
            {
                std::wstring text(globalTestList[i].first.begin(), globalTestList[i].first.end());
                double result = 0;
                if (std::round(result * 10000) / 10000 != std::round(globalTestList[i].second * 10000) / 10000)
                    throw std::logic_error("Ошибка в тесте: " + globalTestList[i].first);
            }
        }
    };
}