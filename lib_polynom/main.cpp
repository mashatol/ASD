
#include <iostream>
#include "polynom.h"

int main() {
    std::cout << "=== Демонстрация работы с полиномами ===\n\n";

    Polynom p1("x^2 + 2x + 1");
    Polynom p2("x - 1");
    Polynom p3("2x^2y + 3yz^2 - 5");

    std::cout << "Полином p1: " << p1 << std::endl;
    std::cout << "Полином p2: " << p2 << std::endl;
    std::cout << "Полином p3: " << p3 << std::endl;
    std::cout << std::endl;

    Polynom sum = p1 + p2;
    Polynom diff = p1 - p2;
    Polynom prod = p1 * p2;

    std::cout << "p1 + p2 = " << sum << std::endl;
    std::cout << "p1 - p2 = " << diff << std::endl;
    std::cout << "p1 * p2 = " << prod << std::endl;
    std::cout << std::endl;

    Polynom scaled = p3 * 2.5;
    std::cout << "p3 * 2.5 = " << scaled << std::endl;
    std::cout << std::endl;

    double x = 2, y = 3, z = 1;
    std::cout << "p3(" << x << ", " << y << ", " << z << ") = "
        << p3.evaluate(x, y, z) << std::endl;
    std::cout << std::endl;

    Monom m1(2.5, 2, 1, 0);  
    Monom m2(1.5, 2, 1, 0);  
    Monom m3(3.0, 1, 2, 1); 

    std::cout << "Моном m1: " << m1 << std::endl;
    std::cout << "Моном m2: " << m2 << std::endl;
    std::cout << "Моном m3: " << m3 << std::endl;
    std::cout << std::endl;

    
    if (m1.isSimilar(m2)) {
        Monom sumM = m1 + m2;
        std::cout << "m1 + m2 = " << sumM << std::endl;
    }

    Monom prodM = m1 * m3;
    std::cout << "m1 * m3 = " << prodM << std::endl;

    std::cout << "\nЗначение m1 в точке (2,3,1): "
        << m1.evaluate(2, 3, 1) << std::endl;

    return 0;
}