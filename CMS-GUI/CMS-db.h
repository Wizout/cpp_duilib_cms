/*
CMS���ݿ���� ͷ�ļ�
*/
#ifndef _CMS_H_
#define _CMS_H_

//����һ��ͷ�ļ�
#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <atlbase.h>
#include <atlstr.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <odbcss.h>
#include "CMS-utils.h"

//�����ѯ���
#define		QUERY_OPERATOR_BY_NO							L"select * from Operator where OperatorNo = "
#define		QUERY_OPERATOR_BY_NAME					L"select * from Operator where OperatorName like '%"
#define		QUERY_USERINFO_BY_USERNAME				L"select * from UserInfo where Name "
#define		QUERY_USERINFO_BY_MSISDN					L"select * from UserInfo where MSISDN "
#define		QUERY_USERINFO_BY_PLANNO					L"select * from UserInfo where PlanNo "
#define		QUERY_CALLPLAN_BY_PLANNO					L"select * from CallPlan where PlanNo = "
#define		QUERY_CALLPLAN_BY_PLANNAME			L"select * from CallPlan where PlanName like '%"
#define		QUERY_CDR_BY_CALLER								L"select * from CDR where Caller = "
//select * from CDR where CallTime like '%/ 5/%'and Caller = 13800138000;
#define		QUERY_CDR_BY_MONTH_AND_CALLER		L"select * from CDR where CallTime like '%/ "
#define		QUERY_CHARGE_BY_MSISDN						L"select * from Charge where MSISDN = "
//����������
//insert into CallPlan values (5,'����������',0.2,0.03,0.2);
#define		ADD_CALLPLAN											L"insert into CallPlan values ("
#define		ADD_CHARGE												L"insert into Charge values("
#define		ADD_OPERATOR											L"insert into Operator values("
#define		ADD_USERINFO											L"insert into UserInfo values("
//����ɾ�����
#define		DROP_CALLPLAN_BY_PLANNO					L"delete from CallPlan where PlanNo = "
#define		DROP_OPERATOR_BY_OPERATORNO		L"delete from Operator where OperatorNo = "
#define		DROP_USERINFO_BY_MSISDN					L"delete from UserInfo where MSISDN = "
#define		DROP_USERINFO_ALL									L"delete from UserInfo;"
//����������
#define		UPDATE_USERINFO_ON_BALANCE				L"update UserInfo set Balance = "
#define		UPDATE_OPERATOR_ON_PASSWORD		L"update Operator set Password = "
//���屸�ݻָ����
#define		BACKUP_CMS												L"backup database CMS to disk='D:/CMS.bak' ;"
#define		RESTORE_CMS												L"restore database CMS from disk='D:/CMS.bak';"
//���������Ϣ
//#define		ERROR_DROPCALLPLAN_STILLUSED
//�����ַ������鳤��
#define		GENDER_LEN		4
#define		STATUS_LEN		16
#define		NAME_LEN			16
#define		TYPE_LEN				16
#define		MSISDN_LEN		64
#define		PLANNAME_LEN	64
#define		PWD_LEN				66
#define		ADDR_LEN			64
#define		TIME_LEN				64
//�����û���Ϣ��ѯ��ʽ��Ĭ�ϣ����û�����ȷ���ң�
#define		QUI_BY_USERNAME			0
#define		QUI_BY_MSISDN					2
#define		QUI_BY_PLANNO					4
#define		QUI_WAY_ACCURATE			0
#define		QUI_WAY_APPROXIMATE	1
//�����ײͲ�ѯ��ʽ
#define		QP_BY_PLANNO					0
#define		QP_BY_PLANNAME				2
//�����շ�Ա��ѯ��ʽ
#define		QO_BY_OPERATORNO		0
#define		QO_BY_OPERATORNAME	2
//�����û���Ϣɾ����ʽ
#define		DUI_WAY_ALL						0
#define		DUI_WAY_BY_MSISDN		2
//���Կ���
#define		CMS_DEBUG		1

//����һ�����ݽṹ
//�ײ�
struct CallPlan
{
	int						PlanNo;										//�ײͱ��
	wchar_t				PlanName[PLANNAME_LEN];		//�ײ�����
	double					RemoteFee;									//��;����
	double					LocalFee;										//�л�����
	double					RoamingFee;								//���η���
};

//ͨ���굥 CallDetailRecords
struct CDR		
{
	wchar_t		CallTime[TIME_LEN];			//ͨ��ʱ��
	wchar_t		caller[MSISDN_LEN];			//����
	wchar_t		called[MSISDN_LEN];			//����
	wchar_t		type[TYPE_LEN];					//ͨ������
	int				duration;								//ͨ��ʱ��
};

//�շ�
struct Charge
{
	wchar_t			PayTime[TIME_LEN];			//�ɷ�ʱ��
	wchar_t			MSISDN[MSISDN_LEN];		//�û����绰���룩
	double				PayAmount;							//�ɷѽ��
	wchar_t			PayMethod[TYPE_LEN];		//�ɷѷ�ʽ
	int					OperatorNo;						//�շ�Ա����
};

//�շ�Ա
struct Operator
{
	int						OperatorNo;									//����
	wchar_t				OperatorName[NAME_LEN];			//����
	wchar_t				OperatorGender[GENDER_LEN];		//�Ա�
	int						Class;												//Ȩ�޵ȼ�
	wchar_t				password[PWD_LEN];						//���루��ϣ��
	//int						LoginStatus;										//��¼״̬
};

//�û�����
struct UserInfo
{
	wchar_t				MSISDN[MSISDN_LEN];				//�绰����
	double					balance;										//���
	int						PlanNo;										//�ײͱ��
	wchar_t				status[STATUS_LEN];					//�û�״̬
	wchar_t				name[NAME_LEN];						//����
	wchar_t				gender[GENDER_LEN];				//�Ա�
	wchar_t				address[ADDR_LEN];					//סַ
};


//���ݿ������ ����
class DBgo
{
public:
	//һ�ѿɹ����ⲿʹ�õı���...

	//һ�ѿɹ����ⲿ���õĺ���...
	DBgo();
	~DBgo();
	//��ѯ����
	bool QueryPlan(wchar_t* QueryStr, int QP_Method, struct CMS_DB_HEADER* cdh);
	bool QueryCDR(wchar_t* CallerMSISDN, struct CMS_DB_HEADER* cdh);
	bool QueryCharge(wchar_t* MSISDN, struct CMS_DB_HEADER* cdh);
	bool QueryOperator(LPCWSTR QueryStr, int QO_Method, struct CMS_DB_HEADER* cdh);
	bool QueryUserInfo(wchar_t* QueryStr, int QUI_Method, struct CMS_DB_HEADER* cdh);
	//�����ײ͡��շѼ�¼���շ�Ա���û�
	bool AddPlan(struct CallPlan* cp);
	bool AddCharge(struct Charge* c);
	bool AddOperator(struct Operator* op);
	bool AddUserInfo(struct UserInfo* ui);
	//ɾ���ײ͡��շ�Ա���û�	
	bool DropPlan(int PlanNo);
	bool DropOperator(int OperatorNo);
	bool DropUserInfo(wchar_t* MSISDN, int Dui_Way);
	//����Ա��������
	bool OnOperatorChangePwd(int OperatorNo, LPCWSTR NewPwd);
	//�û��ɷ�
	bool OnUserCharge(struct Charge* c, double dBalance);
	//��¼
	bool Login(struct Operator* op, int & LoginResult);
	//��ȡ������ֵ���������С�����
	int GetMaxNo(LPCWSTR MaxItem, LPCWSTR SheetName);
private:
	//���ݿ����������
	SQLHENV			henv;				//�������
	SQLHDBC		hdbc1;				//���Ӿ��
	SQLHSTMT		hstmt1;			//�α�
	//��¼��֤
	std::wstring		dbDSN;			//���ݿ���
	std::wstring		dbUID;				//��¼�û���
	std::wstring		dbPWD;			//��¼�û�����
	//����
	std::wstring		dbSQL;				//SQL���
	RETCODE			retcode;			//����ֵ
	bool					isConnected;	//���ӳɹ���

	//�������ݿ�
	bool ConnectDB();

public:
	// ���ݻ�ԭ���ݿ�
	bool BackupAndRestore(bool isBackup);
};

#endif