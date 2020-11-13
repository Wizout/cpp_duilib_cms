#include "cms-pdf.h"
#include "CMS-utils.h"

void String2text(PDF *p, int &TextFlow, CString &mPagenameAndDate, int fontsize)
{
	char characteristic_cn[100];
	int mPagenameAndDateSize = mPagenameAndDate.GetLength();//�ַ�������
	PDF_set_parameter(p, "FontOutline", "a=../Resource/MSYH.TTF");//����ġ�./font/STXINGKA.TTF��Ϊ�����ļ��Ĵ��·����Ҳ����˵��Ҫ���ֿ��ļ��ŵ���Ӧ��λ�ã���Ȼ����ɴ���
	sprintf_s(characteristic_cn, "fontname=a:0 fontsize = %d encoding = unicode textlen = %d", fontsize, mPagenameAndDateSize * 2);//�����ַ�
	PDF_add_textflow(p, TextFlow, (char *)(mPagenameAndDate).AllocSysString(), mPagenameAndDateSize * 2, characteristic_cn);//����ַ�������
}

void OutputStringToPDF(PDF *p, CString &mPagenameAndDate, int Left, int &Top, int Right, int Reduction, int fontsize)//�������
{
	//�ú���������ݵ�PDF�У���Ҫע������������ҳδ��ʱ������н��л�ҳ
	if (Top<130)
	{
		Top = 740;
		PDF_end_page_ext(p, ""); // �ر�ҳ�沢�����µ�ҳ��
		PDF_begin_page_ext(p, a4_width, a4_height, "");
	}
	int TextFlow = PDF_create_textflow(p, "", 0, "");//�����ַ���
	String2text(p, TextFlow, mPagenameAndDate, fontsize);
	while (true)
	{
		const char *returnstring = PDF_fit_textflow(p, TextFlow, Left, Top, Right, Top - Reduction, "");
		Top -= Reduction;
		if (strcmp(returnstring, "_boxfull") != 0)//��������
		{
			break;
		}
		if (Top<130)
		{
			Top = 740;
			PDF_end_page_ext(p, ""); // �ر�ҳ�沢�����µ�ҳ��
			PDF_begin_page_ext(p, a4_width, a4_height, "");
		}
	}
	PDF_delete_textflow(p, TextFlow);//�ͷ��ַ�������
}

bool CreatePDF(CString Content)
{
	PDF *p = NULL;
	int Left = 85, Top = 740, Right = a4_width - 85;
	//pdf���󴴽�
	if ((p = PDF_new()) == (PDF *)0)
	{
#ifdef CMS_DEBUG
		::MessageBox(NULL, L"Couldn't create PDFlib object (out of memory)!n", L"PDF error", MB_OK);

#endif // CMS_DEBUG

		return false;
	}
	PDF_TRY(p)
	{
		//�ȴ���PDF�ĵ�����Ϊoutout.pdf
		if (PDF_begin_document(p, PDF_FILE_PATH, 0, "") == -1)
		{
#ifdef CMS_DEBUG
			CString ws;
			std::string str = PDF_get_errmsg(p);
			ws.Format(L"Error: %sn", s2ws(str).c_str());
			//printf("Error: %sn", PDF_get_errmsg(p));
			::MessageBox(NULL, ws, L"PDF error", MB_OK);
#endif // CMS_DEBUG
			return false;
		}
		//�ٴ���PDF�ĵ������ҳ�棬������ҳ������ݣ����ﱾ�˽����װ������������
		PDF_begin_page_ext(p, a4_width, a4_height, "");
		//CString mPagenameAndDate = L"�������ƺ�֮ˮ������  ��������������\n";
		//mPagenameAndDate += L"�����������������׷�  ������˿ĺ��ѩ\n";
		//mPagenameAndDate += L"���������뾡��  Īʹ���׿ն���\n";
		//mPagenameAndDate += L"�����Ҳı�����  ǧ��ɢ��������\n";
		//mPagenameAndDate += L"������ţ��Ϊ��  ����һ�����ٱ�\n";
		//mPagenameAndDate += L"᯷���  ������  ������  ��Īͣ\n";
		//mPagenameAndDate += L"�����һ��  ���Ϊ�������\n";
		//mPagenameAndDate += L"�ӹ��������  ��Ը��������\n";
		//mPagenameAndDate += L"����ʥ�ͽԼ�į  Ω������������\n";
		//mPagenameAndDate += L"������ʱ��ƽ��  ����ʮǧ����\n";
		//mPagenameAndDate += L"���˺�Ϊ����Ǯ  �����ȡ�Ծ���\n";
		//mPagenameAndDate += L"�廨��  ǧ����\n";
		//mPagenameAndDate += L"��������������  ���ͬ����ų�\n";
		//�����������PDF������������Ϊ�������߾࣬���ĸ�����Ϊ����ĸ߶ȣ����������Ϊ������ұ߾࣬����������Ϊ�о࣬���߸���������Ĵ�С
		OutputStringToPDF(p, Content, Left, Top, Right, 45, 24);
		//ҳ����
		PDF_end_page_ext(p, "");
		//�ĵ�����
		PDF_end_document(p, "");
	}
	PDF_CATCH(p)//������Ϣ���
	{
#ifdef CMS_DEBUG
		//printf("[%d] %s: %sn", PDF_get_errnum(p), PDF_get_apiname(p), PDF_get_errmsg(p));
		CString ws;
		ws.Format(L"[%d] %s: %sn", PDF_get_errnum(p), PDF_get_apiname(p), PDF_get_errmsg(p));
		//printf("Error: %sn", PDF_get_errmsg(p));
		::MessageBox(NULL, ws, L"PDF error", MB_OK);
		PDF_delete(p);
#endif // CMS_DEBUG
		return false;
	}
	PDF_delete(p);
	//��pdf
	system(PDF_FILE_PATH);
	return true;
}



