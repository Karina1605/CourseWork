#pragma once
#include <stdio.h>
#include <string>
#include <ctype.h>

const int nol = (int)'0';
const char *new_name_f = "help";
const char esc = (char)27;
const char *forbidden = "&*\:<>?/|";

typedef struct adr
{
	char city[20];      //����� ����������
	char street[30];    //�����
	char home[7];       //���
	char flat[4];       //��������
}tadress;

typedef struct per
{
	char surname[25];     //�������
	char name[20];        //���
	char pathronymic[20]; //��������
	tadress adress;       //�����  
	char phone[15];       //����� ��������
}person;

typedef struct fil
{
	FILE *f;			//�������� ����������
	char filename[30];	//��� �����, � ������� ����� ��������� f
} files;				

person empty = { 0 };
