#include "fmt/core.h"
#include "basic.h"

int main()
{
    fmt::println("================== Start Concurrency ================== ");

    fmt::println("++++++++++++ testConcurrancyRaceCondition ++++++++++++");
    for (int i=0; i < 5; i++)
    {
        testConcurrancyRaceCondition();
    }

    fmt::println("\n\n++++++++++++ testConcurrancyRaceConditionAtomic ++++++++++++");
    for (int i=0; i < 5; i++)
    {
        testConcurrancyRaceConditionAtomic();
    }

    fmt::println("\n\n++++++++++++ testConcurrancyRaceConditionMutex ++++++++++++");
    for (int i=0; i < 5; i++)
    {
        testConcurrancyRaceConditionAtomic();
    }
}