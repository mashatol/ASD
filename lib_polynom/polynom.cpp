#include "polynom.h"

Polynom::Polynom() {}

Polynom::Polynom(const std::string& str) {
    if (str.empty()) return;

    std::string s = str;
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

    if (s.empty()) return;

    std::vector<std::string> parts;
    size_t pos = 0;
    size_t lastPos = 0;

    while (pos < s.length()) {
        if (s[pos] == '+' || s[pos] == '-') {
            if (pos > lastPos) {
                parts.push_back(s.substr(lastPos, pos - lastPos));
            }
            lastPos = pos;
        }
        pos++;
    }
    if (lastPos < s.length()) {
        parts.push_back(s.substr(lastPos));
    }

    for (const auto& part : parts) {
        if (part.empty()) continue;

        try {
            std::stringstream ss(part);
            Monom m;
            ss >> m;
            if (!m.isZero()) {
                addMonom(m);
            }
        }
        catch (...) {
            // Игнорируем некорректные мономы
        }
    }

    sortAndCombine();
}

Polynom::Polynom(const char* str) : Polynom(std::string(str)) {}

Polynom::Polynom(const Polynom& other) : monoms(other.monoms) {}

Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other) {
        monoms = other.monoms;
    }
    return *this;
}

void Polynom::addMonom(const Monom& m) {
    if (m.isZero()) return;

    for (auto it = monoms.begin(); it != monoms.end(); ++it) {
        if (it->isSimilar(m)) {
            *it += m;
            if (it->isZero()) {
                monoms.erase(it);
            }
            return;
        }
    }

    monoms.push_back(m);
}

void Polynom::sortAndCombine() {
    if (monoms.empty()) return;

    // Копируем в вектор для сортировки
    std::vector<Monom> vec(monoms.begin(), monoms.end());

    // Сортируем
    std::sort(vec.begin(), vec.end());

    // Объединяем подобные
    std::vector<Monom> result;
    for (const auto& m : vec) {
        bool found = false;
        for (auto& rm : result) {
            if (rm.isSimilar(m)) {
                rm += m;
                found = true;
                break;
            }
        }
        if (!found && !m.isZero()) {
            result.push_back(m);
        }
    }

    // Удаляем нулевые
    result.erase(
        std::remove_if(result.begin(), result.end(),
            [](const Monom& m) { return m.isZero(); }),
        result.end()
    );

    // Заполняем список
    monoms.clear();
    for (const auto& m : result) {
        if (!m.isZero()) {
            monoms.push_back(m);
        }
    }
}

Polynom Polynom::operator+(const Polynom& other) const {
    Polynom result = *this;
    result += other;
    return result;
}

Polynom Polynom::operator-(const Polynom& other) const {
    Polynom result = *this;
    result -= other;
    return result;
}

Polynom Polynom::operator*(const Polynom& other) const {
    Polynom result;

    for (const auto& m1 : monoms) {
        for (const auto& m2 : other.monoms) {
            result.addMonom(m1 * m2);
        }
    }

    result.sortAndCombine();
    return result;
}

Polynom Polynom::operator*(double scalar) const {
    Polynom result = *this;
    result *= scalar;
    return result;
}

Polynom Polynom::operator/(double scalar) const {
    Polynom result = *this;
    result /= scalar;
    return result;
}

Polynom Polynom::operator-() const {
    Polynom result;
    for (const auto& m : monoms) {
        result.addMonom(-m);
    }
    return result;
}

Polynom& Polynom::operator+=(const Polynom& other) {
    for (const auto& m : other.monoms) {
        addMonom(m);
    }
    sortAndCombine();
    return *this;
}

Polynom& Polynom::operator-=(const Polynom& other) {
    for (const auto& m : other.monoms) {
        addMonom(-m);
    }
    sortAndCombine();
    return *this;
}

Polynom& Polynom::operator*=(const Polynom& other) {
    *this = *this * other;
    return *this;
}

Polynom& Polynom::operator*=(double scalar) {
    if (std::abs(scalar) < 1e-10) {
        monoms.clear();
        return *this;
    }

    for (auto& m : monoms) {
        m *= scalar;
    }
    return *this;
}

Polynom& Polynom::operator/=(double scalar) {
    if (std::abs(scalar) < 1e-10) {
        throw std::invalid_argument("Division by zero");
    }

    for (auto& m : monoms) {
        m /= scalar;
    }
    return *this;
}

bool Polynom::operator==(const Polynom& other) const {
    if (monoms.size() != other.monoms.size()) return false;

    auto it1 = monoms.begin();
    auto it2 = other.monoms.begin();

    while (it1 != monoms.end() && it2 != other.monoms.end()) {
        if (*it1 != *it2) return false;
        ++it1;
        ++it2;
    }

    return true;
}

bool Polynom::operator!=(const Polynom& other) const {
    return !(*this == other);
}

double Polynom::evaluate(double x, double y, double z) const {
    double result = 0;
    for (const auto& m : monoms) {
        result += m.evaluate(x, y, z);
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Polynom& p) {
    if (p.monoms.empty()) {
        os << "0";
        return os;
    }

    bool first = true;
    for (const auto& m : p.monoms) {
        if (!first) {
            if (m.getCoef() > 0) {
                os << " + ";
            }
            else {
                os << " - ";
            }

            Monom temp = m;
            if (temp.getCoef() < 0) temp.setCoef(-temp.getCoef());
            os << temp;
        }
        else {
            os << m;
            first = false;
        }
    }

    return os;
}

std::istream& operator>>(std::istream& is, Polynom& p) {
    std::string line;
    std::getline(is, line);
    p = Polynom(line);
    return is;
}

Polynom operator*(double scalar, const Polynom& p) {
    return p * scalar;
}