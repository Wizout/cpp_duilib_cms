#include "CMS-gui.h"
#include "CMS-db.h"
#include "cms-pdf.h"
#include "cms-xls.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CWndShadow::Initialize(hInstance);

	CLoginFrameWnd loginFrame;
	loginFrame.Create(NULL, _T("�շѹ���ϵͳ"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	loginFrame.CenterWindow();

	loginFrame.ShowModal();

	//CMainFrameWnd mainFrame;
	//mainFrame.Create(NULL, _T("�շѹ���ϵͳ"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	//mainFrame.CenterWindow();
	//mainFrame.ShowModal();
	return 0;
}

LPCTSTR CLoginFrameWnd::GetWindowClassName() const {return _T("DUILoginFrame");}

CDuiString CLoginFrameWnd::GetSkinFile(){	return _T(DUI_XML_LOGIN);}

CDuiString CLoginFrameWnd::GetSkinFolder(){	return _T("");}

void CLoginFrameWnd::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		//��¼��ť
		if (msg.pSender->GetName() == _T("btnLogin"))
		{
			pNoEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editNo")));
			pPwdEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editPwd")));
			//::MessageBox(NULL, pNoEdit->GetText(), pPwdEdit->GetText(), NULL);
			if (pNoEdit->GetText().IsEmpty())
				pNoEdit->SetFocus();
			else if (pPwdEdit->GetText().IsEmpty())
				pPwdEdit->SetFocus();
			else
			{
				//if(OnLogin(pNoEdit->GetText(), pPwdEdit->GetText()) == true)
				if (true)			//�ƹ���¼У�� ԭУ������46��
				{
					HWND m_hwnd = GetHWND();
					//����ǰ���ھ������ջ
					stackHwnd.push(m_hwnd);
					//�����������߳�
					_beginthread(MainThread, 0, m_hwnd);
				}
				else
					::MessageBox(NULL, L"��¼ʧ�ܣ����Ż��������", L"��ʾ", MB_OK | MB_ICONERROR);
			}
		}
		//���ð�ť
		else if (msg.pSender->GetName() == _T("btnReset"))
		{
			pNoEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editNo")));
			pPwdEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editPwd")));
			pNoEdit->SetText(_T(""));
			pPwdEdit->SetText(_T(""));
		}
		//��С����ť
		else if (msg.pSender->GetName() == _T("minbtn")) { SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return; }
		//�رհ�ť
		else if (msg.pSender->GetName() == _T("closebtn")) {Close(0); }
	}//if click
	else if (msg.sType == _T("setfocus"))
	{
		if (msg.pSender->GetName() == _T("editNo"))
		{
			pNoEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editNo")));
			pNoEdit->SetBorderSize(2);
		}
		else if (msg.pSender->GetName() == _T("editPwd"))
		{
			pPwdEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editPwd")));
			pPwdEdit->SetBorderSize(2);
		}
	}
	else if (msg.sType == _T("killfocus"))
	{
		if (msg.pSender->GetName() == _T("editNo"))
		{
			pNoEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editNo")));
			pNoEdit->SetBorderSize(1);
		}
		else if (msg.pSender->GetName() == _T("editPwd"))
		{
			pPwdEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editPwd")));
			pPwdEdit->SetBorderSize(1);
		}
	}
}

//��������ϵͳ��Ϣ
LRESULT CLoginFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool & bHandled)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			//CEditUI* pEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editNo")));
			//if (pEdit->GetText().IsEmpty()) pEdit->SetFocus();
			//else {
			//	pEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editPwd")));
			//	if (pEdit->GetText().IsEmpty()) pEdit->SetFocus();
			//	else {
			//		pNoEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editNo")));
			//		pPwdEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editPwd")));
			//		OnLogin(pNoEdit->GetText(), pPwdEdit->GetText());
				//}
			//}
			return true;
		}
		else if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			return true;
		}
	default:
		return false;
	}
}

//����ϵͳ��Ϣ
LRESULT CLoginFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;	//��־����Ϣ�Ƿ񱻴���
	switch (uMsg)
	{
	case WM_NCLBUTTONDBLCLK: return 0;//����˫��������������󻯣����ηǿͻ������˫���¼�
	case WM_CMS_BACKTOPARENT:
		pNoEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editNo")));
		pPwdEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editPwd")));
		pNoEdit->SetText(L"");
		pPwdEdit->SetText(L"");
		break;
	default: bHandled = FALSE;
	}
	//����Ѵ�����Ϣ ��ֱ�ӷ���
	if (bHandled) return lRes;
	//�����ǰ��MessageHandler��������Ϣ ��ֱ�ӷ���
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	//����Ļ���WIB����...
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

//�����¼����
bool CLoginFrameWnd::OnLogin(LPCWSTR wszOperatorNo, LPCWSTR Password)
{
	bool isSucceed = false;
	//�������ݿ�
	DBgo * pDbgo = new DBgo();
	struct Operator * pO = new struct Operator;
	if (pDbgo == NULL || pO == NULL)
		return false;
	//��ȡ����
	CString szStr;
	szStr.Format(L"%s", Password);
	std::wstring wszStr = szStr.GetBuffer(szStr.GetLength());
	//��������MD5
	MD5 * pMD5 = new MD5(ws2s(wszStr));
	if (pMD5 == NULL)
	{
		if (pDbgo)
		{
			delete pDbgo;
			pDbgo = NULL;
		}
		if (pO)
		{
			delete pO;
			pO = NULL;
		}
		return false;
	}
	wszStr = s2ws(pMD5->md5());
	//��ȡ����
	memset(pO, 0, sizeof(struct Operator));
	pO->OperatorNo = _wtoi(wszOperatorNo);
	wcsncpy_s(pO->password, wszStr.c_str(), wszStr.length() * 2);
	int LoginResult = 0;
	//�������ݿ� �жϵ�¼���
	pDbgo->Login(pO, LoginResult);
	if (LoginResult == 1)
	{
		//::MessageBox(NULL, L"����Ա", L"��¼���", MB_OK | MB_ICONINFORMATION);
		OperatorNo = pO->OperatorNo;
		OperatorClass = 1;
		isSucceed = true;
	}
	else if (LoginResult == 666)
	{
		//::MessageBox(NULL, L"����Ա", L"��¼���", MB_OK | MB_ICONINFORMATION);
		OperatorNo = pO->OperatorNo;
		OperatorClass = 666;
		isSucceed = true;
	}
	else
		isSucceed = false;
	//����
	if (pMD5)
	{
		delete pMD5;
		pMD5 = NULL;
	}
	if (pO)
	{
		delete pO;
		pO = NULL;
	}
	if (pDbgo)
	{
		delete pDbgo;
		pDbgo = NULL;
	}

	return isSucceed;
}

LPCTSTR CMainFrameWnd::GetWindowClassName() const{ return _T("DUIMainFrame"); }

CDuiString CMainFrameWnd::GetSkinFile(){	return _T(DUI_XML_OPERATOR);}

CDuiString CMainFrameWnd::GetSkinFolder(){ return _T(""); }

void CMainFrameWnd::Notify(TNotifyUI & msg)
{
	//��ʼ�� ������ʾ��¼����
	//if (msg.sType == _T("windowinit")) OnPrepare();
	if (msg.sType == _T("click"))
	{
		//���޸����롱��ť
		if (msg.pSender->GetName() == L"btnChangePwd")
		{
			//��ʾ��ɫ����
			ctrlGray = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGray"));
			ctrlGray->SetVisible(true);
			ctrlGrayHome = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayHome"));
			ctrlGrayHome->SetVisible(true);

			//��ȡ��ǰ���ھ��
			HWND m_hwnd = GetHWND();
			//����ǰ���ھ������ջ
			stackHwnd.push(m_hwnd);
			//�����޸������Ӵ����߳�
			_beginthread(ChangePwdThread, 0, m_hwnd);
		}
		//����ѯ���롱��ť
		else if (msg.pSender->GetName() == _T("btnMSISDN"))
		{
			//��ȡ���� ���ô�����
			editMSISDN = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editMSISDN")));
			if (editMSISDN && editMSISDN->GetText().GetLength() > 0)
				OnQueryChargeMSISDN(editMSISDN->GetText());
			else
				::MessageBox(GetHWND(), L"����д�û��绰����...", L"ע��", MB_OK | MB_ICONINFORMATION);
		}
		//���ɷѡ���ť
		else if (msg.pSender->GetName() == _T("btnCharge"))
		{	
			//����ci ׼���������߳�
			struct ChargedInfo* ci = new struct ChargedInfo;
			if(ci == NULL)
				::MessageBox(GetHWND(), L"�ڴ治�㣿", L"��ʾ", MB_OK | MB_ICONERROR);
			memset(ci, 0, sizeof(struct ChargedInfo));

			if (this->OnUserCharge(ci) == true)
			{
				//�ɷѳɹ� ��ʾ�Ի洰��
				//::MessageBox(GetHWND(), L"�ɷѳɹ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
				//��ʾ��ɫ����
				ctrlGray = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGray"));
				ctrlGray->SetVisible(true);
				ctrlGrayCharge = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayCharge"));
				ctrlGrayCharge->SetVisible(true);
				//��ȡ��ǰ���ھ��
				HWND m_hwnd = GetHWND();
				//����ǰ���ھ������ջ
				stackHwnd.push(m_hwnd);
				//�����ɷѳɹ��Ӵ����߳�
				_beginthread(ChargedThread, 0, ci);
			}
			else//�ɷ�ʧ��
				::MessageBox(GetHWND(), L"�ɷ�ʧ��", L"��ʾ", MB_OK | MB_ICONERROR);
		}
		//����������ť
		else if (msg.pSender->GetName() == L"btnMgrNew")
		{
			//��ʾ��ɫ����
			ctrlGray = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGray"));
			ctrlGray->SetVisible(true);
			ctrlGrayUserMgr = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayUserMgr"));
			ctrlGrayUserMgr->SetVisible(true);

			//��ȡ��ǰ���ھ��
			//HWND m_hwnd = GetHWND();
			//����ǰ���ھ������ջ
			stackHwnd.push(m_hWnd);
			//�����޸������Ӵ����߳�
			_beginthread(NewThread, 0, m_hWnd);
		}
		//����������ť
		else if (msg.pSender->GetName() == L"btnMgrDel") 
		{
			//��ʾ��ɫ����
			ctrlGray = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGray"));
			ctrlGray->SetVisible(true);
			ctrlGrayUserMgr = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayUserMgr"));
			ctrlGrayUserMgr->SetVisible(true);

			//��ȡ��ǰ���ھ��
			//HWND m_hwnd = GetHWND();
			//����ǰ���ھ������ջ
			stackHwnd.push(m_hWnd);
			//�����޸������Ӵ����߳�
			_beginthread(DelThread, 0, m_hWnd);
		}
		//����ѯ/�޸ġ���ť
		else if (msg.pSender->GetName() == L"btnMgrQnM")
		{
			//��ʾ��ɫ����
			ctrlGray = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGray"));
			ctrlGray->SetVisible(true);
			ctrlGrayUserMgr = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayUserMgr"));
			ctrlGrayUserMgr->SetVisible(true);

			//��ȡ��ǰ���ھ��
			//HWND m_hwnd = GetHWND();
			//����ǰ���ھ������ջ
			stackHwnd.push(m_hWnd);
			//�����޸������Ӵ����߳�
			_beginthread(QnMThread, 0, m_hWnd);
		}
		// ���ɷѼ�¼����ť
		else if (msg.pSender->GetName() == L"btnMgrQR")
		{
			//��ʾ��ɫ����
			ctrlGray = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGray"));
			ctrlGray->SetVisible(true);
			ctrlGrayUserMgr = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayUserMgr"));
			ctrlGrayUserMgr->SetVisible(true);

			//��ȡ��ǰ���ھ��
			//HWND m_hwnd = GetHWND();
			//����ǰ���ھ������ջ
			stackHwnd.push(m_hWnd);
			//�����޸������Ӵ����߳�
			_beginthread(QRThread, 0, m_hWnd);
		}
		//���շ�Ա������ť
		else if (msg.pSender->GetName() == L"btnAdminOperatorMgr")
		{
			//��ʾ��ɫ����
			ctrlGray = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGray"));
			ctrlGray->SetVisible(true);
			ctrlGrayAdmin = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayAdmin"));
			ctrlGrayAdmin->SetVisible(true);

			//����ǰ���ھ������ջ
			stackHwnd.push(m_hWnd);
			//�����շ�Ա�����Ӵ����߳�
			_beginthread(OperatorMgrThread, 0, m_hWnd);
		}
		//���ײ͹�����ť
		else if (msg.pSender->GetName() == L"btnAdminPlanMgr")
		{
			//��ʾ��ɫ����
			ctrlGray = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGray"));
			ctrlGray->SetVisible(true);
			ctrlGrayAdmin = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayAdmin"));
			ctrlGrayAdmin->SetVisible(true);

			//����ǰ���ھ������ջ
			stackHwnd.push(m_hWnd);
			//�����ײ͹����Ӵ����߳�
			_beginthread(PlanMgrThread, 0, m_hWnd);
		}
		//"���뵼���û�����"��ť
		else if (msg.pSender->GetName() == L"btnAdminIOuser")
		{
			//��ʾ��ɫ����
			ctrlGray = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGray"));
			ctrlGray->SetVisible(true);
			ctrlGrayAdmin = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayAdmin"));
			ctrlGrayAdmin->SetVisible(true);

			//����ǰ���ھ������ջ
			stackHwnd.push(m_hWnd);
			//�������뵼���û������Ӵ����߳�
			_beginthread(IOuserThread, 0, m_hWnd);
		}
		//���뵼������Ա��ť
		else if(msg.pSender->GetName() == L"btnAdminIOoperator")
			::MessageBox(m_hWnd, L"�����ڴ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		//���뵼���շѼ�¼
		else if (msg.pSender->GetName() == L"btnAdminIOcharge")
			::MessageBox(m_hWnd, L"�����ڴ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		//���ݻָ����ݿ�
		else if (msg.pSender->GetName() == L"btnAdminBnR")
		{
			int retVal = ::MessageBox(m_hWnd,
				L"���ǡ��������ݿ���D:/CMS.bak\n���񡿴�D:/CMS.bak�ָ����ݿ�\n��ȡ������ִ�в���",
				L"����ѡ��",
				MB_YESNOCANCEL | MB_ICONQUESTION);

			if (retVal == IDYES)
			{
				//����
				DBgo * dbgo = new DBgo;
				if (dbgo->BackupAndRestore(true) == true)
				{
					::MessageBox(m_hWnd, L"���ݳɹ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
				}
				else
				{
					::MessageBox(m_hWnd, L"����ʧ��", L"��ʾ", MB_OK | MB_ICONINFORMATION);
				}
				delete dbgo;
				dbgo = NULL;
			}
			else if (retVal == IDNO)
			{
				//�ָ�
				DBgo * dbgo = new DBgo;
				if (dbgo->BackupAndRestore(true) == true)
				{
					::MessageBox(m_hWnd, L"��ԭ�ɹ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
				}
				else
				{
					::MessageBox(m_hWnd, L"��ԭʧ��", L"��ʾ", MB_OK | MB_ICONINFORMATION);
				}
				delete dbgo;
				dbgo = NULL;
			}
			else
			{
				::MessageBox(m_hWnd, L"�û�ȡ���˲���", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			}
		}
		//��С����ť��//Ϊ������С������������ �ӵ�¼�����ظ���¼ ������Ӧ��С����ť
		else if (msg.pSender->GetName() == _T("minbtn")) { SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return; }
		//�رհ�ť
		else if (msg.pSender->GetName() == _T("closebtn")) 
		{ 
			//��ջ����ȡ�����ھ������ջ
			HWND m_hwnd = stackHwnd.top();
			stackHwnd.pop();

			::EnableWindow(m_hwnd , TRUE);												// �����ڻ�ԭ m_hwndΪ�Ӵ��ھ��
			::SetFocus(m_hwnd);																	//���ý��㵽������
			::PostMessage(m_hwnd, WM_CMS_BACKTOPARENT, 0, 0);		//�򸸴��ڷ�����Ϣ
			//PostQuitMessage(0); 
			Close();
		}
	}//if click
	else if (msg.sType == _T("selectchanged"))
	{
		//��xml�е�opt��Ӧ ������ѡopt �л�switch����
		CDuiString name = msg.pSender->GetName();
		CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("switch")));
		if (name == _T("optHome")) { pControl->SelectItem(0); this->OnSwitchHome(); }
		else if (name == _T("optCharge"))	{pControl->SelectItem(1);	this->OnSwitchCharge();	}
		else if (name == _T("optUserMgr")) { pControl->SelectItem(2); this->OnSwitchUserMgr(); }
		else if (name == _T("optAdmin")) 
		{ 
			if (OperatorClass == 666)
			{
				pControl->SelectItem(3);
				this->OnSwitchAdmin();
			}
			else
				::MessageBox(m_hWnd, L"�����ڴ�~", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		}
	}
	else if (msg.sType == _T("setfocus"))
	{
		if (msg.pSender->GetName() == _T("editMSISDN"))
		{
			editMSISDN = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editMSISDN")));
			editMSISDN->SetBorderSize(2);
		}
		else if (msg.pSender->GetName() == _T("editCharge"))
		{
			editCharge = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editCharge")));
			editCharge->SetBorderSize(2);
		}
	}
	else if (msg.sType == _T("killfocus"))
	{
		if (msg.pSender->GetName() == _T("editMSISDN"))
		{
			editMSISDN = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editMSISDN")));
			editMSISDN->SetBorderSize(1);
		}
		else if (msg.pSender->GetName() == _T("editCharge"))
		{
			editCharge = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editCharge")));
			editCharge->SetBorderSize(1);
		}
	}
	else if (msg.sType == _T("itemselect")) {
		if (msg.pSender->GetName() == _T("optHome")) 
		{
			//CComboUI* pCombox = (CComboUI*)msg.pSender;
			//int nsel = pCombox->GetCurSel();
			//CListLabelElementUI* pItemEle = (CListLabelElementUI*)pCombox->GetItemAt(nsel);
			//CDuiString strText = pItemEle->GetText();
		}
	}
}

void CMainFrameWnd::Init()
{
	//OperatorNo = 2;
	//ִ����ҳ����
	this->OnSwitchHome();
	////����ɫ�ؼ�����Ϊ���ɼ�
	//ctrlGray = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGray"));
	//ctrlGray->SetVisible(false);
}

LRESULT CMainFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool & bHandled)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			//CEditUI* pEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editNo")));
			//if (pEdit->GetText().IsEmpty()) pEdit->SetFocus();
			//else {
			//	pEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editPwd")));
			//	if (pEdit->GetText().IsEmpty()) pEdit->SetFocus();
			//	else {
			//		//pNoEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editNo")));
			//		//pPwdEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editPwd")));
			//		//OnLogin(pNoEdit->GetText(), pPwdEdit->GetText());
			//	}
			//}
			return true;
		}
		else if (wParam == VK_ESCAPE) {
			//PostQuitMessage(0);
			return true;
		}
	default:
		return false;
	}
}

LRESULT CMainFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;	//��־����Ϣ�Ƿ񱻴���
	switch (uMsg)
	{
		//����˫��������������󻯣����ηǿͻ������˫���¼�
	case WM_NCLBUTTONDBLCLK: return 0;
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_CMS_BACKTOPARENT:
		//��Ӧ�Ӵ����˳���Ϣ ���ػ�ɫ����
		ctrlGray = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGray"));
		ctrlGray->SetVisible(false);
		ctrlGrayHome = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayHome"));
		ctrlGrayHome->SetVisible(false);
		ctrlGrayCharge = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayCharge"));
		ctrlGrayCharge->SetVisible(false);
		ctrlGrayUserMgr = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayUserMgr"));
		ctrlGrayUserMgr->SetVisible(false);
		ctrlGrayAdmin = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayAdmin"));
		ctrlGrayAdmin->SetVisible(false);
		break;
	default: bHandled = FALSE;
	}
	//����Ѵ�����Ϣ ��ֱ�ӷ���
	if (bHandled) return lRes;
	//�����ǰ��MessageHandler��������Ϣ ��ֱ�ӷ���
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	//����Ļ���WIB����...
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CMainFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	
	m_PaintManager.Init(m_hWnd);
	CDialogBuilder builder;
	CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T(DUI_XML_OPERATOR), (UINT)0, &cb, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);


	m_WndShadow.Create(m_hWnd);
	m_WndShadow.SetSize(3);
	m_WndShadow.SetPosition(0, 0);

	Init();
	return 0;
}

LRESULT CMainFrameWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);
	RECT rcCaption = m_PaintManager.GetCaptionRect();
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
		CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(pt));
		if (pControl && _tcscmp(pControl->GetClass(), DUI_CTR_BUTTON) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_OPTION) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_TEXT) != 0 &&
			_tcscmp(pControl->GetClass(), DUI_CTR_COMBO) != 0)
			return HTCAPTION;
	}
	return HTCLIENT;
}

LRESULT CMainFrameWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	return 0;
}

LRESULT CMainFrameWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	return 0;
}

LRESULT CMainFrameWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	if (::IsIconic(*this)) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

bool CMainFrameWnd::OnSwitchHome()
{
	ctrlGrayHome = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayHome"));
	ctrlGrayHome->SetVisible(false);

	CLabelUI * labelWelcome = static_cast<CLabelUI*>(m_PaintManager.FindControl(L"labelWelcome"));
	CLabelUI * labelClass = static_cast<CLabelUI*>(m_PaintManager.FindControl(L"labelClass"));

	if (labelWelcome == NULL ||
		labelClass == NULL)
		return false;

	DBgo* dbgo = new DBgo();
	if (dbgo == NULL)
		return false;

	struct CMS_DB_HEADER * cdh = new struct CMS_DB_HEADER;
	if (cdh == NULL)
	{
		if (dbgo != NULL)
		{
			delete dbgo;
			dbgo = NULL;
		}
		return false;
	}
	InitCDH(cdh);

	CString wszStr;
	wszStr.Format(L"%d", OperatorNo);
	if (dbgo->QueryOperator(wszStr.GetBuffer(wszStr.GetLength()),QO_BY_OPERATORNO, cdh) 
		== true &&
		cdh->n == 1)
	{
		wszStr.Format(L"%s������", (((struct Operator*)(cdh->next->content))->OperatorName));
		labelWelcome->SetText(wszStr.GetBuffer(wszStr.GetLength()));
		wszStr.Format(L"�˻�Ȩ�ޣ�%s",
			(((struct Operator*)(cdh->next->content))->Class)==1?L"�շ�Ա":L"����Ա");
		labelClass->SetText(wszStr.GetBuffer(wszStr.GetLength()));
	}
	else
	{
		labelWelcome->SetText(L"���ݿ�����쳣������ϵ����Ա��");
		return false;
	}

	DeleteCDH(cdh);
	if (dbgo != NULL)
	{
		delete dbgo;
		dbgo = NULL;
	}
	return true;
}

bool CMainFrameWnd::OnSwitchCharge()
{
	ctrlGrayCharge = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayCharge"));
	ctrlGrayCharge->SetVisible(false);

	editMSISDN = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editMSISDN")));
	if (editMSISDN)
	{
		editMSISDN->SetText(L"");
	}
	//��ʼ �����°벿����Ϣ
	containerCharge = static_cast<CContainerUI*>(m_PaintManager.FindControl(_T("containerCharge")));
	if (containerCharge)
	{
		containerCharge->SetVisible(false);
	}
	return true;
}

bool CMainFrameWnd::OnSwitchUserMgr()
{
	ctrlGrayUserMgr = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayUserMgr"));
	ctrlGrayUserMgr->SetVisible(false);
	return false;
}

bool CMainFrameWnd::OnSwitchAdmin()
{
	return false;
}

bool CMainFrameWnd::OnUserCharge(struct ChargedInfo * ci)
{
	//��ȡ�ɷѽ��û����롢�ɷѷ�ʽ���û����
	editCharge = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editCharge")));
	editMSISDN = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editMSISDN")));
	CComboUI * pCombox = static_cast<CComboUI*>(m_PaintManager.FindControl(L"comboPayMethod"));
	int nsel = pCombox->GetCurSel();
	CListLabelElementUI* pItemEle = (CListLabelElementUI*)pCombox->GetItemAt(nsel);
	CTextUI* textBalance = static_cast<CTextUI*>(m_PaintManager.FindControl(_T("textBalance")));
	bool isSucceed = false;
	
	if (editCharge != NULL && editMSISDN != NULL && pItemEle != NULL && textBalance != NULL)
	{
		//�ӿؼ���ȡ��Ϣ
		double dCharge = 0.0;
		double dBalance = 0.0;
		swscanf_s(editCharge->GetText(), L"%lf", &dCharge);
		swscanf_s(textBalance->GetText(), L"%lf", &dBalance);
		if (dCharge <= 0.0)
		{
			//::MessageBox(GetHWND(), L"���顰�ɷѽ��Ƿ���ȷ��", L"ע��", MB_OK | MB_ICONQUESTION);
			return false;
		}
		//��������ʼ�������ṹ��
		struct Charge* c = new struct Charge;
		if (c == NULL)
		{
			//::MessageBox(GetHWND(), L"�޷�����Charge�ṹ��", L"ע��", MB_OK | MB_ICONQUESTION);
			return false;
		}
		memset(c, 0, sizeof(struct Charge));
		c->OperatorNo = OperatorNo;
		c->PayAmount = dCharge;
		wcscpy_s(c->MSISDN, editMSISDN->GetText());
		wcscpy_s(c->PayMethod, pItemEle->GetText());

		//д�����ݿ�
		DBgo * dbgo = new DBgo;
		if (dbgo == NULL)
		{
			//::MessageBox(GetHWND(), L"�޷�����dbgo", L"ע��", MB_OK | MB_ICONQUESTION);
			if (c != NULL)
			{
				delete c;
				c = NULL;
			}
			return false;
		}

		if (dbgo->OnUserCharge(c, dBalance) == true)
		{
			//�ɷѳɹ� ��ȡ��Ϣ����дci
			CTextUI* textName = static_cast<CTextUI*>(m_PaintManager.FindControl(_T("textName")));
			CString wszStr;
			std::wstring szStr1 = editMSISDN->GetText();
			std::wstring szStr2 = textName->GetText();
			wszStr.Format(L"%s ��%s��", szStr1.c_str(), szStr2.c_str());
			//��дci
			wcsncpy_s(ci->amount, editCharge->GetText(), 32);
			wcsncpy_s(ci->MSISDN_NAME, wszStr.GetBuffer(wszStr.GetLength()), wszStr.GetLength());
			wcscpy_s(ci->method, pItemEle->GetText());
			wszStr.Format(L"%d", OperatorNo);
			wcsncpy_s(ci->OperatorNo, wszStr.GetBuffer(wszStr.GetLength()), wszStr.GetLength());

			//�趨����ֵ
			isSucceed = true;
		}
		else
			isSucceed = false;			//�ɷ�ʧ��

		//�ͷ��ڴ�
		if (dbgo)
		{
			delete dbgo;
			dbgo = NULL;
		}
		if (c)
		{
			delete c;
			c = NULL;
		}
	}
	return isSucceed;
}

void CMainFrameWnd::OnQueryChargeMSISDN(LPCWSTR MSISDN)
{
	//emmmm�������ݿ�
	DBgo * dbgo = new DBgo();
	struct CMS_DB_HEADER * cdh = new struct CMS_DB_HEADER;
	InitCDH(cdh);

	//ִ�в�ѯ ����MSISDN��ȷ����
	dbgo->QueryUserInfo((wchar_t*)MSISDN, QUI_BY_MSISDN | QUI_WAY_ACCURATE, cdh);

	if (cdh->n == 0 || cdh->next == NULL)
		::MessageBox(GetHWND(), L"û���ҵ��ú����Ӧ���û���", L"��ʾ", MB_OK | MB_ICONINFORMATION);
	else
	{
		//��ȡ����Text���
		CTextUI* textName = static_cast<CTextUI*>(m_PaintManager.FindControl(_T("textName")));
		CTextUI* textBalance = static_cast<CTextUI*>(m_PaintManager.FindControl(_T("textBalance")));
		CTextUI* textStatus = static_cast<CTextUI*>(m_PaintManager.FindControl(_T("textStatus")));
		if (textName==NULL || textBalance == NULL ||textStatus == NULL)
		{
			::MessageBox(GetHWND(), L"һ�������������ʧ�ܡ����ؼ�����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			goto EXITQUERY;
		}

		//ת��������ʽ
		CString wszStr;
		wszStr.Format(L"%.2lf", ((struct UserInfo*)(cdh->next->content))->balance);

		//��ֵ
		textName->SetText(((struct UserInfo*)(cdh->next->content))->name);
		textBalance->SetText(wszStr.GetBuffer(wszStr.GetLength()));
		textStatus->SetText(((struct UserInfo*)(cdh->next->content))->status);

		//�����û��ײͱ�� ��ѯ�ײ����Ƽ��ʷ�
		wszStr.Format(L"%d", ((struct UserInfo*)(cdh->next->content))->PlanNo);
		dbgo->QueryPlan(wszStr.GetBuffer(wszStr.GetLength()), QP_BY_PLANNO, cdh);

		//����Ƿ���ڸ��ײ�
		if (cdh->n != 2)
		{
			::MessageBox(GetHWND(), L"�û���ǰʹ�õ��ײ��Ѳ����ڣ����޸�Ϊ�����ײ͡�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			goto EXITQUERY;
		}

		//��д�ײ���Ϣ
		wszStr.Format(L"%s������%.2lf���У�%.2lf������%.2lf��",
			((struct CallPlan*)(cdh->next->content))->PlanName, ((struct CallPlan*)(cdh->next->content))->RemoteFee,
			((struct CallPlan*)(cdh->next->content))->LocalFee, ((struct CallPlan*)(cdh->next->content))->RoamingFee);

		//��ֵx2
		CTextUI* textPlan = static_cast<CTextUI*>(m_PaintManager.FindControl(_T("textPlan")));
		if (textPlan == NULL)
		{
			::MessageBox(GetHWND(), L"һ�������������ʧ�ܡ����ؼ�����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			goto EXITQUERY;
		}
		textPlan->SetText(wszStr.GetBuffer(wszStr.GetLength()));

		//��ʾ�����е�����
		containerCharge = static_cast<CContainerUI*>(m_PaintManager.FindControl(_T("containerCharge")));
		if (containerCharge)
			containerCharge->SetVisible(true);
	}

EXITQUERY:
	DeleteCDH(cdh);
	if (dbgo)
	{
		delete dbgo;
		dbgo = NULL;
	}
	return;
}

void CMainFrameWnd::OnPrepare()
{
	//CLoginFrameWnd duiFrame;
	//duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	//duiFrame.CenterWindow();
	//duiFrame.ShowModal();

	return;
}

void MainThread(void * pParam)
{
	::EnableWindow((HWND)pParam, false);    //��������Ч��
	//����������
	CMainFrameWnd *pMainWnd = new CMainFrameWnd();
	pMainWnd->Create((HWND)pParam, _T("�շѹ���ϵͳ"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pMainWnd->CenterWindow();
	CPaintManagerUI::MessageLoop();
}

void ChangePwdThread(void * pParam)
{
	::EnableWindow((HWND)pParam, false);    //��������Ч��
	CSubChangePwdFrameWnd *pChangePwdWnd = new CSubChangePwdFrameWnd();
	pChangePwdWnd->Create((HWND)pParam, _T("�޸�����"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pChangePwdWnd->CenterWindow();
	CPaintManagerUI::MessageLoop();
}

void ChargedThread(void * pParam)
{
	HWND m_hwnd = stackHwnd.top();
	::EnableWindow(m_hwnd, false);
	CSubChargedFrameWnd * pChargedWnd = new CSubChargedFrameWnd((struct ChargedInfo*)pParam);
	pChargedWnd->Create(m_hwnd, _T("�ɷѳɹ�"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pChargedWnd->CenterWindow();
	CPaintManagerUI::MessageLoop();
}

void NewThread(void * pParam)
{
	HWND m_hwnd = stackHwnd.top();
	::EnableWindow(m_hwnd, false);
	CSubNewFrameWnd * pNewWnd = new CSubNewFrameWnd();
	pNewWnd->Create(m_hwnd, _T("����"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pNewWnd->CenterWindow();
	CPaintManagerUI::MessageLoop();
}

void DelThread(void * pParam)
{
	HWND m_hwnd = stackHwnd.top();
	::EnableWindow(m_hwnd, false);
	CSubDelFrameWnd * pDelWnd = new CSubDelFrameWnd();
	pDelWnd->Create(m_hwnd, _T("����"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pDelWnd->CenterWindow();
	CPaintManagerUI::MessageLoop();
}

void QnMThread(void * pParam)
{
	HWND m_hwnd = stackHwnd.top();
	::EnableWindow(m_hwnd, false);
	CSubQnMFrameWnd * pQnMWnd = new CSubQnMFrameWnd();
	pQnMWnd->Create(m_hwnd, _T("��ѯ/�޸�"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pQnMWnd->CenterWindow();
	CPaintManagerUI::MessageLoop();
}

void QRThread(void * pParam)
{
	HWND m_hwnd = stackHwnd.top();
	::EnableWindow(m_hwnd, false);
	CSubQRFrameWnd * pQRWnd = new CSubQRFrameWnd();
	pQRWnd->Create(m_hwnd, _T("��ѯ�ɷѼ�¼"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pQRWnd->CenterWindow();
	CPaintManagerUI::MessageLoop();
}

void OperatorMgrThread(void * pParam)
{
	HWND m_hwnd = stackHwnd.top();
	::EnableWindow(m_hwnd, false);
	CSubOperatorMgrFrameWnd * pOperatorMgrWnd = new CSubOperatorMgrFrameWnd();
	pOperatorMgrWnd->Create(m_hwnd, _T("�շ�Ա����"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pOperatorMgrWnd->CenterWindow();
	CPaintManagerUI::MessageLoop();
}

void ModifyOperatorThread(void * pParam)
{
	HWND m_hwnd = stackHwnd.top();
	::EnableWindow(m_hwnd, false);
	CModifyOperatorFrameWnd * pModifyOperatorWnd = 
		new CModifyOperatorFrameWnd((struct CMS_DB_NODE*)pParam);
	pModifyOperatorWnd->Create(m_hwnd, _T("�޸��շ�Ա"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pModifyOperatorWnd->CenterWindow();
	CPaintManagerUI::MessageLoop();
}

void PlanMgrThread(void * pParam)
{
	HWND m_hwnd = stackHwnd.top();
	::EnableWindow(m_hwnd, false);
	CPlanMgrFrameWnd * pPlanMgrWnd = new CPlanMgrFrameWnd();
	pPlanMgrWnd->Create(m_hwnd, _T("�ײ͹���"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pPlanMgrWnd->CenterWindow();
	CPaintManagerUI::MessageLoop();
}

void ModifyPlanThread(void * pParam)
{
	HWND m_hwnd = stackHwnd.top();
	::EnableWindow(m_hwnd, false);
	CModifyPlanFrameWnd * pModifyPlanWnd =
		new CModifyPlanFrameWnd((struct CMS_DB_NODE*)pParam);
	pModifyPlanWnd->Create(m_hwnd, _T("�޸��ײ�"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pModifyPlanWnd->CenterWindow();
	CPaintManagerUI::MessageLoop();
}

void IOuserThread(void * pParam)
{
	HWND m_hwnd = stackHwnd.top();
	::EnableWindow(m_hwnd, false);
	CIOuserFrameWnd * pIOuserWnd = new CIOuserFrameWnd();
	pIOuserWnd->Create(m_hwnd, _T("�ײ͹���"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pIOuserWnd->CenterWindow();
	CPaintManagerUI::MessageLoop();
}

LPCTSTR CSubChangePwdFrameWnd::GetWindowClassName() const{ return _T("DUILoginFrame"); }

CDuiString CSubChangePwdFrameWnd::GetSkinFile() { return _T(DUI_XML_SUB_CHANGEPWD); }

CDuiString CSubChangePwdFrameWnd::GetSkinFolder() { return _T(""); }

void CSubChangePwdFrameWnd::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		//���޸����롱��ť
		if (msg.pSender->GetName() == _T("btnChange"))
		{
			pRawPwdEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editRawPwd")));
			pNewPwdEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editNewPwd")));
			pNewPwd2Edit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editNewPwd2")));
			
			if (pRawPwdEdit->GetText().IsEmpty())
				pRawPwdEdit->SetFocus();
			else if (pNewPwdEdit->GetText().IsEmpty())
				pNewPwdEdit->SetFocus();
			else if (pNewPwd2Edit->GetText().IsEmpty())
				pNewPwd2Edit->SetFocus();
			else
				if (OnChangePwd() == true)
					::MessageBox(GetHWND(), L"�޸ĳɹ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);


		}
		//���ð�ť
		else if (msg.pSender->GetName() == _T("btnReset"))
		{
			pRawPwdEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editRawPwd")));
			pNewPwdEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editNewPwd")));
			pNewPwd2Edit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editNewPwd2")));

			pNewPwdEdit->SetText(_T(""));
			pNewPwd2Edit->SetText(_T(""));
			pRawPwdEdit->SetText(_T(""));
		}
		//�رհ�ť
		else if (msg.pSender->GetName() == _T("closebtn"))
		{
			//��ջ����ȡ�����ھ������ջ
			HWND m_hwnd = stackHwnd.top();
			stackHwnd.pop();

			::EnableWindow(m_hwnd, TRUE);												// �����ڻ�ԭ m_hwndΪ�Ӵ��ھ��
			::SetFocus(m_hwnd);																	//���ý��㵽������
			::PostMessage(m_hwnd, WM_CMS_BACKTOPARENT, 0, 0);		//�򸸴��ڷ�����Ϣ
			Close(); 
		}
	}//if click
}

LRESULT CSubChangePwdFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool & bHandled)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			return true;
		}
		else if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			return true;
		}
	default:
		return false;
	}
}

LRESULT CSubChangePwdFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;	//��־����Ϣ�Ƿ񱻴���
	switch (uMsg)
	{
	case WM_NCLBUTTONDBLCLK: return 0;//����˫��������������󻯣����ηǿͻ������˫���¼�
	default: bHandled = FALSE;
	}
	//����Ѵ�����Ϣ ��ֱ�ӷ���
	if (bHandled) return lRes;
	//�����ǰ��MessageHandler��������Ϣ ��ֱ�ӷ���
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	//����Ļ���WIB����...
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CSubChangePwdFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_PaintManager.Init(m_hWnd);
	CDialogBuilder builder;
	//CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T(DUI_XML_SUB_CHANGEPWD), (UINT)0, NULL, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);


	m_WndShadow.Create(m_hWnd);
	m_WndShadow.SetSize(3);
	m_WndShadow.SetPosition(0, 0);

	//Init();
	return 0;
}

bool CSubChangePwdFrameWnd::OnChangePwd()
{
	bool isSucceed = false;
	pRawPwdEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editRawPwd")));
	pNewPwdEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editNewPwd")));
	pNewPwd2Edit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editNewPwd2")));

	//�������������������Ƿ�һ��
	if (pNewPwdEdit->GetText() != pNewPwd2Edit->GetText())
	{
		::MessageBox(GetHWND(), L"��������������벻һ��Ŷ~", L"��ʾ", MB_OK | MB_ICONQUESTION);
		return false;
	}
	//���ԭ�����Ƿ���ȷ
	CString wszStr;
	wszStr.Format(L"%d", OperatorNo);
	if (CLoginFrameWnd::OnLogin(wszStr.GetBuffer(wszStr.GetLength()), pRawPwdEdit->GetText())
		== false)
	{
		::MessageBox(GetHWND(), L"ԭ���벻��Ŷ~", L"��ʾ", MB_OK | MB_ICONQUESTION);
		return false;
	}

	//�������ݿ� ִ�и������
	DBgo * dbgo = new DBgo;
	if (dbgo == NULL)
		return false;
	//
	if (dbgo->OnOperatorChangePwd(OperatorNo, pNewPwdEdit->GetText()) 
		== true)
		isSucceed = true;
	else
	{
		::MessageBox(GetHWND(), L"���ݿ����ִ��ʧ��", L"��ʾ", MB_OK | MB_ICONERROR);
		isSucceed = false;
	}
	
	if (dbgo)
	{
		delete dbgo;
		dbgo = NULL;
	}
	return isSucceed;
}

LPCTSTR CSubChargedFrameWnd::GetWindowClassName() const { return _T("DUILoginFrame"); }

CDuiString CSubChargedFrameWnd::GetSkinFile() { return _T(DUI_XML_SUB_CHANGEPWD); }

CDuiString CSubChargedFrameWnd::GetSkinFolder() { return _T(""); }

void CSubChargedFrameWnd::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		//��ȷ������ť
		if (msg.pSender->GetName() == _T("btnOK"))
		{
			//��ջ����ȡ�����ھ������ջ
			HWND m_hwnd = stackHwnd.top();
			stackHwnd.pop();

			::EnableWindow(m_hwnd, TRUE);												// �����ڻ�ԭ m_hwndΪ�Ӵ��ھ��
			::SetFocus(m_hwnd);																	//���ý��㵽������
			::PostMessage(m_hwnd, WM_CMS_BACKTOPARENT, 0, 0);		//�򸸴��ڷ�����Ϣ
			Close();
		}
		//����ӡ��Ʊ����ť
		else if (msg.pSender->GetName() == _T("btnPrint"))
		{
			//���ʧ�� ���Դ�ӡ3��
			if (OnCreateReceipt() == false)
			{
				if (OnCreateReceipt() == false)
				{
					if (OnCreateReceipt() == false)
					{
						::MessageBox(m_hWnd, L"��Ʊ��ӡʧ�ܣ�", L"ע��", MB_OK | MB_ICONERROR);
					}
				}
			}
		}
		//�رհ�ť
		else if (msg.pSender->GetName() == _T("closebtn"))
		{
			//��ջ����ȡ�����ھ������ջ
			HWND m_hwnd = stackHwnd.top();
			stackHwnd.pop();

			::EnableWindow(m_hwnd, TRUE);												// �����ڻ�ԭ m_hwndΪ�Ӵ��ھ��
			::SetFocus(m_hwnd);																	//���ý��㵽������
			::PostMessage(m_hwnd, WM_CMS_BACKTOPARENT, 0, 0);		//�򸸴��ڷ�����Ϣ
			Close();
		}
	}//if click
}

CSubChargedFrameWnd::CSubChargedFrameWnd(ChargedInfo * ci)
{
	pci = new struct ChargedInfo;

	if (pci)
	{
		memset(pci, 0, sizeof(struct ChargedInfo));
		memcpy(pci, ci, sizeof(struct ChargedInfo));
	}
}

void CSubChargedFrameWnd::Init()
{
	labelMSISDN_NAME = static_cast<CLabelUI*>(m_PaintManager.FindControl(L"labelMSISDN_NAME"));
	labelAmount = static_cast<CLabelUI*>(m_PaintManager.FindControl(L"labelAmount"));

	if (labelMSISDN_NAME == NULL ||
		labelAmount == NULL ||
		pci == NULL)
	{
		::MessageBox(m_hWnd, L"???", L"...", MB_OK | MB_ICONERROR);
		return;
	}

	labelMSISDN_NAME->SetText(pci->MSISDN_NAME);
	labelAmount->SetText(pci->amount);
	return;
}

LRESULT CSubChargedFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool & bHandled)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			return true;
		}
		else if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			return true;
		}
	default:
		return false;
	}
}

LRESULT CSubChargedFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;	//��־����Ϣ�Ƿ񱻴���
	switch (uMsg)
	{
	case WM_NCLBUTTONDBLCLK: return 0;//����˫��������������󻯣����ηǿͻ������˫���¼�
	default: bHandled = FALSE;
	}
	//����Ѵ�����Ϣ ��ֱ�ӷ���
	if (bHandled) return lRes;
	//�����ǰ��MessageHandler��������Ϣ ��ֱ�ӷ���
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	//����Ļ���WIB����...
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CSubChargedFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_PaintManager.Init(m_hWnd);
	CDialogBuilder builder;
	//CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T(DUI_XML_SUB_CHARGED), (UINT)0, NULL, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);


	//m_WndShadow.Create(m_hWnd);
	//m_WndShadow.SetSize(3);
	//m_WndShadow.SetPosition(0, 0);

	Init();
	return 0;
}

bool CSubChargedFrameWnd::OnCreateReceipt()
{
	bool isSucceed = false;
	//��ȡ��ǰʱ��
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString wszStr;
	wszStr.Format(L"%4d-%2d-%2d %2d:%2d:%2d",
		st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	//ת�����
	double dCharge = 0.0;
	swscanf_s(pci->amount, L"%lf", &dCharge);

	CString ReceiptContent = "�ʵ���շѷ�Ʊ\n";
	ReceiptContent += "-------------------------------------\nʱ�䣺";
	ReceiptContent += wszStr;																//�Զ���ȡʱ��
	ReceiptContent += "\n�û���";
	ReceiptContent += pci->MSISDN_NAME;										//���롢����
	ReceiptContent += "\n�ɷѽ�";
	ReceiptContent += pci->amount;													//���
	ReceiptContent += "Ԫ\n����д��";
	ReceiptContent += ConvertMoneyCaps(dCharge).c_str();				//��д���
	ReceiptContent += "\n�ɷѷ�ʽ��";
	ReceiptContent += pci->method;													//�ɷѷ�ʽ
	ReceiptContent += "\n�շ�Ա���ţ�";
	ReceiptContent += pci->OperatorNo;											//����
	ReceiptContent += "\n-------------------------------------\n�������ʵ��3\n150420220 κ�Ӻ�";

	isSucceed = CreatePDF(ReceiptContent);
	return isSucceed;
}

LPCTSTR CSubNewFrameWnd::GetWindowClassName() const { return _T("DUILoginFrame"); }

CDuiString CSubNewFrameWnd::GetSkinFile() { return _T(DUI_XML_SUB_NEW); }

CDuiString CSubNewFrameWnd::GetSkinFolder() { return _T(""); }

void CSubNewFrameWnd::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		//����������ť
		if (msg.pSender->GetName() == _T("btnNew"))
		{	
			if (OnNewUser() == true)
				::MessageBox(m_hWnd, L"�����ɹ�~", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			else
				::MessageBox(m_hWnd, L"����ʧ����...������û��û��ġ���û��ѡ�ײ�~��", L"��ʾ", MB_OK | MB_ICONERROR);
		}
		//�����á���ť
		else if (msg.pSender->GetName() == _T("btnReset"))
		{
			CEditUI * edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editName")));
			edits->SetText(L"");
			edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editGender")));
			edits->SetText(L"");
			edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editAddr")));
			edits->SetText(L"");
			edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editMSISDN")));
			edits->SetText(L"");
			edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editCharge")));
			edits->SetText(L"");
		}
		//�رհ�ť
		else if (msg.pSender->GetName() == _T("closebtn"))
		{
			//��ջ����ȡ�����ھ������ջ
			HWND m_hwnd = stackHwnd.top();
			stackHwnd.pop();

			::EnableWindow(m_hwnd, TRUE);												// �����ڻ�ԭ m_hwndΪ�Ӵ��ھ��
			::SetFocus(m_hwnd);																	//���ý��㵽������
			::PostMessage(m_hwnd, WM_CMS_BACKTOPARENT, 0, 0);		//�򸸴��ڷ�����Ϣ
			Close();
		}
	}//if click
}

void CSubNewFrameWnd::Init()
{
	////��ʼ������һ��list�е�Ԫ��
	//��ȡ���ݿ��е��ײ�����
	struct CMS_DB_HEADER * cdh = new struct CMS_DB_HEADER;
	InitCDH(cdh);
	DBgo * dbgo = new DBgo;
	dbgo->QueryPlan(L"", QP_BY_PLANNAME, cdh);

	//���list�б�����
	CListUI * listPlan = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listPlan")));
	struct CMS_DB_NODE * cdn = cdh->next;
	CString wszStr;
	// ���List�б����ݣ�������Add(pListElement)����SetText
	while(cdn != NULL)
	{
		CListTextElementUI* pListElement = new CListTextElementUI;
		pListElement->SetTag(((struct CallPlan*)(cdn->content))->PlanNo);		//��PlanNo��Ϊtag
		listPlan->Add(pListElement);

		wszStr.Format(L"   %d", ((struct CallPlan*)(cdn->content))->PlanNo);
		pListElement->SetText(0, wszStr.GetBuffer(wszStr.GetLength()));
		pListElement->SetText(1, ((struct CallPlan*)(cdn->content))->PlanName);
		wszStr.Format(L"   %.2lf", ((struct CallPlan*)(cdn->content))->RemoteFee);
		pListElement->SetText(2, wszStr.GetBuffer(wszStr.GetLength()));
		wszStr.Format(L"   %.2lf", ((struct CallPlan*)(cdn->content))->LocalFee);
		pListElement->SetText(3, wszStr.GetBuffer(wszStr.GetLength()));
		wszStr.Format(L"   %.2lf", ((struct CallPlan*)(cdn->content))->RoamingFee);
		pListElement->SetText(4, wszStr.GetBuffer(wszStr.GetLength()));

		cdn = cdn->next;
	}

	DeleteCDH(cdh);
	delete dbgo;
	dbgo = NULL;

	return;
}

LRESULT CSubNewFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool & bHandled)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			return true;
		}
		else if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			return true;
		}
	default:
		return false;
	}
}

LRESULT CSubNewFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;	//��־����Ϣ�Ƿ񱻴���
	switch (uMsg)
	{
	case WM_NCLBUTTONDBLCLK: return 0;//����˫��������������󻯣����ηǿͻ������˫���¼�
	default: bHandled = FALSE;
	}
	//����Ѵ�����Ϣ ��ֱ�ӷ���
	if (bHandled) return lRes;
	//�����ǰ��MessageHandler��������Ϣ ��ֱ�ӷ���
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	//����Ļ���WIB����...
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CSubNewFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_PaintManager.Init(m_hWnd);
	CDialogBuilder builder;
	//CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T(DUI_XML_SUB_NEW), (UINT)0, NULL, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);


	//m_WndShadow.Create(m_hWnd);
	//m_WndShadow.SetSize(3);
	//m_WndShadow.SetPosition(0, 0);

	Init();
	return 0;
}

bool CSubNewFrameWnd::OnNewUser()
{
	bool isSucceed = false;
	////��ȡ��ѡ�ײ�
	CListUI * listPlan = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listPlan")));
	CListTextElementUI * pListElement = new CListTextElementUI;
	int nIndex = listPlan->GetCurSel();
	if (nIndex < 0)
		return false;
	pListElement = (CListTextElementUI*)listPlan->GetItemAt(nIndex);
	CLabelUI* labelPlan = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("labelPlan")));
	labelPlan->SetText(pListElement->GetText(1));

	////����UserInfo
	struct UserInfo * pui = new struct UserInfo;
	memset(pui, 0, sizeof(struct UserInfo));

	////���UserInfo
	//��ȡ�ַ���
	CEditUI * edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editName")));
	if (edits->GetText().GetLength() == 0)
	{
		edits->SetFocus();
		return false;
	}
	wcsncpy_s(pui->name, edits->GetText(), edits->GetText().GetLength());
	edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editGender")));
	if (edits->GetText().GetLength() == 0)
	{
		edits->SetFocus();
		return false;
	}
	wcsncpy_s(pui->gender, edits->GetText(), edits->GetText().GetLength());
	edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editAddr")));
	if (edits->GetText().GetLength() == 0)
	{
		edits->SetFocus();
		return false;
	}
	wcsncpy_s(pui->address, edits->GetText(), edits->GetText().GetLength());
	edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editMSISDN")));
	if (edits->GetText().GetLength() == 0)
	{
		edits->SetFocus();
		return false;
	}
	wcsncpy_s(pui->MSISDN, edits->GetText(), edits->GetText().GetLength());
	wcsncpy_s(pui->status, L"����", wcslen(L"����"));
	
	//��ȡ����
	int PlanNO = 0;
	double dCharge = 0.0;
	edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editCharge")));
	swscanf_s(edits->GetText(), L"%lf", &dCharge);
	swscanf_s(pListElement->GetText(0), L"%d", &PlanNO);
	pui->PlanNo = PlanNO;
	pui->balance = dCharge;

	////�������ݿ� 
	DBgo * dbgo = new DBgo;
	if (dbgo->AddUserInfo(pui) == true)
		isSucceed = true;
	else
		isSucceed = false;

	////����
	delete dbgo;
	dbgo = NULL;
	delete pui;
	pui = NULL;
	return true;
}

LPCTSTR CSubDelFrameWnd::GetWindowClassName() const { return _T("DUILoginFrame"); }

CDuiString CSubDelFrameWnd::GetSkinFile() { return _T(DUI_XML_SUB_DEL); }

CDuiString CSubDelFrameWnd::GetSkinFolder() { return _T(""); }

void CSubDelFrameWnd::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		//����ѯ����ť
		if (msg.pSender->GetName() == _T("btnQuery"))
		{
			//��ȡ���� ���ô�����
			CEditUI* editMSISDN = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editMSISDN")));
			if (editMSISDN && editMSISDN->GetText().GetLength() > 0)
			{
				if (!OnQueryUserInfo(editMSISDN->GetText()))
					::MessageBox(GetHWND(), L"��ѯʧ��...�����Ƿ���ڣ�", L"ע��", MB_OK | MB_ICONINFORMATION);
			}
			else
				::MessageBox(GetHWND(), L"����д�û��绰����...", L"ע��", MB_OK | MB_ICONINFORMATION);
		}
		//����������ť
		else if (msg.pSender->GetName() == _T("btnDel"))
		{
			//��ȡ���� ���ô�����
			CEditUI* editMSISDN = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editMSISDN")));
			if (editMSISDN && editMSISDN->GetText().GetLength() > 0)
				if(OnDelUser(editMSISDN->GetText()))
					::MessageBox(GetHWND(), L"�����ɹ�", L"ע��", MB_OK | MB_ICONINFORMATION);
				else
					::MessageBox(GetHWND(), L"����ʧ��...�����Ƿ���ڣ�", L"ע��", MB_OK | MB_ICONINFORMATION);
			else
			{
				::MessageBox(GetHWND(), L"����д�û��绰����...", L"ע��", MB_OK | MB_ICONINFORMATION);
				editMSISDN->SetFocus();
			}
		}
		//�رհ�ť
		else if (msg.pSender->GetName() == _T("closebtn"))
		{
			//��ջ����ȡ�����ھ������ջ
			HWND m_hwnd = stackHwnd.top();
			stackHwnd.pop();

			::EnableWindow(m_hwnd, TRUE);												// �����ڻ�ԭ m_hwndΪ�Ӵ��ھ��
			::SetFocus(m_hwnd);																	//���ý��㵽������
			::PostMessage(m_hwnd, WM_CMS_BACKTOPARENT, 0, 0);		//�򸸴��ڷ�����Ϣ
			Close();
		}
	}//if click
}

void CSubDelFrameWnd::Init()
{
	return;
}

LRESULT CSubDelFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool & bHandled)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			return true;
		}
		else if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			return true;
		}
	default:
		return false;
	}
}

LRESULT CSubDelFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;	//��־����Ϣ�Ƿ񱻴���
	switch (uMsg)
	{
	case WM_NCLBUTTONDBLCLK: return 0;//����˫��������������󻯣����ηǿͻ������˫���¼�
	default: bHandled = FALSE;
	}
	//����Ѵ�����Ϣ ��ֱ�ӷ���
	if (bHandled) return lRes;
	//�����ǰ��MessageHandler��������Ϣ ��ֱ�ӷ���
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	//����Ļ���WIB����...
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CSubDelFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_PaintManager.Init(m_hWnd);
	CDialogBuilder builder;
	//CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T(DUI_XML_SUB_DEL), (UINT)0, NULL, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);


	//m_WndShadow.Create(m_hWnd);
	//m_WndShadow.SetSize(3);
	//m_WndShadow.SetPosition(0, 0);

	Init();
	return 0;
}

bool CSubDelFrameWnd::OnQueryUserInfo(LPCWSTR MSISDN)
{
	bool isSucceed = false;
	//emmmm�������ݿ�
	DBgo * dbgo = new DBgo();
	struct CMS_DB_HEADER * cdh = new struct CMS_DB_HEADER;
	InitCDH(cdh);

	//ִ�в�ѯ ����MSISDN��ȷ����
	dbgo->QueryUserInfo((wchar_t*)MSISDN, QUI_BY_MSISDN | QUI_WAY_ACCURATE, cdh);

	if (cdh->n == 0 || cdh->next == NULL)
	{
		::MessageBox(GetHWND(), L"û���ҵ��ú����Ӧ���û���", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		isSucceed = false;
	}
	else
	{
		//��ȡ����Text���
		CLabelUI* textName = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("textName")));
		CLabelUI* textBalance = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("textBalance")));
		CLabelUI* textStatus = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("textStatus")));
		if (textName == NULL || textBalance == NULL || textStatus == NULL)
		{
			::MessageBox(GetHWND(), L"һ�������������ʧ�ܡ����ؼ�����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			isSucceed = false;
			goto EXITQUERY;
		}

		//ת��������ʽ
		CString wszStr;
		wszStr.Format(L"%.2lf", ((struct UserInfo*)(cdh->next->content))->balance);

		//��ֵ
		textName->SetText(((struct UserInfo*)(cdh->next->content))->name);
		textBalance->SetText(wszStr.GetBuffer(wszStr.GetLength()));
		textStatus->SetText(((struct UserInfo*)(cdh->next->content))->status);

		//�����û��ײͱ�� ��ѯ�ײ����Ƽ��ʷ�
		wszStr.Format(L"%d", ((struct UserInfo*)(cdh->next->content))->PlanNo);
		dbgo->QueryPlan(wszStr.GetBuffer(wszStr.GetLength()), QP_BY_PLANNO, cdh);

		//����Ƿ���ڸ��ײ�
		if (cdh->n != 2)
		{
			::MessageBox(GetHWND(), L"�û���ǰʹ�õ��ײ��Ѳ����ڣ����޸�Ϊ�����ײ͡�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			isSucceed = false;
			goto EXITQUERY;
		}

		//��д�ײ���Ϣ
		wszStr.Format(L"%s������%.2lf���У�%.2lf������%.2lf��",
			((struct CallPlan*)(cdh->next->content))->PlanName, ((struct CallPlan*)(cdh->next->content))->RemoteFee,
			((struct CallPlan*)(cdh->next->content))->LocalFee, ((struct CallPlan*)(cdh->next->content))->RoamingFee);

		//��ֵx2
		CLabelUI* textPlan = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("textPlan")));
		if (textPlan == NULL)
		{
			::MessageBox(GetHWND(), L"һ�������������ʧ�ܡ����ؼ�����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			isSucceed = false;
			goto EXITQUERY;
		}
		textPlan->SetText(wszStr.GetBuffer(wszStr.GetLength()));
	}
	isSucceed = true;

EXITQUERY:
	DeleteCDH(cdh);
	if (dbgo)
	{
		delete dbgo;
		dbgo = NULL;
	}
	return isSucceed;
}

bool CSubDelFrameWnd::OnDelUser(LPCWSTR MSISDN)
{
	bool isSucceed = false;

	DBgo * dbgo = new DBgo;
	isSucceed = dbgo->DropUserInfo((wchar_t*)MSISDN, DUI_WAY_BY_MSISDN);

	delete dbgo;
	dbgo = NULL;
	return isSucceed;
}

LPCTSTR CSubQnMFrameWnd::GetWindowClassName() const { return _T("DUILoginFrame"); }

CDuiString CSubQnMFrameWnd::GetSkinFile() { return _T(DUI_XML_SUB_QNM); }

CDuiString CSubQnMFrameWnd::GetSkinFolder() { return _T(""); }

void CSubQnMFrameWnd::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		//����ѯ����ť
		if (msg.pSender->GetName() == _T("btnQuery"))
		{
			//��ȡ���� ���ô�����
			CEditUI* editMSISDN = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editMSISDN")));
			if (editMSISDN && editMSISDN->GetText().GetLength() > 0)
			{
				if (!OnQueryUserInfo(editMSISDN->GetText()))
					::MessageBox(GetHWND(), L"��ѯʧ��...�����Ƿ���ڣ�", L"ע��", MB_OK | MB_ICONINFORMATION);
				else
					isQueried = true;
			}
			else
				::MessageBox(GetHWND(), L"����д�û��绰����...", L"ע��", MB_OK | MB_ICONINFORMATION);
		}
		//���޸ġ���ť
		else if (msg.pSender->GetName() == _T("btnModify"))
		{
			//if (!isQueried)
			//{
			//	::MessageBox(m_hWnd, L"���Ȳ�ѯ...", L"��ʾ", MB_OK | MB_ICONERROR);
			//	return;
			//}
			//��ȡ���� ���ô�����
			CEditUI* editMSISDN = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editMSISDN")));
			if (editMSISDN && editMSISDN->GetText().GetLength() > 0)
			{
				if (OnModifyUserInfo(editMSISDN->GetText()))
				{
					::MessageBox(GetHWND(), L"�޸ĳɹ�", L"ע��", MB_OK | MB_ICONINFORMATION);
					isQueried = false;
				}
				else
					::MessageBox(GetHWND(), 
						L"�޸�ʧ��...��ȷ�Ϻ����Ƿ���ڡ��Ƿ���ѡ���ײ͡��Ƿ���д�������ֶ�",
						L"ע��",
						MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				::MessageBox(GetHWND(), L"����д�û��绰����...", L"ע��", MB_OK | MB_ICONINFORMATION);
				editMSISDN->SetFocus();
			}
		}
		//�رհ�ť
		else if (msg.pSender->GetName() == _T("closebtn"))
		{
			//��ջ����ȡ�����ھ������ջ
			HWND m_hwnd = stackHwnd.top();
			stackHwnd.pop();

			::EnableWindow(m_hwnd, TRUE);												// �����ڻ�ԭ m_hwndΪ�Ӵ��ھ��
			::SetFocus(m_hwnd);																	//���ý��㵽������
			::PostMessage(m_hwnd, WM_CMS_BACKTOPARENT, 0, 0);		//�򸸴��ڷ�����Ϣ
			Close();
		}
	}//if click
}

void CSubQnMFrameWnd::Init()
{
	isQueried = false;

	////��ʼ������һ��list�е�Ԫ��
	//��ȡ���ݿ��е��ײ�����
	struct CMS_DB_HEADER * cdh = new struct CMS_DB_HEADER;
	InitCDH(cdh);
	DBgo * dbgo = new DBgo;
	dbgo->QueryPlan(L"", QP_BY_PLANNAME, cdh);

	//���list�б�����
	CListUI * listPlan = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listPlan")));
	struct CMS_DB_NODE * cdn = cdh->next;
	CString wszStr;
	// ���List�б����ݣ�������Add(pListElement)����SetText
	while (cdn != NULL)
	{
		CListTextElementUI* pListElement = new CListTextElementUI;
		pListElement->SetTag(((struct CallPlan*)(cdn->content))->PlanNo);		//��PlanNo��Ϊtag
		listPlan->Add(pListElement);

		wszStr.Format(L"   %d", ((struct CallPlan*)(cdn->content))->PlanNo);
		pListElement->SetText(0, wszStr.GetBuffer(wszStr.GetLength()));
		pListElement->SetText(1, ((struct CallPlan*)(cdn->content))->PlanName);
		wszStr.Format(L"   %.2lf", ((struct CallPlan*)(cdn->content))->RemoteFee);
		pListElement->SetText(2, wszStr.GetBuffer(wszStr.GetLength()));
		wszStr.Format(L"   %.2lf", ((struct CallPlan*)(cdn->content))->LocalFee);
		pListElement->SetText(3, wszStr.GetBuffer(wszStr.GetLength()));
		wszStr.Format(L"   %.2lf", ((struct CallPlan*)(cdn->content))->RoamingFee);
		pListElement->SetText(4, wszStr.GetBuffer(wszStr.GetLength()));

		cdn = cdn->next;
	}

	DeleteCDH(cdh);
	delete dbgo;
	dbgo = NULL;

	return;
}

LRESULT CSubQnMFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool & bHandled)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			return true;
		}
		else if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			return true;
		}
	default:
		return false;
	}
}

LRESULT CSubQnMFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;	//��־����Ϣ�Ƿ񱻴���
	switch (uMsg)
	{
	case WM_NCLBUTTONDBLCLK: return 0;//����˫��������������󻯣����ηǿͻ������˫���¼�
	default: bHandled = FALSE;
	}
	//����Ѵ�����Ϣ ��ֱ�ӷ���
	if (bHandled) return lRes;
	//�����ǰ��MessageHandler��������Ϣ ��ֱ�ӷ���
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	//����Ļ���WIB����...
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CSubQnMFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_PaintManager.Init(m_hWnd);
	CDialogBuilder builder;
	//CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T(DUI_XML_SUB_QNM), (UINT)0, NULL, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);


	//m_WndShadow.Create(m_hWnd);
	//m_WndShadow.SetSize(3);
	//m_WndShadow.SetPosition(0, 0);

	Init();
	return 0;
}

bool CSubQnMFrameWnd::OnQueryUserInfo(LPCWSTR MSISDN)
{
	bool isSucceed = false;
	//emmmm�������ݿ�
	DBgo * dbgo = new DBgo();
	struct CMS_DB_HEADER * cdh = new struct CMS_DB_HEADER;
	InitCDH(cdh);

	//ִ�в�ѯ ����MSISDN��ȷ����
	dbgo->QueryUserInfo((wchar_t*)MSISDN, QUI_BY_MSISDN | QUI_WAY_ACCURATE, cdh);

	if (cdh->n == 0 || cdh->next == NULL)
	{
		::MessageBox(GetHWND(), L"û���ҵ��ú����Ӧ���û���", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		isSucceed = false;
	}
	else
	{
		//��ȡ����Text���
		CEditUI* textName = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editName")));
		CEditUI* textGender = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editGender")));
		CEditUI* textAddr = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editAddr")));
		CEditUI* textStatus = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editStatus")));
		CLabelUI* textBalance = static_cast<CLabelUI*>(m_PaintManager.FindControl(L"labelBalance"));
		if (textName == NULL || textGender == NULL || textAddr == NULL)
		{
			::MessageBox(GetHWND(), L"һ�������������ʧ�ܡ����ؼ�����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			isSucceed = false;
			goto EXITQUERY;
		}

		//ת��������ʽ
		CString wszStr;
		wszStr.Format(L"%.2lf", ((struct UserInfo*)(cdh->next->content))->balance);

		//��ֵ
		textName->SetText(((struct UserInfo*)(cdh->next->content))->name);
		textGender->SetText(((struct UserInfo*)(cdh->next->content))->gender);
		textAddr->SetText(((struct UserInfo*)(cdh->next->content))->address);
		textBalance->SetText(wszStr.GetBuffer(wszStr.GetLength()));
		textStatus->SetText(((struct UserInfo*)(cdh->next->content))->status);

		//�����û��ײͱ�� ��ѯ�ײ����Ƽ��ʷ�
		wszStr.Format(L"%d", ((struct UserInfo*)(cdh->next->content))->PlanNo);
		dbgo->QueryPlan(wszStr.GetBuffer(wszStr.GetLength()), QP_BY_PLANNO, cdh);

		//����Ƿ���ڸ��ײ�
		if (cdh->n != 2)
		{
			::MessageBox(GetHWND(), L"�û���ǰʹ�õ��ײ��Ѳ����ڣ����޸�Ϊ�����ײ͡�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			isSucceed = false;
			goto EXITQUERY;
		}

		//��д�ײ���Ϣ
		wszStr.Format(L"%s������%.2lf���У�%.2lf������%.2lf��",
			((struct CallPlan*)(cdh->next->content))->PlanName, ((struct CallPlan*)(cdh->next->content))->RemoteFee,
			((struct CallPlan*)(cdh->next->content))->LocalFee, ((struct CallPlan*)(cdh->next->content))->RoamingFee);

		//��ֵx2
		CLabelUI* textPlan = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("labelPlan")));
		if (textPlan == NULL)
		{
			::MessageBox(GetHWND(), L"һ�������������ʧ�ܡ����ؼ�����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			isSucceed = false;
			goto EXITQUERY;
		}
		textPlan->SetText(wszStr.GetBuffer(wszStr.GetLength()));
	}
	isSucceed = true;

EXITQUERY:
	DeleteCDH(cdh);
	if (dbgo)
	{
		delete dbgo;
		dbgo = NULL;
	}
	return isSucceed;
}

bool CSubQnMFrameWnd::OnModifyUserInfo(LPCWSTR MSISDN)
{
	bool isSucceed = false;
	////��ȡ��ѡ�ײ�
	CListUI * listPlan = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listPlan")));
	CListTextElementUI * pListElement = new CListTextElementUI;
	int nIndex = listPlan->GetCurSel();
	if (nIndex < 0)
		return false;
	pListElement = (CListTextElementUI*)listPlan->GetItemAt(nIndex);
	CLabelUI* labelPlan = static_cast<CLabelUI*>(m_PaintManager.FindControl(_T("labelPlan")));
	labelPlan->SetText(pListElement->GetText(1));

	////����UserInfo
	struct UserInfo * pui = new struct UserInfo;
	memset(pui, 0, sizeof(struct UserInfo));

	////���UserInfo
	//��ȡ�ַ���
	CEditUI * 	edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editMSISDN")));
	if (edits->GetText().GetLength() == 0)
	{
		edits->SetFocus();
		return false;
	}
	wcsncpy_s(pui->MSISDN, edits->GetText(), edits->GetText().GetLength());
	//����ɾ��ԭ��Ϣ �ٲ�������Ϣ ����޸�
	DBgo * dbgo = new DBgo;
	isSucceed = dbgo->DropUserInfo((wchar_t*)MSISDN, DUI_WAY_BY_MSISDN);
	//�������
	 edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editName")));
	if (edits->GetText().GetLength() == 0)
	{
		edits->SetFocus();
		return false;
	}
	wcsncpy_s(pui->name, edits->GetText(), edits->GetText().GetLength());
	edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editGender")));
	if (edits->GetText().GetLength() == 0)
	{
		edits->SetFocus();
		return false;
	}
	wcsncpy_s(pui->gender, edits->GetText(), edits->GetText().GetLength());
	edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editAddr")));
	if (edits->GetText().GetLength() == 0)
	{
		edits->SetFocus();
		return false;
	}
	wcsncpy_s(pui->address, edits->GetText(), edits->GetText().GetLength());
	edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editStatus")));
	if (edits->GetText().GetLength() == 0)
	{
		edits->SetFocus();
		return false;
	}
	wcsncpy_s(pui->status, edits->GetText(), edits->GetText().GetLength());

	//��ȡ����
	int PlanNO = 0;
	double dCharge = 0.0;
	//edits = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editCharge")));
	CLabelUI * labels = static_cast<CLabelUI*>(m_PaintManager.FindControl(L"labelBalance"));
	swscanf_s(labels->GetText(), L"%lf", &dCharge);
	swscanf_s(pListElement->GetText(0), L"%d", &PlanNO);
	pui->PlanNo = PlanNO;
	pui->balance = dCharge;

	////�������ݿ� 
	//DBgo * dbgo = new DBgo;
	if (dbgo->AddUserInfo(pui) == true)
		isSucceed = true;
	else
		isSucceed = false;

	////����
	delete dbgo;
	dbgo = NULL;
	delete pui;
	pui = NULL;
	return true;
}

LPCTSTR CSubQRFrameWnd::GetWindowClassName() const { return _T("DUILoginFrame"); }

CDuiString CSubQRFrameWnd::GetSkinFile() { return _T(DUI_XML_SUB_QR); }

CDuiString CSubQRFrameWnd::GetSkinFolder() { return _T(""); }

void CSubQRFrameWnd::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		//����ѯ����ť
		if (msg.pSender->GetName() == _T("btnQuery"))
		{
			CEditUI* editMSISDN = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editMSISDN"));
			if (editMSISDN && editMSISDN->GetText().GetLength() != 0)
			{
				if (OnQueryRecords(editMSISDN->GetText()))
					//::MessageBox(m_hWnd, L"���ݿ������", L"��ʾ", MB_OK | MB_ICONERROR);

				//else
					isQueried = true;
			}
			else
				::MessageBox(m_hWnd, L"�����������~", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		}
		//����������ť
		else if (msg.pSender->GetName() == _T("btnOut"))
		{
			CEditUI* editMSISDN = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editMSISDN"));
			if (editMSISDN && editMSISDN->GetText().GetLength() != 0)
			{
				if (!OnOut(editMSISDN->GetText()))
					::MessageBox(m_hWnd, L"�ɷѼ�¼����ʧ��", L"��ʾ", MB_OK | MB_ICONERROR);
				else
					::MessageBox(m_hWnd, L"�ɷѼ�¼�����ɹ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			}
			else
				::MessageBox(m_hWnd, L"�����������~", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		}
		//�رհ�ť
		else if (msg.pSender->GetName() == _T("closebtn") ||
			msg.pSender->GetName() == L"btnClose")
		{
			//��ջ����ȡ�����ھ������ջ
			HWND m_hwnd = stackHwnd.top();
			stackHwnd.pop();

			::EnableWindow(m_hwnd, TRUE);												// �����ڻ�ԭ m_hwndΪ�Ӵ��ھ��
			::SetFocus(m_hwnd);																	//���ý��㵽������
			::PostMessage(m_hwnd, WM_CMS_BACKTOPARENT, 0, 0);		//�򸸴��ڷ�����Ϣ
			Close();
		}
	}
}

void CSubQRFrameWnd::Init()
{
	isQueried = false;
}

LRESULT CSubQRFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool & bHandled)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			return true;
		}
		else if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			return true;
		}
	default:
		return false;
	}
}

LRESULT CSubQRFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;	//��־����Ϣ�Ƿ񱻴���
	switch (uMsg)
	{
	case WM_NCLBUTTONDBLCLK: return 0;//����˫��������������󻯣����ηǿͻ������˫���¼�
	default: bHandled = FALSE;
	}
	//����Ѵ�����Ϣ ��ֱ�ӷ���
	if (bHandled) return lRes;
	//�����ǰ��MessageHandler��������Ϣ ��ֱ�ӷ���
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	//����Ļ���WIB����...
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CSubQRFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_PaintManager.Init(m_hWnd);
	CDialogBuilder builder;
	//CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T(DUI_XML_SUB_QR), (UINT)0, NULL, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);


	//m_WndShadow.Create(m_hWnd);
	//m_WndShadow.SetSize(3);
	//m_WndShadow.SetPosition(0, 0);

	Init();
	return 0;
}

bool CSubQRFrameWnd::OnQueryRecords(LPCWSTR MSISDN)
{
	bool isSucceed = false;

	cdh = new struct CMS_DB_HEADER;
	DBgo * dbgo = new DBgo;

	if (cdh == NULL || dbgo == NULL)
		isSucceed = false;
	else
	{
		InitCDH(cdh);
		dbgo->QueryCharge((wchar_t*)MSISDN, cdh);
		isSucceed = true;
	}
	
	if (dbgo)
	{
		delete dbgo;
		dbgo = NULL;
	}

	if (cdh->n == 0)
	{
		::MessageBox(m_hWnd, L"���޽ɷ���Ϣ", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		return false;
	}

	//�����б�
	CListUI * listPlan = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listPlan")));
	struct CMS_DB_NODE * cdn = cdh->next;
	CString wszStr;
	int i = 0;
	// ���List�б����ݣ�������Add(pListElement)����SetText
	while (cdn != NULL)
	{
		CListTextElementUI* pListElement = new CListTextElementUI;
		pListElement->SetTag(i++);		//��PlanNo��Ϊtag
		listPlan->Add(pListElement);

		pListElement->SetText(0,  ((struct Charge*)(cdn->content))->PayTime);
		wszStr.Format(L"   %.2lf", ((struct Charge*)(cdn->content))->PayAmount);
		pListElement->SetText(1, wszStr.GetBuffer(wszStr.GetLength()));
		pListElement->SetText(2, ((struct Charge*)(cdn->content))->PayMethod);
		wszStr.Format(L"   %d", ((struct Charge*)(cdn->content))->OperatorNo);
		pListElement->SetText(3, wszStr.GetBuffer(wszStr.GetLength()));

		cdn = cdn->next;
	}

	return isSucceed;
}

bool CSubQRFrameWnd::OnOut(LPCWSTR MSISDN)
{
	bool isSucceed = false;
	Book* book = xlCreateBook();
	if (book)
	{
		Sheet* sheet = book->addSheet(L"Sheet1");
		if (sheet)
		{
			//������û����룺13800138000��
			sheet->writeStr(0, 0, L"�û����룺");
			sheet->writeStr(0, 1, MSISDN);
			//�����ͷ���ɷ�ʱ�� �ɷѽ�� ֧����ʽ ����Ա���š�
			sheet->writeStr(1, 0, L"�ɷ�ʱ��");
			sheet->writeStr(1, 1, L"�ɷѽ��");
			sheet->writeStr(1, 2, L"֧����ʽ");
			sheet->writeStr(1, 3, L"����Ա����");
			//ѭ�������������
			struct CMS_DB_NODE * cdn = cdh->next;
			int i = 2;
			while (cdn != NULL)
			{
				sheet->writeStr(i, 0, ((struct Charge*)(cdn->content))->PayTime);
				sheet->writeNum(i, 1, ((struct Charge*)(cdn->content))->PayAmount);
				sheet->writeStr(i, 2, ((struct Charge*)(cdn->content))->PayMethod);
				sheet->writeNum(i++, 3, ((struct Charge*)(cdn->content))->OperatorNo);
				cdn = cdn->next;
			}

			sheet->setCol(1, 1, 12);
		}
		//���û��绰������Ϊ�ļ���
		CString wszFileName = MSISDN;
		wszFileName += ".xls";
		if (book->save(wszFileName.GetBuffer(wszFileName.GetLength())))
		{
			::ShellExecute(NULL, L"open", wszFileName.GetBuffer(wszFileName.GetLength()), NULL, NULL, SW_SHOW);
			isSucceed = true;
		}
		else
		{
			//std::cout << book->errorMessage() << std::endl;
			::MessageBox(m_hWnd, s2ws(book->errorMessage()).c_str(), L"XLS FAILED", MB_OK | MB_ICONERROR);
			isSucceed = false;
		}

		book->release();
	}
	else
		isSucceed = false;
	return isSucceed;
}

LPCTSTR CSubOperatorMgrFrameWnd::GetWindowClassName() const { return _T("DUILoginFrame"); }

CDuiString CSubOperatorMgrFrameWnd::GetSkinFile() { return _T(DUI_XML_SUB_OPERATORMGR); }

CDuiString CSubOperatorMgrFrameWnd::GetSkinFolder() { return _T(""); }

void CSubOperatorMgrFrameWnd::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		//�رհ�ť
		if (msg.pSender->GetName() == _T("closebtn"))
		{
			//��ջ����ȡ�����ھ������ջ
			HWND m_hwnd = stackHwnd.top();
			stackHwnd.pop();

			::EnableWindow(m_hwnd, TRUE);												// �����ڻ�ԭ m_hwndΪ�Ӵ��ھ��
			::SetFocus(m_hwnd);																	//���ý��㵽������
			::PostMessage(m_hwnd, WM_CMS_BACKTOPARENT, 0, 0);		//�򸸴��ڷ�����Ϣ
			//PostQuitMessage(0); 
			Close();
		}
		//����շ�Ա
		else if (msg.pSender->GetName() == _T("btnAdd"))
		{
			if (OnNewOperator() == true)
				::MessageBox(m_hWnd, L"��ӳɹ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			else
				::MessageBox(m_hWnd, L"���ʧ�ܡ��Ƿ���δ���", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		}
		//����
		else if (msg.pSender->GetName() == _T("btnReset"))
		{
			CEditUI * editName = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editName"));
			CEditUI * editGender = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editGender"));
			CEditUI * editPwd = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editPwd"));
			if (editName != NULL &&
				editGender != NULL &&
				editPwd != NULL)
			{
				editName->SetText(L"");
				editGender->SetText(L"");
				editPwd->SetText(L"");
			}
		}
		//��ѯ
		else if (msg.pSender->GetName() == _T("btnQuery"))
		{
			if(OnQueryOperator() == false)
				::MessageBox(m_hWnd, L"��ѯʧ�ܡ�\n�Ƿ�δ��������ݡ������������ѯ��ʽ�Ƿ�ƥ�䣿", 
					L"��ʾ", MB_OK | MB_ICONINFORMATION);
		}
		//�޸�
		else if (msg.pSender->GetName() == _T("btnModify"))
		{
			if(cdh == NULL)
				::MessageBox(m_hWnd, L"����ִ�в�ѯ...",	L"��ʾ", MB_OK | MB_ICONINFORMATION);
			else
			{
				//��ȡѡ��Ԫ�صľ��
				CListUI * listOperator = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listOperator")));
				CListTextElementUI * pListElement = new CListTextElementUI;
				int nIndex = listOperator->GetCurSel();
				if (nIndex < 0)
				{
					::MessageBox(m_hWnd, L"��ѡ����Ҫ�޸ĵ���Ϣ...", L"��ʾ", MB_OK | MB_ICONINFORMATION);
					return;
				}
				pListElement = (CListTextElementUI*)listOperator->GetItemAt(nIndex);
				//��ȡѡ��Ԫ�صĹ���
				int SelectedNo = 0;
				swscanf_s(pListElement->GetText(0), L"%d", &SelectedNo);

				//�ҵ���Ԫ�ض�Ӧ��������
				struct CMS_DB_NODE * cdn = cdh->next;
				while (cdn != NULL)
				{
					if (((struct Operator*)(cdn->content))->OperatorNo == SelectedNo)
						break;
					cdn = cdn->next;
				}
				if (cdn == NULL)
				{
					::MessageBox(m_hWnd, L"�������", L"��ʾ", MB_OK | MB_ICONERROR);
					return;
				}
				//��ʾ��ɫ����
				ctrlGrayOpMgr = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayOpMgr"));
				ctrlGrayOpMgr->SetVisible(true);
				ctrlGrayOpMgrQMD = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayOpMgrQMD"));
				ctrlGrayOpMgrQMD->SetVisible(true);

				//��ȡ��ǰ���ھ��
				HWND m_hwnd = GetHWND();
				//����ǰ���ھ������ջ
				stackHwnd.push(m_hwnd);
				//�����޸��շ�Ա�Ӵ����߳�
				_beginthread(ModifyOperatorThread, 0, cdn);
			}
		}
		//ɾ��
		else if (msg.pSender->GetName() == _T("btnDelete"))
		{
			if (cdh == NULL)
				::MessageBox(m_hWnd, L"����ִ�в�ѯ...", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			else
			{
				//��ȡѡ��Ԫ�صľ��
				CListUI * listOperator = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listOperator")));
				CListTextElementUI * pListElement = new CListTextElementUI;
				int nIndex = listOperator->GetCurSel();
				if (nIndex < 0)
				{
					::MessageBox(m_hWnd, L"��ѡ����Ҫ�޸ĵ���Ϣ...", L"��ʾ", MB_OK | MB_ICONINFORMATION);
					return;
				}
				pListElement = (CListTextElementUI*)listOperator->GetItemAt(nIndex);
				//��ȡѡ��Ԫ�صĹ���
				int SelectedNo = 0;
				swscanf_s(pListElement->GetText(0), L"%d", &SelectedNo);

				//�ҵ���Ԫ�ض�Ӧ��������
				struct CMS_DB_NODE * cdn = cdh->next;
				while (cdn != NULL)
				{
					if (((struct Operator*)(cdn->content))->OperatorNo == SelectedNo)
						break;
					cdn = cdn->next;
				}
				if (cdn == NULL)
				{
					::MessageBox(m_hWnd, L"�������", L"��ʾ", MB_OK | MB_ICONERROR);
					return;
				}
				//��ȡһ�¹���
				int OpNoToDel = ((struct Operator*)(cdn->content))->OperatorNo;
				//������ɾ��
				DBgo * dbgo = new DBgo;
				if (dbgo == NULL)
				{
					::MessageBox(m_hWnd, L"dbgo Null Pointer��", L"��ʾ", MB_OK | MB_ICONERROR);
					return;
				}
				if(dbgo->DropOperator(OpNoToDel) == true)
					::MessageBox(m_hWnd, L"ɾ���ɹ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
				else
					::MessageBox(m_hWnd, L"ɾ��ʧ��\n���ݿ����", L"��ʾ", MB_OK | MB_ICONERROR);
				delete dbgo;
				dbgo = NULL;
			}
			return;
		}
	}
	else if (msg.sType == _T("selectchanged"))
	{
		//��xml�е�opt��Ӧ ������ѡopt �л�switch����
		CDuiString name = msg.pSender->GetName();
		CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("switch")));
		if (name == _T("optNew")) { pControl->SelectItem(0); this->OnSwitchNew(); }
		else if (name == _T("optQMD")) { pControl->SelectItem(1);	this->OnSwitchQMD(); }
	}
}

CSubOperatorMgrFrameWnd::~CSubOperatorMgrFrameWnd()
{
	if (cdh != NULL)
		DeleteCDH(cdh);
}

void CSubOperatorMgrFrameWnd::Init()
{
	cdh = NULL;
	return;
}

LRESULT CSubOperatorMgrFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool & bHandled)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			return true;
		}
		else if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			return true;
		}
	default:
		return false;
	}
}

LRESULT CSubOperatorMgrFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;	//��־����Ϣ�Ƿ񱻴���
	switch (uMsg)
	{
	case WM_NCLBUTTONDBLCLK: return 0;//����˫��������������󻯣����ηǿͻ������˫���¼�
	case WM_CMS_BACKTOPARENT:
		ctrlGrayOpMgr = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayOpMgr"));
		ctrlGrayOpMgr->SetVisible(false);
		ctrlGrayOpMgrQMD = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayOpMgrQMD"));
		ctrlGrayOpMgrQMD->SetVisible(false);
		break;
	default: bHandled = FALSE;
	}
	//����Ѵ�����Ϣ ��ֱ�ӷ���
	if (bHandled) return lRes;
	//�����ǰ��MessageHandler��������Ϣ ��ֱ�ӷ���
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	//����Ļ���WIB����...
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CSubOperatorMgrFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_PaintManager.Init(m_hWnd);
	CDialogBuilder builder;
	CSubOperatorMgrBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T(DUI_XML_SUB_OPERATORMGR), (UINT)0, &cb, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);


	//m_WndShadow.Create(m_hWnd);
	//m_WndShadow.SetSize(3);
	//m_WndShadow.SetPosition(0, 0);

	Init();
	return 0;
}

bool CSubOperatorMgrFrameWnd::OnSwitchNew()
{
	return false;
}

bool CSubOperatorMgrFrameWnd::OnSwitchQMD()
{
	return false;
}


// ��Ӧ����������ǩҳ�еġ����ӡ���ť�¼�
bool CSubOperatorMgrFrameWnd::OnNewOperator()
{
	bool isSucceed = false;
	//��ȡ�������Ա����롢�ȼ�
	CEditUI * editName = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editName"));
	CEditUI * editGender = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editGender"));
	CEditUI * editPwd = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editPwd"));
	CComboUI * pCombox = static_cast<CComboUI*>(m_PaintManager.FindControl(L"comboClass"));
	int nsel = pCombox->GetCurSel();
	CListLabelElementUI* pItemEle = (CListLabelElementUI*)pCombox->GetItemAt(nsel);
	
	//�Ϸ��Լ��
	if (editName == NULL ||
		editGender == NULL ||
		editPwd == NULL ||
		pItemEle == NULL)
		return false;
	else if (editName->GetText().GetLength() == 0 ||
		editGender->GetText().GetLength() == 0 ||
		editPwd->GetText().GetLength() == 0)
		return false;

	//��ȡ����MD5
	std::wstring wszStr = editPwd->GetText();
	MD5 * md5 = new MD5(ws2s(wszStr));
	wszStr = s2ws(md5->md5());

	//��ȡ��ǰ��󹤺�
	DBgo * dbgo = new DBgo;
	if(dbgo == NULL)
	{
		if (md5)
		{
			delete md5;
			md5 = NULL;
		}
		return false;
	}
	int MaxNo = dbgo->GetMaxNo(L"OperatorNo", L"Operator");
	if (MaxNo == -1)
	{
		if (md5)
		{
			delete md5;
			md5 = NULL;
		}
		if (dbgo)
		{
			delete dbgo;
			dbgo = NULL;
		}
		return false;
	}
	++MaxNo;		//���շ�Ա����Ϊ����󹤺�+1

	//���ṹ��
	struct Operator * pOperator = new struct Operator;
	if (pOperator == NULL)
	{	
		if (md5)
		{
			delete md5;
			md5 = NULL;
		}
		return false;
	}
	memset(pOperator, 0, sizeof(struct Operator));
	pOperator->Class = (pItemEle->GetText() == L"����Ա") ? 666 : 1;
	//pOperator->LoginStatus = 0;
	pOperator->OperatorNo = MaxNo;
	wcsncpy_s(pOperator->password, wszStr.c_str(), wszStr.length() * 2);
	wszStr = editName->GetText();
	wcsncpy_s(pOperator->OperatorName, wszStr.c_str(), wszStr.length() * 2);
	wszStr = editGender->GetText();
	wcsncpy_s(pOperator->OperatorGender, wszStr.c_str(), wszStr.length() * 2);
	
	//ִ�����ݿ⶯��
	isSucceed = dbgo->AddOperator(pOperator);

	if (md5)
	{
		delete md5;
		md5 = NULL;
	}
	if (pOperator)
	{
		delete pOperator;
		pOperator = NULL;
	}
	if (dbgo)
	{
		delete dbgo;
		dbgo = NULL;
	}
	return isSucceed;
}

bool CSubOperatorMgrFrameWnd::OnQueryOperator()
{
	//��ȡ�ؼ����
	CEditUI * editContent = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editContent"));
	CComboUI * pCombox = static_cast<CComboUI*>(m_PaintManager.FindControl(L"comboMethod"));
	int nsel = pCombox->GetCurSel();
	CListLabelElementUI* pItemEle = (CListLabelElementUI*)pCombox->GetItemAt(nsel);

	cdh = new struct CMS_DB_HEADER;

	if (editContent == NULL ||
		pItemEle == NULL ||
		cdh == NULL)
	{
		if (cdh != NULL)
		{
			delete cdh;
			cdh = NULL;
		}
		return false;
	}
	//��ʼ��cdh
	InitCDH(cdh);

	//�������ݿ� 
	DBgo * dbgo = new DBgo;
	if (dbgo == NULL)
	{
		delete cdh;
		cdh = NULL;
		return false;
	}

	//��ȡ�������ݡ���ѯ��ʽ
	int QueryMethod = (pItemEle->GetText() == L"���ţ���ȷ��ѯ��") ? QO_BY_OPERATORNO : QO_BY_OPERATORNAME;
	CString wszStr = editContent->GetText();
	//ִ�в�ѯ
	if (dbgo->QueryOperator(wszStr.GetBuffer(wszStr.GetLength()), QueryMethod, cdh)
		== false)
		::MessageBox(m_hWnd, L"��ѯ������~", L"��ʾ", MB_OK|MB_ICONERROR);
	else if(cdh->n == 0)
		::MessageBox(m_hWnd, L"û�в鵽�����Ϣ", L"��ʾ", MB_OK | MB_ICONINFORMATION);
	else
	{
		////д���б�
		//��ȡ���
		CListUI * listOperator = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listOperator")));
		struct CMS_DB_NODE * cdn = cdh->next;

		// ���List�б����ݣ�������Add(pListElement)����SetText
		while (cdn != NULL)
		{
			CListTextElementUI* pListElement = new CListTextElementUI;
			pListElement->SetTag(((struct Operator*)(cdn->content))->OperatorNo);		//��OperatorNo��Ϊtag
			listOperator->Add(pListElement);

			wszStr.Format(L"   %d", ((struct Operator*)(cdn->content))->OperatorNo);
			pListElement->SetText(0, wszStr.GetBuffer(wszStr.GetLength()));
			pListElement->SetText(1, ((struct Operator*)(cdn->content))->OperatorName);
			pListElement->SetText(2, ((struct Operator*)(cdn->content))->OperatorGender);
			pListElement->SetText(3, ((struct Operator*)(cdn->content))->Class==666?L"����Ա":L"�շ�Ա");

			cdn = cdn->next;
		}
	}
	if (dbgo)
	{
		delete dbgo;
		dbgo = NULL;
	}
	return true;
}

LPCTSTR CModifyOperatorFrameWnd::GetWindowClassName() const { return _T("DUILoginFrame"); }

CDuiString CModifyOperatorFrameWnd::GetSkinFile() { return _T(DUI_XML_SUB_MODIFYOPERATOR); }

CDuiString CModifyOperatorFrameWnd::GetSkinFolder() { return _T(""); }

void CModifyOperatorFrameWnd::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		//�رհ�ť
		if (msg.pSender->GetName() == _T("closebtn"))
		{
			//��ջ����ȡ�����ھ������ջ
			HWND m_hwnd = stackHwnd.top();
			stackHwnd.pop();

			::EnableWindow(m_hwnd, TRUE);												// �����ڻ�ԭ m_hwndΪ�Ӵ��ھ��
			::SetFocus(m_hwnd);																	//���ý��㵽������
			::PostMessage(m_hwnd, WM_CMS_BACKTOPARENT, 0, 0);		//�򸸴��ڷ�����Ϣ
																	//PostQuitMessage(0); 
			Close();
		}
		//�޸İ�ť
		else if (msg.pSender->GetName() == L"btnModify")
		{
			if (OnModify() == true)
				::MessageBox(m_hWnd, L"�޸ĳɹ�~", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		}
		//���ð�ť
		else if (msg.pSender->GetName() == L"btnReset")
		{
			editName = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editName"));
			editGender = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editGender"));
			editPwd = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editPwd"));
			if (editName == NULL ||
				editGender == NULL ||
				editPwd == NULL)
			{
				::MessageBox(m_hWnd, L"��ָ���쳣��", L"��ʾ", MB_OK | MB_ICONINFORMATION);
				return;
			}
			editName->SetText(L"");
			editGender->SetText(L"");
			editPwd->SetText(L"");
		}
	}
}

CModifyOperatorFrameWnd::CModifyOperatorFrameWnd(CMS_DB_NODE * cdn)
{
	if (cdn != NULL)
		pOperator = (struct Operator*)(cdn->content);
	else
		pOperator = NULL;
}

void CModifyOperatorFrameWnd::Init()
{
	//Ϊ���ؼ���ֵ
	CLabelUI * labelOperatorNo = static_cast<CLabelUI*>(m_PaintManager.FindControl(L"labelOperatorNo"));
	CString wszStr;
	wszStr.Format(L"%d", pOperator->OperatorNo);

	if (labelOperatorNo != NULL)
		labelOperatorNo->SetText(wszStr.GetBuffer(wszStr.GetLength()));
	CEditUI * edits = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editName"));
	if (edits != NULL)
		edits->SetText(pOperator->OperatorName);
	edits = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editGender"));
	if(edits != NULL)
		edits->SetText(pOperator->OperatorGender);
	
	return;
}

LRESULT CModifyOperatorFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool & bHandled)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			return true;
		}
		else if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			return true;
		}
	default:
		return false;
	}
}

LRESULT CModifyOperatorFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;	//��־����Ϣ�Ƿ񱻴���
	switch (uMsg)
	{
	case WM_NCLBUTTONDBLCLK: return 0;//����˫��������������󻯣����ηǿͻ������˫���¼�
	default: bHandled = FALSE;
	}
	//����Ѵ�����Ϣ ��ֱ�ӷ���
	if (bHandled) return lRes;
	//�����ǰ��MessageHandler��������Ϣ ��ֱ�ӷ���
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	//����Ļ���WIB����...
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CModifyOperatorFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_PaintManager.Init(m_hWnd);
	CDialogBuilder builder;
	//CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T(DUI_XML_SUB_MODIFYOPERATOR), (UINT)0, NULL, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);


	//m_WndShadow.Create(m_hWnd);
	//m_WndShadow.SetSize(3);
	//m_WndShadow.SetPosition(0, 0);

	Init();
	return 0;
}


// ��Ӧ���޸ġ���ť
bool CModifyOperatorFrameWnd::OnModify()
{
	//����һ������
	editName = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editName"));
	editGender = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editGender"));
	editPwd = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editPwd"));
	if (editName == NULL ||
		editGender == NULL ||
		editPwd == NULL)
	{
		::MessageBox(m_hWnd, L"��ָ���쳣��", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		return false;
	}
	CComboUI * pCombox = static_cast<CComboUI*>(m_PaintManager.FindControl(L"comboClass"));
	int nsel = pCombox->GetCurSel();
	if (nsel < 0)
	{
		::MessageBox(m_hWnd, L"��ѡ���û��ȼ���", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		return false;
	}
	pItemEle = (CListLabelElementUI*)pCombox->GetItemAt(nsel);
	//��ɾ
	DBgo * dbgo = new DBgo;
	if (dbgo == NULL)
	{
		::MessageBox(m_hWnd, L"dbgo Null Pointer", L"��ʾ", MB_OK);
		return false;
	}

	if (dbgo->DropOperator(pOperator->OperatorNo) == false)
	{
		::MessageBox(m_hWnd, L"�޸�ʧ��\nûɾ�ɹ�...", L"��ʾ", MB_OK);
		delete dbgo;
		dbgo = NULL;
		return false;
	}
	//�ٽ�
	struct Operator* pO = new struct Operator;
	if (pO == NULL)
	{
		::MessageBox(m_hWnd, L"pO Null Pointer", L"��ʾ", MB_OK);
		delete dbgo;
		dbgo = NULL;
		return false;
	}
	memset(pO, 0, sizeof(struct Operator));
	//����
	pO->OperatorNo = pOperator->OperatorNo;
	//dbgo->AddOperator()
	pO->Class = (pItemEle->GetText() == L"����Ա") ? 666 : 1;
	std::wstring wszStr = editName->GetText();
	memcpy_s(pO->OperatorName, NAME_LEN, wszStr.c_str(), wszStr.length() * 2);
	wszStr = editGender->GetText();
	memcpy_s(pO->OperatorGender, GENDER_LEN, wszStr.c_str(), wszStr.length() * 2);
	//�������MD5
	wszStr = editPwd->GetText();
	MD5 * md5 = new MD5(ws2s(wszStr));
	wszStr = s2ws(md5->md5());
	memcpy_s(pO->password, PWD_LEN, wszStr.c_str(), wszStr.length() * 2);
	//�������ݿ�
	bool isSucceed = false;
	if (dbgo->AddOperator(pO) == false)
	{
		::MessageBox(m_hWnd, L"�޸�ʧ��\nûInsert�ɹ�...", L"��ʾ", MB_OK);
		isSucceed = false;
	}
	else
		isSucceed = true;

	delete dbgo;
	dbgo = NULL;
	delete md5;
	md5 = NULL;
	delete pO;
	pO = NULL;

	return isSucceed;
}

LPCTSTR CPlanMgrFrameWnd::GetWindowClassName() const { return _T("DUILoginFrame"); }

CDuiString CPlanMgrFrameWnd::GetSkinFile() { return _T(DUI_XML_SUB_PLANMGR); }

CDuiString CPlanMgrFrameWnd::GetSkinFolder() { return _T(""); }

void CPlanMgrFrameWnd::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		//�رհ�ť
		if (msg.pSender->GetName() == _T("closebtn"))
		{
			//��ջ����ȡ�����ھ������ջ
			HWND m_hwnd = stackHwnd.top();
			stackHwnd.pop();

			::EnableWindow(m_hwnd, TRUE);												// �����ڻ�ԭ m_hwndΪ�Ӵ��ھ��
			::SetFocus(m_hwnd);																	//���ý��㵽������
			::PostMessage(m_hwnd, WM_CMS_BACKTOPARENT, 0, 0);		//�򸸴��ڷ�����Ϣ

			Close();
		}
		//����ײ�
		else if (msg.pSender->GetName() == _T("btnAdd"))
		{
			if (OnNewPlan() == true)
				::MessageBox(m_hWnd, L"��ӳɹ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			else
				::MessageBox(m_hWnd, L"���ʧ�ܡ��Ƿ���δ���", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		}
		//����
		else if (msg.pSender->GetName() == _T("btnReset"))
		{
			//��ȡ���
			CEditUI* editName = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editName"));
			CEditUI* editRemote = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editRemote"));
			CEditUI* editLocal = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editLocal"));
			CEditUI* editRoaming = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editRoaming"));
			//��ָ����
			if (editName == NULL ||
				editRemote == NULL ||
				editLocal == NULL ||
				editRoaming == NULL)
			{
				::MessageBox(m_hWnd, L"handles Null Pointer Exceptions...", L"Error", MB_OK | MB_ICONERROR);

				return ;
			}
			else
			{
				editName->SetText(L"");
				editRemote->SetText(L"");
				editLocal->SetText(L"");
				editRoaming->SetText(L"");
			}
		}
		//��ѯ
		else if (msg.pSender->GetName() == _T("btnQuery"))
		{
			if (OnQueryPlan() == false)
				::MessageBox(m_hWnd, L"��ѯʧ�ܡ�\n�Ƿ�δ��������ݣ�\n�����������ѯ��ʽ�Ƿ�ƥ�䣿",
					L"��ʾ", MB_OK | MB_ICONINFORMATION);
		}
		//�޸�
		else if (msg.pSender->GetName() == _T("btnModify"))
		{
			if (cdh == NULL)
				::MessageBox(m_hWnd, L"����ִ�в�ѯ...", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			else
			{
				//��ȡѡ��Ԫ�صľ��
				struct CMS_DB_NODE * cdn = NULL;
				if (CDNCallPlanWalker(cdn) == false)
					return;

				//��ʾ��ɫ����
				ctrlGrayPlanMgr = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayPlanMgr"));
				ctrlGrayPlanMgr->SetVisible(true);
				ctrlGrayPlanMgrQMD = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayPlanMgrQMD"));
				ctrlGrayPlanMgrQMD->SetVisible(true);

				//��ȡ��ǰ���ھ��
				HWND m_hwnd = GetHWND();
				//����ǰ���ھ������ջ
				stackHwnd.push(m_hwnd);
				//�����޸��շ�Ա�Ӵ����߳�
				_beginthread(ModifyPlanThread, 0, cdn);
			}
		}
		//ɾ��
		else if (msg.pSender->GetName() == _T("btnDelete"))
		{
			if (cdh == NULL)
				::MessageBox(m_hWnd, L"����ִ�в�ѯ...", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			else
			{
				if (OnDeletePlan() == true)
					::MessageBox(m_hWnd, L"ɾ���ɹ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			}
			return;
		}
	}
	else if (msg.sType == _T("selectchanged"))
	{
		//��xml�е�opt��Ӧ ������ѡopt �л�switch����
		CDuiString name = msg.pSender->GetName();
		CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("switch")));
		if (name == _T("optNew"))
		{ 
			pControl->SelectItem(0);  
		}
		else if (name == _T("optQMD"))
		{
			pControl->SelectItem(1);
		}
	}
}

CPlanMgrFrameWnd::~CPlanMgrFrameWnd()
{
	if (cdh != NULL)
		DeleteCDH(cdh);
}

void CPlanMgrFrameWnd::Init()
{
	cdh = NULL;
	return;
}

LRESULT CPlanMgrFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool & bHandled)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			return true;
		}
		else if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			return true;
		}
	default:
		return false;
	}
}

LRESULT CPlanMgrFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;	//��־����Ϣ�Ƿ񱻴���
	switch (uMsg)
	{
	case WM_NCLBUTTONDBLCLK: return 0;//����˫��������������󻯣����ηǿͻ������˫���¼�
	case WM_CMS_BACKTOPARENT:
		ctrlGrayPlanMgr = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayPlanMgr"));
		ctrlGrayPlanMgr->SetVisible(false);
		ctrlGrayPlanMgrQMD = static_cast<CControlUI*>(m_PaintManager.FindControl(L"ctrlGrayPlanMgrQMD"));
		ctrlGrayPlanMgrQMD->SetVisible(false);
		break;
	default: bHandled = FALSE;
	}
	//����Ѵ�����Ϣ ��ֱ�ӷ���
	if (bHandled) return lRes;
	//�����ǰ��MessageHandler��������Ϣ ��ֱ�ӷ���
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	//����Ļ���WIB����...
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CPlanMgrFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_PaintManager.Init(m_hWnd);
	CDialogBuilder builder;
	CPlanMgrBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T(DUI_XML_SUB_PLANMGR), (UINT)0, &cb, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);


	//m_WndShadow.Create(m_hWnd);
	//m_WndShadow.SetSize(3);
	//m_WndShadow.SetPosition(0, 0);

	Init();
	return 0;
}

bool CPlanMgrFrameWnd::OnNewPlan()
{
	//��ȡ���
	CEditUI* editName = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editName"));
	CEditUI* editRemote = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editRemote"));
	CEditUI* editLocal = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editLocal"));
	CEditUI* editRoaming = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editRoaming"));
	//��ָ����
	if (editName == NULL ||
		editRemote == NULL ||
		editLocal == NULL ||
		editRoaming == NULL)
	{
		::MessageBox(m_hWnd, L"handles Null Pointer Exceptions...", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//��ȡ����
	std::wstring wszStr = editName->GetText();
	double dRemote = 0.0;
	double dLocal = 0.0;
	double dRoaming = 0.0;
	swscanf_s(editRemote->GetText(), L"%lf", &dRemote);
	swscanf_s(editLocal->GetText(), L"%lf", &dLocal);
	swscanf_s(editRoaming->GetText(), L"%lf", &dRoaming);
	if (dRemote == 0.0 ||
		dLocal == 0.0 ||
		dRoaming == 0.0)
	{
		::MessageBox(m_hWnd, L"���ʺ���̫���...", L"��ʾ", MB_OK | MB_ICONERROR);
		return false;
	}
	//��ṹ��
	struct CallPlan *pCp = new struct CallPlan;
	if (pCp == NULL)
	{
		::MessageBox(m_hWnd, L"pCp Null Pointer Exceptions...", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	memset(pCp, 0, sizeof(struct CallPlan));
	pCp->LocalFee = dLocal;
	pCp->RemoteFee = dRemote;
	pCp->RoamingFee = dRoaming;
	memcpy_s(pCp->PlanName, PLANNAME_LEN, wszStr.c_str(), wszStr.length() * 2);
	//�����ݿ�
	DBgo * dbgo = new DBgo();
	if (dbgo == NULL)
	{
		::MessageBox(m_hWnd, L"dbgo Null Pointer Exceptions...", L"Error", MB_OK | MB_ICONERROR);
		delete pCp;
		pCp = NULL;
		return false;
	}
	pCp->PlanNo = dbgo->GetMaxNo(L"PlanNo", L"CallPlan") + 1;
	if (pCp->PlanNo == -1)
	{
		::MessageBox(m_hWnd, L"dbgo->GetMaxNo Error...", L"Error", MB_OK | MB_ICONERROR);
		delete pCp;
		pCp = NULL;
		delete dbgo;
		dbgo = NULL;
		return false;
	}
	//�������ݿ�
	if (dbgo->AddPlan(pCp) == false)
	{
		::MessageBox(m_hWnd, L"dbgo->AddPlan Error...", L"Error", MB_OK | MB_ICONERROR);
		delete pCp;
		pCp = NULL;
		delete dbgo;
		dbgo = NULL;
		return false;
	}

	delete dbgo;
	dbgo = NULL;
	delete pCp;
	pCp = NULL;
	return true;
}

bool CPlanMgrFrameWnd::OnQueryPlan()
{
	//��ȡ���
	CEditUI * editContent = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editContent"));
	CComboUI * pCombox = static_cast<CComboUI*>(m_PaintManager.FindControl(L"comboMethod"));
	if (editContent == NULL ||
		pCombox == NULL)
	{
		::MessageBox(m_hWnd, L"handle(s) Null Pointer Exception...", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	int nsel = pCombox->GetCurSel();
	if (nsel < 0)
	{
		::MessageBox(m_hWnd, L"��ѡ��һ����ѯ��ʽ...", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		return false;
	}
	CListLabelElementUI* pItemEle = (CListLabelElementUI*)pCombox->GetItemAt(nsel);
	//��ȡ����
	std::wstring wszStr = editContent->GetText();
	if (wszStr.length() == 0)
	{
		::MessageBox(m_hWnd, L"���ܵ������ɶ���ܲ��...", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		return false;
	}
	int Query_Method = (pItemEle->GetText() == L"�ײͺţ���ȷ��ѯ��") ? QP_BY_PLANNO : QP_BY_PLANNAME;
	//��cdh�����ڴ�
	if (cdh == NULL)
	{
		cdh = new struct CMS_DB_HEADER;
		if (cdh == NULL)
		{
			::MessageBox(m_hWnd, L"cdh Null Pointer Exception...", L"Error", MB_OK | MB_ICONERROR);

			return false;
		}
		InitCDH(cdh);
	}
	//�����ݿ�
	DBgo * dbgo = new DBgo();
	if (dbgo == NULL)
	{
		::MessageBox(m_hWnd, L"dbgo Null Pointer Exception...", L"Error", MB_OK | MB_ICONERROR);

		return false;
	}
	if (dbgo->QueryPlan((wchar_t*)wszStr.c_str(), Query_Method, cdh) == false)
	{
		::MessageBox(m_hWnd, L"SQL����", L"��ʾ", MB_OK | MB_ICONERROR);
		delete dbgo;
		dbgo = NULL;
		return false;
	}
	else if (cdh->n == 0)
	{
		::MessageBox(m_hWnd, L"û����...�����ʶ����ԣ�", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		delete dbgo;
		dbgo = NULL;
		return false;
	}
	//��ȡ���
	CListUI * listPlan = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listPlan")));

	struct CMS_DB_NODE * cdn = cdh->next;
	CString szStr;
	// ���List�б����ݣ�������Add(pListElement)����SetText
	while (cdn != NULL)
	{
		CListTextElementUI* pListElement = new CListTextElementUI;
		pListElement->SetTag(((struct CallPlan*)(cdn->content))->PlanNo);		//��PlanNo��Ϊtag
		listPlan->Add(pListElement);

		szStr.Format(L"   %d", ((struct CallPlan*)(cdn->content))->PlanNo);
		pListElement->SetText(0, szStr.GetBuffer(szStr.GetLength()));
		pListElement->SetText(1, ((struct CallPlan*)(cdn->content))->PlanName);
		szStr.Format(L"   %.2lf", ((struct CallPlan*)(cdn->content))->RemoteFee);
		pListElement->SetText(2, szStr.GetBuffer(szStr.GetLength()));
		szStr.Format(L"   %.2lf", ((struct CallPlan*)(cdn->content))->LocalFee);
		pListElement->SetText(3, szStr.GetBuffer(szStr.GetLength()));
		szStr.Format(L"   %.2lf", ((struct CallPlan*)(cdn->content))->RoamingFee);
		pListElement->SetText(4, szStr.GetBuffer(szStr.GetLength()));
		
		cdn = cdn->next;
	}
	delete dbgo;
	dbgo = NULL;
	return true;
}

LPCTSTR CModifyPlanFrameWnd::GetWindowClassName() const { return _T("DUILoginFrame"); }

CDuiString CModifyPlanFrameWnd::GetSkinFile() { return _T(DUI_XML_SUB_MODIFYPLAN); }

CDuiString CModifyPlanFrameWnd::GetSkinFolder() { return _T(""); }

void CModifyPlanFrameWnd::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		//�رհ�ť
		if (msg.pSender->GetName() == _T("closebtn"))
		{
			//��ջ����ȡ�����ھ������ջ
			HWND m_hwnd = stackHwnd.top();
			stackHwnd.pop();

			::EnableWindow(m_hwnd, TRUE);												// �����ڻ�ԭ m_hwndΪ�Ӵ��ھ��
			::SetFocus(m_hwnd);																	//���ý��㵽������
			::PostMessage(m_hwnd, WM_CMS_BACKTOPARENT, 0, 0);		//�򸸴��ڷ�����Ϣ
																	//PostQuitMessage(0); 
			Close();
		}
		//�޸İ�ť
		else if (msg.pSender->GetName() == L"btnModify")
		{
			if (OnModify() == true)
				::MessageBox(m_hWnd, L"�޸ĳɹ�~", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		}
		//���ð�ť
		else if (msg.pSender->GetName() == L"btnReset")
		{
			editName = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editName"));
			editRemote = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editRemote"));
			editLocal = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editLocal"));
			editRoaming = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editRoaming"));

			if (editName == NULL ||
				editLocal == NULL ||
				editRoaming == NULL ||
				editRemote == NULL)
			{
				::MessageBox(m_hWnd, L"��ָ���쳣��", L"��ʾ", MB_OK | MB_ICONINFORMATION);
				return;
			}
			editName->SetText(L"");
			editLocal->SetText(L"");
			editRemote->SetText(L"");
			editRoaming->SetText(L"");
		}
	}
}

CModifyPlanFrameWnd::CModifyPlanFrameWnd(CMS_DB_NODE * cdn)
{
	if (cdn != NULL)
		pPlan = (struct CallPlan*)(cdn->content);
	else
		pPlan = NULL;
}

void CModifyPlanFrameWnd::Init()
{
	//Ϊ���ؼ���ֵ
	CLabelUI * labelPlanNo = static_cast<CLabelUI*>(m_PaintManager.FindControl(L"labelPlanNo"));
	CString wszStr;
	wszStr.Format(L"%d", pPlan->PlanNo);

	if (labelPlanNo != NULL)
		labelPlanNo->SetText(wszStr.GetBuffer(wszStr.GetLength()));
	CEditUI * edits = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editName"));
	if (edits != NULL)
		edits->SetText(pPlan->PlanName);
	edits = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editRemote"));
	if (edits != NULL)
	{
		wszStr.Format(L"%.2lf", pPlan->RemoteFee);
		edits->SetText(wszStr.GetBuffer(wszStr.GetLength()));
	}
	edits = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editRoaming"));
	if (edits != NULL)
	{
		wszStr.Format(L"%.2lf", pPlan->RoamingFee);
		edits->SetText(wszStr.GetBuffer(wszStr.GetLength()));
	}
	edits = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editLocal"));
	if (edits != NULL)
	{
		wszStr.Format(L"%.2lf", pPlan->LocalFee);
		edits->SetText(wszStr.GetBuffer(wszStr.GetLength()));
	}
	return;
}

LRESULT CModifyPlanFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool & bHandled)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			return true;
		}
		else if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			return true;
		}
	default:
		return false;
	}
}

LRESULT CModifyPlanFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;	//��־����Ϣ�Ƿ񱻴���
	switch (uMsg)
	{
	case WM_NCLBUTTONDBLCLK: return 0;//����˫��������������󻯣����ηǿͻ������˫���¼�
	default: bHandled = FALSE;
	}
	//����Ѵ�����Ϣ ��ֱ�ӷ���
	if (bHandled) return lRes;
	//�����ǰ��MessageHandler��������Ϣ ��ֱ�ӷ���
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	//����Ļ���WIB����...
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CModifyPlanFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_PaintManager.Init(m_hWnd);
	CDialogBuilder builder;
	//CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T(DUI_XML_SUB_MODIFYPLAN), (UINT)0, NULL, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");
	m_PaintManager.AttachDialog(pRoot);
	m_PaintManager.AddNotifier(this);


	//m_WndShadow.Create(m_hWnd);
	//m_WndShadow.SetSize(3);
	//m_WndShadow.SetPosition(0, 0);

	Init();
	return 0;
}

bool CModifyPlanFrameWnd::OnModify()
{
	//��ȡ���
	CEditUI * editName = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editName"));
	CEditUI * editRemote = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editRemote"));
	CEditUI * editLocal = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editLocal"));
	CEditUI * editRoaming = static_cast<CEditUI*>(m_PaintManager.FindControl(L"editRoaming"));
	if (editName == NULL ||
		editRemote == NULL ||
		editLocal == NULL ||
		editRoaming == NULL)
	{
		::MessageBox(m_hWnd, L"handle(s) Null Pointer Exception...", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//����
	DBgo * dbgo = new DBgo();
	if (dbgo == NULL)
	{
		::MessageBox(m_hWnd, L"dbgo Null Pointer Exception...", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}
	//��ɾ
	if (dbgo->DropPlan(pPlan->PlanNo) == false)
	{
		::MessageBox(m_hWnd, L"SQL Error...", L"Error", MB_OK | MB_ICONERROR);
		delete dbgo;
		dbgo = NULL;
		return false;
	}
	//��ȡ����
	std::wstring wszStr = editName->GetText();
	double dRemote = 0.0;
	double dLocal = 0.0;
	double dRoaming = 0.0;
	swscanf_s(editRemote->GetText(), L"%lf", &dRemote);
	swscanf_s(editLocal->GetText(), L"%lf", &dLocal);
	swscanf_s(editRoaming->GetText(), L"%lf", &dRoaming);
	if (dRemote == 0.0 ||
		dLocal == 0.0 ||
		dRoaming == 0.0)
	{
		::MessageBox(m_hWnd, L"���ʺ���̫���...", L"��ʾ", MB_OK | MB_ICONERROR);
		delete dbgo;
		dbgo = NULL;
		return false;
	}
	//�����ṹ��
	struct CallPlan * pCp = new struct CallPlan;
	if (pCp == NULL)
	{
		::MessageBox(m_hWnd, L"pCp Null Pointer Exception...", L"Error", MB_OK | MB_ICONERROR);
		delete dbgo;
		dbgo = NULL;
		return false;
	}
	memset(pCp, 0, sizeof(struct CallPlan));
	//��д�ṹ��
	pCp->PlanNo = pPlan->PlanNo;
	pCp->LocalFee = dLocal;
	pCp->RemoteFee = dRemote;
	pCp->RoamingFee = dRoaming;
	memcpy_s(pCp->PlanName, PLANNAME_LEN, wszStr.c_str(), wszStr.length() * 2);
	//�ٲ������ݿ�
	if (dbgo->AddPlan(pCp) == false)
	{
		::MessageBox(m_hWnd, L"dbgo->AddPlan Error...", L"Error", MB_OK | MB_ICONERROR);
		delete pCp;
		pCp = NULL;
		delete dbgo;
		dbgo = NULL;
		return false;
	}

	delete dbgo;
	dbgo = NULL;
	delete pCp;
	pCp = NULL;
	return true;
}


// ɾ��ѡ���ײ�
bool CPlanMgrFrameWnd::OnDeletePlan()
{
	struct CMS_DB_NODE * cdn = NULL;
	if (CDNCallPlanWalker(cdn) == false)
		return false;
	
	//��ȡһ�¹���
	int PlanNoToDel = ((struct CallPlan*)(cdn->content))->PlanNo;
	//������ɾ��
	DBgo * dbgo = new DBgo;
	if (dbgo == NULL)
	{
		::MessageBox(m_hWnd, L"dbgo Null Pointer��", L"��ʾ", MB_OK | MB_ICONERROR);
		return false;
	}
	bool isSucceed = false;
	if (dbgo->DropPlan(PlanNoToDel) == true)
		isSucceed = true;
	else
	{
		::MessageBox(m_hWnd, L"ɾ��ʧ��\n���ݿ����", L"��ʾ", MB_OK | MB_ICONERROR);
		isSucceed = false;
	}

	delete dbgo;
	dbgo = NULL;
	
	return isSucceed;
}


// ��ȡѡ��Ԫ���������е�ָ��
bool CPlanMgrFrameWnd::CDNCallPlanWalker(struct CMS_DB_NODE * &cdn)
{
	if (cdh == NULL)
	{
		::MessageBox(m_hWnd, L"����ִ�в�ѯ...", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		return false;
	}
	else
	{
		//��ȡѡ��Ԫ�صľ��
		CListUI * listPlan = static_cast<CListUI*>(m_PaintManager.FindControl(_T("listPlan")));
		if (listPlan == NULL)
		{
			::MessageBox(m_hWnd, L"listPlan Null Pointer Exception", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}
		CListTextElementUI * pListElement = new CListTextElementUI;
		int nIndex = listPlan->GetCurSel();
		if (nIndex < 0)
		{
			::MessageBox(m_hWnd, L"��ѡ����Ҫ�޸ĵ���Ϣ...", L"��ʾ", MB_OK | MB_ICONINFORMATION);
			return false;
		}
		pListElement = (CListTextElementUI*)listPlan->GetItemAt(nIndex);
		//��ȡѡ��Ԫ�ص��ײͺ�
		int SelectedNo = 0;
		swscanf_s(pListElement->GetText(0), L"%d", &SelectedNo);

		//�ҵ���Ԫ�ض�Ӧ��������
		cdn = cdh->next;
		struct CallPlan * pCp = NULL;
		while (cdn != NULL)
		{
			pCp = (struct CallPlan*)cdn->content;
			if (pCp->PlanNo == SelectedNo)
				break;
			cdn = cdn->next;
		}
		if (cdn == NULL)
		{
			::MessageBox(m_hWnd, L"�������", L"��ʾ", MB_OK | MB_ICONERROR);
			return false;
		}
	}
	return true;
}

LPCTSTR CIOuserFrameWnd::GetWindowClassName() const { return _T("DUILoginFrame"); }

CDuiString CIOuserFrameWnd::GetSkinFile() { return _T(DUI_XML_SUB_IOUSER); }

CDuiString CIOuserFrameWnd::GetSkinFolder() { return _T(""); }

void CIOuserFrameWnd::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		//�رհ�ť
		if (msg.pSender->GetName() == _T("closebtn"))
		{
			//��ջ����ȡ�����ھ������ջ
			HWND m_hwnd = stackHwnd.top();
			stackHwnd.pop();

			::EnableWindow(m_hwnd, TRUE);												// �����ڻ�ԭ m_hwndΪ�Ӵ��ھ��
			::SetFocus(m_hwnd);																	//���ý��㵽������
			::PostMessage(m_hwnd, WM_CMS_BACKTOPARENT, 0, 0);		//�򸸴��ڷ�����Ϣ
																	//PostQuitMessage(0); 
			Close();
		}
		//���밴ť
		else if (msg.pSender->GetName() == L"btnIn")
		{
			if (::MessageBox(m_hWnd, L"����������Ḳ���������ݣ�ȷ����", L"ȷ�ϲ���", MB_OKCANCEL | MB_DEFBUTTON2 | MB_ICONQUESTION)
				== IDOK)
			{
				if (OnIn() == true)
					::MessageBox(m_hWnd, L"����ɹ�~", L"��ʾ", MB_OK | MB_ICONINFORMATION);
				else
					::MessageBox(m_hWnd, L"����ʧ��...", L"��ʾ", MB_OK | MB_ICONINFORMATION);

			}
			else
				::MessageBox(m_hWnd, L"�û�ȡ���˲���", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		}
		//������ť
		else if (msg.pSender->GetName() == L"btnOut")
		{
			if (OnOut() == false)
				::MessageBox(m_hWnd, L"����ʧ��...", L"��ʾ", MB_OK | MB_ICONINFORMATION);

		}
	}
}

LRESULT CIOuserFrameWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool & bHandled)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			return true;
		}
		else if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			return true;
		}
	default:
		return false;
	}
}

LRESULT CIOuserFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;	//��־����Ϣ�Ƿ񱻴���
	switch (uMsg)
	{
	case WM_NCLBUTTONDBLCLK: return 0;//����˫��������������󻯣����ηǿͻ������˫���¼�
	default: bHandled = FALSE;
	}
	//����Ѵ�����Ϣ ��ֱ�ӷ���
	if (bHandled) return lRes;
	//�����ǰ��MessageHandler��������Ϣ ��ֱ�ӷ���
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	//����Ļ���WIB����...
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}


// �����û�����
bool CIOuserFrameWnd::OnOut()
{
	//�ȴ����ݿ�������
	struct CMS_DB_HEADER * cdh = new struct CMS_DB_HEADER;
	DBgo * dbgo = new DBgo;
	if (cdh == NULL || dbgo == NULL)
		return false;
	InitCDH(cdh);
	
	if (dbgo->QueryUserInfo(L"%", QUI_BY_USERNAME | QUI_WAY_APPROXIMATE, cdh) == false)
	{
		delete dbgo;
		delete cdh;
		dbgo = NULL;
		cdh = NULL;
		return false;
	}
	bool isSucceed = false;
	if (cdh->n == 0)
	{
		::MessageBox(m_hWnd, L"�����û�����", L"��ʾ", MB_OK | MB_ICONINFORMATION);
		isSucceed = true;
		delete dbgo;
		delete cdh;
		dbgo = NULL;
		cdh = NULL;
	}
	//д��xls�ļ�
	else
	{
		Book* book = xlCreateBook();
		if (book)
		{
			Sheet* sheet = book->addSheet(L"Sheet1");
			if (sheet)
			{
				//�����ͷ
				sheet->writeStr(0, 0, L"�û�����");
				sheet->writeStr(0, 1, L"�û����");
				sheet->writeStr(0, 2, L"�ײͺ�");
				sheet->writeStr(0, 3, L"״̬");
				sheet->writeStr(0, 4, L"����");
				sheet->writeStr(0, 5, L"�Ա�");
				sheet->writeStr(0, 6, L"��ַ");

				//ѭ�������������
				struct CMS_DB_NODE * cdn = cdh->next;
				struct UserInfo * ui = NULL;
				int i = 1;
				while (cdn != NULL)
				{
					ui = (struct UserInfo *)cdn->content;

					sheet->writeStr(i, 0, ui->MSISDN);
					sheet->writeNum(i, 1, ui->balance);
					sheet->writeNum(i, 2, ui->PlanNo);
					sheet->writeStr(i, 3, ui->status);
					sheet->writeStr(i, 4, ui->name);
					sheet->writeStr(i, 5, ui->gender);
					sheet->writeStr(i++, 6, ui->address);

					cdn = cdn->next;
				}

				sheet->setCol(1, 1, 12);
			}
			//����ǰʱ����Ϊ�ļ�����һ����
			//SYSTEMTIME st;
			//GetLocalTime(&st);

			CString wszFileName = L"D:/�û�����.xls";
			//wszFileName.Format(L"�û����� %4d-%2d-%2d %2d:%2d:%2d.xls",
			//	 st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
			//wszFileName += ".xls";
			if (book->save(wszFileName.GetBuffer(wszFileName.GetLength())))
			{
				::ShellExecute(NULL, L"open", wszFileName.GetBuffer(wszFileName.GetLength()), NULL, NULL, SW_SHOW);
				isSucceed = true;
			}
			else
			{
				//std::cout << book->errorMessage() << std::endl;
				::MessageBox(m_hWnd, s2ws(book->errorMessage()).c_str(), L"XLS FAILED", MB_OK | MB_ICONERROR);
				isSucceed = false;
			}

			book->release();
		}
		else
			isSucceed = false;
	}
	delete dbgo;
	delete cdh;
	dbgo = NULL;
	cdh = NULL;
	return isSucceed;
}


// �����û�����
bool CIOuserFrameWnd::OnIn()
{
	bool isSucceed = false;
	//��������ͷ
	struct CMS_DB_HEADER * cdh = new struct CMS_DB_HEADER;
	if (cdh == NULL)
		return false;
	InitCDH(cdh);
	//�򿪲���xls�����û�����
	Book* book = xlCreateBook();
	if (book)
	{
		if (book->load(L"D:/�û�����.xls"))
		{
			Sheet* sheet = book->getSheet(0);

			if (sheet)
			{
				//const wchar_t* s = sheet->readStr(2, 1);
				//if (s) std::wcout << s << std::endl << std::endl;

				//std::cout << sheet->readNum(4, 1) << std::endl;
				//std::cout << sheet->readNum(5, 1) << std::endl;
				//const wchar_t* f = sheet->readFormula(6, 1);
				//if (f) std::wcout << f << std::endl << std::endl;
				const wchar_t* s = sheet->readStr(1, 0);
				struct CMS_DB_NODE * cdn = NULL;
				struct UserInfo * pUI = NULL;
				int i = 1;		//��ʼ��Ϊ1��
				while (s != NULL)
				{
					//�������
					cdn = new struct CMS_DB_NODE;
					if (cdn == NULL)
						return false;
					memset(cdn, 0, sizeof(struct CMS_DB_NODE));
					pUI = (struct UserInfo*)cdn->content;
					//��д���
					wcsncpy(pUI->MSISDN, s, wcsnlen_s(s, MSISDN_LEN));		//MSISDN
					pUI->balance = sheet->readNum(i, 1);									//���
					pUI->PlanNo = (int)sheet->readNum(i, 2);							//�ײͱ��
					s = sheet->readStr(i, 3);
					if (s == NULL)
						return false;
					wcsncpy(pUI->status, s, wcsnlen_s(s, STATUS_LEN));				//״̬
					s = sheet->readStr(i, 4);
					if (s == NULL)
						return false;
					wcsncpy(pUI->name, s, wcsnlen_s(s, NAME_LEN));				//����
					s = sheet->readStr(i, 5);
					if (s == NULL)
						return false;
					wcsncpy(pUI->gender, s, wcsnlen_s(s, GENDER_LEN));				//�Ա�
					s = sheet->readStr(i++, 6);
					if (s == NULL)
						return false;
					wcsncpy(pUI->address, s, wcsnlen_s(s, ADDR_LEN));				//��ַ
					//������������
					AddToCDH(cdh, pUI, sizeof(struct UserInfo));
					//ָ����һ������
					s = sheet->readStr(i, 0);
				}
			}
		}
		else
		{
			//std::cout << "At first run generate !" << std::endl;
			::MessageBox(m_hWnd, L"ȷ�ϡ��û�����.xls�����ڣ�", L"��ʾ", MB_OK | MB_ICONQUESTION);
			DeleteCDH(cdh);
			isSucceed = false;
		}

		book->release();
	}
	else
		return false;

	if (cdh->n == 0)
	{
		DeleteCDH(cdh);
		return false;
	}
	//�������ݿ� ɾ��ԭ������
	DBgo * dbgo = new DBgo;
	if (dbgo == NULL)
	{
		DeleteCDH(cdh);
		return false;
	}
	if (dbgo->DropUserInfo(NULL, DUI_WAY_ALL) == false)
	{
		delete dbgo;
		dbgo = NULL;
		DeleteCDH(cdh);
		return false;
	}
	//���������
	struct CMS_DB_NODE * cdn = cdh->next;
	struct UserInfo * ui = NULL;
	isSucceed = true;
	while (cdn != NULL)
	{
		ui = (struct UserInfo*)cdn->content;
		if (dbgo->AddUserInfo(ui) == false)
		{
			isSucceed = false;
			break;
		}
		cdn = cdn->next;
	}

	//����
	delete dbgo;
	dbgo = NULL;
	DeleteCDH(cdh);
	return isSucceed;
}
