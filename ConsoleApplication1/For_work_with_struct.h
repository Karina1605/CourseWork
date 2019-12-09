#pragma once
#include "Constants_types_globals.h"

int check_file_name(char *st) //�������� ����� ����� �� ������������
{
	int k = 1;
	int len = strlen(st);
	int i = 0;
	while (k && i < len)
		if (strchr(forbidden, st[i]))
			k = 0;
		else
			i++;
	return k;
}

long int get_size_of_file(files *f) //���-�� ������� � �����, 0-���� ������,  -1-������ � ����� �� ��������� 
{
	if (feof(f->f))
		return 0;
	else
	{
		fseek(f->f, 0, SEEK_END);
		long int n = ftell(f->f);
		if (n % sizeof(person) > 0)
			return -1;
		else
		return (n / sizeof(person));
	}
}

int input_name_of_file(files *file, char *s, int k = 30) // ���� ����� �����
{
	int i;
	printf_s("%s\nSymbols %s are forbidden\nenter - escape\n", s, forbidden);
	do
	{
		getchar();
		gets_s(file->filename, 30);
		if (!strlen(file->filename))
			i = 3;
		else
		{
			i = check_file_name(file->filename);
			if (!i)
				printf_s("Uncorrect name of file, please retry entering\n");
		}
	} while (!i);
	return i;
}

int is_exists(int must, files *file) //�������� ����� ����� �� ������������� 1-���� ���������� � ������ ��� �� ���������� � �� ������, 0-���� ������, �� �� ������ ������������, -1-���� �� ������
{
	int k;
	errno_t err = fopen_s(&(file->f), file->filename, "rb");
	if (!err && must) 
	{
		fclose((file->f));
		k = 1;
	}
	else
		if (!err && !must)
		{
			fclose((file->f));
			k = 0;
		}
		else
			if (err && !must)
				k = 1;
			else
				if (err && must)
					k = -1;
	return k;
}
