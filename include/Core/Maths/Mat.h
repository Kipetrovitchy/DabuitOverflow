#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "Vec3.h"

typedef unsigned int uint;

namespace Core::Maths
{
    struct Mat
    {
        #pragma region Attributes

        union 
        {
            float*  _elements;
            float*  elements;
        };

        union 
        {
            uint    _rows;
            uint    rows;
        };

        union 
        {
            uint    _cols;
            uint    cols;
        };
        
        #pragma endregion

        #pragma region Constructors
        Mat();
        Mat(uint m, uint n);
        Mat(float* elem, uint m, uint n);
        Mat(const Mat& m);
        ~Mat();
        #pragma endregion

        #pragma region Operators
        Mat&    operator= (const Mat& m);
        float*  operator[](uint i);
        Mat     operator+ (const Mat& m) const;
        Mat     operator* (const Mat& m) const;
        Vec3    operator* (const Vec3& v) const;
        Mat     operator* (float value) const;
        Mat&    operator*=(float value);
        #pragma endregion

        #pragma region Fonctions
        void    print() const;
        Mat&    transpose();
        Mat     transpose() const;
        
        #pragma region Inverse
        Mat     inverse() const;
        float   determinant() const;
        float   getMinor(uint row, uint col) const;
        float   cofactor(uint row, uint col) const;
        Mat     subMatrix(uint row, uint col) const;
        Mat     cofactorMatrix() const;
        Mat     transposedCofactorMatrix() const;
        #pragma endregion
        #pragma endregion

        static Mat identity(uint m);
        static Mat zero(uint m, uint n);
        static Mat createRotation (const Vec3& axis, float angle);

    private:
        #pragma region 
        float   determinant44() const;
        float   determinant33() const;
        float   determinant22() const;
        float   determinant11() const;
        #pragma endregion
    };
}

#endif
