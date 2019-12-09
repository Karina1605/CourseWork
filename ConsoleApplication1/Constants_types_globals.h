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
	char city[20];      //Город проживания
	char street[30];    //Улица
	char home[7];       //Дом
	char flat[4];       //Квартира
}tadress;

typedef struct per
{
	char surname[25];     //Фамилия
	char name[20];        //Имя
	char pathronymic[20]; //Отчество
	tadress adress;       //Адрес  
	char phone[15];       //Номер телефона
}person;

typedef struct fil
{
	FILE *f;			//Файловая переменная
	char filename[30];	//Имя файла, к которой будет привязана f
} files;				

person empty = { 0 };
