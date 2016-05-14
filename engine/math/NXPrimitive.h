/*
 *  File:    NXPrimitive.h
 *  author:  张雄
 *  date:    2016_05_13
 *  purpose: 基本的3D图元
 */

#ifndef __ZX_NXENGINE_PRIMITIVE_H_
#define __ZX_NXENGINE_PRIMITIVE_H_

#include <utility>
#include "NXVector.h"
#include "NXMatrix.h"
namespace NX{
    class Line;
    class Plane;
    
    class Line{
    public:
        inline explicit Line();
        explicit Line(const vector<float, 3> &begin, const vector<float, 3> &end);
    public:
        template<typename T>
        inline Line& Transform(const Matrix<T, 3, 3> &rhs);
        template<typename T>
        inline Line& Transform(const Matrix<T, 4, 4> &rhs);
    public:
        inline vector<float, 3> GetBeginPosition() const;
        inline vector<float, 3> GetDirection() const;
        inline vector<float, 3> GetPoint(const float t) const;
        inline float Distance(const Line &rhs) const;//两直线距离
        template<typename T>
        inline float Distance(const vector<T, 3> &Point) const;
        inline std::pair<bool, vector<float, 3> >  Intersect(const Line &rhs) const;   //两直线的交点
        inline std::pair<bool, vector<float, 3> >  Intersect(const Plane &plane) const;//直线与平面交点
    public:
        vector<float, 3> m_BeginPosition;
        vector<float, 3> m_vDirection;
    };
    //==================================begin line nomember function====================================================
    template<typename T>
    inline Line Transform(const Line &lhs, const Matrix<T, 3, 3> &rhs);
    
    template<typename T>
    inline Line Transform(const Matrix<T, 3, 3> &lhs, const Line &rhs);
    
    template<typename T>
    inline Line Transform(const Line &lhs, const Matrix<T, 4, 4> &rhs);
    
    template<typename T>
    inline Line Transform(const Matrix<T, 4, 4> &lhs, const Line &rhs);
    
    inline float Distance(const Line &lhs, const Line &rhs);
    
    inline std::pair<bool, vector<float, 3> >  Intersect(const Line &lhs, const Line &rhs);
    //==================================end line nomember function======================================================
    
    
    class Plane{
    public:
        inline explicit Plane();
        template<typename T>
        inline explicit Plane(const vector<T, 4> &L);
        inline explicit Plane(const vector<float, 3> &a, const vector<float, 3> &b, const vector<float, 3> &c);
        inline explicit Plane(const Plane &rhs);
        inline explicit Plane(const vector<float, 3> &Normal, const vector<float, 3> &PointInPlane);
        inline explicit Plane(const vector<float, 3> &Normal, const float fDistFromOriginal);
    public:
        template<typename T, typename U>
        inline Plane& Transform(const Matrix<T, 3, 3> &matrix, const vector<U, 3> &translation);
        template<typename T>
        inline Plane& Transform(const Matrix<T, 4, 4> &matrix);
    public:
        inline std::pair<bool, Line>   Intersect(const Plane &rhs) const;  //平面交线
        inline std::pair<bool, float3> Intersect(const Line  &rhs) const;  //直线与平面交点
        inline float  Distance(const vector<float, 3> &rhs) const;         //点到平面距离
    public:
        vector<float, 3> m_vPlaneNormal;
        float            m_fDistFromOriginal;
    };
    //=================================begin plane nomember function====================================================
    template<typename T, typename U>
    inline Plane Transform(const Plane &plane, const Matrix<T, 3, 3> &matrix, const vector<U, 3> &translation);
    
    template<typename T>
    inline Plane Transform(const Plane &plane, const Matrix<T, 4, 4> &matrix);
    
    template<typename T>
    inline Plane Transform(const Matrix<T, 4, 4> &matrix, const Plane &plane);
    
    inline std::pair<bool, Line>   Intersect(const Plane &lhs, const Plane &rhs);
    
    inline std::pair<bool, float3> Intersect(const Line  &line,  const Plane &plane);
    
    inline std::pair<bool, float3> Intersect(const Plane &plane, const Line  &line);
    
    inline float  Distance(const Plane &plane, const vector<float, 3> &rhs);
    
    inline float  Distance(const vector<float, 3> &rhs, const Plane &plane);
    
    inline std::pair<bool, vector<float, 3> > Intersect(const Plane &PlaneA, const Plane &PlaneB, const Plane &PlaneC);
    //==================================end plane nomember function=====================================================
    
#include "NXPrimitive.inl"
}

#endif