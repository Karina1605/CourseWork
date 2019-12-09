#include "pch.h"
#include "Constants_types_globals.h"
#include "Errors.h"
#include "New.h"
#include "Menu.h"
#include <stdio.h>
#include <cstdlib>
#include <clocale>
#include <string.h>

int main()
{
	int a, k, g;
	files fmain;
	setlocale(LC_ALL, "Russian");
	printf_s("Hello, print enter for start\n");
	do
	{
		a = first();
		switch (a)
		{
		case 1: k = create_new_file(&fmain);
			if (k != -1 && k!=-2)
				do
				{
					g = choose();
					work(g, &fmain);
				} while (g != 8);
				break;
		case 2: k = open_old_file(&fmain);
			if (k != -1 && k!=-2)
			{
				do
				{
					g = choose();
					work(g, &fmain);
				} while (g != 8);
			}
			else
				a = first();
			break;
		case 3:
		{
			char st[] = "Enter name of existing textfile";
			do
			{
				input_name_of_file(&fmain, st);
				if (!strlen(fmain.filename))
					g = 3;
				else
				{
					g = open_for_reading_t(&fmain);
					printf_s("g = %d\n", g);
					if (g != 1)
						printf_s("Error, reenter name of file\n");
				}
				
			} while (g != 1 && g!=3);
			if (g!=3)
			{
				read_from_text_to_screen(&fmain);
				fclose(fmain.f);
			}
		}
		break;
		}

	} while (a != 4);
	printf_s("Goodbye");
	return 0;
}
