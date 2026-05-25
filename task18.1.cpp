#include <iostream>
#include <string>
#include <numeric>
#include <cmath>

namespace MyNamespace {
    // Шаблонна функція для пошуку максимуму двох чисел
    template <typename T>
    T get_max(const T& a, const T& b) {
        return (a > b) ? a : b;
    }

    // Клас Раціональний дріб із попередніх тем
    class Rational {
    private:
        int nominator;
        unsigned int denominator;

        void reduce() {
            if (nominator == 0) { denominator = 1; return; }
            unsigned int g = std::gcd(std::abs(nominator), denominator);
            nominator /= static_cast<int>(g);
            denominator /= g;
        }

    public:
        Rational(int nom = 0, int denom = 1) : nominator(nom), denominator(denom) {
            if (denom < 0) {
                nominator = -nom;
                denominator = static_cast<unsigned int>(-denom);
            }
            reduce();
        }

        // КРИТИЧНО НЕОБХІДНИЙ ОПЕРАТОР, щоб шаблон функцій працював з цим класом
        bool operator>(const Rational& other) const {
            return 1LL * nominator * other.denominator > 1LL * other.nominator * denominator;
        }

        friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
            os << r.nominator << "/" << r.denominator;
            return os;
        }
    };
}

int main() {
    // 1. Тест для стандартних числових типів
    std::cout << "Максимум int: " << MyNamespace::get_max(10, 25) << "\n";
    std::cout << "Максимум double: " << MyNamespace::get_max(45.7, 12.3) << "\n";

    // 2. Тест для рядків (працює за лексикографічним порядком)
    std::string s1 = "Apple", s2 = "Banana";
    std::cout << "Максимум string: " << MyNamespace::get_max(s1, s2) << "\n";

    // 3. Тест для власного класу Раціональний дріб
    MyNamespace::Rational r1(1, 2); // 1/2
    MyNamespace::Rational r2(3, 4); // 3/4
    std::cout << "Максимум Rational: " << MyNamespace::get_max(r1, r2) << "\n";

    return 0;
}
