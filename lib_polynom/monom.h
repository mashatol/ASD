#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

class Monom {
private:
    double coef;
    int px, py, pz;

public:
    Monom();
    Monom(double c, int x_deg = 0, int y_deg = 0, int z_deg = 0);
    Monom(const Monom& other);
    ~Monom() = default;

    double getCoef() const { return coef; }
    int getPx() const { return px; }
    int getPy() const { return py; }
    int getPz() const { return pz; }

    void setCoef(double c) { coef = c; }
    void setDegrees(int x_deg, int y_deg, int z_deg) {
        px = x_deg; py = y_deg; pz = z_deg;
    }

    bool isSimilar(const Monom& other) const;

    bool operator==(const Monom& other) const;
    bool operator!=(const Monom& other) const;
    bool operator<(const Monom& other) const;  

    Monom operator+(const Monom& other) const;
    Monom operator-(const Monom& other) const;
    Monom operator*(const Monom& other) const;
    Monom operator/(const Monom& other) const;
    Monom operator*(double scalar) const;
    Monom operator/(double scalar) const;
    Monom operator-() const;

    Monom& operator+=(const Monom& other);
    Monom& operator-=(const Monom& other);
    Monom& operator*=(const Monom& other);
    Monom& operator/=(const Monom& other);
    Monom& operator*=(double scalar);
    Monom& operator/=(double scalar);
    Monom& operator=(const Monom& other);

    double evaluate(double x, double y, double z) const;

    bool isZero() const { return std::abs(coef) < 1e-10; }
    void normalize() { if (isZero()) { coef = 0; px = py = pz = 0; } }

    friend std::ostream& operator<<(std::ostream& os, const Monom& m);
    friend std::istream& operator>>(std::istream& is, Monom& m);
};