#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <string>

// === ОБЩИЙ ШАБЛОН КЛАССА ===
template <typename CharType>
class CustomString {
private:
    std::vector<CharType> content;
    CharType delimiter;

public:
    // Конструктор
    CustomString(CharType delim) : delimiter(delim) {}

    // Метод изменения разделителя
    void set_delimiter(CharType delim) {
        delimiter = delim;
    }

    CharType get_delimiter() const {
        return delimiter;
    }

    // Длина строки
    size_t length() const {
        return content.size();
    }

    // Доступ по квадратным скобкам с валидацией индекса
    CharType& operator[](size_t index) {
        if (index >= content.size()) {
            throw std::out_of_range("Ошибка: Индекс за пределами строки!");
        }
        return content[index];
    }

    const CharType& operator[](size_t index) const {
        if (index >= content.size()) {
            throw std::out_of_range("Ошибка: Индекс за пределами строки!");
        }
        return content[index];
    }

    // Удаление символа по индексу
    void remove_at(size_t index) {
        if (index >= content.size()) {
            throw std::out_of_range("Ошибка удаления: Некорректный индекс!");
        }
        content.erase(content.begin() + index);
    }

    // Метод конкатенации с добавлением разделителя между строками
    CustomString<CharType> concatenate(const CustomString<CharType>& other) const {
        CustomString<CharType> result(delimiter);
        result.content = this->content;
        if (!this->content.empty() && !other.content.empty()) {
            result.content.push_back(delimiter);
        }
        for (const auto& ch : other.content) {
            result.content.push_back(ch);
        }
        return result;
    }

    // Слияние символов (добавление массива символов в строку)
    void merge_tokens(const std::vector<CharType>& tokens) {
        for (const auto& token : tokens) {
            content.push_back(token);
        }
    }

    // Ввод и вывод из консоли
    friend std::ostream& operator<<(std::ostream& os, const CustomString<CharType>& cs) {
        for (const auto& ch : cs.content) {
            os << ch;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, CustomString<CharType>& cs) {
        size_t count;
        std::cout << "Количество вводимых символов: ";
        if (!(is >> count)) {
            throw std::invalid_argument("Ошибка ввода количества элементов.");
        }
        cs.content.resize(count);
        std::cout << "Введите " << count << " символов:\n";
        for (size_t i = 0; i < count; ++i) {
            is >> cs.content[i];
        }
        return is;
    }

    // Работа с текстовыми файлами
    void save_to_file(const std::string& filename) const {
        std::ofstream out(filename);
        if (!out.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
        }
        for (const auto& ch : content) {
            out << ch << " ";
        }
        out.close();
    }

    void load_from_file(const std::string& filename) {
        std::ifstream in(filename);
        if (!in.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для чтения: " + filename);
        }
        content.clear();
        CharType ch;
        while (in >> ch) {
            content.push_back(ch);
        }
        in.close();
    }
};

// === ПОЛНАЯ СПЕЦИАЛИЗАЦИЯ ДЛЯ ТИПА CHAR ===
template <>
class CustomString<char> {
private:
    std::string content;
    char delimiter;

public:
    CustomString(char delim = ' ') : content(""), delimiter(delim) {}

    void set_delimiter(char delim) { delimiter = delim; }
    char get_delimiter() const { return delimiter; }
    size_t length() const { return content.length(); }

    char& operator[](size_t index) {
        if (index >= content.length()) throw std::out_of_range("Индекс за пределами!");
        return content[index];
    }

    void remove_at(size_t index) {
        if (index >= content.length()) throw std::out_of_range("Некорректный индекс!");
        content.erase(content.begin() + index);
    }

    CustomString<char> concatenate(const CustomString<char>& other) const {
        CustomString<char> result(delimiter);
        if (this->content.empty()) result.content = other.content;
        else if (other.content.empty()) result.content = this->content;
        else result.content = this->content + delimiter + other.content;
        return result;
    }

    void merge_tokens(const std::vector<char>& tokens) {
        for (char ch : tokens) content.push_back(ch);
    }

    friend std::ostream& operator<<(std::ostream& os, const CustomString<char>& cs) {
        os << cs.content;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, CustomString<char>& cs) {
        std::cout << "Введите строку: ";
        is >> cs.content;
        return is;
    }

    void save_to_file(const std::string& filename) const {
        std::ofstream out(filename);
        if (!out.is_open()) throw std::runtime_error("Файл не открыт!");
        out << content;
        out.close();
    }

    void load_from_file(const std::string& filename) {
        std::ifstream in(filename);
        if (!in.is_open()) throw std::runtime_error("Файл не найден!");
        in >> content;
        in.close();
    }
};

int main() {
    try {
        std::cout << "--- ТЕСТ 1: Специализация для стандартного char ---\n";
        CustomString<char> str1(',');
        std::cin >> str1;

        CustomString<char> str2(',');
        std::cin >> str2;

        CustomString<char> concat_str = str1.concatenate(str2);
        std::cout << "Результат конкатенации: " << concat_str << "\n";
        std::cout << "Длина строки: " << concat_str.length() << "\n";

        std::cout << "\n--- ТЕСТ 2: Общий шаблон для типа int (коды символов) ---\n";
        CustomString<int> int_str(0); // разделитель 0
        std::vector<int> tokens = {65, 66, 67, 68}; // Буквы A, B, C, D
        int_str.merge_tokens(tokens);
        
        std::cout << "Строка int_str: " << int_str << "\n";
        int_str.remove_at(1); // Удаляем 66 (второй элемент)
        std::cout << "После удаления индекса 1: " << int_str << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Перехвачено исключение: " << e.what() << std::endl;
    }

    return 0;
}
