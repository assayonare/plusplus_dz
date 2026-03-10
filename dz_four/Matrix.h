#ifndef MATRIX_H
#define MATRIX_H

#include "Sample.h"
#include <stdexcept>

class Matrix: public Sample<double> {

public:

    Matrix() = default;
    ~Matrix() = default;

    Matrix(int size) {
        Resize(size);
    }

    Matrix(int size_x, int size_y) {
        Resize(size_x, size_y);
    }

    // создание единичной матрицы
    static Matrix Identity(int size)
    {
        Matrix I(size);

        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
                I(i,j) = (i == j) ? 1.0 : 0.0;

        return I;
    }

    // проверка возможности произведения
    bool CanMultiply(const Matrix& B) const
    {
        return GetSizeY() == B.GetSizeX();
    }

    // матричное произведение
    Matrix operator*(const Matrix& B) const
    {
        if (!CanMultiply(B))
            throw std::runtime_error("Невозможно перемножить матрицы");

        Matrix C;
        C.Resize(GetSizeX(), B.GetSizeY());

        for (int i = 0; i < GetSizeX(); i++)
        {
            for (int j = 0; j < B.GetSizeY(); j++)
            {
                C(i, j) = 0;

                for (int k = 0; k < GetSizeY(); k++)
                    C(i, j) += (*this)(i, k) * B(k, j);
            }
        }

        return C;
    }

    // транспонирование
    Matrix operator~() const
    {
        Matrix T;
        T.Resize(GetSizeY(), GetSizeX());

        for (int i = 0; i < GetSizeX(); i++)
            for (int j = 0; j < GetSizeY(); j++)
                T(j, i) = (*this)(i, j);

        return T;
    }

    // запрет /= 
    Matrix& operator/=(double)
    {
        throw std::runtime_error("Оператор /= запрещён для Matrix");
    }

    // запрет *=
    Matrix& operator*=(double)
    {
        throw std::runtime_error("Оператор *= запрещён для Matrix");
    }
};

#endif