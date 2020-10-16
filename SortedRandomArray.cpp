#include <iostream>
#include <ctime>
#include <iomanip>
#include <stdlib.h>



 /*ДОМАШНЕЕ ЗАДАНИЕ:
  Задание 3: SortedRandomArray
  + В конструкторе укажите количество элементов массива и функтор для
  определения критерия сортировки
  + Напишите два класса для функторов которые будут определять, как именно
  будут отсортированы рандомные числа внутри SortedRandomArray
  (от большего к меньшему или наоборот)
  + Реализуйте конструкторы копирования и перемещения
  + Реализуйте операторы присваивания копированием и перемещением
  + Реализуйте деструктор
  + Реализуйте дружественный оператор вывода для SortedRandomArray*/

class Down {
public:
    bool operator() (const int left, const int right) {
        return left < right;
    }
};

class Up {
public:
    bool operator() (const int left, const int right) {
        return left > right;
    }
};

class FixedRandomArray
{
public:
    FixedRandomArray() {
        m_count++;
    }

    void operator()(Down a) {
        for (int i = 0; i < m_index; i++) {
            for (int j = i + 1; j < m_index; j++) {
                if (a(m_arr[i], m_arr[j])) {
                    std::swap(m_arr[i], m_arr[j]);
                }
            }
        }
    }

    void operator()(Up a) {
        for (int i = 0; i < m_index; i++) {
            for (int j = i + 1; j < m_index; j++) {
                if (a(m_arr[i], m_arr[j])) {
                    std::swap(m_arr[i], m_arr[j]);
                }
            }
        }
    }

    FixedRandomArray(const int sizeArr) {
        m_arr = new int[sizeArr];
        regenerationArr(sizeArr);
        m_count++;
    }

    FixedRandomArray(const FixedRandomArray& other) {
        m_index = other.m_index;
        m_sizeArr = other.m_sizeArr;
        m_capacity = other.m_capacity;
        m_arr = new int[m_sizeArr];

        for (int i = 0; i < m_sizeArr; i++)
            m_arr[i] = other.m_arr[i];
    }

    /*FixedRandomArray(FixedRandomArray&& other)
    {
        m_index = other.m_index;
        m_sizeArr = other.m_sizeArr;
        m_capacity = other.m_capacity;
        m_arr = other.m_arr;
        other.m_arr = nullptr;
    }*/

    FixedRandomArray& operator=(const FixedRandomArray& other)
    {
        m_index = other.m_index;
        m_sizeArr = other.m_sizeArr;
        m_capacity = other.m_capacity;
        m_arr = new int[m_sizeArr];

        for (int i = 0; i < m_sizeArr; i++)
            m_arr[i] = other.m_arr[i];

        return *this;
    }

    /*FixedRandomArray& operator=(const FixedRandomArray&& other)
    {
        m_index = other.m_index;
        m_sizeArr = other.m_sizeArr;
        m_capacity = other.m_capacity;
        m_arr= other.m_arr;

        return *this;
    }*/

    ~FixedRandomArray() {
        delete[] m_arr;
    }

    int countSizeArr() const {
        return m_sizeArr;
    }

    int getCountIndex() const {
        return m_index;
    }

    int sizeRezerv() const {
        return (m_sizeArr - m_index);
    }

    int getElement(const int number) const {
        return m_arr[number];
    }

    void reSize(const int size, const int number = 0) {
        capacityRegulator(size, number);
    }

    void regenerationArr(const int sizeArr) {
        capacityRegulator(sizeArr);

        m_index = sizeArr;

        for (int i = 0; i < m_index; i++)
            m_arr[i] = rand() % 11;

    }

    void mixArray() {
        for (int i = m_index - 1; i >= 1; i--) {
            int j = rand() % (i + 1);

            std::swap(m_arr[i], m_arr[j]);
        }
    }

    static int getCount() {
        return m_count;
    }

private:

    void capacityUp(const int sizeArr, int number = 0) {

        while (sizeArr > m_sizeArr) {
            m_sizeArr += m_capacity;
        }

        int* tmp = new int[m_sizeArr];

        for (int i = 0; i < m_index; i++) {
            tmp[i] = m_arr[i];
        }

        for (int i = m_index; i < sizeArr; i++) {
            tmp[i] = number;
        }

        m_index = sizeArr;
        delete[] m_arr;
        m_arr = tmp;
    }


    void capacityRegulator(const int sizeArr, int number = 0) {
        if (sizeArr > m_sizeArr) {
            capacityUp(sizeArr, number);
        }
        else if (sizeArr < (m_sizeArr - m_capacity)) {
            capacityDown(sizeArr);
        }
        else {
            int* tmp = new int[m_sizeArr];

            for (int i = 0; i < m_index; i++) tmp[i] = m_arr[i];

            for (int i = m_index; i < sizeArr; i++) tmp[i] = number;

            m_index = sizeArr;
            delete[] m_arr;
            m_arr = tmp;
        }
    }


    void capacityDown(const int sizeArr)
    {
        while (true) {
            if ((m_sizeArr - m_capacity) >= sizeArr) {
                m_sizeArr -= m_capacity;
            }
            else {
                break;
            }
        }
        m_index = sizeArr;
        int* tmp = new int[m_sizeArr];
        for (size_t i = 0; i < m_index; i++)tmp[i] = m_arr[i];

        delete[] m_arr;
        m_arr = tmp;
    }

    friend std::ostream& operator<<(std::ostream& os, FixedRandomArray& n);
    static  int m_count;
    int m_sizeArr = 5;
    int m_capacity = 5;
    int m_index = 0;
    int* m_arr = new int[m_sizeArr];
};

int FixedRandomArray::m_count = 0;

std::ostream& operator<<(std::ostream& os, FixedRandomArray& arr)
{
    if (arr.m_index) {
        os << "\nArrar # " << arr.m_count << "\n__________________\n                  |\n";
        for (size_t i = 0; i < arr.m_index; i++) {
            os << " arr["
                << std::right << std::setw(2) << std::setfill(' ') << i << "]  = "
                << std::right << std::setw(5) << arr.m_arr[i] << " |\n";
        }
        os << "__________________|\n\nAll size arr   =  " << arr.m_sizeArr << "\nUsed size      =  " << arr.m_index
            << "\nReserved size  =  " << (arr.m_sizeArr - arr.m_index) << "\n\n\n";
    }
    else {
        os << "\nNo data!!\n\n";
    }
    return os;
}


int main() {

    srand(time(nullptr));

    FixedRandomArray arr(9);
    Down a;
    Up b;
    arr(a);
    std::cout << arr;
    arr(b);
    std::cout << arr;

}