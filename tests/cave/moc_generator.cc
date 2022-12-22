#include "moc_generator.h"
#include <iostream>

int MocRandomGenerator::GetRandomPercent() {
    static int num = 50;
    static int even_call = 0;
    if (even_call % 2 == 0) {
        num += 1;
    } else {
        num -=1;
    }
    even_call += 1;
    return num;
}
