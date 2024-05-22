#ifndef RING_H
#define RING_H

class RingElement {};

class IntegerRingElement : public RingElement {
    public:
        int value;
        IntegerRingElement(int value) : value(value) {}
        IntegerRingElement operator+(const IntegerRingElement &rightOperand) const;
        IntegerRingElement operator-(const IntegerRingElement &rightOperand) const;
        IntegerRingElement operator*(const IntegerRingElement &rightOperand) const;
};


class RationalRingElement : public RingElement {
    public:
        int numerator;
        int denominator;
        RationalRingElement(int numerator, int denominator);
        RationalRingElement operator+(const RationalRingElement &rightOperand) const;
        RationalRingElement operator-(const RationalRingElement &rightOperand) const;
        RationalRingElement operator*(const RationalRingElement &rightOperand) const;

    private:
        static int gcd(int a, int b);
        static int lcm(int a, int b);
        void simplify();
};

class RealRingElement : public RingElement {
    public:
        const double value;
        RealRingElement(double value) : value(value) {}
        RealRingElement operator+(const RealRingElement &rightOperand) const;
        RealRingElement operator-(const RealRingElement &rightOperand) const;
        RealRingElement operator*(const RealRingElement &rightOperand) const;
};




template <class T>
class MatrixRingElement : public RingElement {
    static_assert(std::is_base_of<RingElement, T>::value, "Only RingElement subclasses are allowed as template arguments.");
    public:
        const int size;
        T **matrix;
        MatrixRingElement(int size);
        MatrixRingElement(int size, T **matrix);
        void setElement(int row, int column, T value);
        MatrixRingElement operator+(const MatrixRingElement &rightOperand) const;
        MatrixRingElement operator-(const MatrixRingElement &rightOperand) const;
        MatrixRingElement operator*(const MatrixRingElement &rightOperand) const;
};

template <class T>
class PolynomialRingElement : public RingElement {
    static_assert(std::is_base_of<RingElement, T>::value, "Only RingElement subclasses are allowed as template arguments.");
    public:
        const int degree;
        T *coefficients;
        PolynomialRingElement(int degree);
        PolynomialRingElement(int degree, T *coefficients);
        PolynomialRingElement(T value) : value(value) {}
        PolynomialRingElement operator+(const PolynomialRingElement &rightOperand) const;
        PolynomialRingElement operator-(const PolynomialRingElement &rightOperand) const;
        PolynomialRingElement operator*(const PolynomialRingElement &rightOperand) const;
};

template <class T>
class ComplexRingElement : public RingElement {
    static_assert(std::is_base_of<RingElement, T>::value, "Only RingElement subclasses are allowed as template arguments.");
    public:
        const T real;
        const T imaginary;
        ComplexRingElement(T real, T imaginary);
        ComplexRingElement operator+(const ComplexRingElement &rightOperand) const;
        ComplexRingElement operator-(const ComplexRingElement &rightOperand) const;
        ComplexRingElement operator*(const ComplexRingElement &rightOperand) const;
};

#endif