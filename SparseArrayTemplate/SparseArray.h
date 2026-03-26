#pragma once

#include <list>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <utility>
#include <string>

template <typename T>
struct SparseElement
{
    std::size_t logicalIndex{};
    T value{};

    SparseElement() = default;
    SparseElement(std::size_t index, const T& val) : logicalIndex(index), value(val) {}
};

template <typename T>
class SparseArray
{
private:
    std::size_t logicalSize;
    std::list<SparseElement<T>> physicalData;

    typename std::list<SparseElement<T>>::iterator findElement(std::size_t index)
    {
        for (auto it = physicalData.begin(); it != physicalData.end(); ++it)
        {
            if (it->logicalIndex == index)
            {
                return it;
            }
        }
        return physicalData.end();
    }

    typename std::list<SparseElement<T>>::const_iterator findElement(std::size_t index) const
    {
        for (auto it = physicalData.begin(); it != physicalData.end(); ++it)
        {
            if (it->logicalIndex == index)
            {
                return it;
            }
        }
        return physicalData.end();
    }

public:
    SparseArray() : logicalSize(0) {}

    explicit SparseArray(std::size_t size) : logicalSize(size) {}

    SparseArray(const SparseArray& other) = default;

    SparseArray& operator=(const SparseArray& other) = default;

    std::size_t size() const
    {
        return logicalSize;
    }

    std::size_t storedCount() const
    {
        return physicalData.size();
    }

    T& operator[](std::size_t index)
    {
        if (index >= logicalSize)
        {
            throw std::out_of_range("Index is outside the logical size of the sparse array.");
        }

        auto it = findElement(index);
        if (it != physicalData.end())
        {
            return it->value;
        }

        auto insertPos = physicalData.begin();
        while (insertPos != physicalData.end() && insertPos->logicalIndex < index)
        {
            ++insertPos;
        }

        auto inserted = physicalData.insert(insertPos, SparseElement<T>(index, T{}));
        return inserted->value;
    }

    const T& at(std::size_t index) const
    {
        if (index >= logicalSize)
        {
            throw std::out_of_range("Index is outside the logical size of the sparse array.");
        }

        auto it = findElement(index);
        if (it == physicalData.end())
        {
            throw std::runtime_error("Element with this logical index is not stored physically.");
        }

        return it->value;
    }

    bool contains(std::size_t index) const
    {
        if (index >= logicalSize)
        {
            throw std::out_of_range("Index is outside the logical size of the sparse array.");
        }

        return findElement(index) != physicalData.end();
    }

    void show(const std::string& title) const
    {
        std::cout << "\n" << title << "\n";
        std::cout << "Logical size: " << logicalSize << "\n";
        std::cout << "Stored elements: " << physicalData.size() << "\n";

        if (physicalData.empty())
        {
            std::cout << "[no stored elements]\n";
            return;
        }

        std::cout << std::left << std::setw(18) << "Logical index" << "Value\n";
        std::cout << std::string(32, '-') << "\n";

        for (const auto& element : physicalData)
        {
            std::cout << std::left << std::setw(18) << element.logicalIndex << element.value << "\n";
        }
    }
};
