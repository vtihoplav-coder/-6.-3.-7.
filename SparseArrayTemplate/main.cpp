#include <iostream>
#include <iomanip>
#include <limits>
#include "SparseArray.h"

template <typename T>
void demoSparseArray(const std::string& title, const T& a, const T& b, const T& c)
{
    SparseArray<T> arr(20);

    arr[2] = a;
    arr[7] = b;
    arr[15] = c;

    arr.show(title);

    std::cout << "Contains element 7? " << (arr.contains(7) ? "yes" : "no") << "\n";
    std::cout << "Element [7] = " << arr[7] << "\n";

    SparseArray<T> copied(arr);
    copied[7] = static_cast<T>(copied[7] + copied[7]);

    copied.show(title + " (copy constructor demo)");

    SparseArray<T> assigned;
    assigned = arr;
    assigned.show(title + " (assignment operator demo)");
}

int main()
{
    try
    {
        std::cout << "Template sparse one-dimensional array demo\n";
        std::cout << "-----------------------------------------\n";

        demoSparseArray<int>("SparseArray<int>", 10, 25, 90);
        demoSparseArray<float>("SparseArray<float>", 1.5f, 2.75f, 8.25f);
        demoSparseArray<double>("SparseArray<double>", 3.14159, 12.5, 99.875);

        SparseArray<int> test(5);
        test[0] = 111;
        test[4] = 999;
        test.show("Extra check: edge logical indices");

        std::cout << "\nProgram completed successfully.\n";
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
