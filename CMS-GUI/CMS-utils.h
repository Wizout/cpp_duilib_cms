/*
CMS�߼����� ͷ�ļ�
*/
#ifndef _CMS_UTILS_H_
#define _CMS_UTILS_H_

#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "CMS-md5.h"

#define CONTENT_LEN	512

//���������㡢����ͷ
struct CMS_DB_NODE
{
	char content[CONTENT_LEN];
	struct CMS_DB_NODE* next;
};
struct CMS_DB_HEADER
{
	int n;
	struct CMS_DB_NODE* next;
};

//struct CMS_HWND_NODE
//{
//	HWND hwnd;
//	struct CMS_HWND_NODE* next;
//};
//
//struct CMS_HWND_HEADER
//{
//	int n;
//	struct CMS_HWND_NODE* next;
//};

//��ʼ������ͷ
bool InitCDH(struct CMS_DB_HEADER* cdh);
//ɾ����������
bool DeleteCDH(struct CMS_DB_HEADER* cdh);
//������ͷ�����µĽ��
bool AddToCDH(struct CMS_DB_HEADER* cdh, void* content, size_t ContentLen);

std::string WChar2Ansi(LPCWSTR pwszSrc);
std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen);
std::string ws2s(std::wstring& inputws);
std::wstring s2ws(const std::string& s);

//���ת����Ҵ�д
std::string ConvertMoneyCaps(long double moneySum);


#endif // !_CMS_UTILS_H_