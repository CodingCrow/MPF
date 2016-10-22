//////////////////////////////////////////////////////////////////////////////
// ComboBoxItem.cpp

#include <Extend/Controls/ComboBoxItem.h>
#include <Framework/Controls/Selector.h>
#include <System/Tools/VisualTreeOp.h>
#include <System/Windows/CoreTool.h>

namespace suic
{

ImplementRTTIOfClass(ComboBoxItem, ListBoxItem)

/// <summary>
///  ��Ͽ�������ɼ�����������Ԫ��
/// </summary>
ComboBoxItem::ComboBoxItem()
{
}

ComboBoxItem::~ComboBoxItem()
{
}

bool ComboBoxItem::StaticInit()
{
    static bool s_init = false;
    if (!s_init)
    {
        s_init = true;
        IsMouseOverProperty->OverrideMetadata(RTTIType()
            , DpPropMemory::GetPropMeta(suic::Boolean::False, PropMetadataOptions::AffectsNone, &OnVisualStatePropChanged));
    }
    return true;
}

}
