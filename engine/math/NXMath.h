/*
 *  File:    math.h
 *  author:  张雄
 *  date:    2016_02_26
 *  purpose: 基本的数学库函数
 */

//写一些sin,cos之类的快速计算函数
#ifndef __ZX_NXENGINE_MATH_H__
#define __ZX_NXENGINE_MATH_H__

#include "NXNumeric.h"
#include "../common/NXCore.h"

namespace NX {
    template<typename T, int Scale>
    class vector;
    
    template<typename T, int Row, int Col>
    class Matrix;
    
    void InitNXMath();
    
    template<typename T>
    inline float DG2RD(const T angle);
    
    inline double DG2RD(const double angle);
    
    template<typename T>
    inline float RD2DG(const T angle);
    
    inline double RD2DG(const double angle);
    /**
     *  返回acos和asin值，若value超出[-1, 1]，则返回边界上的最大值
     */
    float SafeACos(const float value);
    float SafeASin(const float value);
    
    std::pair<double, double> GetSinAndCos(const double radian);
    void GetSinAndCos(const double radian, double * const pSinvalue, double * const pCosValue);
    
    void QuickGetSinAndCos(const double radian, double * const pSinValue, double * const pCosValue);
    std::pair<double, double> QuickGetSinAndCos(const double radian);
    
    double QuickCosWithAngle(const double Angle);
    double QuickSinWithAngle(const double Angle);
    double QuickCosWithRadian(const double Radian);
    double QuickSinWithRadian(const double Radian);
    float QuickCosWithAngle(const float Angle);
    float QuickSinWithAngle(const float Angle);
    float QuickCosWithRadian(const float Radian);
    float QuickSinWithRadian(const float Radian);
    inline float QuickCosWithAngle(const int Angle);
    inline float QuickSinWithAngle(const int Angle);
    inline float QuickCosWithRadian(const int Radian);
    inline float QuickSinWithRadian(const int Radian);
    inline int   RandInt();
    inline int   RandIntInRange(int left, int right);
    inline float RandUnitFloat();//rand float with (0,1)
    inline float RandFloatInRange(float left, float right);
    
    //ComparedValue >= NewValue
    template<typename T, typename U>
    T ClampFloor(T& ComparedValue, const U NewValue);
    //ComparedValue <= NewValue
    template<typename T, typename U>
    T ClampCeil(T& ComparedValue, const U NewValue);
    //FloorValue <= CompraedValue <= CeilValue
    template<typename T, typename U, typename X>
    T Clamp(T& ComparedValue, const U FloorValue, const X CeilValue);
    
    //以mode为单位，将value变换到[-mode, mode]之间，返回变换之前的value, mode > 0 is required
    template<typename T, typename U>
    T Wrap(T &value, const U mode);
    
    //以mode为单位，将value变换到[0, mode)之间，返回变换之前的value, mode > 0 is required
    template<typename T, typename U>
    T Mode(T &value, const U mode);
    template<typename T>
    T NXAbs(const T value);
    
    template<typename T, typename U>
    T NXMin(const T l, const U r);
    
    template<typename T, typename U>
    T NXMax(const T l, const U r);
    
    template<typename T>
    void NXSwap(T& lhs, T &rhs);
    
    template<typename T>
    T NXSign(const T v);
    
    template<typename T>
    T NXQuickPow(const T base, const int exp);
    
    double  NXQuickKSquare(const double base, const int k, const double Delta = NX::Epsilon<double>::m_Epsilon);
    double  NXKSquare(const double base, const int k);
    
    inline bool EqualZero(const float v,  const float Delta = Epsilon<float>::m_Epsilon){
        return v >= -Delta && v <= Delta;
    }
    
    inline bool EqualZero(const double v, const double Delta = Epsilon<double>::m_Epsilon){
        return v >= -Delta && v <= Delta;
    }
    
    //============================================begin float comparsion macro==========================================
#ifndef DECLARE_EQUAL_TYPE
#define DECLARE_EQUAL_TYPE(type) \
inline bool Equal##type(const type va, const type vb){\
return (va == vb) || (NX::NXAbs(va - vb) <= NX::Epsilon<type>::m_Epsilon);\
}
#endif
    DECLARE_EQUAL_TYPE(float)
    DECLARE_EQUAL_TYPE(double)
#undef DECLARE_EQUAL_TYPE
    
#ifndef DECLARE_EQUAL_TYPE_WITH_TOLERANCE
#define DECLARE_EQUAL_TYPE_WITH_TOLERANCE(type) \
inline bool Equal##type##WithDelta(const type va, const type vb, const type delta = NX::Epsilon<type>::m_Epsilon){\
return NX::NXAbs(va - vb) <= delta;\
}
#endif
    DECLARE_EQUAL_TYPE_WITH_TOLERANCE(float)
    DECLARE_EQUAL_TYPE_WITH_TOLERANCE(double)
#undef DECLARE_EQUAL_TYPE_WITH_TOLERANCE
    //=================================================end float comparsion macro=======================================
    
    
    //===================================================解方程==========================================================
    class Complex;
    /**
     *  ax + b = 0
     */
    std::vector<NX::Complex> SolveEquation(const float a, const float b);
    std::vector<float>  SolveEquationWithOnlyRealResult(const float a, const float b);
    
    /**
     * axx + bx + c = 0
     */
    std::vector<NX::Complex> SolveEquation(const float a, const float b, const float c);
    std::vector<float>  SolveEquationWithOnlyRealResult(const float a, const float b, const float c);
    
    /**
     *  axxx + bxx + cx + d = 0
     */
    std::vector<NX::Complex> SolveEquation(const float a, const float b, const float c, const float d);
    std::vector<float>  SolveEquationWithOnlyRealResult(const float a, const float b, const float c, const float d);
    
    /**
     *  axxxx + bxxx + cxx + dx + e = 0
     */
    std::vector<NX::Complex> SolveEquation(const float a, const float b, const float c, const float d, const float e);
    std::vector<float>  SolveEquationWithOnlyRealResult(const float a, const float b, const float c, const float d, const float e);
    
    std::pair<bool, NX::vector<float, 2> > SolveEquation(const NX::Matrix<float, 2, 2> &M, const NX::vector<float, 2> &V);
    //==================================================================================================================
    
    
    //==================================================begin of get eigenvalue=========================================
    std::vector<float> GetEigenValueOfSymmetricMatrix(const NX::Matrix<float, 3, 3> &M);
    std::vector<NX::vector<float, 3> > GetEigenVectorOfSymmetricMatrix(const NX::Matrix<float, 3, 3> &M);
    //==================================================end of get eigenvalue===========================================
    
    //===============================================begin string hash==================================================
    unsigned int NXBKDRHash(const char *str);

    unsigned int NXBKDRHash(const std::string &str);
    //=================================================end string hash==================================================

    unsigned int NXUpperPow2(unsigned int x);
    unsigned int NXLowerPow2(unsigned int x);
    NXUInt64     NXUpperPow2(NXUInt64 x);
    NXUInt64     NXLowerPow2(NXUInt64 x);
#include "NXMath.inl"
}

#endif
