// ���ڿƼ���Ȩ���� 2010-2011
// 
// �ļ�����ThemeInfo.h
// ��  �ܣ�������Ŀ�����������
// 
// ��  �ߣ�Sharpui������
// ʱ  �䣺2010-07-02
// 
// ============================================================================

#ifndef _UITHEMEINFO_H_
#define _UITHEMEINFO_H_

#include <System/Types/Structure.h>
#include <System/Types/StreamDef.h>
#include <System/Graphics/Resource.h>

namespace suic 
{

class SUICORE_API IThemeInfo : public Object
{
public:

    virtual ~IThemeInfo() {}

    virtual int ReadRes(const String& key, ISStream* data) = 0;
};

class SUICORE_API ThemeCreator
{
public:

    /// <summary>
    ///  ����һ��Ŀ¼����������ﷵ��IThemeInfo�Ѿ����������ü���
    ///  �ⲿʹ�ú�������unref�ͷ�
    /// </summary>
    /// <param name="dir">Ŀ¼</param>
    /// <returns>�����������</returns>
    static IThemeInfo* CreateDir(const String& dir);
    static IThemeInfo* CreateTheme(const String& path, const String& pwd);
    static IThemeInfo* CreateMemory(ByteStream& data, const String& pwd);

private:

    ThemeCreator();
};

enum ResReadFrom
{
    rrfDef,
    rrfApp,
    rrfRes,
    rrfFile,
    rrfSysDir,
    rrfSysRes,
};

/// 
/// <Summary>
///  ��ȡ��Դʱ����������Ϣ
/// </Summary>
/// 
struct ResContext
{
    String resPath;
    ResReadFrom rftType;    
    IThemeInfo* resInfo;

    ResContext() : resInfo(NULL), rftType(ResReadFrom::rrfDef) {}
};

}

#endif
