#pragma once
#include "Constants_types_globals.h"
#include "Errors.h"
#include "For_work_with_struct.h"
#include <stdio.h>
#include <string.h> 

void print_head(FILE *d) //Печать заголовка таблицы в текстовый файл d
{
	fprintf_s(d, "%4s|%12s|%10s|%15s|%10s|%15s|%4s|%8s|%12s|\n", "Code", "Surname", "Name", "Pathronymic", "City", "Street", "Home", "Flat", "Phone");
}

void in_buff(person *a, FILE *file) //Считывание записи из бинарного файла
{
	if (!feof(file))
		size_t k = fread(*(&a), sizeof(person), 1, file);
}

void print_person(person &a, int i, FILE *f) //Печать в формате таблицы
{
	fprintf_s(f, "%3d.|%12s|%10s|%15s|%10s|%15s|%4s|%8s|%12s|\n", i, a.surname, a.name, a.pathronymic, a.adress.city, a.adress.street, a.adress.home, a.adress.flat, a.phone);
}

void write_text(person &a, FILE *f) //Печать в формате списка записей
{

	fprintf_s(f, "Surname: %s\n", a.surname);
	fprintf_s(f, "Name: %s\n", a.name);
	fprintf_s(f, "Pathronymic: %s\n", a.pathronymic);
	fprintf_s(f, "City: %s\n", a.adress.city);
	fprintf_s(f, "Street: %s\n", a.adress.street);
	fprintf_s(f, "House: %s\n", a.adress.home);
	fprintf_s(f, "Flat: %s\n", a.adress.flat);
	fprintf_s(f, "Phone: %s\n", a.phone);
	fprintf_s(f, "\n");
}

int read_all(files *file, FILE *ft, int k) //Прочиать все из типизированного файла в тектовый ft
{
	long int n = get_size_of_file(file);
	if (!n)
		printf_s("File is empty\n");
	else
		if (n == -1)
			printf_s("Uncorrect file\n");
		else
		{
			person buff=empty;
			if (k==1)
				print_head(ft);
			fseek(file->f, 0, SEEK_SET);
			int i = 0;
			switch (k)
			{
			case 1:
				while (i < n)
				{
					in_buff(&buff, file->f);
					print_person(buff, i + 1, ft);
					buff = empty;
					i++;
				}
				break;
			default:
				while (i < n)
				{
					in_buff(&buff, file->f);
					write_text(buff, ft);
					buff = empty;
					i++;
				}
				break;
			}
		}
	return n;
}

int is_right(int k, person &buff, char *s) //Проверка соотвествия критерию поиска
{
	if (((k == 1) && (!strcmp(buff.surname, s))) || ((k == 2) && (!strcmp(buff.name, s))) || ((k == 3) && (!strcmp(buff.pathronymic, s)))
		|| ((k == 4) && (!strcmp(buff.adress.city, s))) || ((k == 5) && (!strcmp(buff.adress.street, s))) || ((k == 6) && (!strcmp(buff.adress.home, s)))
		|| ((k == 7) && (!strcmp(buff.adress.flat, s))) || ((k == 8) && (!strcmp(buff.phone, s))))
		return 1;
	else
		return 0;

}

void print_find(int k, files *file, char *s, FILE *ft, int format) //Распечатать в текстовый файл ft найденные по критерию записи в формате, определяемом format
{
	int count = 0;
	long int n = get_size_of_file(file);
	if (!n)
		printf_s("File is empty\n");
	else
	{
		person buff;
		if (format==1)
			print_head(ft);
		fseek(file->f, 0, SEEK_SET);
		for (int i = 0; i < n; i++)
		{
			fread(&buff, sizeof(person), 1, file->f);
			if (is_right(k, buff, s))
			{
				count++;
				switch (format)
				{
				case 1:print_person(buff, count, ft);
					break;
				default: write_text(buff, ft);
					break;
				}	
			}
		}
		if (!count)
			printf_s("There are not records with your chritery\n");
	}
}

void read_from_text_to_screen(files *f)  //Чтение из текстового файла на экран
{
	char buff[100];
	if (feof(f->f))
		printf_s("File is empty\n");
	else
		while (!feof(f->f))
		{
			fgets(buff, 100, f->f);
			printf_s("%s", buff);
		}
}
