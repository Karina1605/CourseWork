#pragma once
#include "Constants_types_globals.h"
#include "Errors.h"
#include "For_work_with_struct.h"
#include "Printing.h"
#include "Open.h"
#include <stdio.h>
#include <string.h>

int input(person a, files *file) //Запись в бинарный файл
{
	int ok;
	ok = fwrite(&a, sizeof(person), 1, file->f);
	return ok;
}

void input_part(int k, person &buff) //корректировка поля записи
{
	int ok;
	getchar();
	switch (k)
	{
	case 1:
		printf_s("New surname : ");
		gets_s(buff.surname);
		break;
	case 2:
		printf_s("New name : ");
		gets_s(buff.name);
		break;
	case 3:
		printf_s("New pathronymic : ");
		gets_s(buff.pathronymic);
		break;
	case 4:
		printf_s("New city : ");
		gets_s(buff.adress.city);
		break;
	case 5:
		printf_s("New street : ");
		gets_s(buff.adress.street);
		break;
	case 6:
		printf_s("New house number : ");
		do
		{
			gets_s(buff.adress.home);
			ok = check_home_number(buff.adress.home);
			if (!ok)
				printf_s("Uncorrect home number, retry entering\n");
		} while (!ok);
		break;
	case 7:
		printf_s("New float number : ");
		do
		{
			gets_s(buff.adress.flat);
			ok = check_float_number(buff.adress.flat);
			if (!ok)
				printf_s("Uncorrect flat number, retry entering\n");
		} while (!ok);
		break;
	case 8:
		printf_s("New phone : ");
		do
		{
			gets_s(buff.phone);
			ok = check_number(buff.phone);
			if (!ok)
				printf_s("Uncorrect phone number, retry entering\n");
		} while (!ok);
		break;
	}
}

void input_new(person &a) //Ввол структуры с клавиатуры
{
	int ok;
	printf_s("Surname : ");
	getchar();
	gets_s(a.surname, 25);
	printf_s("Name : ");
	gets_s(a.name, 20);
	printf_s("Pathronymic : ");
	gets_s(a.pathronymic, 20);
	printf_s("Adress : \n");
	printf_s("    City : ");
	gets_s(a.adress.city, 20);
	printf_s("    Street : ");
	gets_s(a.adress.street, 30);
	printf_s("    House: ");
	do
	{
		gets_s(a.adress.home, 5);
		ok = check_float_number(a.adress.home);
		if (!ok)
			printf_s("Error, reenter number of house\n");
	} while (!ok);
	printf_s("    Flat : ");
	do
	{
		gets_s(a.adress.flat, 4);
		ok = check_float_number(a.adress.flat);
		if (!ok)
			printf_s("Error, reenter number of flat\n");
	} while (!ok);
	printf_s("Phone (11 or 7 digits) : ");
	do
	{
		gets_s(a.phone, 15);
		ok = check_number(a.phone);
		if (!ok)
			printf_s("Error, reenter phone number\n");
	} while (!ok);

}

void add(int n, files *file) //Ввод структуры и запись ее в файл
{
	person a;
	int ok;
	a = empty;
	
	printf_s("Abonent №%d \n", n);
	input_new(a);
	ok = input(a, file);
	if (!ok)
	{
		printf_s("Error of entering\n");
		fclose(file->f);
	}
}

int searching_chritery(int find_correct) //Выбор критерия поиска или поля корректировки
{
	int k;
	char st[] = "Choose searching chritery";
	char st1[] = "Choose correct part";
	printf_s("1. %s\n2. %s\n3. %s\n4. %s\n5. %s\n6. %s\n7. %s\n8. %s\n", "Surname", "Name", "Pathronymic", "City", "Street", "House", "Flat", "Phone");
	if (find_correct == 1)
		k = check_desision(st, 1, 8);
	else
		k = check_desision(st1, 1, 8);
	return k;
}

void correct(files *file, int n) //Корректировка считанной записи и ее перезапись в файл
{
	char s[] = "Input position of line you want to correct ";
	int des;
	int k;
	if (n != -1)
	{
		person a=empty;
		des = check_desision(s, 1, n) - 1;
		fseek(file->f, des * sizeof(person), SEEK_SET);
		in_buff(&a, file->f);
		fseek(file->f, des * sizeof(person), SEEK_SET);
		k = searching_chritery(2);
		input_part(k, a);
		fwrite(&a, sizeof(person), 1, file->f);
	}
}

void delete_elem(files *file) //Удаление элемента из бинарного файла
{
	int i = 0;
	person buff;
	int kin, kout;
	long int n = get_size_of_file(file);
	if (!n)
		printf_s("File is empty\n");
	else
	{
		char s[] = "Input the position the line you want to delete ";
		char ans[] = "Delete more?";
		files new_file;
		read_all(file, stdout, 1);
		int des = check_desision(s, 1, n) - 1;
		strcpy_s(new_file.filename, new_name_f);
		fseek(file->f, 0, SEEK_SET);
		fclose(file->f);
		kin=open_for_creating(&new_file);
		kout=open_for_reading(file);
		buff = empty;
		if (kin == 1 && kout == 1)
		{
			while (i<n && i!=des)
			{
				in_buff(&buff, file->f);
				input(buff, &new_file);
				i++;
				fseek(file->f, sizeof(person)*i, SEEK_SET);
			}
			fseek(file->f, sizeof(person), SEEK_CUR);
			i++;
			while (i < n)
			{
				in_buff(&buff, file->f);
				input(buff, &new_file);
				i++;
				fseek(file->f, sizeof(person)*i, SEEK_SET);
			}
			fclose(new_file.f);
			fclose(file->f);
			kout = open_for_creating(file);
			kin = open_for_reading(&new_file);
			n--;
			i = 0;
			while (i<n)
			{
				in_buff(&buff, new_file.f);
				input(buff, file);
				i++;
			}
			fclose(file->f);
			fclose(new_file.f);
			remove(new_file.filename);
		}
		else
			printf_s("Error \n");
	}
	getchar();
}

void input_line(int k, char *c) //Ввод строки, по которой будет осуществляться поиск
{
	int len;
	printf_s("Input ");
	switch (k)
	{
	case 1: printf_s("Surname: ");
		break;
	case 2:printf_s("Name: ");
		break;
	case 3:printf_s("Pathronymic: ");
		break;
	case 4:printf_s("City: ");
		break;
	case 5:printf_s("Street: ");
		break;
	case 6:printf_s("Home number: ");
		break;
	case 7:printf_s("Float number: ");
		break;
	default:printf_s("Phone number: ");
		break;
	}
	do
	{
		getchar();
		gets_s(c, 20);
		len = strlen(c);
		if (len == 0)
			printf_s("The line is empty, please, retry\n");
	} while (len == 0);
}
