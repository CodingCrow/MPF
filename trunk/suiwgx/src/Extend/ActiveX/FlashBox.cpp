// ======================================================================
//
// Copyright (c) 2008-2020 ����(�ӵ�UI), Inc. All rights reserved.
//
// MPF�����������ʹ�ã������˾�빺����Ȩ�������ܾ��ڴ˿������κ���ҵ���ʵĿ����롣
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// FlashBox.cpp

#include "stdafx.h"

#include "flash10a.tlh"
#include <System/Windows/CoreTool.h>
#include <System/Tools/CoreHelper.h>
#include <Extend/ActiveX/FlashBox.h>

namespace suic
{

ImplementRTTIOfClass(FlashBox, ActiveX)

suic::DpProperty* FlashBox::SourceProperty;
suic::DpProperty* FlashBox::PlayProperty;

void FlashBox::OnPlayPropChanged(suic::DpObject* d, suic::DpPropChangedEventArg* e)
{
    FlashBox* pFlash = suic::RTTICast<FlashBox>(d);
    if (NULL != pFlash)
    {
        if (e->GetNewValue()->ToBool())
        {
            pFlash->Play();
        }
        else
        {
            pFlash->Stop();
        }
    }
}

bool FlashBox::StaticInit()
{
    if (NULL == SourceProperty)
    {
        SourceProperty = suic::DpProperty::Register(_U("Source"), RTTIType(), suic::OString::RTTIType()
            , suic::DpPropMemory::GetPropMeta(suic::OString::EmptyString, suic::PropMetadataOptions::AffectsRender));
        PlayProperty  = suic::DpProperty::Register(_U("Play"), RTTIType(), suic::Boolean::RTTIType()
            , suic::DpPropMemory::GetPropMeta(suic::Boolean::False, suic::PropMetadataOptions::AffectsRender, &FlashBox::OnPlayPropChanged));
    }

    return true;
}

FlashBox::FlashBox()
    : ActiveX(new ActiveXSite())
{
}

FlashBox::~FlashBox()
{
}

// flash�ؼ������ʶ����������flash�ؼ�
const suic::String FLASH_CLSID = _T("{D27CDB6E-AE6D-11CF-96B8-444553540000}");

bool FlashBox::LoadMovie(suic::String uri)
{
    if (uri.Empty())
    {
        return false;
    }

    // 
    // ���������flash�ļ��ľ���·����ַ
    //
    suic::String strUri = suic::FileDir::CalculatePath(uri);

    IShockwaveFlash* pFlash = NULL;
    QueryControl(__uuidof(IShockwaveFlash), (void**)&pFlash);

    if (pFlash != NULL)
    {
        // 
        // ���ļ�����flash�����в���
        //
        HRESULT hr = pFlash->LoadMovie(0, _bstr_t(strUri.c_str()));

        // 
        // �ؼ�ʹ����ϼǵü������ü���
        //
        pFlash->Release();

        //
        // ����ؼ�
        //
        DoVerb(OLEIVERB_INPLACEACTIVATE);

        return true;
    }
    else
    {
        return false;
    }
}

void FlashBox::SetTransparent(bool bTransparent)
{
    IShockwaveFlash* pFlash = NULL;
    QueryControl(__uuidof(IShockwaveFlash), (void**)&pFlash);

    if (pFlash != NULL) 
    {
        pFlash->put_WMode(_bstr_t(_T("Transparent")));
        pFlash->Release();
    }
}

void FlashBox::Play()
{
    LoadActiveX(FLASH_CLSID);

    IShockwaveFlash* pFlash = NULL;
    QueryControl(__uuidof(IShockwaveFlash), (void**)&pFlash);

    if (pFlash != NULL) 
    {
        pFlash->Play();
        pFlash->Release();
    }
}

void FlashBox::Pause()
{
    IShockwaveFlash* pFlash = NULL;
    QueryControl(__uuidof(IShockwaveFlash), (void**)&pFlash);

    if (pFlash != NULL) 
    {
        if (_site)
        {
            SetTransparent(true);
            LoadMovie(GetSource());
        }

        pFlash->StopPlay();
        pFlash->Release();
    }

}

void FlashBox::Stop()
{
    IShockwaveFlash* pFlash = NULL;
    QueryControl(__uuidof(IShockwaveFlash), (void**)&pFlash);

    if (pFlash != NULL) 
    {
        pFlash->StopPlay();
        pFlash->Release();
    }
}

/////////////////////////////////////////////////////////////////
//
void FlashBox::OnInitialized(suic::EventArg* e)
{
    ActiveX::OnInitialized(e);

    suic::ObjectPtr obj(GetValue(SourceProperty));

    if (obj)
    {
        SetSource(obj->ToString());
    }
}

void FlashBox::OnRender(suic::Drawing* drawing)
{
    ActiveX::OnRender(drawing);
}

void FlashBox::OnRenderSizeChanged(suic::SizeChangedInfo& e)
{
    suic::Rect rect(GetRenderBound(this));
    if (_site)
    {
        _site->SetControlRect(&rect);
    }
}

void FlashBox::OnVisibilityChanged()
{
    //ActiveX::OnVisibilityChanged();
}

bool FlashBox::OpenOverride()
{
    if (IsLoaded())
    {
        suic::Rect rect(GetRenderBound(this));
        if (_site)
        {
            _site->SetControlRect(&rect);

            SetTransparent(true);
            LoadMovie(GetSource());
        }
    }

    return true;
}

void FlashBox::OnLoaded(suic::LoadedEventArg* e)
{
    LoadActiveX(FLASH_CLSID);

    suic::Rect rect(GetRenderBound(this));
    if (_site)
    {
        _site->SetControlRect(&rect);

        SetTransparent(true);
        LoadMovie(GetSource());
    }

    ActiveX::OnLoaded(e);
}

void FlashBox::OnUnloaded(suic::LoadedEventArg* e)
{
    Stop();
    ActiveX::OnUnloaded(e);
}

}
