#ifndef _CMS_GUI_H_
#define _CMS_GUI_H_

#pragma once
#include <UIlib.h>
#include <stack>
using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif

//������ʽ��XML�ļ�λ��
#define	DUI_XML_LOGIN						"../Resource/cms-login.xml"
#define	DUI_XML_OPERATOR				"../Resource/cms-operator.xml"
#define	DUI_XML_OPERATOR_HOME	"../Resource/cms-operator-home.xml"
#define	DUI_XML_OPERATOR_CHARGE	"../Resource/cms-operator-charge.xml"
#define	DUI_XML_OPERATOR_USERMGR	"../Resource/cms-operator-usermgr.xml"
#define	DUI_XML_OPERATOR_ADMIN	"../Resource/cms-operator-admin.xml"
#define	DUI_XML_ADMIN					"../Resource/cms-admin.xml"
#define	DUI_XML_SUB_CHANGEPWD			"../Resource/cms-sub-changepwd.xml"
#define	DUI_XML_SUB_CHARGED			"../Resource/cms-sub-charged.xml"
#define	DUI_XML_SUB_NEW					"../Resource/cms-sub-new.xml"
#define	DUI_XML_SUB_DEL						"../Resource/cms-sub-del.xml"
#define	DUI_XML_SUB_QNM					"../Resource/cms-sub-qnm.xml"
#define	DUI_XML_SUB_QR						"../Resource/cms-sub-qr.xml"
#define	DUI_XML_SUB_OPERATORMGR	"../Resource/cms-sub-OperatorMgr.xml"
#define	DUI_XML_SUB_OPERATORMGR_NEW	"../Resource/cms-sub-OperatorMgr-New.xml"
#define	DUI_XML_SUB_OPERATORMGR_QMD	"../Resource/cms-sub-OperatorMgr-QMD.xml"
#define	DUI_XML_SUB_MODIFYOPERATOR		"../Resource/cms-sub-ModifyOperator.xml"
#define	DUI_XML_SUB_PLANMGR	"../Resource/cms-sub-PlanMgr.xml"
#define	DUI_XML_SUB_PLANMGR_NEW	"../Resource/cms-sub-PlanMgr-New.xml"
#define	DUI_XML_SUB_PLANMGR_QMD	"../Resource/cms-sub-PlanMgr-QMD.xml"
#define	DUI_XML_SUB_MODIFYPLAN		"../Resource/cms-sub-ModifyPlan.xml"
#define	DUI_XML_SUB_IOUSER				"../Resource/cms-sub-IOuser.xml"



//�Զ�����Ϣ
#define	WM_CMS_BACKTOPARENT	(WM_USER + 233)

//XML�ļ���<Window>��ǩ��"mininfo"���Ա�ʾ�����ػ�֮��Ĵ�С

struct ChargedInfo
{
	wchar_t MSISDN_NAME[128];
	wchar_t amount[32];
	wchar_t method[16];
	wchar_t OperatorNo[16];
};

//�̴߳���
void MainThread(void * pParam);					//�����������߳�
void ChangePwdThread(void * pParam);		//�����޸������߳�
void ChargedThread(void * pParam);				//�����ɷѳɹ��߳�
void NewThread(void * pParam);					//���������߳�
void DelThread(void * pParam);						//���������߳�
void QnMThread(void * pParam);					//������ѯ/�޸��߳�
void QRThread(void * pParam);						//������ѯ�ɷѼ�¼�߳�
void OperatorMgrThread(void * pParam);		//�����շ�Ա�����߳�
void ModifyOperatorThread(void * pParam);	//�����޸��շ�Ա�߳�
void PlanMgrThread(void * pParam);				//�����շ�Ա�����߳�
void ModifyPlanThread(void * pParam);			//�����޸��շ�Ա�߳�
void IOuserThread(void * pParam);					//�������뵼���û������߳�


static int OperatorNo;			//��ǰ����Ա/����Ա����
static int OperatorClass;		//��ǰ����Ա/����Ա�ȼ�
stack<HWND> stackHwnd;

class CLoginFrameWnd : public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void	Notify(TNotifyUI& msg);
	//��������ϵͳ��Ϣ
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	//����ϵͳ��Ϣ
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	static bool OnLogin(LPCWSTR OperatorNo, LPCWSTR Password);

private:
	CEditUI* pNoEdit;
	CEditUI* pPwdEdit;
	CButtonUI* btnMin;
	CButtonUI* btnClose;
};

class CMainFrameWnd : public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void	Notify(TNotifyUI& msg);
	void Init();
	//��������ϵͳ��Ϣ
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	//����ϵͳ��Ϣ
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	//�л�������ҳ����ǩҳ
	bool OnSwitchHome();
	//�л������û��ɷѡ���ǩҳ
	bool OnSwitchCharge();
	//�л������û�������ǩҳ
	bool OnSwitchUserMgr();
	//�л������ۺϹ�����ǩҳ
	bool OnSwitchAdmin();

	bool OnUserCharge(struct ChargedInfo * ci);
	void OnQueryChargeMSISDN(LPCWSTR MSISDN);
	void OnPrepare();
private:
	CButtonUI* btnMin;
	CButtonUI* btnClose;
	CEditUI* editMSISDN;
	CEditUI* editCharge;
	CContainerUI* containerCharge;
	COptionUI* optHome;
	CWndShadow m_WndShadow;
	CControlUI* ctrlGray;
	CControlUI* ctrlGrayHome;
	CControlUI* ctrlGrayCharge;
	CControlUI* ctrlGrayUserMgr;
	CControlUI* ctrlGrayAdmin;
};

class OperatorHomeUI : public CContainerUI
{
public:
	OperatorHomeUI()
	{
		CDialogBuilder builder;
		CContainerUI* pOperatorHome = static_cast<CContainerUI*>(builder.Create(_T(DUI_XML_OPERATOR_HOME), (UINT)0));
		if (pOperatorHome) 
		{
			this->Add(pOperatorHome);
		}
		else {
			this->RemoveAll();
			return;
		}
	}
};

class OperatorChargeUI : public CContainerUI
{
public:
	OperatorChargeUI()
	{
		CDialogBuilder builder;
		CContainerUI* pOperatorCharge = static_cast<CContainerUI*>(builder.Create(_T(DUI_XML_OPERATOR_CHARGE), (UINT)0));
		if (pOperatorCharge)
		{
			this->Add(pOperatorCharge);
		}
		else {
			this->RemoveAll();
			return;
		}
	}
};

class OperatorUserMgrUI : public CContainerUI
{
public:
	OperatorUserMgrUI()
	{
		CDialogBuilder builder;
		CContainerUI* pOperatorUserMgr = static_cast<CContainerUI*>(builder.Create(_T(DUI_XML_OPERATOR_USERMGR), (UINT)0));
		if (pOperatorUserMgr)
		{
			this->Add(pOperatorUserMgr);
		}
		else {
			this->RemoveAll();
			return;
		}
	}
};

class OperatorAdminUI : public CContainerUI
{
public:
	OperatorAdminUI()
	{
		CDialogBuilder builder;
		CContainerUI* pOperatorAdmin = static_cast<CContainerUI*>(builder.Create(_T(DUI_XML_OPERATOR_ADMIN), (UINT)0));
		if (pOperatorAdmin)
		{
			this->Add(pOperatorAdmin);
		}
		else {
			this->RemoveAll();
			return;
		}
	}
};
//�����Զ���ؼ� Ƕ��XML
class CDialogBuilderCallbackEx : public IDialogBuilderCallback
{
public:
	CControlUI* CreateControl(LPCTSTR pstrClass)
	{
		//��XML�е�switchռλ��ǩ����Ӧ
		if (_tcscmp(pstrClass, _T("OperatorHome")) == 0) return new OperatorHomeUI;
		if (_tcscmp(pstrClass, _T("OperatorCharge")) == 0) return new OperatorChargeUI;
		if (_tcscmp(pstrClass, _T("OperatorUserMgr")) == 0) return new OperatorUserMgrUI;
		if (_tcscmp(pstrClass, _T("OperatorAdmin")) == 0) return new OperatorAdminUI;


		return NULL;
	}
};

//�����Ӵ�����
//�޸����봰����
class CSubChangePwdFrameWnd : public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void	Notify(TNotifyUI& msg);
	//��������ϵͳ��Ϣ
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	//����ϵͳ��Ϣ
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//������������Ϣ
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	//�����޸���������
	bool OnChangePwd();

private:
	CEditUI* pRawPwdEdit;
	CEditUI* pNewPwdEdit;
	CEditUI* pNewPwd2Edit;
	CButtonUI* btnClose;
	CButtonUI* btnChange;
	CButtonUI* btnReset;
	CWndShadow m_WndShadow;
};

//�ɷѳɹ�������
class CSubChargedFrameWnd : public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void	Notify(TNotifyUI& msg);

	//��ʼ����
	CSubChargedFrameWnd(struct ChargedInfo * ci);
	//��ʼ������
	void Init();
	//��������ϵͳ��Ϣ
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	//����ϵͳ��Ϣ
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//������������Ϣ
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//�����ӡ��Ʊ����
	bool OnCreateReceipt();

private:
	CLabelUI* labelMSISDN_NAME;
	CLabelUI* labelAmount;
	CButtonUI* btnClose;
	CButtonUI* btnPrint;

	struct ChargedInfo * pci;

};

//������
class CSubNewFrameWnd : public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void	Notify(TNotifyUI& msg);

	//��ʼ������
	void Init();
	//��������ϵͳ��Ϣ
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	//����ϵͳ��Ϣ
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//������������Ϣ
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//����������
	bool OnNewUser();
};

//������
class CSubDelFrameWnd : public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void	Notify(TNotifyUI& msg);

	//��ʼ������
	void Init();
	//��������ϵͳ��Ϣ
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	//����ϵͳ��Ϣ
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//������������Ϣ
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//�����ѯ�û���Ϣ����
	bool OnQueryUserInfo(LPCWSTR MSISDN);
	//������������
	bool OnDelUser(LPCWSTR MSISDN);
};

//�޸�/��ѯ��
class CSubQnMFrameWnd : public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void	Notify(TNotifyUI& msg);

	//��ʼ������
	void Init();
	//��������ϵͳ��Ϣ
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	//����ϵͳ��Ϣ
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//������������Ϣ
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//�����ѯ�û���Ϣ����
	bool OnQueryUserInfo(LPCWSTR MSISDN);
	//�����޸�����
	bool OnModifyUserInfo(LPCWSTR MSISDN);
private:
	bool isQueried;
};

//��ѯ�ɷѼ�¼��
class CSubQRFrameWnd : public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void	Notify(TNotifyUI& msg);

	//��ʼ������
	void Init();
	//��������ϵͳ��Ϣ
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	//����ϵͳ��Ϣ
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//������������Ϣ
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//�����ѯ�û���Ϣ����
	bool OnQueryRecords(LPCWSTR MSISDN);
	//����������
	bool OnOut(LPCWSTR MSISDN);
private:
	bool isQueried;
	struct CMS_DB_HEADER * cdh;
};

class CSubOperatorMgrFrameWnd :public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void	Notify(TNotifyUI& msg);

	~CSubOperatorMgrFrameWnd();
	//��ʼ������
	void Init();
	//��������ϵͳ��Ϣ
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	//����ϵͳ��Ϣ
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//������������Ϣ
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	//��ǩҳ�л�
	bool OnSwitchNew();
	bool OnSwitchQMD();
	// ��Ӧ����������ǩҳ�еġ����ӡ���ť�¼�
	bool OnNewOperator();
	//��Ӧ����ɾ�ġ���ǩҳ�еġ���ѯ����ť�¼�
	bool OnQueryOperator();
private:
	struct CMS_DB_HEADER * cdh;
	CControlUI* ctrlGrayOpMgrQMD;
	CControlUI* ctrlGrayOpMgr;

};

//�շ�Ա���� ���½�����ǩҳ
class OperatorMgrNewUI : public CContainerUI
{
public:
	OperatorMgrNewUI()
	{
		CDialogBuilder builder;
		CContainerUI* pOperatorMgrNew =
			static_cast<CContainerUI*>(builder.Create(_T(DUI_XML_SUB_OPERATORMGR_NEW), (UINT)0));
		if (pOperatorMgrNew)
		{
			this->Add(pOperatorMgrNew);
		}
		else {
			this->RemoveAll();
			return;
		}
	}
};

//�շ�Ա���� �����ɾ����ǩҳ
class OperatorMgrQMDUI : public CContainerUI
{
public:
	OperatorMgrQMDUI()
	{
		CDialogBuilder builder;
		CContainerUI* pOperatorMgrQMD =
			static_cast<CContainerUI*>(builder.Create(_T(DUI_XML_SUB_OPERATORMGR_QMD), (UINT)0));
		if (pOperatorMgrQMD)
		{
			this->Add(pOperatorMgrQMD);
		}
		else {
			this->RemoveAll();
			return;
		}
	}
};

//�����Զ���ؼ� Ƕ��XML
class CSubOperatorMgrBuilderCallbackEx : public IDialogBuilderCallback
{
public:
	CControlUI* CreateControl(LPCTSTR pstrClass)
	{
		//��XML�е�switchռλ��ǩ����Ӧ
		if (_tcscmp(pstrClass, _T("OperatorMgrNew")) == 0) return new OperatorMgrNewUI;
		if (_tcscmp(pstrClass, _T("OperatorMgrQMD")) == 0) return new OperatorMgrQMDUI;

		return NULL;
	}
};

//�շ�Ա�����޸ġ��Ӵ���
class CModifyOperatorFrameWnd :public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void	Notify(TNotifyUI& msg);

	CModifyOperatorFrameWnd(struct CMS_DB_NODE * cdn);
	//��ʼ������
	void Init();
	//��������ϵͳ��Ϣ
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	//����ϵͳ��Ϣ
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//������������Ϣ
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
	struct Operator* pOperator;
	CEditUI * editName;
	CEditUI * editGender;
	CEditUI * editPwd;
	CListLabelElementUI* pItemEle;
public:
	// ��Ӧ���޸ġ���ť
	bool OnModify();
};

//�ײ͹���
class CPlanMgrFrameWnd :public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void	Notify(TNotifyUI& msg);

	~CPlanMgrFrameWnd();
	//��ʼ������
	void Init();
	//��������ϵͳ��Ϣ
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	//����ϵͳ��Ϣ
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//������������Ϣ
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	// ��Ӧ����������ǩҳ�еġ����ӡ���ť�¼�
	bool OnNewPlan();
	//��Ӧ����ɾ�ġ���ǩҳ�еġ���ѯ����ť�¼�
	bool OnQueryPlan();
private:
	struct CMS_DB_HEADER * cdh;
	CControlUI* ctrlGrayPlanMgrQMD;
	CControlUI* ctrlGrayPlanMgr;
public:
	// ɾ��ѡ���ײ�
	bool OnDeletePlan();
	// ��ȡѡ��Ԫ���������е�ָ��
	bool CDNCallPlanWalker(struct CMS_DB_NODE * &cdn);
};

//�ײ͹��� ���½�����ǩҳ
class PlanMgrNewUI : public CContainerUI
{
public:
	PlanMgrNewUI()
	{
		CDialogBuilder builder;
		CContainerUI* pPlanMgrNew =
			static_cast<CContainerUI*>(builder.Create(_T(DUI_XML_SUB_PLANMGR_NEW), (UINT)0));
		if (pPlanMgrNew)
		{
			this->Add(pPlanMgrNew);
		}
		else {
			this->RemoveAll();
			return;
		}
	}
};

//�ײ͹��� �����ɾ����ǩҳ
class PlanMgrQMDUI : public CContainerUI
{
public:
	PlanMgrQMDUI()
	{
		CDialogBuilder builder;
		CContainerUI* pPlanMgrQMD =
			static_cast<CContainerUI*>(builder.Create(_T(DUI_XML_SUB_PLANMGR_QMD), (UINT)0));
		if (pPlanMgrQMD)
		{
			this->Add(pPlanMgrQMD);
		}
		else {
			this->RemoveAll();
			return;
		}
	}
};

//�����Զ���ؼ� Ƕ��XML
class CPlanMgrBuilderCallbackEx : public IDialogBuilderCallback
{
public:
	CControlUI* CreateControl(LPCTSTR pstrClass)
	{
		//��XML�е�switchռλ��ǩ����Ӧ
		if (_tcscmp(pstrClass, _T("PlanMgrNew")) == 0) return new PlanMgrNewUI;
		if (_tcscmp(pstrClass, _T("PlanMgrQMD")) == 0) return new PlanMgrQMDUI;

		return NULL;
	}
};

//�ײ͹����޸ġ��Ӵ���
class CModifyPlanFrameWnd :public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void	Notify(TNotifyUI& msg);

	CModifyPlanFrameWnd(struct CMS_DB_NODE * cdn);
	//��ʼ������
	void Init();
	//��������ϵͳ��Ϣ
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	//����ϵͳ��Ϣ
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//������������Ϣ
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
private:
	struct CallPlan* pPlan;
	CEditUI * editRemote;
	CEditUI * editLocal;
	CEditUI * editRoaming;
	CEditUI * editName;
public:
	// ��Ӧ���޸ġ���ť
	bool OnModify();
};

//�ײ͹������뵼���û����ݡ��Ӵ���
class CIOuserFrameWnd :public WindowImplBase
{
public:
	virtual LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void	Notify(TNotifyUI& msg);

	//��������ϵͳ��Ϣ
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	//����ϵͳ��Ϣ
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	// �����û�����
	bool OnOut();
	// �����û�����
	bool OnIn();
};
#endif