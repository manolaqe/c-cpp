/*
Tema:
Realizati aplicatia care tine evidenta persoanelor infectate cu Coronavirus in Romania.

Se presupune ca la 2 saptamani de la internare, pacientul este vindecat.

Primul caz de Coronavirus a fost confirmat pe 26 februarie 2020, deci orice internare inainte de aceasta este aberanta.
*/

#include <stdio.h>
#include <string.h>
#pragma warning(disable: 4996)

typedef struct
{
	char indicator_stare = NULL;
	int cod_pacient = NULL;
	char nume[20] = "nume";
	char prenume[20] = "prenume";
	int varsta = NULL;
	char boli_preexistente = NULL;
	char diabetic = '0';
	char boli_pulmonare = '0';
	char afectiuni_cardiovasculare = '0';

	struct data
	{
		int zi = NULL;
		int luna = NULL;
		int an = NULL;
	} data_internarii;

} pacient;

//functie care traduce din valorile boolene in DA sau NU
const char* adevar(char c)
{
	if (c == '1')
		return "DA";
	else if (c == '0')
		return "NU";

}

//functie care masoara intervalul dintre data curenta si data internarii pacientului
int durata(int zi, int luna)
{
	int durata = 0;
	int i = 0;

	while (i < luna)
	{
		if (i == 2) durata += 29;
		else if (i % 2 == 0) durata += 30;
			else durata += 31;
		i++;
	}
	return durata;
}

int nr_art(FILE* f, int p)
{
	int l, m;
	l = ftell(f);
	fseek(f, 0, 2);
	m = ftell(f) / p;
	fseek(f, l, 0);
	return m;
}

//crearea fisierului binar + populare
void populare()
{
	FILE* f;
	pacient p;

	int n, i, nr = sizeof(pacient);
	char nume_fisier[20];

	printf("Numele fisierului:");
	gets_s(nume_fisier);
	f = fopen(nume_fisier, "wb+");

	printf("n = ");
	scanf("%d", &n);

	while (!feof(stdin))
	{
		if (n > nr_art(f, sizeof(pacient)))
		{
			fseek(f, 0, 2);

			p.indicator_stare = 0;

			for (i = nr_art(f, sizeof(pacient)); i < n; i++)
				fwrite(&p, sizeof(pacient), 1, f);

			fseek(f, (n - 1) * sizeof(pacient), 0);

			p.indicator_stare = 1;
			p.cod_pacient = n;

			printf("Numele pacientului: "); getc(stdin), gets_s(p.nume);
			printf("Prenumele pacientului: "); gets_s(p.prenume);
			printf("Varsta pacientului: "); scanf("%d", &p.varsta);
			printf("Pacientul sufera de boli cronice preexistente?(0/1)"); scanf(" %c", &p.boli_preexistente);

			if (p.boli_preexistente == '1')
			{
				printf("(0/1)Diabetic: "); scanf(" %c", &p.diabetic);
				printf("(0/1)Boli pulmonare: "); scanf(" %c", &p.boli_pulmonare);
				printf("(0/1)Afectiuni cardiovasculare: "); scanf(" %c", &p.afectiuni_cardiovasculare);
			}
			printf("\nData internarii (zi, luna, an) dupa 26 februarie 2020: ");
			scanf("%d %d %d", &p.data_internarii.zi, &p.data_internarii.luna, &p.data_internarii.an);

			fseek(f, (n - 1) * sizeof(pacient), 0);
			fwrite(&p, sizeof(pacient), 1, f);
		}
		else
		{
			fseek(f, (n - 1) * sizeof(pacient), 0);
			fread(&p, sizeof(pacient), 1, f);

			if (p.indicator_stare == 0)
			{
				p.indicator_stare = 1;
				p.cod_pacient = n;

				printf("Numele pacientului: "); getc(stdin), gets_s(p.nume);
				printf("Prenumele pacientului: "); gets_s(p.prenume);
				printf("Varsta pacientului: "); scanf("%d", &p.varsta);
				printf("Pacientul sufera de boli cronice preexistente?(0/1)"); scanf(" %c", &p.boli_preexistente);

				if (p.boli_preexistente == '1')
				{
					printf("(0/1)Diabetic: "); scanf(" %c", &p.diabetic);
					printf("(0/1)Boli pulmonare: "); scanf(" %c", &p.boli_pulmonare);
					printf("(0/1)Afectiuni cardiovasculare: "); scanf(" %c", &p.afectiuni_cardiovasculare);
				}

				printf("Data internarii (zi, luna, an) dupa 26 februarie 2020: ");
				scanf("%d %d %d", &p.data_internarii.zi, &p.data_internarii.luna, &p.data_internarii.an);

				fseek(f, (n - 1) * sizeof(pacient), 0);
				fwrite(&p, sizeof(pacient), 1, f);
			}
			else printf("Inregistrarea exista\n");
		}
		printf("\nn = ");
		scanf_s("%d", &n);
	}
	fclose(f);
}

//adaugarea unui articol in fisier
void adaugare()
{
	FILE* f;
	pacient p;

	int n, i, nr = sizeof(pacient);
	char nume_fisier[20];
	
	printf("Numele fisierului:");
	gets_s(nume_fisier);
	f = fopen(nume_fisier, "rb+");

	if(f == NULL) f = fopen(nume_fisier, "wb+");
	printf("\nn = "); scanf("%d", &n);

	while (!feof(stdin))
	{

		if (n > nr_art(f, sizeof(pacient)))
		{
			fseek(f, 0, 2);
			p.indicator_stare = 0;

			for (i = nr_art(f, sizeof(pacient)); i < n; i++)
				fwrite(&p, sizeof(pacient), 1, f);

			fseek(f, (n - 1) * sizeof(pacient), 0);

			p.indicator_stare = 1;
			p.cod_pacient = n;

			printf("Numele pacientului: "); getc(stdin), gets_s(p.nume);
			printf("Prenumele pacientului: "); gets_s(p.prenume);
			printf("Varsta pacientului: "); scanf("%d", &p.varsta);
			printf("Pacientul sufera de boli cronice preexistente?(0/1)"); scanf(" %c", &p.boli_preexistente);

			if (p.boli_preexistente == '1')
			{
				printf("(0/1)Diabetic: "); scanf(" %c", &p.diabetic);
				printf("(0/1)Boli pulmonare: "); scanf(" %c", &p.boli_pulmonare);
				printf("(0/1)Afectiuni cardiovasculare: "); scanf(" %c", &p.afectiuni_cardiovasculare);
			}

			printf("\nData internarii (zi, luna, an) dupa 26 februarie 2020: ");
			scanf("%d %d %d", &p.data_internarii.zi, &p.data_internarii.luna, &p.data_internarii.an);

			fseek(f, (n - 1) * sizeof(pacient), 0);
			fwrite(&p, sizeof(pacient), 1, f);
		}
		else
		{
			fseek(f, (n - 1) * sizeof(pacient), 0);
			fread(&p, sizeof(pacient), 1, f);

			if (p.indicator_stare == 0)
			{
				p.indicator_stare = 1;
				p.cod_pacient = n;

				printf("Numele pacientului: "); getc(stdin), gets_s(p.nume);
				printf("Prenumele pacientului: "); gets_s(p.prenume);
				printf("Varsta pacientului: "); scanf("%d", &p.varsta);
				printf("Pacientul sufera de boli cronice preexistente?(0/1)"); scanf(" %c", &p.boli_preexistente);

				if (p.boli_preexistente == '1')
				{
					printf("(0/1)Diabetic: "); scanf(" %c", &p.diabetic);
					printf("(0/1)Boli pulmonare: "); scanf(" %c", &p.boli_pulmonare);
					printf("(0/1)Afectiuni cardiovasculare: "); scanf(" %c ", &p.afectiuni_cardiovasculare);
				}
				else if (p.boli_preexistente == '0')
				{
					p.diabetic = '0';
					p.boli_preexistente = '0';
					p.afectiuni_cardiovasculare = '0';
				}

				printf("Data internarii (zi, luna, an) dupa 26 februarie 2020: ");
				scanf("%d %d %d", &p.data_internarii.zi, &p.data_internarii.luna, &p.data_internarii.an);

				fseek(f, (n - 1) * sizeof(pacient), 0);
				fwrite(&p, sizeof(pacient), 1, f);
			}
			else printf("Inregistrarea exista\n");
		}
		printf("\nn = ");
		scanf_s("%d", &n);
	}
	fclose(f);
}

//stergerea unui articol 
void stergere()
{
	FILE* f;
	pacient p;

	int n;
	char nume_fisier[20];

	printf("Numele fisierului: ");
	gets_s(nume_fisier);
	if (!(f = fopen(nume_fisier, "rb+")))
		printf("Fisier inexistent");
	else {
		printf("\n Sterge inregistrarea de pe pozitia: ");
		scanf("%d", &n);
		while (!feof(stdin))
		{
			if (n > nr_art(f, sizeof(pacient)))
				printf("Depaseste lungimea fisierului");
			else
			{
				fseek(f, (n - 1) * sizeof(pacient), 0);
				fread(&p, sizeof(pacient), 1, f);

				if (p.indicator_stare == 1)
				{
					printf("\n%s || %s || %5d || BOLI PREEXISTENTE %4s || DIABET %4s || BOLI PULMONARE %4s || AFECTIUNI CARDIOVASCULARE %4s || DATA INTERNARII %d.%d.%d \n", p.nume, p.prenume, p.varsta, adevar(p.boli_preexistente), adevar(p.diabetic), adevar(p.boli_pulmonare), adevar(p.afectiuni_cardiovasculare), p.data_internarii.zi, p.data_internarii.luna, p.data_internarii.an);

					p.indicator_stare = 0;

					fseek(f, (n - 1) * sizeof(pacient), 0);
					fwrite(&p, sizeof(pacient), 1, f);
				}
				else printf("Inregistrarea nu exista");
			}
			printf("\nn= "); scanf("%d", &n);
		}
		fclose(f);
	}
}

//generare raport cu toate articolele din fisier
void afisare()
{
	FILE* f, * g;
	pacient p;

	char nume_fisier[20];

	printf("Numele fisierului: ");
	gets_s(nume_fisier);

	if (!(f = fopen(nume_fisier, "rb")))
		printf("Fisier inexistent");
	else {
		printf("\n============================================================pacienti inregistrati====================================================================================");
		g = fopen("situatie_pacienti.txt", "w");
		printf("\n ");

		fprintf(g, "================================================================================================================================================================\n ");
		fprintf(g, " COD ||         NUME         ||       PRENUME        || VARSTA || BOLI PREEXISTENTE || DIABET || BOLI PULMONARE || AFECTIUNI CARDIOVASCULARE || DATA INTERNARII \n ");
		fprintf(g, "================================================================================================================================================================\n ");

		printf("===================================================================================================================================================================\n ");
		printf(" COD ||         NUME         ||       PRENUME        || VARSTA || BOLI PREEXISTENTE || DIABET || BOLI PULMONARE || AFECTIUNI CARDIOVASCULARE || DATA INTERNARII \n ");
		printf("===================================================================================================================================================================\n ");

		fread(&p, sizeof(pacient), 1, f);

		while (!feof(f))
		{
			if (p.indicator_stare == 1)
			{
				printf("\n %5d|| %-20s || %-20s ||  %5d || %17s || %6s || %14s || %25s || %d. %d. %d", p.cod_pacient, p.nume, p.prenume, p.varsta, adevar(p.boli_preexistente), adevar(p.diabetic), adevar(p.boli_pulmonare), adevar(p.afectiuni_cardiovasculare), p.data_internarii.zi, p.data_internarii.luna, p.data_internarii.an);

				fprintf(g, "\n %5d|| %-20s || %-20s ||  %5d || %17s || %6s || %14s || %25s || %d. %d. %d", p.cod_pacient, p.nume, p.prenume, p.varsta, adevar(p.boli_preexistente), adevar(p.diabetic), adevar(p.boli_pulmonare), adevar(p.afectiuni_cardiovasculare), p.data_internarii.zi, p.data_internarii.luna, p.data_internarii.an);
			}
			fread(&p, sizeof(pacient), 1, f);
		}
		fclose(f), fclose(g);
	}
}

//generare raport al oamenilor vindecati (au fost tratati timp de 14 zile)
void afisare_vindecati()
{
	FILE* f, * g;
	pacient p;

	char nume_fisier[20];
	int zi_curenta, luna_curenta;

	printf("Numele fisierului: ");
	gets_s(nume_fisier);
	
	printf("Zi curenta:"); scanf("%d", &zi_curenta);
	printf("Luna curenta:"); scanf("%d", &luna_curenta);

	if (!(f = fopen(nume_fisier, "rb")))
		printf("Fisier inexistent");
	else {
		printf("\n=========================================================pacienti declarati vindecati===============================================================================");
		g = fopen("situatie_pacienti_vindecati.txt", "w");

		printf("\n ");
		fprintf(g, "===================================================================================================================================================================\n ");
		fprintf(g, " COD ||         NUME         ||       PRENUME        || VARSTA || BOLI PREEXISTENTE || DIABET || BOLI PULMONARE || AFECTIUNI CARDIOVASCULARE || DATA INTERNARII \n ");
		fprintf(g, "===================================================================================================================================================================\n ");

		printf("===================================================================================================================================================================\n ");
		printf(" COD ||         NUME         ||       PRENUME        || VARSTA || BOLI PREEXISTENTE || DIABET || BOLI PULMONARE || AFECTIUNI CARDIOVASCULARE || DATA INTERNARII \n ");
		printf("===================================================================================================================================================================\n ");

		fread(&p, sizeof(pacient), 1, f);

		while (!feof(f))
		{
			if (p.indicator_stare == 1 && (durata(zi_curenta, luna_curenta) - durata(p.data_internarii.zi, p.data_internarii.luna)) >= 14)
			{
				printf("\n %5d|| %-20s || %-20s ||  %5d || %17s || %6s || %14s || %25s || %d. %d. %d", p.cod_pacient, p.nume, p.prenume, p.varsta, adevar(p.boli_preexistente), adevar(p.diabetic), adevar(p.boli_pulmonare), adevar(p.afectiuni_cardiovasculare), p.data_internarii.zi, p.data_internarii.luna, p.data_internarii.an);
				fprintf(g, "\n %5d|| %-20s || %-20s ||  %5d || %17s || %6s || %14s || %25s || %d. %d. %d", p.cod_pacient, p.nume, p.prenume, p.varsta, adevar(p.boli_preexistente), adevar(p.diabetic), adevar(p.boli_pulmonare), adevar(p.afectiuni_cardiovasculare), p.data_internarii.zi, p.data_internarii.luna, p.data_internarii.an);
			}
			fread(&p, sizeof(pacient), 1, f);
		}
		fclose(f), fclose(g);
	}
}

/*
Actualizare a inregistrarilor din fisier.
Se poate modifica oricare dintre campuri alegand o optiune din meniu.
*/
void modificare_pacient()
{

	FILE* f;
	pacient p;

	int n, zi, luna, an, optiune = 0, varsta;
	char boli_preexistente, boli_pulmonare, boli_cardiovasculare, diabet, nume_fisier[20], prenume[20], nume[20];
	
	printf("Numele fisierului: ");
	gets_s(nume_fisier);

	printf("Modificari: \n nume: 1 \n prenume: 2 \n varsta: 3 \n data: 4 \n boli preexistente: 5");
	printf("\n Introduceti optiunea: ");
	scanf("%d", &optiune);

	if (!(f = fopen(nume_fisier, "rb+")))
		printf("Fisier inexistent");
	else {
		printf("Introduceti pozitia pacientului de modificat: ");
		scanf("%d", &n);
		while (!feof(stdin))
		{
			if (n > nr_art(f, sizeof(pacient))) 
				printf("Depaseste lungimea fisierului");
			else
			{
				fseek(f, (n - 1) * sizeof(pacient), 0);
				fread(&p, sizeof(pacient), 1, f);
				if (p.indicator_stare == 1)
				{
					printf("\n%s || %s || %5d || BOLI PREEXISTENTE %4s || DIABET %4s || BOLI PULMONARE %4s || AFECTIUNI CARDIOVASCULARE %4s || DATA INTERNARII %d.%d.%d \n", p.nume, p.prenume, p.varsta, adevar(p.boli_preexistente), adevar(p.diabetic), adevar(p.boli_pulmonare), adevar(p.afectiuni_cardiovasculare), p.data_internarii.zi, p.data_internarii.luna, p.data_internarii.an);

					switch (optiune)
					{
					case 1:
					{
						printf("Introduceti numele actualizat: ");
						getc(stdin);
						gets_s(nume);
						strcpy(p.nume, nume);
					}
						break;
					case 2:
					{
						printf("Introduceti prenumele actualizat: ");
						getc(stdin);
						gets_s(prenume);
						strcpy(p.prenume, prenume);
					}
						break;
					case 3:
					{
						varsta = p.varsta;
						printf("Introduceti varsta actualizata: ");
						scanf("%d", &varsta);
						p.varsta = varsta;
					}
						break;
					case 4:
					{
						printf("Zi actualizata: ");
						scanf("%d", &zi);
						p.data_internarii.zi = zi;
						printf("Luna actualizata: ");
						scanf("%d", &luna);
						p.data_internarii.luna = luna;
						printf("An actualizat: ");
						scanf("%d", &an);
						p.data_internarii.an = an;
					}
						break;
					case 5:
					{	
						printf("\n(0/1)Diabet: ");
						scanf(" %c",&diabet);
						p.diabetic = diabet;
						printf("\n(0/1)Boli pulmonare: ");
						scanf(" %c", &boli_pulmonare);
						p.boli_pulmonare = boli_pulmonare;
						printf("\n(0/1)Afectiuni cardiovasculare: ");
						scanf(" %c", &boli_cardiovasculare);
						p.afectiuni_cardiovasculare = boli_cardiovasculare;
					}
						break;
					default: printf("Optiune aleasa gresit");
					}

					if ((p.diabetic == '0' && p.boli_pulmonare == '0') && p.afectiuni_cardiovasculare == '0')
						p.boli_preexistente = '0';
					else
						p.boli_preexistente = '1';
					
					printf("\n%s || %s || %5d || BOLI PREEXISTENTE %4s || DIABET %4s || BOLI PULMONARE %4s || AFECTIUNI CARDIOVASCULARE %4s || DATA INTERNARII %d.%d.%d \n", p.nume, p.prenume, p.varsta, adevar(p.boli_preexistente), adevar(p.diabetic), adevar(p.boli_pulmonare), adevar(p.afectiuni_cardiovasculare), p.data_internarii.zi, p.data_internarii.luna, p.data_internarii.an);

					fseek(f, (n - 1) * sizeof(pacient), 0);
					fwrite(&p, sizeof(pacient), 1, f);
				}
				else printf("Inregistrarea nu exista");
			}
			printf("\nn= "); scanf("%d", &n);
		}
		fclose(f);
	}
}

void main()
{ 
//	populare();

//	adaugare();

//	stergere();

//	modificare_pacient();

//	afisare();

//	afisare_vindecati();
}