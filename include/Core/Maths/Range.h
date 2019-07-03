#ifndef __RANGE_H__
#define __RANGE_H__

namespace Core::Maths
{
    struct Range
    {
            #pragma region Attributes
            union
            {
                float _min;
                float min;
            };
            union
            {
                float _max;
                float max;
            };
            #pragma endregion
    
            #pragma region Constructors
            Range();
            Range(float min, float max);
            Range(const Range& r);
            ~Range() = default;
            #pragma endregion
    
            #pragma region Operators
            Range& operator=(const Range& r);
            #pragma endregion

            #pragma region Functions
            Range& update(float value);
            bool isOverlapping(const Range& r) const;
            #pragma endregion
    };
} // Maths::Core


#endif//__RANGE_H__