// ���ڿƼ���Ȩ���� 2010-2011
// 
// �ļ�����SystemParameters.h
// ��  �ܣ�����ϵͳ������
// 
// ��  �ߣ�MPF������
// ʱ  �䣺2010-07-02
// 
// ============================================================================

#ifndef _UISYSTEMPARAMETERS_H_
#define _UISYSTEMPARAMETERS_H_

#include <System/Types/StringCore.h>

namespace suic
{

struct SUICORE_API SystemParameters
{
    static int MessageFontSize;
    static String MessageFontName;

    static Float DpiX;
    static Float DpiY;

    static Float DpiScaleX;
    static Float DpiScaleY;

    static float RoundDpiValue(float val, float dpiScale);

    static fSize TransformToDevice(fSize size);
    static fSize TransformFromDevice(fSize size);

    static fRect TransformToDevice(fRect rect);
    static fRect TransformFromDevice(fRect rect);
};

}

#endif
