
class DIBHelper
{
public:

    static void FreeBytes(suic::Byte* lpBytes)
    {
        if (lpBytes != NULL)
        {
            free(lpBytes);
        }
    }

    static suic::Byte* DIBFromBitmap(HBITMAP bmp, suic::Uint32& size)
    {
        // ָ��λͼ��Ϣͷ�ṹ  
        LPBITMAPINFOHEADER lpbi;

        if (bmp != NULL)
        {
            HDC hDC = NULL;
            
            // ��ǰ�ֱ�����ÿ������ռ�ֽ���
            int iBits;

            // λͼ��ÿ������ռ�ֽ���
            WORD wBitCount;

            // �����ɫ���С,λͼ�������ֽڴ�С,λͼ�ļ���С,д���ļ��ֽ��� 
            DWORD dwPaletteSize = 0;
            DWORD dwBmBitsSize = 0;
            DWORD dwDIBSize = 0;
            DWORD dwWritten = 0; 

            // λͼ���Խṹ 
            BITMAP bmi;
            // λͼ��Ϣͷ�ṹ 
            BITMAPINFOHEADER bi;

            // �����ļ��������ڴ�������ɫ���� 
            HANDLE hPal = NULL;
            HANDLE hOldPal = NULL; 

            // ����λͼ�ļ�ÿ��������ռ�ֽ��� 
            hDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
            iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES); 
            ::DeleteDC(hDC);

            if (iBits <= 1)  
            {
                wBitCount = 1;
            }
            else if (iBits <= 4)  
            {
                wBitCount = 4; 
            }
            else if (iBits <= 8)  
            {
                wBitCount = 8; 
            }
            else     
            {
                wBitCount = 24;
            }

            // ȡ��Bitmap������Ϣ
            GetObject(bmp, sizeof(BITMAP), (LPVOID)&bmi);

            bi.biSize = sizeof(BITMAPINFOHEADER);
            bi.biWidth = bmi.bmWidth;
            bi.biHeight = bmi.bmHeight;
            bi.biPlanes = 1;
            bi.biBitCount = wBitCount;
            bi.biCompression = BI_RGB;
            bi.biSizeImage = 0;
            bi.biXPelsPerMeter = 0;
            bi.biYPelsPerMeter = 0;
            bi.biClrImportant = 0;
            bi.biClrUsed  = 0;

            dwBmBitsSize = ((bmi.bmWidth * wBitCount + 31) / 32) * 4 * bmi.bmHeight;

            size = dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER);
            // Ϊλͼ���ݷ����ڴ� 
            lpbi = (LPBITMAPINFOHEADER)malloc(size);
            *lpbi = bi;

            // �����ɫ��  
            hPal = GetStockObject(DEFAULT_PALETTE); 
            if (hPal) 
            {
                hDC = ::GetDC(NULL); 
                hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE); 
                RealizePalette(hDC); 
            }

            // ��ȡ�õ�ɫ�����µ�����ֵ 
            GetDIBits(hDC, bmp, 0, (UINT)bmi.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) 
                + dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS); 

            //�ָ���ɫ��  
            if (hOldPal) 
            { 
                ::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE); 
                RealizePalette(hDC); 
                ::ReleaseDC(NULL, hDC); 
            }
        }

        return (suic::Byte*)lpbi;
    }
};