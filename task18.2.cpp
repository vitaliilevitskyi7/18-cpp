#include <iostream>
#include <stack>

namespace MyNamespace {
    // Власний шаблон класу Стек на основі динамічних вузлів
    template <typename T>
    class Stack {
    private:
        struct Node {
            T data;
            Node* next;
            Node(const T& val, Node* n = nullptr) : data(val), next(n) {}
        };
        Node* topNode;

    public:
        Stack() : topNode(nullptr) {}

        ~Stack() {
            while (!empty()) pop();
        }

        bool empty() const { return topNode == nullptr; }

        void push(const T& val) {
            topNode = new Node(val, topNode);
        }

        void pop() {
            if (empty()) return;
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }

        T top() const {
            if (empty()) throw std::runtime_error("Стек порожній!");
            return topNode->data;
        }
    };

    // Функція введення чисел до першого 0 з використанням нашого Стеку
    int read_until_zero(int*& result_array) {
        Stack<int> temp_stack;
        int num;
        int count = 0;

        std::cout << "Введіть цілі числа (0 - кінець введення):\n";
        while (std::cin >> num && num != 0) {
            temp_stack.push(num);
            count++;
        }

        // Виділяємо пам'ять під масив результату через покажчик-аргумент
        result_array = new int[count];
        
        // Оскільки стек повертає числа у зворотному порядку, заповнюємо масив з кінця
        // або з початку, залежно від бажаного збереження порядку. Заповнимо з кінця:
        MyNamespace::Stack<int> invert_stack;
        while (!temp_stack.empty()) {
            invert_stack.push(temp_stack.top());
            temp_stack.pop();
        }

        for (int i = 0; i < count; ++i) {
            result_array[i] = invert_stack.top();
            invert_stack.pop();
        }

        return count;
    }
}

int main() {
    int* my_array = nullptr;
    
    // Виклик функції з використанням власного динамічного стеку
    int size = MyNamespace::read_until_zero(my_array);

    std::cout << "\nОтриманий масив через динамічний Стек (елементів: " << size << "):\n";
    for (int i = 0; i < size; ++i) {
        std::cout << my_array[i] << " ";
    }
    std::cout << "\n\n";

    // ПЕРЕВІРКА РОБОТИ ЗА ДОПОМОГОЮ СТАНДАРТНОГО КЛАСУ std::stack (для типу double)
    std::cout << "--- Перевірка роботи стандартного std::stack<double> ---\n";
    std::stack<double> std_s;
    
    std_s.push(1.1);
    std_s.push(2.2);
    std_s.push(3.3);

    std::cout << "Елементи зі стандартного std::stack (LIFO порядок): ";
    while (!std_s.empty()) {
        std::cout << std_s.top() << " ";
        std_s.pop();
    }
    std::cout << "\n";

    delete[] my_array; // Звільнення пам'яті виділеного динамічного масиву
    return 0;
}
