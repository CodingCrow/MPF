// ======================================================================
//
// Copyright (c) 2008-2012 ����, Inc. All rights reserved.
//
// suiwgx��Դ����ѭCPLЭ����п�Դ���κθ��˻�����������ʹ�ã������ܾ��ڴ˿������κ���ҵ���ʵĿ����롣
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// TextEditor.cpp

#include <Extend/Richedit/TextEditor.h>
#include "TextContainer.h"

namespace suic
{

TextEditor::TextEditor()
{
    _textContainer = new TextContainer();
    _textContainer->ref();
}

TextEditor::~TextEditor()
{
    _textContainer->unref();
}

}
