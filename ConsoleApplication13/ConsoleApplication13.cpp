﻿#include <iostream>
#include <windows.h>

using namespace std;

class Vector
{
    unsigned int size = 0; // количество действительно присутствующих элементов в контейнере
    unsigned int capacity = 10; // ёмкость (вместительность, запас памяти)
    int* data = nullptr; // указатель на динамический массив целых чисел

public:
    Vector() : Vector(10)
    {
        // cout << "C-TOR WITHOUT PARAMS!\n";
    }

    Vector(unsigned int capacity)
    {
        if (capacity < 10)
        {
            capacity = 10;
        }
        this->capacity = capacity;
        data = new int[capacity];
        // cout << "C-TOR WITH PARAMS!\n";
    }

    ~Vector()
    {
        // cout << "DESTRUCTOR!\n";
        if (data != nullptr)
        {
            delete[] data;
            data = nullptr;
        }
    }

private:
    void EnsureCapacity()
    {
        if (size < capacity)
        {
            return;
        }

        capacity *= 2;

        int* temp = new int[capacity];
        for (int i = 0; i < size; i++)
        {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }

public:
    void PushBack(int value)
    {
        EnsureCapacity(); // проверка, хватит ли места для нового элемента
        data[size] = value;
        size++;
        // cout << capacity << "\n";
    }

    void PushFront(int value)
    {
        EnsureCapacity();
        for (int i = size; i > 0; i--) // i = 1
        {
            data[i] = data[i - 1]; // data[1] = data[0]
        }
        data[0] = value;
        size++;
    }

    void Clear()
    {
        size = 0;
    }

    bool IsEmpty() const
    {
        return size == 0;
    }

    void Print() const
    {
        if (IsEmpty())
        {
            cout << "Vector is empty.\n";
            return;
        }

        for (int i = 0; i < size; i++)
        {
            cout << data[i] << " ";
        }
        cout << "\n";
    }

    // Добавленные методы:
    unsigned int GetSize() const
    {
        return size;
    }

    unsigned int GetCapacity() const
    {
        return capacity;
    }

    void Insert(int value, unsigned int index)
    {
        if (index > size)
        {
            cerr << "Error: Index out of bounds.\n";
            return;
        }

        EnsureCapacity();

        for (int i = size; i > index; i--)
        {
            data[i] = data[i - 1];
        }

        data[index] = value;
        size++;
    }

    void RemoveByIndex(unsigned int index)
    {
        if (index >= size)
        {
            cerr << "Error: Index out of bounds.\n";
            return;
        }

        for (int i = index; i < size - 1; i++)
        {
            data[i] = data[i + 1];
        }

        size--;
    }

    void RemoveByValue(int value)
    {
        int* newData = new int[capacity];
        int newSize = 0;

        for (int i = 0; i < size; i++)
        {
            if (data[i] != value)
            {
                newData[newSize] = data[i];
                newSize++;
            }
        }

        delete[] data;
        data = newData;
        size = newSize;
    }

    void PopFront()
    {
        if (size > 0)
        {
            RemoveByIndex(0);
        }
    }

    void PopBack()
    {
        if (size > 0)
        {
            size--;
        }
    }
};

int main()
{
    Vector ar;

    for (int i = 0; i < 10000; i++)
    {
        ar.PushBack(rand() % 100);
        Sleep(15);
    }
}
