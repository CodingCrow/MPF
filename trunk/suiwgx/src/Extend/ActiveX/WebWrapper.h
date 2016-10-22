// ���ڿƼ���Ȩ���� 2010-2011
// 
// �ļ�����WebWrapper.h
// ��  �ܣ���װWEB�ؼ���
// 
// ��  �ߣ�����
// ʱ  �䣺2012-07-02
// 
// ============================================================================

# ifndef _UIWEBWRAPPER_H_
# define _UIWEBWRAPPER_H_

#include <sui/sharpuiconfig.h>
#include <sui/activexsite.h>

class WebWrapper : public ActiveXSite
{
public:

    WebWrapper();
    ~WebWrapper(void);

public:

    IWebBrowser2* GetWebBrowser2();
    IHTMLDocument2* GetHTMLDocument2();
    IHTMLDocument3* GetHTMLDocument3();
    IHTMLWindow2* GetHTMLWindow2();
    IHTMLEventObj* GetHTMLEventObject();
  
    BOOL OpenWebBrowser();
    BOOL OpenURL(LPCTSTR pUrl);

private:

    bool  _bWebWndInited;

private:

    IStorage* _pStorage;
    IWebBrowser2* _pWB2;
    IHTMLDocument2* _pHtmlDoc2;
    IHTMLDocument3* _pHtmlDoc3;
    IHTMLWindow2* _pHtmlWnd2;
    IHTMLEventObj* _pHtmlEvent;
};

# endif
