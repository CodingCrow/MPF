// ���ڿƼ���Ȩ���� 2010-2011
// 
// �ļ�����Rectangle.h
// ��  �ܣ����οؼ���
// 
// ��  �ߣ�MPF������
// ʱ  �䣺2011-07-02
// 
// ============================================================================


#ifndef _UIRECTANGLE_H_
#define _UIRECTANGLE_H_

#include <Framework/Controls/Shape.h>

namespace suic
{

class SUICORE_API Rectangle : public Shape
{
public:

    static DpProperty* RadiusXProperty;
    static DpProperty* RadiusYProperty;

    static bool StaticInit();

    Rectangle();
    virtual ~Rectangle();

    RTTIOfClass(Rectangle)

    Float GetRadiusX();
    Float GetRadiusY();

    void SetRadiusX(Float val);
    void SetRadiusY(Float val);

protected:

    fSize OnMeasure(const fSize& size);
    void OnRenderSizeChanged(SizeChangedInfo& e);

    void OnRender(Drawing* drawing);
};

inline Float Rectangle::GetRadiusX()
{
    return GetValue(RadiusXProperty)->ToFloat();
}

inline Float Rectangle::GetRadiusY()
{
    return GetValue(RadiusYProperty)->ToFloat();
}

inline void Rectangle::SetRadiusX(Float val)
{
    SetValue(RadiusXProperty, new OFloat(val));
}

inline void Rectangle::SetRadiusY(Float val)
{
    SetValue(RadiusYProperty, new OFloat(val));
}

}

#endif
