#include <iostream>
#include "TransferQueue.h"
#include "fmt/core.h"

int main()
{
    fmt::println("Tranfer Queue");

    TransferQueue tfQ1;
    TransferQueue tfQ2;

    tfQ2 = tfQ1;

    return 0;
}