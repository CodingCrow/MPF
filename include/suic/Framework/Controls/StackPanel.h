// ���ڿƼ���Ȩ���� 2010-2011
// 
// �ļ�����StackPanel.h
// ��  �ܣ�ջʽ���
// 
// ��  �ߣ�MPF������
// ʱ  �䣺2010-08-31
// 
// =============================================================

#ifndef _UISTACKPANEL_H_
#define _UISTACKPANEL_H_

#include <Framework/Controls/Panel.h>
#include <System/Windows/ScrollInfo.h>

namespace suic
{

/// <summary>
/// StackPanel��
/// </summary>
class SUICORE_API StackPanel : public Panel
{
public:

    static DpProperty* OrientationProperty;

    static void OnOrientationPropChanged(DpObject* d, DpPropChangedEventArg* e);
    static bool StaticInit();

    StackPanel();
    virtual ~StackPanel();

    RTTIOfClass(StackPanel)

    /// <summary>
    ///  ��ȡ����Ԫ�صķ���
    /// </summary>
    /// <remarks>
    ///  ����Ԫ�صķ����Ϊˮƽ�ʹ�ֱ��Horizontal��Vertical����
    /// </remarks>
    /// <returns>Horizontal: ˮƽ; Vertical: ��ֱ</returns> 
    Orientation GetOrientation();
    void SetOrientation(Orientation val);

    int GetLogicalOrientation();
    int GetVisibleIndex() const;
    int GetVisibleCount() const;
    int GetVisibleOffset() const;

    int GetVisibleChildrenCount();
    Element* GetVisibleChild(int index);
    void NotifyItemChanged();

protected:

    IScrollInfo* GetScrollInfo();
    ScrollData* GetScrollData();
    bool IsScrolling();

protected:

    void OnInitialized(EventArg* e);
    void OnItemsChangedInternal(Object* sender, ItemsChangedEventArg* e);

    fSize OnMeasure(const fSize& constraintSize);
    void OnArrange(const fSize& arrangesize);

private:

    void OnScrollChange();
    void EnsureScrollingData(fSize viewport, fSize extent, fPoint offset);

private:

    int _visibleIndex;
    int _visibleCount;
    Float _visibleOffset;
    ScrollInfo* _scrollInfo;
};

inline Orientation StackPanel::GetOrientation()
{
    return (Orientation)GetValue(OrientationProperty)->ToInt();
}

inline int StackPanel::GetVisibleIndex() const
{
    return _visibleIndex;
}

inline int StackPanel::GetVisibleCount() const
{
    return _visibleCount;
}

inline int StackPanel::GetVisibleOffset() const
{
    return _visibleOffset;
}

inline void StackPanel::SetOrientation(Orientation val)
{
    SetValue(OrientationProperty, OrientationBox::From(val));
}

inline int StackPanel::GetLogicalOrientation()
{
    return GetOrientation();
}

typedef shared<StackPanel> StackPanelPtr;

}

#endif
