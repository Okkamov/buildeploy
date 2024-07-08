#include "../include/list.hpp"
#include <fmt/core.h>
#include <fmt/format.h>
#include <zlib.h>
//#include <iostream>

int main(int, char**) {
    fmt::print("Hello for GitHub Actions!\n\n\n");
    fmt::print("FMT version is {}\n\n",
               "ZLIB version is {}\n", 
               FMT_VERSION, ZLIB_VERSION);

    const size_t count = 6;

    otus::List<size_t> list;
    for (size_t i = 0; i < count; ++i) {
        list.push_back(i);
        list.push_front(i);
    }

    for (size_t i = 0; i < count * 2; ++i) {
        fmt::print(fmt::format("Pushed into list {}\n",list.front()));
        //std::cout << list.front() << ' ';
        list.pop_front();
    }
//    std::cout << std::endl;

    return 0;
}
