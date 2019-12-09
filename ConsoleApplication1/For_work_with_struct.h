#pragma once
#include "Constants_types_globals.h"

int check_file_name(char *st) //Проверка имени файла на корректность
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

long int get_size_of_file(files *f) //Кол-во струтур в файле, 0-файл пустой,  -1-данный в файле не корректны 
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

int input_name_of_file(files *file, char *s, int k = 30) // Ввод имени файла
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

int is_exists(int must, files *file) //Проверка имени файла на существование 1-файл существует и найден или не существует и не найден, 0-файл найден, но не должен существовать, -1-файл не найден
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
