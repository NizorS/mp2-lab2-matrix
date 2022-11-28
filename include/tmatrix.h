// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

//Веденные библиотеки
#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__
#include <iostream>
using namespace std;
//Константы
const int MAX_MATRIX_SIZE = 10000;
const int MAX_VECTOR_SIZE = 100000000;
// Динамический вектор -  шаблонный вектор на динамической памяти


template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz <= 0 || sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size should be greater than zero");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* massive, size_t s) : sz(s)
    {
        if (sz <= 0 || sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size should be greater than zero");
        assert(massive != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(massive, massive + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        sz = 0;
        swap(*this, v);
    }
    ~TDynamicVector()
    {
        if (pMem != nullptr)
        {
            delete[] pMem;
        }
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
        {
            return *this;
        }
        sz = v.sz;
        delete[] pMem;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        sz = 0;
        delete[] pMem;
        pMem = nullptr;
        swap(*this, v);
        return *this;
    }

    size_t size() const noexcept { return sz; }



    // Индексация
    T& operator[](size_t index)
    {
        return pMem[index];
    }
    const T& operator[](size_t index) const
    {
        return pMem[index];
    }





    // Индексация с контролем
    T& at(size_t index)
    {
        if (index < 0 || index >= sz)
        {
            throw "Invalid index";
        }
        return pMem[index];
    }
    const T& at(size_t index) const
    {
        if (index < 0 || index >= sz)
        {
            throw "Invalid index";
        }
        return pMem[index];
    }




    // Сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz)
        {
            return false;
        }
        else
        {
            for (size_t i = 0; i < sz; i++)
            {
                if (pMem[i] != v.pMem[i])
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        if ((*this) == v)
        {
            return false;
        }
        else
        {
            return true;
        }
    }




    // Скалярные операции над векторами
    TDynamicVector operator+(T val)
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] + val;
        }
        return tmp;
    }
    TDynamicVector operator-(/*double*/T val)
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] - val;
        }
        return tmp;
    }
    TDynamicVector operator*(/*double*/T val)
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] * val;
        }
        return tmp;
    }





    // Векторные операции 
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz)
        {
            throw "Invalid index";
        }
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < tmp.sz; i++)
        {
            tmp.pMem[i] = pMem[i] + v.pMem[i];
        }
        return tmp;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
        {
            throw "Invalid index";
        }
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < tmp.sz; i++)
        {
            tmp.pMem[i] = pMem[i] - v.pMem[i];
        }
        return tmp;
    }
    T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
    {
        if (sz != v.sz)
        {
            throw out_of_range("Invalid index");
        }
        T result = {};
        for (size_t i = 0; i < sz; i++)
        {
            result += pMem[i] * v.pMem[i];
        }
        return result;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }




    //Ввод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    //Вывод
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};





// Динамическая матрица - шаблонная матрица на динамической памяти

template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (sz <= 0 || s > MAX_MATRIX_SIZE)
        {
            throw "Invalid index";
        }
        for (size_t i = 0; i < sz; i++)
        {
            pMem[i] = TDynamicVector<T>(sz);
        }
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    size_t size() const noexcept { return sz; }

    T& at(size_t index1, size_t index2)
    {
        if (index1 >= sz || index2 >= sz || index1 < 0 || index2 < 0)
        {
            throw "Invalid index";
        }
        return pMem[index1][index2];
    }





    //Этап сравнения
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        return TDynamicVector<TDynamicVector<T>>::operator==(m);
    }







    // Матрично-скалярные операции
    TDynamicMatrix<T> operator*(const T& val)
    {
        TDynamicMatrix tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] * val;
        }
        return tmp;
    }






    // Матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size())
        {
            throw "Invalid index";
        }
        TDynamicVector<T> tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp[i] = pMem[i] * v;
        }
        return tmp;
    }






    // Матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
        {
            throw "Invalid index";
        }
        TDynamicMatrix tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] + m.pMem[i];
        }
        return tmp;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
        {
            throw "Invalid index";
        }
        TDynamicMatrix tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] - m.pMem[i];
        }
        return tmp;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
        {
            throw "Invalid index";
        }
        TDynamicMatrix tmp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            for (size_t j = 0; j < sz; j++)
            {
                for (size_t k = 0; k < sz; k++)
                {
                    tmp.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
                }
            }
        }
        return tmp;
    }



    //Ввод значений
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
        {
            for (size_t j = 0; j < v.sz; j++)
            {
                istr >> v.pMem[i][j];
            }
        }
        return istr;
    }





    //Вывод значений
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
        {
            for (size_t j = 0; j < v.sz; j++)
            {
                ostr << v.pMem[i][j] << "\t";
            }
            ostr << " \n";
        }
        return ostr;
    }
};

#endif

