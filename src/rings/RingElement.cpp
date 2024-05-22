#include "RingElement.h"
#include <stdexcept>

IntegerRingElement::IntegerRingElement(int value) : value(value) {}
IntegerRingElement IntegerRingElement::operator+(const IntegerRingElement &rightOperand) const {
    return IntegerRingElement(this->value + rightOperand.value);
}

IntegerRingElement IntegerRingElement::operator-(const IntegerRingElement &rightOperand) const {
    return IntegerRingElement(this->value - rightOperand.value);
}

IntegerRingElement IntegerRingElement::operator*(const IntegerRingElement &rightOperand) const {
    return IntegerRingElement(this->value * rightOperand.value);
}

RealRingElement::RealRingElement(double value) : value(value) {}
RealRingElement RealRingElement::operator+(const RealRingElement &rightOperand) const {
    return RealRingElement(this->value + rightOperand.value);
}

RealRingElement RealRingElement::operator-(const RealRingElement &rightOperand) const {
    return RealRingElement(this->value - rightOperand.value);
}

RealRingElement RealRingElement::operator*(const RealRingElement &rightOperand) const {
    return RealRingElement(this->value * rightOperand.value);
}

RationalRingElement::RationalRingElement(int numerator, int denominator) : numerator(numerator), denominator(denominator) {
    if (denominator == 0) { throw std::runtime_error("Denominator cannot be zero."); }
    simplify();
}

RationalRingElement RationalRingElement::operator+(const RationalRingElement &rightOperand) const {
    int newNumerator = this->numerator * rightOperand.denominator + rightOperand.numerator * this->denominator;
    int newDenominator = this->denominator * rightOperand.denominator;
    return RationalRingElement(newNumerator, newDenominator);
}

RationalRingElement RationalRingElement::operator-(const RationalRingElement &rightOperand) const {
    int newNumerator = this->numerator * rightOperand.denominator - rightOperand.numerator * this->denominator;
    int newDenominator = this->denominator * rightOperand.denominator;
    return RationalRingElement(newNumerator, newDenominator);
}

RationalRingElement RationalRingElement::operator*(const RationalRingElement &rightOperand) const {
    int newNumerator = this->numerator * rightOperand.numerator;
    int newDenominator = this->denominator * rightOperand.denominator;
    return RationalRingElement(newNumerator, newDenominator);
}

int RationalRingElement::gcd(int a, int b) {
    if (b == 0) { return a; }
    return gcd(b, a % b);
}

int RationalRingElement::lcm(int a, int b) {
    return a * b / gcd(a, b);
}

void RationalRingElement::simplify() {
    int divisor = gcd(numerator, denominator);
    numerator /= divisor;
    denominator /= divisor;
}

template <class T>
MatrixRingElement<T>::MatrixRingElement(int size) : size(size) {
    matrix = new T*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new T[size];
    }
}

template <class T>
MatrixRingElement<T>::MatrixRingElement(int size, T **matrix) : size(size), matrix(matrix) {}

template <class T>
void MatrixRingElement<T>::setElement(int row, int column, T value) {
    matrix[row][column] = value;
}

template <class T>
MatrixRingElement<T> MatrixRingElement<T>::operator+(const MatrixRingElement &rightOperand) const {
    T **newMatrix = new T*[size];
    for (int i = 0; i < size; i++) {
        newMatrix[i] = new T[size];
        for (int j = 0; j < size; j++) {
            newMatrix[i][j] = matrix[i][j] + rightOperand.matrix[i][j];
        }
    }
    return MatrixRingElement(size, newMatrix);
}

template <class T>
MatrixRingElement<T> MatrixRingElement<T>::operator-(const MatrixRingElement &rightOperand) const {
    T **newMatrix = new T*[size];
    for (int i = 0; i < size; i++) {
        newMatrix[i] = new T[size];
        for (int j = 0; j < size; j++) {
            newMatrix[i][j] = matrix[i][j] - rightOperand.matrix[i][j];
        }
    }
    return MatrixRingElement(size, newMatrix);
}

template <class T>
MatrixRingElement<T> MatrixRingElement<T>::operator*(const MatrixRingElement &rightOperand) const {
    T **newMatrix = new T*[size];
    for (int i = 0; i < size; i++) {
        newMatrix[i] = new T[size];
        for (int j = 0; j < size; j++) {
            newMatrix[i][j] = 0;
            for (int k = 0; k < size; k++) {
                newMatrix[i][j] += matrix[i][k] * rightOperand.matrix[k][j];
            }
        }
    }
    return MatrixRingElement(size, newMatrix);
}

template <class T>
PolynomialRingElement<T>::PolynomialRingElement(int degree) : degree(degree) {
    coefficients = new T[degree + 1];
}

template <class T>
PolynomialRingElement<T>::PolynomialRingElement(int degree, T *coefficients) : degree(degree), coefficients(coefficients) {}

template <class T>
PolynomialRingElement<T> PolynomialRingElement<T>::operator+(const PolynomialRingElement &rightOperand) const {
    int newDegree = std::max(this->degree, rightOperand.degree);
    T *newCoefficients = new T[newDegree + 1];
    for (int i = 0; i <= newDegree; i++) {
        newCoefficients[i] = (i <= this->degree ? this->coefficients[i] : 0) + (i <= rightOperand.degree ? rightOperand.coefficients[i] : 0);
    }
    return PolynomialRingElement(newDegree, newCoefficients);
}

template <class T>
PolynomialRingElement<T> PolynomialRingElement<T>::operator-(const PolynomialRingElement &rightOperand) const {
    int newDegree = std::max(this->degree, rightOperand.degree);
    T *newCoefficients = new T[newDegree + 1];
    for (int i = 0; i <= newDegree; i++) {
        newCoefficients[i] = (i <= this->degree ? this->coefficients[i] : 0) - (i <= rightOperand.degree ? rightOperand.coefficients[i] : 0);
    }
    return PolynomialRingElement(newDegree, newCoefficients);
}

template <class T>
PolynomialRingElement<T> PolynomialRingElement<T>::operator*(const PolynomialRingElement &rightOperand) const {
    int newDegree = this->degree + rightOperand.degree;
    T *newCoefficients = new T[newDegree + 1];
    for (int i = 0; i <= newDegree; i++) {
        newCoefficients[i] = 0;
        for (int j = 0; j <= i; j++) {
            newCoefficients[i] += (j <= this->degree ? this->coefficients[j] : 0) * (i - j <= rightOperand.degree ? rightOperand.coefficients[i - j] : 0);
        }
    }
    return PolynomialRingElement(newDegree, newCoefficients);
}
