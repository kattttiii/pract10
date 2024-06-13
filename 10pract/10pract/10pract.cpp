#include <iostream>  // Подключение стандартных библиотек
#include <thread>     // для работы с потоками
#include <vector>     // для работы с векторами
#include <algorithm>  // для использования алгоритмов

class MergeSort {
public:
    void Sort(std::vector<int>& arr) {  // Функция сортировки массива методом слияния
        if (arr.size() <= 1) return;    // Если размер массива меньше или равен 1, возврат

        int mid = arr.size() / 2;  // Находим середину массива
        std::vector<int> left(arr.begin(), arr.begin() + mid); // Создаем левую половину массива
        std::vector<int> right(arr.begin() + mid, arr.end());  // Создаем правую половину массива

        Sort(left);  // Рекурсивно сортируем левую половину
        Sort(right); // Рекурсивно сортируем правую половину

        Merge(arr, left, right);  // Выполняем слияние двух отсортированных массивов
    }

private:
    void Merge(std::vector<int>& arr, std::vector<int>& left, std::vector<int>& right) {
        int i = 0, j = 0, k = 0;  // Индексы для исходного массива и двух сливаемых
        while (i < left.size() && j < right.size()) {  // Пока не кончилась хотя бы одна из половин
            if (left[i] < right[j]) {
                arr[k++] = left[i++];  // Выбираем минимальный элемент и увеличиваем соответствующий индекс
            }
            else {
                arr[k++] = right[j++]; // Выбираем минимальный элемент и увеличиваем соответствующий индекс
            }
        }
        while (i < left.size()) {   // Дозапись всех элементов из левого массива, если остались
            arr[k++] = left[i++];
        }
        while (j < right.size()) {  // Дозапись всех элементов из правого массива, если остались
            arr[k++] = right[j++];
        }
    }
};

int main() {
    std::vector<int> arr(10);  // Создание вектора для хранения 10 чисел
    std::cout << "Enter 10 integers: ";  // Просьба ввести 10 чисел
    for (int& i : arr) {
        std::cin >> i;  // Ввод 10 чисел пользователем
    }

    MergeSort sorter;  // Создание объекта для сортировки
    std::thread t(&MergeSort::Sort, &sorter, std::ref(arr)); {  // Создание потока для выполнения сортировки
        sorter.Sort(arr);  // Вызов функции сортировки
    }

    t.join();  // Ожидание завершения потока

    std::cout << "Sorted array: ";  // Вывод отсортированного массива
    for (int i : arr) {
        std::cout << i << " ";  // Печать каждого элемента
    }
    std::cout << std::endl;  // Переход на новую строку

    return 0;  // Возвращение успешного завершения программы
}