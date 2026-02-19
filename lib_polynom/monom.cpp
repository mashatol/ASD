#include "monom.h"

Monom::Monom() : coef(0), px(0), py(0), pz(0) {}

Monom::Monom(double c, int x_deg, int y_deg, int z_deg)
    : coef(c), px(x_deg), py(y_deg), pz(z_deg) {
    if (px < 0 || py < 0 || pz < 0) {
        throw std::invalid_argument("Degrees must be non-negative");
    }
    normalize();
}

Monom::Monom(const Monom& other)
    : coef(other.coef), px(other.px), py(other.py), pz(other.pz) {
}

bool Monom::isSimilar(const Monom& other) const {
    return px == other.px && py == other.py && pz == other.pz;
}

bool Monom::operator==(const Monom& other) const {
    return isSimilar(other) && std::abs(coef - other.coef) < 1e-10;
}

bool Monom::operator!=(const Monom& other) const {
    return !(*this == other);
}

bool Monom::operator<(const Monom& other) const {
    if (px != other.px) return px > other.px;
    if (py != other.py) return py > other.py;
    return pz > other.pz;
}

Monom Monom::operator+(const Monom& other) const {
    if (!isSimilar(other)) {
        throw std::invalid_argument("Cannot add dissimilar monomials");
    }
    return Monom(coef + other.coef, px, py, pz);
}

Monom Monom::operator-(const Monom& other) const {
    if (!isSimilar(other)) {
        throw std::invalid_argument("Cannot subtract dissimilar monomials");
    }
    return Monom(coef - other.coef, px, py, pz);
}

Monom Monom::operator*(const Monom& other) const {
    return Monom(coef * other.coef,
        px + other.px, py + other.py, pz + other.pz);
}

Monom Monom::operator/(const Monom& other) const {
    if (std::abs(other.coef) < 1e-10) {
        throw std::invalid_argument("Division by zero");
    }
    if (px < other.px || py < other.py || pz < other.pz) {
        throw std::invalid_argument("Negative degree would result");
    }
    return Monom(coef / other.coef,
        px - other.px, py - other.py, pz - other.pz);
}

Monom Monom::operator*(double scalar) const {
    return Monom(coef * scalar, px, py, pz);
}

Monom Monom::operator/(double scalar) const {
    if (std::abs(scalar) < 1e-10) {
        throw std::invalid_argument("Division by zero");
    }
    return Monom(coef / scalar, px, py, pz);
}

Monom Monom::operator-() const {
    return Monom(-coef, px, py, pz);
}

Monom& Monom::operator+=(const Monom& other) {
    if (!isSimilar(other)) {
        throw std::invalid_argument("Cannot add dissimilar monomials");
    }
    coef += other.coef;
    normalize();
    return *this;
}

Monom& Monom::operator-=(const Monom& other) {
    if (!isSimilar(other)) {
        throw std::invalid_argument("Cannot subtract dissimilar monomials");
    }
    coef -= other.coef;
    normalize();
    return *this;
}

Monom& Monom::operator*=(const Monom& other) {
    coef *= other.coef;
    px += other.px;
    py += other.py;
    pz += other.pz;
    normalize();
    return *this;
}

Monom& Monom::operator/=(const Monom& other) {
    if (std::abs(other.coef) < 1e-10) {
        throw std::invalid_argument("Division by zero");
    }
    if (px < other.px || py < other.py || pz < other.pz) {
        throw std::invalid_argument("Negative degree would result");
    }
    coef /= other.coef;
    px -= other.px;
    py -= other.py;
    pz -= other.pz;
    normalize();
    return *this;
}

Monom& Monom::operator*=(double scalar) {
    coef *= scalar;
    normalize();
    return *this;
}

Monom& Monom::operator/=(double scalar) {
    if (std::abs(scalar) < 1e-10) {
        throw std::invalid_argument("Division by zero");
    }
    coef /= scalar;
    normalize();
    return *this;
}

Monom& Monom::operator=(const Monom& other) {
    if (this != &other) {
        coef = other.coef;
        px = other.px;
        py = other.py;
        pz = other.pz;
    }
    return *this;
}

double Monom::evaluate(double x, double y, double z) const {
    return coef * std::pow(x, px) * std::pow(y, py) * std::pow(z, pz);
}

std::ostream& operator<<(std::ostream& os, const Monom& m) {
    if (std::abs(m.coef) < 1e-10) {
        os << "0";
        return os;
    }

    if (std::abs(m.coef - 1) > 1e-10 && std::abs(m.coef + 1) > 1e-10) {
        os << std::fixed << std::setprecision(2) << m.coef;
    }
    else if (std::abs(m.coef + 1) < 1e-10) {
        os << "-";
    }

    bool hasVar = false;

    if (m.px > 0) {
        os << "x";
        hasVar = true;
        if (m.px > 1) os << "^" << m.px;
    }
    if (m.py > 0) {
        os << "y";
        hasVar = true;
        if (m.py > 1) os << "^" << m.py;
    }
    if (m.pz > 0) {
        os << "z";
        hasVar = true;
        if (m.pz > 1) os << "^" << m.pz;
    }

    if (!hasVar && std::abs(m.coef - 1) < 1e-10) {
        os << "1";
    }
    else if (!hasVar && std::abs(m.coef + 1) < 1e-10) {
        os << "-1";
    }

    return os;
}

std::istream& operator>>(std::istream& is, Monom& m) {
    std::string token;
    is >> token;

    double coef = 1.0;
    int px = 0, py = 0, pz = 0;
    size_t pos = 0;

    if (token[0] == '-') {
        coef = -1.0;
        pos = 1;
    }
    else if (token[0] == '+') {
        pos = 1;
    }

    size_t numEnd = pos;
    while (numEnd < token.length() &&
        (isdigit(token[numEnd]) || token[numEnd] == '.')) {
        numEnd++;
    }

    if (numEnd > pos) {
        coef *= std::stod(token.substr(pos, numEnd - pos));
        pos = numEnd;
    }

    while (pos < token.length()) {
        char var = token[pos];
        pos++;

        int deg = 1;
        if (pos < token.length() && token[pos] == '^') {
            pos++;
            size_t degStart = pos;
            while (pos < token.length() && isdigit(token[pos])) {
                pos++;
            }
            deg = std::stoi(token.substr(degStart, pos - degStart));
        }

        switch (var) {
        case 'x': px = deg; break;
        case 'y': py = deg; break;
        case 'z': pz = deg; break;
        default: throw std::invalid_argument("Invalid variable");
        }
    }

    m = Monom(coef, px, py, pz);
    return is;
}