#include <iostream>
#include <string>
#include <cmath>
#include <clocale>

class Money {
private:
    long hryvnia;
    unsigned char kopeck;

public:
    // Конструктори з Лаби 3
    Money() {
        hryvnia = 0;
        kopeck = 0;
    }

    Money(long h, int k) {
        if (k >= 0 && k < 100 && h >= 0) {
            hryvnia = h;
            kopeck = static_cast<unsigned char>(k);
        } else {
            hryvnia = 0;
            kopeck = 0;
        }
    }

    Money(const Money& other) {
        hryvnia = other.hryvnia;
        kopeck = other.kopeck;
    }

    ~Money() {}

    bool Init(long h, int k) {
        if (k >= 0 && k < 100 && h >= 0) {
            hryvnia = h;
            kopeck = static_cast<unsigned char>(k);
            return true;
        }
        return false;
    }

    void Read() {
        long h;
        int k;
        do {
            std::cout << "Введіть гривні: ";
            std::cin >> h;
            std::cout << "Введіть копійки (0-99): ";
            std::cin >> k;
            if (Init(h, k)) break;
            std::cout << "Помилка введення! Спробуйте ще раз.\n";
        } while (true);
    }

    std::string toString() const {
        std::string kopStr = std::to_string(static_cast<int>(kopeck));
        if (kopStr.length() == 1) {
            kopStr = "0" + kopStr;
        }
        return std::to_string(hryvnia) + "," + kopStr;
    }

    void Display() const {
        std::cout << toString() << " грн" << std::endl;
    }

    // ========================================================
    // ПЕРЕВАНТАЖЕННЯ ОПЕРАЦІЙ ДЛЯ ЛАБОРАТОРНОЇ №4
    // ========================================================

    // 1. Перевантаження оператора + (додавання)
    Money operator+(const Money& other) const {
        long totalKop = (hryvnia + other.hryvnia) * 100 + static_cast<int>(kopeck) + static_cast<int>(other.kopeck);
        return Money(totalKop / 100, totalKop % 100);
    }

    // 2. Перевантаження оператора - (віднімання)
    Money operator-(const Money& other) const {
        long long kop1 = hryvnia * 100 + static_cast<int>(kopeck);
        long long kop2 = other.hryvnia * 100 + static_cast<int>(other.kopeck);
        long long diff = kop1 - kop2;
        if (diff < 0) {
            std::cout << "Помилка: результат віднімання від'ємний!\n";
            return Money();
        } else {
            return Money(diff / 100, diff % 100);
        }
    }

    // 3. Перевантаження оператора == (рівність)
    bool operator==(const Money& other) const {
        return (hryvnia == other.hryvnia && kopeck == other.kopeck);
    }

    // 4. Перевантаження оператора > (більше)
    bool operator>(const Money& other) const {
        long kop1 = hryvnia * 100 + static_cast<int>(kopeck);
        long kop2 = other.hryvnia * 100 + static_cast<int>(other.kopeck);
        return kop1 > kop2;
    }
    // ========================================================

    // Ділення та множення на число залишаємо методами
    Money DivNum(double factor) const {
        if (factor == 0) return Money();
        double totalKop = (hryvnia * 100.0 + static_cast<int>(kopeck)) / factor;
        long roundedKop = std::round(totalKop);
        return Money(roundedKop / 100, roundedKop % 100);
    }

    Money MulNum(double factor) const {
        double totalKop = (hryvnia * 100.0 + static_cast<int>(kopeck)) * factor;
        long roundedKop = std::round(totalKop);
        return Money(roundedKop / 100, roundedKop % 100);
    }
};

int main() {
    std::setlocale(LC_ALL, "uk_UA.UTF-8");

    Money m1, m2;
    
    std::cout << "--- Введення першої суми m1 ---\n";
    m1.Read();
    
    std::cout << "--- Введення другої суми m2 ---\n";
    m2.Read();

    std::cout << "\nСума m1: "; m1.Display();
    std::cout << "Сума m2: "; m2.Display();

    // Використання перевантажених операторів + та -
    std::cout << "\n--- Використання операторів + та - ---\n";
    Money sum = m1 + m2; 
    std::cout << "Результат (m1 + m2): "; sum.Display();

    Money diff = m1 - m2;
    std::cout << "Результат (m1 - m2): "; diff.Display();

    // Використання операторів порівняння == та >
    std::cout << "\n--- Використання операторів порівняння ---\n";
    if (m1 == m2) {
        std::cout << "Суми m1 та m2 рівні між собою.\n";
    } else if (m1 > m2) {
        std::cout << "Сума m1 більша за суму m2.\n";
    } else {
        std::cout << "Сума m1 менша за суму m2.\n";
    }

    return 0;
}
