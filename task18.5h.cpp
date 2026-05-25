#include <iostream>
#include <vector>
#include <string>

namespace MyNamespace {
    
    // Шаблон класу Масив
    template <typename T>
    class Array {
    private:
        T* data;      // Динамічний масив для збереження елементів
        int size;     // Поточний розмір масиву

    public:
        // Конструктор
        Array(int n) : size(n) {
            data = new T[size];
        }

        // Деструктор для запобігання витокам пам'яті
        ~Array() {
            delete[] data;
        }

        // Метод для встановлення значення елемента за індексом
        void set(int index, const T& value) {
            if (index >= 0 && index < size) {
                data[index] = value;
            }
        }

        // Метод для отримання значення елемента за індексом
        T get(int index) const {
            if (index >= 0 && index < size) {
                return data[index];
            }
            throw std::out_of_range("Індекс поза межами масиву");
        }

        int get_size() const { return size; }

        // Функція виведення масиву
        void print() const {
            for (int i = 0; i < size; ++i) {
                std::cout << data[i] << " ";
            }
            std::cout << "\n";
        }

        // Варіант г) Сортування вставками як метод самого масиву (inplace)
        void sort_insertion_inplace() {
            for (int i = 1; i < size; ++i) {
                T key = data[i];
                int j = i - 1;

                // Зсуваємо елементи, які більші за key, на одну позицію вперед
                while (j >= 0 && data[j] > key) {
                    data[j + 1] = data[j];
                    j = j - 1;
                }
                data[j + 1] = key;
            }
        }

        // Варіант г) Сортування вставками як статичний метод (приймає вказівник та розмір)
        static void sort_insertion_static(T* arr, int n) {
            for (int i = 1; i < n; ++i) {
                T key = arr[i];
                int j = i - 1;

                while (j >= 0 && arr[j] > key) {
                    arr[j + 1] = arr[j];
                    j = j - 1;
                }
                arr[j + 1] = key;
            }
        }
    };
}

int main() {
    std::cout << "--- ТЕСТ 1: Сортування вставками як метод класу (inplace) ---\n";
    int n1 = 6;
    MyNamespace::Array<double> double_arr(n1);
    double_arr.set(0, 4.3);
    double_arr.set(1, 1.2);
    double_arr.set(2, 8.9);
    double_arr.set(3, 3.1);
    double_arr.set(4, 5.5);
    double_arr.set(5, 2.0);

    std::cout << "Початковий масив: ";
    double_arr.print();

    // Виклик методу inplace
    double_arr.sort_insertion_inplace();

    std::cout << "Відсортований масив: ";
    double_arr.print();


    std::cout << "\n--- ТЕСТ 2: Статичний метод сортування для стандартного масиву рядків ---\n";
    int n2 = 4;
    std::string string_raw_arr[] = {"Груша", "Яблуко", "Абрикос", "Банан"};

    std::cout << "Початковий сирий масив: ";
    for(int i = 0; i < n2; ++i) std::cout << string_raw_arr[i] << " ";
    std::cout << "\n";

    // Виклик статичного методу шаблону класу
    MyNamespace::Array<std::string>::sort_insertion_static(string_raw_arr, n2);

    std::cout << "Відсортований сирий масив: ";
    for(int i = 0; i < n2; ++i) std::cout << string_raw_arr[i] << " ";
    std::cout << "\n";

    return 0;
}
