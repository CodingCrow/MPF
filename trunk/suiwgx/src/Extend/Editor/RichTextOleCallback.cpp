// ======================================================================
//
// Copyright (c) 2008-2012 ����, Inc. All rights reserved.
//
// suiwgx��Դ����ѭCPLЭ����п�Դ���κθ��˻�����������ʹ�ã������ܾ��ڴ˿������κ���ҵ���ʵĿ����롣
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// RichEditOleCallback.cpp

#include "stdafx.h"
#include "ReadStmOp.h"
#include "RichTextOleCallback.h"
#include <TOM.h>

static suic::String SharpuiStmName = L"SharpuiStm";

EXTERN_C const CLSID CLSID_UIOleObject;

static bool CreateNewStorageObject(IStorage** lpStg)
{
    //static IStorage* s_stg = NULL;
    const UINT flag = STGM_TRANSACTED | STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE;
    HRESULT lr = ::StgCreateDocfile(NULL, flag, 0 , lpStg);

    /*if (s_stg == NULL)
    {
        ::StgCreateDocfile(NULL, flag, 0 , &s_stg);
    }

    static int iCount = 0;
    String strName;

    strName.Format(_U("SharpuiStg_%d"), ++iCount);

    HRESULT lr = s_stg ->CreateStorage(strName.c_str(), flag, 0 , 0 , lpStg);*/

    if (NOERROR == lr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

UIOleObject::UIOleObject(suic::Embbed* embbed)
    : _embbedObj(embbed)
    , _clientSite(NULL)
{
    if (_embbedObj)
    {
        _embbedObj->ref();
    }
}

UIOleObject::~UIOleObject()
{
    _embbedObj->unref();
}

void UIOleObject::Render(suic::Drawing* drawing, suic::Rect rect)
{
    if (_embbedObj)
    {
        _embbedObj->Arrange(rect.TofRect());
        _embbedObj->Render(drawing);
    }
}

suic::Embbed* UIOleObject::GetEmbbedObj() const
{
    return _embbedObj;
}

bool UIOleObject::SaveToStream(suic::ISStream* stm)
{
    OleHeader oleHead;
    suic::Mulstr name(_embbedObj->GetRTTIType()->typeName);

    oleHead.type = _embbedObj->GetType();
    strcpy(oleHead.typeName, name.c_str());
    stm->Write((suic::Byte*)&oleHead, sizeof(OleHeader));
    _embbedObj->Save(stm);

    return true;
}

bool UIOleObject::LoadFromStream(suic::ISStream* stm)
{
    OleHeader oleHead;
    int iHeadSize = sizeof(OleHeader);
    bool bFindStm = false;

    if (iHeadSize == stm->Read((suic::Byte*)&oleHead, iHeadSize) && 
        oleHead.cbSize == 72)
    {
        bFindStm = true;
    }

    if (!bFindStm)
    {
        return false;
    }

    if (NULL == _embbedObj)
    {
        suic::RTTIOfInfo* rttiInfo = suic::BuildFactory::Ins()->Lookup(oleHead.typeName);
        if (NULL != rttiInfo)
        {
            _embbedObj = dynamic_cast<suic::Embbed*>(rttiInfo->Create());
            _embbedObj->ref();
        }
    }

    if (NULL == _embbedObj)
    {
        return false;
    }
    else
    {
        _embbedObj->Restore(oleHead.type, stm);

        return true;
    }
}

HRESULT WINAPI UIOleObject::GetUserClassID(CLSID *pClsid)
{
    *pClsid = CLSID_UIOleObject;
    return S_OK;
}

void UIOleObject::MeasureEmbbed(LPSIZEL lpsizel)
{
    if (_embbedObj)
    {
        suic::fSize contraint(suic::FloatUtil::PosInfinity, suic::FloatUtil::PosInfinity);
        _embbedObj->Measure(contraint);
        lpsizel->cx = ::MulDiv(_embbedObj->GetDesiredSize().cx, 2540, suic::SystemParameters::DpiX);
        lpsizel->cy = ::MulDiv(_embbedObj->GetDesiredSize().cy, 2540, suic::SystemParameters::DpiY);
    }
}

HRESULT WINAPI UIOleObject::SetExtent(DWORD dwDrawAspect, SIZEL *lpsizel)
{
    MeasureEmbbed(lpsizel);
    return S_OK;
}

HRESULT WINAPI UIOleObject::GetExtent(DWORD dwDrawAspect, LONG lindex, DVTARGETDEVICE *ptd, LPSIZEL lpsizel)
{
    MeasureEmbbed(lpsizel);
    return S_OK;
}

//=================================================================
// OleDataObj

OleDataObj::OleDataObj()
{
    _refCount = 0;
}

HRESULT STDMETHODCALLTYPE OleDataObj::QueryInterface(REFIID iid, void** ppvObject)
{
    HRESULT hr = S_OK;
    *ppvObject = NULL;
    hr = E_NOINTERFACE;

    return hr;
}

ULONG STDMETHODCALLTYPE OleDataObj::AddRef()
{
    return ++_refCount;
}

ULONG STDMETHODCALLTYPE OleDataObj::Release()
{
    if (--_refCount == 0)
    {
        delete this ;
    }
    return _refCount;
}

HRESULT WINAPI OleDataObj::GetData(FORMATETC *pformatetcIn, STGMEDIUM *pmedium)
{
    return S_OK;
}

HRESULT WINAPI OleDataObj::GetDataHere(FORMATETC* pformatetc, STGMEDIUM*  pmedium)
{
    return E_NOTIMPL;
}

HRESULT WINAPI OleDataObj::QueryGetData(FORMATETC*  pformatetc)
{
    return E_NOTIMPL;
}

HRESULT WINAPI OleDataObj::GetCanonicalFormatEtc(FORMATETC*  pformatectIn, FORMATETC* pformatetcOut)
{
    return E_NOTIMPL;
}

HRESULT WINAPI OleDataObj::SetData(FORMATETC* pformatetc, STGMEDIUM*  pmedium, BOOL  fRelease)
{
    return S_OK;
}

HRESULT WINAPI OleDataObj::EnumFormatEtc(DWORD  dwDirection , IEnumFORMATETC** ppenumFormatEtc)
{
    return E_NOTIMPL;
}

HRESULT WINAPI OleDataObj::DAdvise(FORMATETC *pformatetc, DWORD advf, IAdviseSink *pAdvSink, DWORD *pdwConnection)
{
    return E_NOTIMPL;
}

HRESULT WINAPI OleDataObj::DUnadvise(DWORD dwConnection)
{
    return E_NOTIMPL;
}

HRESULT WINAPI OleDataObj::EnumDAdvise(IEnumSTATDATA **ppenumAdvise)
{
    return E_NOTIMPL;
}

bool UIOleObject::IsSharpuiClsid(const CLSID& clsid)
{
    return IsEqualCLSID(clsid, CLSID_UIOleObject) != 0;
}

bool UIOleObject::InsertOleObj(IRichEditOle* pRichEditOle, suic::Int32 cp, suic::Embbed* embbed)
{
    HRESULT hr = 0;
    IOleClientSite *pOleClientSite = NULL;

    // ��ȡrichedit��IOleClientSite�������ǵĶ��󽫻��ɴ˶������
    // ��Richeditʵ������COleObject����
    pRichEditOle->GetClientSite(&pOleClientSite);
    IStorage *pStorage = NULL;

    embbed->ref();

    CreateNewStorageObject(&pStorage);

    //
    // ���������Լ���IOleObject����
    //
    UIOleObject *pOleImage = new UIOleObject(embbed);
    IOleObject *pOleObject = NULL;

    //
    // �õ�IOleObject��������ʵ�ʾ���OleImage����
    //
    pOleImage->QueryInterface(IID_IOleObject, (void**)&pOleObject);
    pOleObject->SetClientSite(pOleClientSite);

    //
    // ֪ͨ��������
    //
    hr = ::OleSetContainedObject(pOleObject, TRUE);

    //
    // ���湹���������Object��Ϣ
    //
    REOBJECT reobject;
    ZeroMemory(&reobject, sizeof(REOBJECT));
    reobject.cbStruct = sizeof(REOBJECT);

    //
    // �����Լ��������ID
    //
    pOleImage->GetUserClassID(&(reobject.clsid));

    //
    // REO_CP_SELECTION:�ڵ�ǰѡ��λ�ò������
    //
    if (cp < 0)
    {
        reobject.cp = REO_CP_SELECTION;
    }
    else
    {
        reobject.cp = cp;
    }

    //
    // �����Ժ��ַ�ʽ��ʾ��RTF��
    // DVASPECT_CONTENT��ʾ��������
    //
    reobject.dvaspect = DVASPECT_CONTENT;
    reobject.poleobj = pOleObject;
    reobject.polesite = pOleClientSite;
    reobject.pstg = pStorage;
    reobject.dwUser = 0;

    //
    // ���õײ��Ļ��߶���
    //
    reobject.dwFlags = REO_BELOWBASELINE;

    //
    // ����һ������,��������pStorage��AddRef
    //
    pRichEditOle->InsertObject(&reobject);
    pStorage->SetClass(CLSID_UIOleObject);

    pOleObject->Release();
    pOleClientSite->Release();
    pStorage->Release();
    pOleImage->Release();

    embbed->unref();

    return true;
}

//============================================================
//
RichEditOleCallback::RichEditOleCallback()
    : _textSrv(NULL)
{
    _oldDataObj = new OleDataObj();
    _storage = NULL;
    _storageCount = 0 ;
    _refCount = 0 ;

    const UINT flag = STGM_TRANSACTED | STGM_READWRITE | STGM_SHARE_EXCLUSIVE;
    //::StgCreateDocfile(NULL, flag, 0 , &_storage);

    _oldDataObj->AddRef();
}

RichEditOleCallback::~RichEditOleCallback()
{
    _oldDataObj->Release();
}

HRESULT STDMETHODCALLTYPE 
RichEditOleCallback::GetNewStorage(LPSTORAGE* lplpstg)
{
    CreateNewStorageObject(lplpstg);
    
    /*static int g_iStorages = 0;
    suic::String strName;
    const UINT flag = STGM_TRANSACTED | STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE;

    strName.Format(_U("REOLEStorage%d"), ++g_iStorages);
    _storage->CreateStorage(strName.c_str(), flag, 0, 0, lplpstg);*/

    return NOERROR;
}

EXTERN_C const IID IID_IRichEditOleExCallback = { 0x00020D03,0,0,{0xC0,0,0,0,0,0,0,0x46}};

HRESULT STDMETHODCALLTYPE 
RichEditOleCallback::QueryInterface(REFIID iid, void** ppvObject)
{
    HRESULT hr = S_OK;
    * ppvObject = NULL;

    if (iid == IID_IUnknown || iid == IID_IRichEditOleExCallback)
    {
        *ppvObject = this ;
        hr = NOERROR;

        AddRef();
    }
    else
    {
        hr = E_NOINTERFACE;
    }

    return hr;
}

ULONG STDMETHODCALLTYPE RichEditOleCallback::AddRef()
{
    return ++ _refCount;
}

ULONG STDMETHODCALLTYPE RichEditOleCallback::Release()
{
    if (--_refCount == 0)
    {
        delete this ;
        return 0 ;
    }
    return _refCount;
}

HRESULT STDMETHODCALLTYPE 
RichEditOleCallback::GetInPlaceContext(LPOLEINPLACEFRAME FAR* lplpFrame,
    LPOLEINPLACEUIWINDOW FAR* lplpDoc, LPOLEINPLACEFRAMEINFO lpFrameInfo)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE RichEditOleCallback::ShowContainerUI(BOOL fShow)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE RichEditOleCallback::
QueryInsertObject(LPCLSID lpclsid, LPSTORAGE lpstg, LONG cp)
{
    //
    // ���������Լ���IOleObject��ֱ�ӷ���
    //
    if ((*lpclsid) == CLSID_UIOleObject)
    {
        return NOERROR;
    }
    /*else if (IsEqualCLSID((*lpclsid), CLSID_StaticMetafile) ||
        IsEqualCLSID((*lpclsid), CLSID_StaticDib) ||
        IsEqualCLSID((*lpclsid), CLSID_Picture_EnhMetafile))
    {
        return NOERROR;
    }*/
    else
    {
        return E_NOTIMPL;
    }
    /*
    BOOL IsExcelCLSID(REFGUID clsid)
{
	DWORD i;

    for( i = 0; i < cclsidExcel; i++ )
    {
        if (IsEqualCLSID(clsid, rgclsidExcel[i]))
        {
			return TRUE;
        }
    }

    return FALSE;
}
    // 
// data private to this file
//
static const OLECHAR szSiteFlagsStm[] = OLESTR("RichEditFlags");	

// 
// EXCEL clsid's.  We have to make some special purpose hacks
// for XL.
const CLSID rgclsidExcel[] =
{
    { 0x00020810L, 0, 0, {0xC0, 0, 0, 0, 0, 0, 0, 0x46} },  // Excel Worksheet
    { 0x00020811L, 0, 0, {0xC0, 0, 0, 0, 0, 0, 0, 0x46} },  // Excel Chart
    { 0x00020812L, 0, 0, {0xC0, 0, 0, 0, 0, 0, 0, 0x46} },  // Excel App1
    { 0x00020841L, 0, 0, {0xC0, 0, 0, 0, 0, 0, 0, 0x46} },  // Excel App2
};
const INT cclsidExcel = sizeof(rgclsidExcel) / sizeof(rgclsidExcel[0]);


//
//	WordArt CLSID for more special purpose hacks.
//
const GUID CLSID_WordArt = 
    { 0x000212F0L, 0, 0, {0xC0, 0, 0, 0, 0, 0, 0, 0x46} };
const GUID CLSID_PaintbrushPicture = 
    { 0x0003000AL, 0x0000, 0x0000, { 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 } };
const GUID CLSID_BitmapImage = 
    { 0xD3E34B21L, 0x9D75, 0x101A, { 0x8C, 0x3D, 0x00, 0xAA, 0x00, 0x1A, 0x16, 0x52 } };

    if( IsEqualCLSID(preobj->clsid, CLSID_StaticMetafile) ||
		IsEqualCLSID(preobj->clsid, CLSID_StaticDib) ||
		IsEqualCLSID(preobj->clsid, CLSID_Picture_EnhMetafile) )
	{
		_pi.dwFlags |= REO_STATIC;
	}
	else if( IsExcelCLSID(preobj->clsid) )
	{
		_pi.dwFlags |= REO_GETMETAFILE;
	}
	else if( IsEqualCLSID(preobj->clsid, CLSID_WordArt ) )
	{
		_fIsWordArt2 = TRUE;
	}
	else if(IsEqualCLSID(preobj->clsid, CLSID_PaintbrushPicture) ||
			IsEqualCLSID(preobj->clsid, CLSID_BitmapImage))
	{
    }
    */
}

HRESULT STDMETHODCALLTYPE RichEditOleCallback::DeleteObject(LPOLEOBJECT lpoleobj)
{
    /*OleImage* imgole(dynamic_cast<OleImage*>(lpoleobj));
    if (imgole)
    {
    }*/
    return S_OK;
}

HRESULT STDMETHODCALLTYPE RichEditOleCallback::
QueryAcceptData(LPDATAOBJECT lpdataobj, CLIPFORMAT FAR * lpcfFormat
                , DWORD reco, BOOL fReally, HGLOBAL hMetaPict)
{
    //return E_NOTIMPL;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE RichEditOleCallback::ContextSensitiveHelp(BOOL fEnterMode)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE 
RichEditOleCallback::GetClipboardData(CHARRANGE FAR * lpchrg, DWORD reco, LPDATAOBJECT FAR * lplpdataobj)
{
    return E_NOTIMPL;
    if (!_textSrv)
    {
        return S_OK;
    }

    IRichEditOle *pRichEditOle = NULL;
    _textSrv->TxSendMessage(EM_GETOLEINTERFACE, 0, (LPARAM)&pRichEditOle, 0);

    if (pRichEditOle == NULL)
    {
        return S_OK;
    }
    
    HRESULT hr = S_OK;
    int nObjCount = pRichEditOle->GetObjectCount();
    for (int i = 0;i < nObjCount; i++)
    {
        bool bFind = false;
        suic::Rect rect;
        REOBJECT reo;
        ZeroMemory(&reo, sizeof(REOBJECT));
        reo.cbStruct = sizeof(REOBJECT);

        hr = pRichEditOle->GetObject(i, &reo, REO_GETOBJ_POLEOBJ);
        if (reo.cp >= lpchrg->cpMin && reo.cp <= lpchrg->cpMax)
        {
            UIOleObject* oleimg = dynamic_cast<UIOleObject*>(reo.poleobj);
            *lplpdataobj = (LPDATAOBJECT)oleimg;
            bFind = true;
        }

        if (reo.poleobj)
        {
            reo.poleobj->Release();
        }
        if (reo.pstg)
        {
            reo.pstg->Release();
        }
        if (reo.polesite)
        {
            reo.polesite->Release();
        }

        if (bFind)
        {
            break;
        }
    }

    pRichEditOle->Release();

    return S_OK;
}

HRESULT STDMETHODCALLTYPE RichEditOleCallback::
GetDragDropEffect(BOOL fDrag, DWORD grfKeyState, LPDWORD pdwEffect)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE RichEditOleCallback::
GetContextMenu(WORD seltyp, LPOLEOBJECT lpoleobj, CHARRANGE FAR * lpchrg, HMENU FAR* lphmenu)
{
    return S_OK;
}
