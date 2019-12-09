#pragma once
#include "Constants_types_globals.h"
#include "For_work_with_struct.h"
#include <string>
#include <stdio.h>
#include <conio.h>

int answer(char *s) // Диалог с пользователем, вопрос с ответом да/нет
{
	char c;
	int k;
	printf_s("%s (y or n) \n", s);
	do
	{
		scanf_s("%c", &c);
		getchar();
		if (c != 'n' && c != 'y')
			printf_s("Action did not chosen\n");
	} while (c != 'n' && c != 'y');
	if (c == 'n')
		k = 0;
	else
		k = 1;
	return k;
}

int check_desision(char *s, char min, char max) // Ввод натурального числа числа в диапазоне от min до max
{
	int k;
	printf_s("%s ", s);
	do
	{
		scanf_s("%d", &k);
		if (k<min || k>max)
			printf_s("You must enter number from %d to %d", min, max);
	} while (k<min || k>max);
	return k;
}

int check_number(char *s) // Проверка телефонного номера
{
	int ok;
	ok = 0;
	int f = strlen(s);
	if ((f == 11) || (f == 7))
	{
		register int j = 0;
		ok = 1;
		while ((ok) && (j < f))
			if ((s[j] >= '0') && (s[j] <= '9'))
				j++;
			else
				ok = 0;
	}
	else
		ok = 0;
	return ok;
}

int check_home_number(char *s) // Проверка номера дома
{
	int k, j, i;
	j = strlen(s);
	if (j > 3)
		return 0;
	else
		for (i = 0; i < j, (s[i] >= '0' && s[i] <= '9'|| s[i]>='0' && s[i]<='z'); i++);
	if (i < j)
		return 0;
	return 1;
}

int check_float_number(char *s) // Проверка номера квартиры
{
	int k, j, i;
	j = strlen(s);
	if (j > 3)
		return 0;
	else
		for ( i = 0; i < j, (s[i] >= '0' && s[i] <= '9' ); i++);
	if (i < j)
		return 0;
	return 1;
}
