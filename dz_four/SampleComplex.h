#ifndef SAMPLE_COMPLEX_H
#define SAMPLE_COMPLEX_H

#include "Sample.h"
#include <complex>
#include <fstream>
#include <cmath>

class SampleComplex : public Sample<std::complex<double>> {

public:
    // конструктор
    SampleComplex(int size){

        Resize(size);
    }
    ~SampleComplex() = default;

    
    // модуль
    double Module(int i, int j) const
    {
        return std::abs((*this)(i, j));
    }

    // фаза
    double Phase(int i, int j) const
    {
        return std::arg((*this)(i, j));
    }

    // интенсивность (квадрат модуля)
    void Intensity()
    {
        for (int i = 0; i < GetSizeX(); i++)
        {
            for (int j = 0; j < GetSizeY(); j++)
            {
                double val = std::norm((*this)(i, j));
                (*this)(i, j) = std::complex<double>(val, 0);
            }
        }
    }

    // преобразование в Sample<double>
    Sample<double> ToRealSample() const
    {
        Sample<double> result;
        result.Resize(GetSizeX(), GetSizeY());

        for (int i = 0; i < GetSizeX(); i++)
        {
            for (int j = 0; j < GetSizeY(); j++)
            {
                result(i, j) = (*this)(i, j).real();
            }
        }

        return result;
    }

    // преобразование из Sample<double>
    static SampleComplex FromRealSample(const Sample<double>& s)
    {
        SampleComplex result(s.GetSizeX());

        for (int i = 0; i < s.GetSizeX(); i++)
        {
            for (int j = 0; j < s.GetSizeY(); j++)
            {
                result(i, j) = std::complex<double>(s(i, j), 0);
            }
        }

        return result;
    }

    // вывод вещественной части
    void SaveReal(const std::string& file)
    {
        std::ofstream out(file);

        for (int i = 0; i < GetSizeX(); i++)
        {
            for (int j = 0; j < GetSizeY(); j++)
                out << (*this)(i, j).real() << " ";

            out << std::endl;
        }
    }

    // вывод мнимой части
    void SaveImag(const std::string& file)
    {
        std::ofstream out(file);

        for (int i = 0; i < GetSizeX(); i++)
        {
            for (int j = 0; j < GetSizeY(); j++)
                out << (*this)(i, j).imag() << " ";

            out << std::endl;
        }
    }

    // вывод модуля
    void SaveModule(const std::string& file)
    {
        std::ofstream out(file);

        for (int i = 0; i < GetSizeX(); i++)
        {
            for (int j = 0; j < GetSizeY(); j++)
                out << std::abs((*this)(i, j)) << " ";

            out << std::endl;
        }
    }

    // вывод фазы
    void SavePhase(const std::string& file)
    {
        std::ofstream out(file);

        for (int i = 0; i < GetSizeX(); i++)
        {
            for (int j = 0; j < GetSizeY(); j++)
                out << std::arg((*this)(i, j)) << " ";

            out << std::endl;
        }
    }

    // вывод интенсивности
    void SaveIntensity(const std::string& file)
    {
        std::ofstream out(file);

        for (int i = 0; i < GetSizeX(); i++)
        {
            for (int j = 0; j < GetSizeY(); j++)
                out << std::norm((*this)(i, j)) << " ";

            out << std::endl;
        }
    }
};



#endif