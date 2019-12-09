#pragma once
#include "Constants_types_globals.h"
#include "Entering.h"
#include"Errors.h"
#include "Printing.h"
#include <stdio.h>

int first() //Выбор файла, с которым будет работать пользователь
{
	char st[]="Select action: ";
	int k;
	getchar();
	printf_s("1.Create new file\n2.Go on working with old file\n3.Read textfile\n4.Escape\n");
	k = check_desision(st, 1, 4);
	return k;
}

int choose() // выбор операции над типизированнымм файлом
{
	char c[]="Select action : ";
	int k;
	printf_s("1.Clean the file\n2.Add to the file\n3.Read all from file\n4.Search information\n5.Correct records\n6.Delete records\n7.Erase file\n8.Escape\n");
	k = check_desision(c, 1, 8);
	return k;
}

void work(int a, files *file) //действие над файлом. определенное в пред функции
{
	int k, c, f, ok;
	files ft;
	switch (a)
	{
	case 1:
	{
		open_for_creating(file);
		char s[] = "Are you sure?";
		 k= answer(s);
		if (k)
		{
			fclose(file->f);
		}
		fopen_s(&(file->f), file->filename, "wb");
		printf_s("File is cleaned\n");
		fclose(file->f);
		system("cls");
	}
		break;
	case 2:
	{
		k = 1;
		char st[] = "Enter more?";
		open_for_correct(file);
		fseek(file->f, 0, SEEK_END);
		printf_s("Input dates\n");
		do
		{
			add(k, file);
			c = answer(st);
			k++;
		} while (c);
		fclose(file->f);
		system("cls");
	}
		break;
	case 3:
	{
		int res;
		char s[] = "Print in file or (no - in console)?";
		char st1[] = "Input name of the file";
		char st2[] = "What kind of format you want to see in text (1-table, 2-list)";
		system("cls");
		k = open_for_reading(file);
		if (k == 1)
		{
			getchar();
			k = answer(s);
			f = check_desision(st2, 1, 2);
			if (!k)
			{
				read_all(file, stdout, f);
			}
			else
			{
				do
				{
					res= input_name_of_file(&ft, st1);
					if (!strcmp(ft.filename, file->filename))
					{
						ok = 0;
						printf_s("You can not rewrite file which already opened\n");
					}
					else
						ok = 1;
				} while ((!ok) && res!=3);
				if (res != 3)
				{
					open_for_creating_t(&ft);
					read_all(file, ft.f, f);
					fclose(ft.f);
					printf_s("text file %s was created\n", ft.filename);
				}
			}
			fclose(file->f);
		}
	}
		break;
	case 4:
	{
		char s[] = "Print in file or (no - in console)? ";
		char st1[] = "Input name of the file";
		char st2[] = "What kind of format you want to see in text (1-table, 2-list): ";
		system("cls");
		char st[30];
		int ch = searching_chritery(1);
		input_line(ch, st);
		k= open_for_reading(file);
		if (k == 1)
		{
			k = answer(s);
			if (!k)
			{
				k = check_desision(st2, 1, 2);
				print_find(ch, file, st, stdout, k);
			}
			else
			{
				f = check_desision(st2, 1, 2);

				do
				{
					input_name_of_file(&ft, st1);
					if (!strcmp(ft.filename, file->filename))
					{
						ok = 0;
						printf_s("Yoy can not rewrite in file which already opened\n");
					}
					else
						ok = 1;
				} while (!ok);
				open_for_creating_t(&ft);
				read_all(file, ft.f, f);
				fclose(ft.f);
				open_for_creating_t(&ft);
				k = check_desision(st2, 1, 2);
				print_find(ch, file, st, ft.f, k);
				fclose(ft.f);
			}
			fclose(file->f);
		}
	}
		break;
	case 5:
	{
		char s[] = "Correct more?";
		open_for_reading(file);
		int n = read_all(file, stdout, 1);
		fclose(file->f);
		if (n != -1)
			do
			{
				int t;
				t= open_for_correct(file);
				if (t == 1)
				{
					correct(file, n);
					c = answer(s);
				}
				else
					c = 0;
			} while (c);
			fclose(file->f);
			system("cls");
	}
		break;
	case 6:
	{
		char s[] = "Delete more?";
		do
		{
			k = open_for_correct(file);
			delete_elem(file);
			c = answer(s);
		} while (c);
		system("cls");
	}
		
		break;
	case 7:
		if (remove(file->filename) == -1)
			printf_s("Error of deleting\n");
		else
			printf_s("file is deleted\n");
		system("cls");
		break;
	}
}
