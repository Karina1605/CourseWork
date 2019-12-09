#pragma once
#include "For_work_with_struct.h"
#include "Errors.h"
#include "Open.h"
#include "Printing.h"
#include <stdio.h>

int create_new_file(files *f) //Ввод имени и создание файла с этим именем
{
	char s[] = "Enter name of new file";
	int c;
	char s1[] = "File exists, erase it?";
	int k	;
	int op=	input_name_of_file(f, s);
	if (op != -2)
	{
		k = is_exists(0, f);
		if (!k)
		{
			c = answer(s1);
			if (!c)
			{
				printf_s("File was not corrupted\n");
				k = -1;
			}
		}
		else
			k = open_for_creating(f);
		fclose(f->f);
		return k;
	}
	else
		return op;
}

int open_old_file(files *file) //Поиск старого файла
{
	char s[] = "Enter name of old file";
	int k=0;
	int f=input_name_of_file(file, s);
	if (f != -2)
	{
		k = is_exists(1, file);
		if(k==-1)
			printf_s("File did not found\n");
		return k;
	}
	else
		return f;
}
