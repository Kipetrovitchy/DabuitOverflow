#include "Mat.h"
#include <iostream>
#include <cmath>

namespace Core::Maths
{
    #pragma region Constructors
    Mat::Mat():
        _elements {nullptr},
        _rows   {0},
        _cols   {0}
    {}

    Mat::Mat(uint m, uint n):
        _elements {new float[m * n]},
        _rows   {m},
        _cols   {n}
    {}

    Mat::Mat(float* elem, uint m, uint n):
        _elements    {elem},
        _rows        {m},
        _cols        {n}
    {}

    Mat::Mat(const Mat& m):
        _elements {new float[m._rows * m._cols]},
        _rows   {m._rows},
        _cols   {m._cols}
    {
        uint size = _rows * _cols;
        for (uint i = 0; i < size; i++)
            _elements[i] = m._elements[i];
    }

    Mat::~Mat()
    {
        if (_elements)
            delete[] _elements;
    }
    #pragma endregion

    #pragma region operators

    Mat& Mat::operator=(const Mat& m)
    {
        if (_elements)
            delete[] _elements;

        _rows = m._rows;
        _cols = m._cols;

        uint size = _rows * _cols;
        _elements = new float[size];
        for (uint i = 0; i < size; i++)
        {
            _elements[i] = m._elements[i];
        }

        return *this;
    }

    float* Mat::operator[](uint i)
    {
        return &_elements[i * _rows];
    }

    Mat Mat::operator+(const Mat& m) const
    {
        if (_rows != m._rows || _cols != m._cols)
        {
                std::cout << "cannot add matrix that does not have the same size" << '\n';
            return *this;
        }

        Mat matrix(_rows, _cols);
        uint size = _rows * _cols;
        for (uint i = 0; i < size; i++)
            matrix._elements[i] = _elements[i] + m._elements[i];

        return matrix;
    }

    Mat Mat::operator*(const Mat& m) const
    {
        if (_cols != m._rows)
        {
            std::cout << "cannot multply those matrix" << '\n';
            return *this;
        }

        Mat matrix(_rows, m._cols);

        for (uint i = 0; i < matrix._rows; i++)
        {
            for (uint j = 0; j < matrix._cols; j++)
            {
                float sum = 0;
                for (uint k = 0; k < _cols; k++)
                    sum += _elements[i * _cols + k] * m._elements[k * m._cols + j];

                matrix._elements[i * matrix._rows + j] = sum;
            }
        }

        return matrix;
    }

    Vec3 Mat::operator*(const Vec3& vec) const
    {
        Vec3 out = Vec3::zero;

        uint h;
        if (_cols == 3)
        {
            for (uint i = 0; i < 3; i++)
            {
                h = i * _cols;
                out[i] =  _elements[h]     * vec.x
                        + _elements[h + 1] * vec.y
                        + _elements[h + 2] * vec.z;
            }
        }
        else if (_cols == 4)
        {
            for (uint i = 0; i < 3; i++)
            {
                h = i * _cols;
                out[i] =  _elements[h]     * vec.x
                        + _elements[h + 1] * vec.y
                        + _elements[h + 2] * vec.z
                        + _elements[h + 3];
            }
        }

        return out;
    }

    Mat Mat::operator*(float value) const
    {
        Mat out(_rows, _cols);

        uint size = _rows * _cols;
        for (uint i = 0; i < size; i++)
            out._elements[i] = _elements[i] * value;

        return out;
    }

    Mat& Mat::operator*=(float value)
    {
        uint size = _rows * _cols;
        for (uint i = 0; i < size; i++)
            _elements[i] = _elements[i] * value;

        return *this;
    }
    #pragma endregion

    #pragma region Fonctions
    void Mat::print() const
    {
        uint size = _rows * _cols;
        for (uint i = 0; i < size; i++)
        {
            std::cout << _elements[i] << ' ';
            if ((i + 1) % _cols == 0)
                std::cout << std::endl;
        }
    }

    Mat& Mat::transpose()
    {
        if (_cols == _rows)
        {
            for (uint i = 0; i < _cols - 1; i++)
            {
                for (uint j = i + 1; j < _cols; j++)
                {
                    float& aij = _elements[_cols * i + j];
                    float& aji = _elements[_cols * j + i];

                    float temp = aij;
                    aij = aji;
                    aji = temp;
                }
            }
        }
        else
        {
            uint size = _rows * _cols;
            float* elem = new float[size];
            for (uint i = 0; i < size; i++)
            {
                elem[i] = _elements[(i % _rows) * _cols + i / _rows];
            }
            delete[] _elements;
            _elements = elem;
        }

        return *this;
    }

    Mat Mat::transpose() const
    {
        Mat m(_rows, _cols);
        if (_cols == _rows)
        {
            for (uint i = 0; i < _cols; i++)
            {
                m._elements[_cols * i + i] = _elements[_cols * i + i];
                for (uint j = i + 1; j < _cols; j++)
                {
                    m._elements[_cols * j + i] = _elements[_cols * i + j];
                    m._elements[_cols * i + j] = _elements[_cols * j + i];
                }
            }
        }
        else
        {
            uint size = _rows * _cols;
            for (uint i = 0; i < size; i++)
            {
                m._elements[i] = _elements[(i % _rows) * _cols + i / _rows];
            }
        }

        return *this;
    }

    #pragma region Inverse

    float Mat::cofactor(uint row, uint col) const
    {
        return (((row+col) % 2 == 0) ? 1 : -1) * getMinor(row, col);
    }

    float Mat::getMinor(uint row, uint col) const
    {
        if (_rows != _cols)
            return 0.0f;

        return subMatrix(row, col).determinant();
    }

    float Mat::determinant() const
    {
        if (_rows != _cols)
            return 0.0f;

        switch (_rows)
        {
            case 1: return determinant11();
            case 2: return determinant22();
            case 3: return determinant33();
            case 4: return determinant44();
            default:
            {
                float determinant = 0.0f;
                for (uint i = 0; i < _cols; i++)
                    determinant += _elements[i] * cofactor(0, i);

                return determinant;
            }
        }
    }

    float Mat::determinant44() const
    {
        float a10 = _elements[4];
        float a11 = _elements[5];
        float a12 = _elements[6];
        float a13 = _elements[7];
        float a20 = _elements[8];
        float a21 = _elements[9];
        float a22 = _elements[10];
        float a23 = _elements[11];
        float a30 = _elements[12];
        float a31 = _elements[13];
        float a32 = _elements[14];
        float a33 = _elements[15];

        return _elements[0] * (  a11 * (a22*a33 - a32*a23)
                                - a12 * (a21*a33 - a31*a23)
                                + a13 * (a21*a32 - a31*a22))
                - _elements[1] * (  a10 * (a22*a33 - a32*a23)
                                - a12 * (a20*a33 - a30*a23)
                                + a13 * (a20*a32 - a30*a22))
                + _elements[2] * (  a10 * (a21*a33 - a31*a23)
                                - a11 * (a20*a33 - a30*a23)
                                + a13 * (a20*a31 - a30*a21))
                - _elements[3] * (  a10 * (a21*a32 - a31*a22)
                                - a11 * (a20*a32 - a30*a22)
                                + a12 * (a20*a31 - a30*a21));
    }

    float Mat::determinant33() const
    {
        float a10 = _elements[3];
        float a11 = _elements[4];
        float a12 = _elements[5];
        float a20 = _elements[6];
        float a21 = _elements[7];
        float a22 = _elements[8];

        return  _elements[0] * (a11*a22 - a21*a12)
                - _elements[1] * (a10*a22 - a20*a12)
                + _elements[2] * (a10*a21 - a20*a11);
    }

    float Mat::determinant22() const
    {
        return _elements[0] * _elements[3] - _elements[2] * _elements[1];
    }

    float Mat::determinant11() const
    {
        return _elements[0];
    }

    Mat Mat::subMatrix(uint row, uint col) const
    {
        Mat subM(_rows - 1, _cols - 1);
        uint index = 0;

        for (uint i = 0; i < _rows; i++)
        {
            if (i == row)
                continue;

            for (uint j = 0; j < _cols; j++)
            {
                if (j == col)
                    continue;

                subM._elements[index++] = _elements[i * _cols + j];
            }
        }

        return subM;
    }

    Mat Mat::cofactorMatrix() const
    {
        if (_rows != _cols)
            return Mat::zero(_rows, _cols);

        Mat m(_rows, _cols);
        for (uint i = 0; i < _rows; i++)
        {
            uint h = i * _cols;
            for (uint j = 0; j < _cols; j++)
            {
                m._elements[h + j] = cofactor(i, j);
            }
        }

        return m;
    }

    Mat Mat::transposedCofactorMatrix() const
    {
        if (_rows != _cols)
            return Mat::zero(_rows, _cols);

        Mat m(_rows, _cols);
        for (uint i = 0; i < _rows; i++)
        {
            uint h = i * _cols;
            for (uint j = 0; j < _cols; j++)
            {
                m._elements[h + j] = cofactor(j, i);
            }
        }

        return m;
    }

    Mat Mat::inverse() const
    {
        float det = determinant();
        if (det == 0)
            return Mat::identity(_rows);
            
        return transposedCofactorMatrix() * (1.0f / det);
    }
    #pragma endregion
    #pragma endregion

    /* Static fonctions */
    Mat Mat::zero(uint m, uint n)
    {
        Mat matrix(m, n);

        uint size = m * n;
        for (uint i = 0; i < size; i++)
        {
            matrix._elements[i] = 0;
        }

        return matrix;
    }

    Mat Mat::identity(uint m)
    {
        Mat matrix(m, m);

        for (uint i = 0; i < m; i++)
        {
            for (uint j = 0; j < m; j++)
            {
                if (i == j)
                    matrix._elements[i * m + j] = 1;
                else
                    matrix._elements[i * m + j] = 0;
            }
        }

        return matrix;
    }

    Mat Mat::createRotation(const Vec3& axis, float angle)
    {
        float c { cosf(angle) };
        float s { sinf(angle) };
        float t { 1.0f - c };

        float* elem = new float[16]
        {
            axis.x * axis.x * t + c,
            axis.x * axis.y * t - axis.z * s,
            axis.x * axis.z * t + axis.y * s,
            0.0f,
            axis.x * axis.y * t + axis.z * s,
            axis.y * axis.y * t + c,
            axis.y * axis.z * t - axis.x * s,
            0.0f,
            axis.x * axis.z * t - axis.y * s,
            axis.y * axis.z * t + axis.x * s,
            axis.z * axis.z * t + c,
            0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        return Mat(elem, 4, 4);
    }
} /* Maths */