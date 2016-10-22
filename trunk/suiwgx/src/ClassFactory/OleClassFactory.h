// ���ڿƼ���Ȩ���� 2010-2011
// 
// �ļ�����OleClassFactory.h
// ��  �ܣ�ʵ��OleClassFactory�ӿ�
// 
// ��  �ߣ�MPF������
// ʱ  �䣺2010-08-31
// 
// ============================================================================

#ifndef _OLECLASSFACTORY_H_
#define _OLECLASSFACTORY_H_

class OleClassFactory : public IClassFactory
{
public:

    static OleClassFactory* Ins();

    HRESULT WINAPI QueryInterface(REFIID iid, void ** ppvObject);
    ULONG WINAPI AddRef(void);
    ULONG WINAPI Release(void);

    HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppvObject);
    HRESULT STDMETHODCALLTYPE LockServer(BOOL fLock);

private:

    OleClassFactory();

    LONG _refCount;
};

#endif
