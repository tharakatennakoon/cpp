#include <iostream>
#include "TransferQueue.h"

int main()
{
    std::cout << "Tranfer Queue" << std::endl;

    TransferQueue tfQ1;
    TransferQueue tfQ2;

    tfQ2 = tfQ1;

    return 0;
}