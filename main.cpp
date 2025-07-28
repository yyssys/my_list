#include <iostream>
#include "list.h"

int main(int argc, char const *argv[])
{
    List<int> numbers;
    numbers.push_back(100);
    numbers.push_back(200);
    numbers.push_back(300);
    numbers.push_front(50);
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    auto it = numbers.begin();
    ++it;
    numbers.insert(it, 150);
    numbers.insert(it, 200);

    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    auto end = numbers.end();
    --end;
    --end;
    auto test = numbers.erase(end);
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    numbers.remove(200);
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    numbers.pop_front();
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    numbers.pop_back();
    for (auto it = numbers.begin(); it != numbers.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}
