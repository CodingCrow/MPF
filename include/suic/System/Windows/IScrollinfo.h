// ���ڿƼ���Ȩ���� 2010-2011
// 
// �ļ�����IScrollInfo.h
// ��  �ܣ�����֧�ֹ����ӿڣ���Panel������ʵ��֧�ֹ���
// 
// ��  �ߣ�MPF������
// ʱ  �䣺2010-08-31
// 
// =============================================================

#ifndef _UIISCROLLINFO_H_
#define _UIISCROLLINFO_H_

#include <System/Windows/Element.h>

namespace suic
{

class ScrollViewer;

class SUICORE_API IScrollInfo
{
public:

    virtual ~IScrollInfo() {}

    virtual void LineDown() = 0;
    virtual void LineLeft() = 0;
    virtual void LineRight() = 0;
    virtual void LineUp() = 0;
    virtual void MouseWheelDown() = 0;
    virtual void MouseWheelLeft() = 0;
    virtual void MouseWheelRight() = 0;
    virtual void MouseWheelUp() = 0;
    virtual void PageDown() = 0;
    virtual void PageLeft() = 0;
    virtual void PageRight() = 0;
    virtual void PageUp() = 0;

    virtual Rect MakeVisible(Element* visual, Rect rect) = 0;

    virtual Float GetComputeHorizontalOffset() = 0;
    virtual Float GetComputeVerticalOffset() = 0;

    virtual Float GetHorizontalOffset() const = 0;
    virtual Float GetVerticalOffset() const = 0;

    virtual void SetHorizontalOffset(int offset) = 0;
    virtual void SetVerticalOffset(int offset) = 0;

    virtual bool CanHorizontalScroll() const = 0;
    virtual bool CanVerticalScroll() const = 0;

    virtual void SetCanHorizontalScroll(bool val) = 0;
    virtual void SetCanVerticalScroll(bool val) = 0;

    virtual void EnableHorizontalScroll(bool val) = 0;
    virtual void EnableVerticalScroll(bool val) = 0;
    
    virtual Float GetExtentHeight() const = 0;
    virtual Float GetExtentWidth() const = 0;

    virtual Float GetViewportHeight() const = 0;
    virtual Float GetViewportWidth() const = 0;

    virtual ScrollViewer* GetScrollOwner()  const = 0;
    virtual void SetScrollOwner(ScrollViewer* val) = 0;
};

}

#endif
