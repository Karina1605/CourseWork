#pragma once
#include "Constants_types_globals.h"
#include <stdio.h>

int open_for_creating(files *file) //�������� ��������� �����
{
	fopen_s(&(file->f), file->filename, "w+b");
	if ((file->f) ==NULL)
	{
		printf_s("Error of crearing\n");
		return -1;
	}
	else
		return 1;
}

int open_for_creating_t(files *file) //�������� ���������� �����
{
	char name[50];
	strcpy_s(name, file->filename);
	fopen_s(&(file->f), file->filename, "w");
	if ((file->f) == NULL)
	{
		printf_s("Error of creating of the file\n");
		return -1;
	}
	else
		return 1;
}

int open_for_reading( files *file) //�������� ��������� ����� ��� ������ ��� ����������� ��������������
{
	errno_t err= fopen_s(&file->f, file->filename, "rb");
	if (err)
	{
		printf_s("The document did not found\n");
		return -1;
	}
	else
		return 1;
}

int open_for_reading_t(files *file) //�������� ���������� �����
{
	strcat_s(file->filename, ".txt");
	errno_t err = fopen_s(&file->f, file->filename, "rt");
	if (err)
	{
		printf_s("The document did not found\n");
		return -1;
	}
	else
		return 1;
}

int open_for_correct( files *file) // �������� ������������� ��������� ����� ��� ������������� ������
{
	errno_t err = fopen_s(&(file->f), file->filename, "r+b");
	if (err)
	{
		printf_s("The document did not found\n");
		return -1;
	}
	else
		return 1;
}
