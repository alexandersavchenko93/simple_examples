#include <iostream>
#include <numeric>
#include <stdexcept>

class RationalNumber
{
public:
    RationalNumber(): numerator(0), denominator(1) {}

    RationalNumber(int num, int den) {
        if (den == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }

        numerator = num;
        denominator = den;

        normalize();
    }

    int getNumerator() const {
        return numerator;
    }

    int getDenominator() const {
        return denominator;
    }

    RationalNumber operator+(const RationalNumber& other) const {
        int newNumerator =
            numerator * other.denominator +
            other.numerator * denominator;

        int newDenominator =
            denominator * other.denominator;

        return RationalNumber(newNumerator, newDenominator);
    }

    RationalNumber operator-(const RationalNumber& other) const {
        int newNumerator =
            numerator * other.denominator -
            other.numerator * denominator;

        int newDenominator =
            denominator * other.denominator;

        return RationalNumber(newNumerator, newDenominator);
    }

    RationalNumber operator*(const RationalNumber& other) const {
        int newNumerator =
            numerator * other.numerator;

        int newDenominator =
            denominator * other.denominator;

        return RationalNumber(newNumerator, newDenominator);
    }

    RationalNumber operator/(const RationalNumber& other) const {
        if (other.numerator == 0) {
            throw std::runtime_error("Division by zero rational number");
        }

        int newNumerator = numerator * other.denominator;
        int newDenominator = denominator * other.numerator;
        
        return RationalNumber(newNumerator, newDenominator);
    }

    bool operator==(const RationalNumber& other) const
    {
        return numerator == other.numerator &&
               denominator == other.denominator;
    }

    bool operator!=(const RationalNumber& other) const
    {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const RationalNumber& value) {
        os << value.numerator;

        if (value.denominator != 1) {
            os << "/" << value.denominator;
        }

        return os;
    }

private:
    int numerator;
    int denominator;

    void normalize() {
        // 0/x -> 0/1
        if (numerator == 0)
        {
            denominator = 1;
            return;
        }

        int divisor = std::gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }
};

int main() try
{
    RationalNumber a(9, -6);   // -3/2
    RationalNumber b(-9, 6);    //  3/2
    
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    std::cout << "\nAddition:" << std::endl;
    std::cout << a << " + " << b
                << " = " << (a + b) << std::endl;

    std::cout << "\nSubtraction:" << std::endl;
    std::cout << a << " - " << b
                << " = " << (a - b) << std::endl;

    std::cout << "\nMultiplication:" << std::endl;
    std::cout << a << " * " << b
                << " = " << (a * b) << std::endl;

    std::cout << "\nDivision:" << std::endl;
    std::cout << a << " / " << b
                  << " = " << (a / b) << std::endl;
    
    bool res = a == b;
    std::cout << "\n==:" << std::endl;
    std::cout << std::boolalpha << res << std::endl;

    return 0;
}
catch (const std::exception& ex)
{
    std::cout << "Exception: "
              << ex.what() << std::endl;
    return -1;
}
