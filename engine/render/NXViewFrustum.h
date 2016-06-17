/*
 *  File:    NXViewFrustum.h
 *  author:  张雄
 *  date:    2016_06_01
 *  purpose: 定义ViewFrustum及相应的一些操作函数
 */

#ifndef __ZX_NXENGINE_VIEWFRUSTUM_H__
#define __ZX_NXENGINE_VIEWFRUSTUM_H__

#include "../math/NXPlane.h"

namespace NX {
    class Sphere;
    class Ellipsoid;
    
    enum FRUSTUM_VISIBLE_TEST_BIT_MASK{
        VF_VT_FRONT     = 1 << 0,
        VF_VT_BACK      = 1 << 1,
        VF_VT_LEFT      = 1 << 2,
        VF_VT_RIGHT     = 1 << 3,
        VF_VT_TOP       = 1 << 4,
        VF_VT_BOTTOM    = 1 << 5,
        VF_VT_ALL       = (VF_VT_FRONT | VF_VT_BACK | VF_VT_LEFT | VF_VT_RIGHT | VF_VT_TOP | VF_VT_BOTTOM),
    };
    
    class ViewFrustum{
    public:
        ViewFrustum();
        ViewFrustum(const NX::Plane &Front, const NX::Plane &Back, const NX::Plane &left, const NX::Plane &Right, const NX::Plane &Top, const NX::Plane &Bottom);
        virtual ~ViewFrustum();
        
    public:
        inline NX::Plane GetFrontPlane()  const;
        inline NX::Plane GetBackPlane()   const;
        inline NX::Plane GetLeftPlane()   const;
        inline NX::Plane GetRightPlane()  const;
        inline NX::Plane GetTopPlane()    const;
        inline NX::Plane GetBottomPlane() const;
    
    public:
        /**几何体关于视堆的可视性测试*/
        bool Visible(const Sphere &sphere,              const FRUSTUM_VISIBLE_TEST_BIT_MASK mask = VF_VT_ALL);
        bool Visible(const Ellipsoid &ellipsoid,        const FRUSTUM_VISIBLE_TEST_BIT_MASK mask = VF_VT_ALL );
        
    private:
        NX::Plane     m_FrontPlane;
        NX::Plane     m_BackPlane;
        NX::Plane     m_LeftPlane;
        NX::Plane     m_RightPlane;
        NX::Plane     m_TopPlane;
        NX::Plane     m_BottomPlane;
    };
    
    inline NX::Plane ViewFrustum::GetFrontPlane()  const{
        return m_FrontPlane;
    }
    
    inline NX::Plane ViewFrustum::GetBackPlane()   const{
        return m_BackPlane;
    }
    
    inline NX::Plane ViewFrustum::GetLeftPlane()   const{
        return m_LeftPlane;
    }
    
    inline NX::Plane ViewFrustum::GetRightPlane()  const{
        return m_RightPlane;
    }
    
    inline NX::Plane ViewFrustum::GetTopPlane()    const{
        return m_TopPlane;
    }
    
    inline NX::Plane ViewFrustum::GetBottomPlane() const{
        return m_BottomPlane;
    }
}


#endif  //!__ZX_NXENGINE_VIEWFRUSTUM_H__