// ���ڿƼ���Ȩ���� 2010-2011
// 
// �ļ�����Canvas.h
// ��  �ܣ��������֣��������ꡣ
// 
// ��  �ߣ�MPF������
// ʱ  �䣺2011-07-02
// 
// ============================================================================


#ifndef _UICANVAS_H_
#define _UICANVAS_H_

#include <Framework/Controls/Panel.h>

namespace suic
{

class SUICORE_API Canvas : public Panel
{
public:

    // �ӿؼ���Canvas�����Ͻǵ�x���꣨Integer���ͣ��������ԣ�
    static DpProperty* LeftProperty;
    static DpProperty* TopProperty;
    static DpProperty* RightProperty;
    static DpProperty* BottomProperty;

    static bool StaticInit();

    Canvas();
    virtual ~Canvas();

    RTTIOfClass(Canvas)

    static Float GetLeft(Element* element);
    static Float GetTop(Element* element);
    static Float GetRight(Element* element);
    static Float GetBottom(Element* element);

    static void SetLeft(Element* element, Float val);
    static void SetTop(Element* element, Float val);
    static void SetRight(Element* element, Float val);
    static void SetBottom(Element* element, Float val);

protected:

    fSize OnMeasure(const fSize& size);
    void OnArrange(const fSize& arrangeSize);
};

}

#endif
