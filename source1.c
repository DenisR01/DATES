//LISTA DUBLA +S+ARB
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct {
	int cod;
	float salariu;
	char* nume;
	char* functie;
	int vechime;

}Angajat;

typedef struct {
	Angajat* info;
	struct nodLS* prev, * next;
}nodLS;

typedef struct {
	int BF;
	Angajat info;
	struct nodArb* left, * right;
}nodArb;

nodArb* creareNod(Angajat s, nodArb* st, nodArb* dr)
{

	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.cod = s.cod;
	nou->info.salariu = s.salariu;
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);
	nou->info.functie = (char*)malloc((strlen(s.functie) + 1) * sizeof(char));
	strcpy(nou->info.functie, s.functie);
	nou->info.vechime = s.vechime;


	nou->left = NULL;
	nou->right = NULL;
	return nou;
}

nodArb* inserareNod(nodArb* rad, Angajat a) {

	if (rad != NULL)
	{
		if (a.cod < rad->info.cod)
		{
			rad->left = inserareNod(rad->left, a);
			return rad;
		}
		else if (a.cod > rad->info.cod)
		{
			rad->right = inserareNod(rad->right, a);
			return rad;
		}
		else return rad;


	}
	else
	{
		nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
		nou->info = a;
		nou->left = NULL;
		nou->right = NULL;

		return nou;
	}

}

void inordine(nodArb* rad) {
	if (rad != NULL)
	{
		inordine(rad->left);
		printf("\nCod= %d, Nume=%s, Salariu=%f, Functie=%s, Vechime= %d", rad->info.cod, rad->info.nume, rad->info.salariu, rad->info.functie, rad->info.vechime);
		inordine(rad->right);
	}
}
void dezalocareArbore(nodArb* rad) {
	if (rad != NULL)
	{
		nodArb* st = rad->left;
		nodArb* dr = rad->right;
		free(rad->info.nume);
		free(rad->info.functie);
		free(rad);
		dezalocareArbore(st);
		dezalocareArbore(dr);
	}

}
nodLS* inserare(nodLS* cap, nodLS** coada, Angajat* a) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info = (Angajat*)malloc(sizeof(Angajat));
	nou->info->cod = a->cod;
	nou->info->salariu = a->salariu;
	nou->info->functie = a->functie;
	nou->info->vechime = a->vechime;
	nou->info->nume = (char*)malloc((strlen(a->nume) + 1) * sizeof(char));
	strcpy(nou->info->nume, a->nume);
	nou->info->functie = (char*)malloc((strlen(a->functie) + 1) * sizeof(char));
	strcpy(nou->info->functie, a->functie);

	nou->next = NULL;
	nou->prev = NULL;
	if (cap == NULL) {
		cap = nou;
		*coada = nou;
	}
	else {
		nodLS* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
	}
	return cap;

}

void traversare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp != NULL) {
		printf("\n%d %s %s %5.2f %d\n", temp->info->cod, temp->info->nume, temp->info->functie, temp->info->salariu, temp->info->vechime);
		temp = temp->next;
	}
}
void traversareInversa(nodLS* coada) {
	nodLS* temp = coada;
	while (temp != NULL) {
		printf("\n%d %s %s %5.2f %d\n", temp->info->cod, temp->info->nume, temp->info->functie, temp->info->salariu, temp->info->vechime);
		temp = temp->prev;
	}
}

void dezalocareLista(nodLS* cap) {

	nodLS* temp = cap;
	while (temp) {
		nodLS* temp2 = temp->next;
		free(temp->info->nume);
		free(temp->info->functie);
		free(temp);
		temp = temp2;

	}

}
void stergeNodListaDubla(nodLS** prim, struct nodLS** ultim, int cod)
{
	if (*prim)
	{
		if ((*prim)->info->cod == cod)
		{
			nodLS* temp = *prim;
			*prim = (*prim)->next;
			(*prim)->prev = NULL;

			free(temp->info->nume);
			free(temp->info->functie);
			free(temp);
		}
		else
		{
			nodLS* temp = *prim;

			while (temp && temp->info->cod != cod)
				temp = temp->next;

			if (temp)
			{
				nodLS* temp2 = temp->prev;

				//temp->prev->next = temp->next;
				temp2->next = temp->next;

				if (temp->next)
				{
					nodLS* temp4 = temp->next;

					//temp->next->prev = temp->prev;
					temp4->prev = temp->prev;
				}
				else
				{
					*ultim = temp->prev;
				}

				free(temp->info->functie);
				free(temp->info->nume);
				free(temp);
			}
		}
	}

}

nodArb* listaToArbore(nodLS* cap, nodArb* rad)
{
	nodLS* temp = cap;

	while (temp)
	{
		if (temp->info->salariu <= 5000)
			rad = inserareNod(rad, *(temp->info));

		temp = temp->next;
	}

	return rad;
}
void main() {
	int n;
	nodLS* coada = NULL, * cap = NULL;
	Angajat* p;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++) {
		p = (Angajat*)malloc(sizeof(Angajat));
		fscanf(f, "%d", &p->cod);
		fscanf(f, "%f", &p->salariu);
		fscanf(f, "%d", &p->vechime);
		fscanf(f, "%s", buffer);
		p->nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p->nume, buffer);
		fscanf(f, "%s", buffer);
		p->functie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p->functie, buffer);
		cap = inserare(cap, &coada, p);
		free(p->nume);
		free(p->functie);
		free(p);

	}
	traversare(cap);

	printf("---------------STERGERE------------");

	//stergeNodListaDubla(&cap, &coada, 102);
	//traversare(cap);
	printf("\n---------------Arbore------------\n");
	nodArb* rad = NULL;

	rad = listaToArbore(cap, rad);


	inordine(rad);
	//dezalocareArbore(rad);

	//traversare(cap);

	//dezalocareLista(cap);
}


//Chaining
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct {
	char* denumireExamen;
	char* numeStudent;
	char semestru;
	float notaFinala;
	int an;
	int nrMatricol;

}Evaluare;

typedef struct {
	Evaluare info;
	struct nodLS* next;
}nodLS;

typedef struct {
	struct nodLS** vect;
	int dim;
}hashT;

typedef struct {
	int index;
	int nrExamenePromovate;
}Pereche;

int functieDispersie(hashT tabela, char denumireExamen[20]) {

	int x = 0;

	for (int i = 0; i < strlen(denumireExamen); i++)
		x += denumireExamen[i];

	return x % tabela.dim;
}

int inserare(hashT tabela, Evaluare e) {
	int pozitie = 0;
	if (tabela.vect != NULL) {
		pozitie = functieDispersie(tabela, e.denumireExamen);

		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->info.denumireExamen = (char*)malloc((strlen(e.denumireExamen) + 1) * sizeof(char));
		strcpy(nou->info.denumireExamen, e.denumireExamen);
		nou->info.numeStudent = (char*)malloc((strlen(e.numeStudent) + 1) * sizeof(char));
		strcpy(nou->info.numeStudent, e.numeStudent);
		nou->info.semestru = e.semestru;
		nou->info.notaFinala = e.notaFinala;
		nou->info.an = e.an;
		nou->info.nrMatricol = e.nrMatricol;

		nou->next = NULL;

		if (tabela.vect[pozitie] == NULL)
			tabela.vect[pozitie] = nou;
		else {
			nodLS* temp = tabela.vect[pozitie];
			while (temp->next)
				temp = temp->next;
			temp->next = nou;
		}

	}
	return pozitie;

}

void traversareTabela(hashT tabela) {
	if (tabela.vect != NULL) {
		for (int i = 0; i < tabela.dim; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				printf("\nPozitie = %d", i);
				nodLS* temp = tabela.vect[i];
				while (temp)
				{
					printf("\n Examen= %s, Student= %s, Semestru= %d, nota finala= %5.2f, an= %d, nrMatricol= %d ", temp->info.denumireExamen, temp->info.numeStudent, temp->info.semestru, temp->info.notaFinala, temp->info.an, temp->info.nrMatricol);
					temp = temp->next;
				}
			}
		}
	}

}
void dezalocareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.dim; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				nodLS* temp = tabela.vect[i];
				while (temp)
				{
					nodLS* temp2 = temp->next;
					free(temp->info.denumireExamen);
					free(temp->info.numeStudent);
					free(temp);
					temp = temp2;
				}
			}
		}
		free(tabela.vect);
	}
}

Evaluare* getEvaluariByNota(hashT tabela, Evaluare* vector, int* nrElemente, int nota) {
	*nrElemente = 0;

	for (int i = 0; i < tabela.dim; i++) {
		nodLS* temp = tabela.vect[i];

		while (temp) {
			if (temp->info.notaFinala == nota)
				(*nrElemente)++;
			temp = temp->next;
		}
	}
	vector = (Evaluare*)malloc(sizeof(Evaluare) * (*nrElemente));

	int x = 0;
	for (int i = 0; i < tabela.dim; i++)
	{
		nodLS* temp = tabela.vect[i];

		while (temp) {
			if (temp->info.notaFinala == nota) {

				vector[x].denumireExamen = (char*)malloc((strlen(temp->info.denumireExamen) + 1) * sizeof(char));
				strcpy(vector[x].denumireExamen, temp->info.denumireExamen);
				vector[x].numeStudent = (char*)malloc((strlen(temp->info.numeStudent) + 1) * sizeof(char));
				strcpy(vector[x].numeStudent, temp->info.numeStudent);
				vector[x].semestru = temp->info.semestru;
				vector[x].notaFinala = temp->info.notaFinala;
				vector[x].an = temp->info.an;
				vector[x].nrMatricol = temp->info.nrMatricol;
				x++;

			}
			temp = temp->next;
		}
	}
	return vector;
}
void getExamenePromovateByCluster(hashT tabela, Pereche* vector)
{
	for (int i = 0; i < tabela.dim; i++)
	{
		vector[i].index = i;
		vector[i].nrExamenePromovate = 0;

		if (tabela.vect[i])
		{
			int nr = 0;
			nodLS* temp = tabela.vect[i];

			while (temp)
			{
				if (temp->info.notaFinala >= 5)
					nr++;

				temp = temp->next;
			}

			vector[i].nrExamenePromovate = nr;

		}
	}


}
void main() {
	hashT tabela;
	tabela.dim = 101;
	tabela.vect = (nodLS**)malloc(tabela.dim * sizeof(nodLS*));
	for (int i = 0; i < tabela.dim; i++) {
		tabela.vect[i] = NULL;
	}
	char buffer[20];
	int n;
	Evaluare e;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%s", buffer);
		e.denumireExamen = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(e.denumireExamen, buffer);
		fscanf(f, "%s", buffer);
		e.numeStudent = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(e.numeStudent, buffer);
		fscanf(f, "%i", &e.semestru);
		fscanf(f, "%f", &e.notaFinala);
		fscanf(f, "%i", &e.an);
		fscanf(f, "%i", &e.nrMatricol);

		inserare(tabela, e);
		free(e.denumireExamen);
		free(e.numeStudent);

	}
	fclose(f);

	traversareTabela(tabela);

	Evaluare* vectorEvaluari = NULL;
	int nrElemente;
	vectorEvaluari = getEvaluariByNota(tabela, vectorEvaluari, &nrElemente, 10);
	printf("\n");

	for (int i = 0; i < nrElemente; i++) {
		printf("%d %s %s %1.f %d %d\n", vectorEvaluari[i].nrMatricol, vectorEvaluari[i].denumireExamen, vectorEvaluari[i].numeStudent, vectorEvaluari[i].notaFinala, vectorEvaluari[i].an, vectorEvaluari[i].semestru);
	}

	printf("\n\n");

	Pereche* vector = (Pereche*)malloc(tabela.dim * sizeof(Pereche));

	int dimPerechi = tabela.dim;

	getExamenePromovateByCluster(tabela, vector);

	printf("Clustere si numar examene promovate pe fiecare [CELE AFISATE NU AU EXAMENE SAU NU AU EXAMENE PROMOVATE]\n");

	for (int i = 0; i < dimPerechi; i++)
		if (vector[i].nrExamenePromovate)
			printf("Cluster: %d ----- nr. examene promovate: %d\n", vector[i].index, vector[i].nrExamenePromovate);

	//traversareTabela(tabela);
	//dezalocareTabela(tabela);


}


//ListaSimpla
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>


typedef struct {
	int codProdus;
	char* denumirePreparat;
	float pret;
	int nrIngrediente;

}preparat;


typedef struct {
	preparat* info;
	struct nodLS* next;
}nodLS;

void afisarePreparat(preparat p)
{
	printf("%d %s %f %d\n", p.codProdus, p.denumirePreparat, p.pret, p.nrIngrediente);
}

nodLS* inserare(nodLS* cap, preparat p) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info->codProdus = p.codProdus;
	nou->info->denumirePreparat = (char*)malloc((strlen(p.denumirePreparat) + 1) * sizeof(char));
	strcpy(nou->info->denumirePreparat, p.denumirePreparat);
	nou->info->pret = p.pret;
	nou->info->nrIngrediente = p.nrIngrediente;

	nou->next = NULL;

	if (cap == NULL) {
		cap = nou;
	}
	else
	{
		nodLS* aux = cap;

		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;

	}

	return cap;
}


void traversare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("\nCod: %d , Denumire: %s , Pret: %5.2f , NrIngrediente: %d \n", temp->info->codProdus, temp->info->denumirePreparat, temp->info->pret, temp->info->nrIngrediente);
		temp = temp->next;
	}
}

void dezalocare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		nodLS* temp2 = temp->next;
		free(temp->info->denumirePreparat);
		free(temp);
		temp = temp2;
	}
}

//
nodLS* stergere_nod(nodLS* list, int cod)  //PENTRU SABIN!!!!
{
	//extras->denumirePreparat = NULL;
	if (list)
	{

		if (list->info->codProdus == cod) // nodul sters este primul in lista
		{
			//*extras = list->info;
			nodLS* t = list;
			list = list->next;
			free(t->info->denumirePreparat);
			free(t);
		}
		else
		{
			nodLS* t = list;
			nodLS* temp = list->next;


			while (temp != NULL && temp->info->codProdus != cod) {
				temp = temp->next;
			}

			if (temp)
			{
				nodLS* aux = temp->next; // asta trebuie sters
				temp->next = aux->next;

				free(aux->info->denumirePreparat);
				free(aux);

			}
		}
	}

	return list;
}




void main() {
	nodLS* cap = NULL;
	preparat p;
	int  n;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &p.codProdus);
		fscanf(f, "%s", buffer);
		p.denumirePreparat = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumirePreparat, buffer);
		fscanf(f, "%f", &p.pret);
		fscanf(f, "%d", &p.nrIngrediente);

		cap = inserare(cap, p);


	}
	fclose(f);

	//traversare(cap);


	//stergere_nod(cap, 1);

	//dezalocare(cap);

}


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>


typedef struct {
	int codProdus;
	char* denumirePreparat;
	float pret;
	int nrIngrediente;

}preparat;


typedef struct {
	preparat* info;
	struct nodLS* next;
}nodLS;

void afisarePreparat(preparat p)
{
	printf("%d %s %f %d\n", p.codProdus, p.denumirePreparat, p.pret, p.nrIngrediente);
}

preparat* deepCopy(preparat p)
{
	preparat* copie = (preparat*)malloc(sizeof(preparat));
	(*copie).codProdus = p.codProdus;
	(*copie).nrIngrediente = p.nrIngrediente;
	(*copie).pret = p.pret;
	(*copie).denumirePreparat = (char*)malloc(strlen(p.denumirePreparat) + 1);
	strcpy((*copie).denumirePreparat, p.denumirePreparat);

	return copie;
}
nodLS* inserare(nodLS* cap, preparat p) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	/*nou->info->codProdus = p.codProdus;
	nou->info->denumirePreparat = (char*)malloc((strlen(p.denumirePreparat) + 1) * sizeof(char));
	strcpy(nou->info->denumirePreparat, p.denumirePreparat);
	nou->info->pret = p.pret;
	nou->info->nrIngrediente = p.nrIngrediente;*/
	nou->info = deepCopy(p);

	nou->next = NULL;

	if (cap == NULL) {
		cap = nou;
	}
	else
	{
		nodLS* aux = cap;

		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;

	}

	return cap;
}


void traversare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("\nCod: %d , Denumire: %s , Pret: %5.2f , NrIngrediente: %d \n", temp->info->codProdus, temp->info->denumirePreparat, temp->info->pret, temp->info->nrIngrediente);
		temp = temp->next;
	}
}

void dezalocare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		nodLS* temp2 = temp->next;
		free(temp->info->denumirePreparat);
		free(temp);
		temp = temp2;
	}
}
void stergere(nodLS* cap, int cod) {
	nodLS* temp = cap;
	while (temp && temp->info->codProdus != cod) {
		temp = temp->next;
	}
	if (temp->info->codProdus == cod && temp != NULL) {
		nodLS* temp2 = temp->next;
		free(temp->info->denumirePreparat);
		free(temp);
		temp = temp2;
	}
}
//
nodLS* stergere_nod(nodLS* list, int cod)  //PENTRU SABIN!!!!
{
	//extras->denumirePreparat = NULL;
	if (list)
	{

		if (list->info->codProdus == cod) // nodul sters este primul in lista
		{
			//*extras = list->info;
			nodLS* t = list;
			list = list->next;
			free(t->info->denumirePreparat);
			free(t);
		}
		else
		{
			nodLS* t = list;
			nodLS* temp = list->next;


			while (t->next != NULL && temp->info->codProdus != cod) {
				t = t->next;
				temp = temp->next;
			}

			if (t->next)
			{

				nodLS* x = t->next;
				t->next = x->next;

				free(x->info->denumirePreparat);
				free(x);

			}
		}
	}

	return list;
}




void main() {
	nodLS* cap = NULL;
	int  n;
	char buffer[20];
	preparat p;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++) {

		fscanf(f, "%d", &p.codProdus);
		fscanf(f, "%s", buffer);
		p.denumirePreparat = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumirePreparat, buffer);
		fscanf(f, "%f", &p.pret);
		fscanf(f, "%d", &p.nrIngrediente);

		cap = inserare(cap, p);


	}
	fclose(f);

	traversare(cap);


	cap = stergere_nod(cap, 4);

	traversare(cap);

	//dezalocare(cap);

}


//ARBORE ABC


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct
{
	int cod;
	char* nume;
	float medie;
} student;

//structura nodului include si gradul de echilibru (BF)
typedef struct
{
	int BF;
	student inf;
	struct nodarb* left, * right;
} nodarb;

//functie pentru initializarea unui nod
nodarb* creare(student s, nodarb* st, nodarb* dr)
{
	nodarb* nou = (nodarb*)malloc(sizeof(nodarb));
	nou->inf.cod = s.cod;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->left = st;
	nou->right = dr;
	return nou;
}

//functie de inserare nod in arbore binar de cautare
nodarb* inserareNod(student s, nodarb* rad)
{
	if (rad != NULL)
	{
		if (s.cod < rad->inf.cod)
		{
			rad->left = inserareNod(s, rad->left);
			return rad;
		}
		else
			if (s.cod > rad->inf.cod)
			{
				rad->right = inserareNod(s, rad->right);
				return rad;
			}
			else
				return rad;
	}
	else
		return creare(s, NULL, NULL);
}

//functie de traversare preordine
void preordine(nodarb* rad)
{
	if (rad != NULL)
	{
		printf("\nCod=%d, Nume=%s, Medie=%5.2f, BF=%d", rad->inf.cod, rad->inf.nume, rad->inf.medie, rad->BF);
		preordine(rad->left);
		preordine(rad->right);
	}
}

//functie de traversare inordine
void inordine(nodarb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->left);
		printf("\nCod=%d, Nume=%s, Medie=%5.2f, BF=%d", rad->inf.cod, rad->inf.nume, rad->inf.medie, rad->BF);
		inordine(rad->right);
	}
}

//functie de traversare postordine
void postordine(nodarb* rad)
{
	if (rad != NULL)
	{
		postordine(rad->left);
		postordine(rad->right);
		printf("\nCod=%d, Nume=%s, Medie=%5.2f, BF=%d", rad->inf.cod, rad->inf.nume, rad->inf.medie, rad->BF);
	}
}

//functie de dezalocare arbore
void dezalocare(nodarb* rad)
{
	if (rad != NULL)
	{
		nodarb* st = rad->left;
		nodarb* dr = rad->right;
		free(rad->inf.nume);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}

int maxim(int a, int b)
{
	int max = a;
	if (max < b)
		max = b;
	return max;
}

//functie pentru calcul inaltime arbore
int nrNiveluri(nodarb* rad)
{
	if (rad != NULL)
		return 1 + maxim(nrNiveluri(rad->left), nrNiveluri(rad->right));
	else
		return 0;
}

//functie pentru initializare grad de echilibru la nivelul fiecarui nod
void calculBF(nodarb* rad)
{
	if (rad != NULL)
	{
		rad->BF = nrNiveluri(rad->right) - nrNiveluri(rad->left);
		calculBF(rad->left);
		calculBF(rad->right);
	}
}

//functie pentru implementare rotatie dreapta
nodarb* rotatie_dreapta(nodarb* rad)
{
	printf("\nRotatie dreapta\n");
	nodarb* nod1 = rad->left;
	rad->left = nod1->right;
	nod1->right = rad;
	rad = nod1;
	return rad;
}

//functie pentru implementare rotatie stanga
nodarb* rotatie_stanga(nodarb* rad)
{
	printf("\nRotatie stanga\n");
	nodarb* nod1 = rad->right;
	rad->right = nod1->left;
	nod1->left = rad;
	rad = nod1;
	return rad;
}

//functie pentru implementare rotatie dreapta-stanga
nodarb* rotatie_dreapta_stanga(nodarb* rad)
{
	printf("\nRotatie dreapta-stanga\n");
	nodarb* nod1 = rad->right;
	nodarb* nod2 = nod1->left;
	nod1->left = nod2->right;
	nod2->right = nod1;
	rad->right = nod2->left;
	nod2->left = rad;
	rad = nod2;
	return rad;
}

//functie pentru implementare rotatie stanga-dreapta
nodarb* rotatie_stanga_dreapta(nodarb* rad)
{
	printf("\nRotatie stanga-dreapta\n");
	nodarb* nod1 = rad->left;
	nodarb* nod2 = nod1->right;
	nod1->right = nod2->left;
	nod2->left = nod1;
	rad->left = nod2->right;
	nod2->right = rad;
	rad = nod2;
	return rad;
}

//functie pentru reechilibrare arbore in situatia aplicarii celor 4 rotatii
nodarb* reechilibrare(nodarb* rad)
{
	calculBF(rad);
	nodarb* stanga = rad->left;
	nodarb* dreapta = rad->right;
	if (rad->BF <= -2 && stanga->BF <= -1)
	{
		rad = rotatie_dreapta(rad);
		calculBF(rad);
	}
	else
		if (rad->BF >= 2 && dreapta->BF >= 1)
		{
			rad = rotatie_stanga(rad);
			calculBF(rad);
		}
		else
			if (rad->BF >= 2 && dreapta->BF <= -1)
			{
				rad = rotatie_dreapta_stanga(rad);
				calculBF(rad);
			}
			else
				if (rad->BF <= -2 && stanga->BF >= 1)
				{
					rad = rotatie_stanga_dreapta(rad);
					calculBF(rad);
				}
	return rad;
}

void main()
{
	int n;
	FILE* f = fopen("fisier.txt", "r");

	fscanf(f, "%d", &n);

	nodarb* rad = NULL;
	student s;
	char buffer[20];

	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &s.cod);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);

		rad = inserareNod(s, rad);

		rad = reechilibrare(rad);
	}
	fclose(f);

	inordine(rad);
	printf("\n------------------------\n");
	inordine(rad->left);
	printf("\n------------------------\n");
	inordine(rad->right);
	printf("\n------------------------\n");

	printf("\nInaltime arbore este %d", nrNiveluri(rad));
	printf("\nInaltime subarbore stang este %d", nrNiveluri(rad->left));
	printf("\nInaltime subarbore drept este %d", nrNiveluri(rad->right));

	dezalocare(rad);
}


//ABC SPECTACOL

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct {
	int idSpectacol;
	float pretBilet;
	char* numeClient;
	char dataSustinere[10];
	int durata;
	int locuri;

}Spectacol;

typedef struct {
	int BF;
	Spectacol info;
	struct nodArb* left, * right;
}nodArb;

typedef struct
{
	char* numeClient;
	float costTotal;
} Pereche;

nodArb* creareNod(Spectacol s, nodArb* st, nodArb* dr)
{
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.idSpectacol = s.idSpectacol;
	nou->info.pretBilet = s.pretBilet;
	nou->info.numeClient = (char*)malloc((strlen(s.numeClient) + 1) * sizeof(char));
	strcpy(nou->info.numeClient, s.numeClient);
	strcpy(nou->info.dataSustinere, s.dataSustinere);
	nou->info.durata = s.durata;
	nou->info.locuri = s.locuri;

	nou->left = NULL;
	nou->right = NULL;
	return nou;

}
nodArb* inserareNod(Spectacol s, nodArb* rad)
{
	if (rad != NULL)
	{
		if (s.idSpectacol < rad->info.idSpectacol) {
			rad->left = inserareNod(s, rad->left);
			return rad;
		}
		else {
			if (s.idSpectacol > rad->info.idSpectacol) {
				rad->right = inserareNod(s, rad->right);
				return rad;
			}
			else
				return rad;
		}
	}
	else
		return creareNod(s, NULL, NULL);
}
void preordine(nodArb* rad) {
	if (rad != NULL) {
		printf("\nidSpectacol= %d, Client=%s, pret bilet=%f, data=%s, durata= %d, nrLocuri=%d ", rad->info.idSpectacol, rad->info.numeClient, rad->info.pretBilet, rad->info.dataSustinere, rad->info.durata, rad->info.locuri);
		preordine(rad->left);
		preordine(rad->right);
	}
}
void inordine(nodArb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->left);
		printf("\nidSpectacol= %d, Client=%s, pret bilet=%f, data=%s, durata= %d, nrLocuri=%d ", rad->info.idSpectacol, rad->info.numeClient, rad->info.pretBilet, rad->info.dataSustinere, rad->info.durata, rad->info.locuri);
		inordine(rad->right);
	}
}

void dezalocare(nodArb* rad) {
	if (rad != NULL)
	{
		nodArb* st = rad->left;
		nodArb* dr = rad->right;
		free(rad->info.numeClient);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}

void getClienti(nodArb* rad, Pereche* vect, int* dimPerechi) {
	if (rad)
	{
		int check = 0;
		int index = 0;

		while (index < *dimPerechi)
		{
			if (strcmp(vect[index].numeClient, rad->info.numeClient) == 0)
			{
				vect[index].costTotal += rad->info.pretBilet;
				check = 1;
				break;
			}

			index++;
		}

		if (check == 0)
		{
			strcpy(vect[*dimPerechi].numeClient, rad->info.numeClient);
			vect[*dimPerechi].costTotal = rad->info.pretBilet;
			(*dimPerechi)++;
		}


		getClienti(rad->left, vect, dimPerechi);
		getClienti(rad->right, vect, dimPerechi);
	}


}
void  determinare(nodArb* rad, Spectacol* vect, int* nr, char data[]) {

	if (rad != NULL) {

		if (strcmp(data, rad->info.dataSustinere) == 0) {


			vect[*nr].idSpectacol = rad->info.idSpectacol;
			vect[*nr].pretBilet = rad->info.pretBilet;
			vect[*nr].numeClient = (char*)malloc((strlen(rad->info.numeClient) + 1) * sizeof(char));
			strcpy(vect[*nr].numeClient, rad->info.numeClient);
			strcpy(vect[*nr].dataSustinere, rad->info.dataSustinere);
			vect[*nr].durata = rad->info.durata;
			vect[*nr].locuri = rad->info.locuri;
			(*nr)++;
		}
		determinare(rad->left, vect, nr, data);
		determinare(rad->right, vect, nr, data);

	}

}

void getSpectacoleByDate(nodArb* rad, Spectacol* vector, int* dim, char* dataSpec)
{
	if (rad)
	{
		if (strcmp(rad->info.dataSustinere, dataSpec) == 0) {
			vector[(*dim)++].idSpectacol = rad->info.idSpectacol;
			vector[(*dim)++].idSpectacol = rad->info.locuri;
			vector[(*dim)++].idSpectacol = rad->info.durata;
			vector[(*dim)++].idSpectacol = rad->info.pretBilet;
			vector[(*dim)++].numeClient = (char*)malloc((strlen(rad->info.numeClient) + 1) * sizeof(char));
			strcpy(vector[(*dim)++].numeClient, rad->info.numeClient);
			strcpy(vector[(*dim)++].dataSustinere, rad->info.dataSustinere);
		}
		getSpectacoleByDate(rad->left, vector, dim, dataSpec);
		getSpectacoleByDate(rad->right, vector, dim, dataSpec);

	}
}

void getNumeClienti(nodArb* rad, char** names, int* dim)
{
	if (rad)
	{
		names[*dim] = (char*)malloc(strlen(rad->info.numeClient) + 1);
		strcpy(names[*dim], rad->info.numeClient);

		(*dim)++;

		getNumeClienti(rad->left, names, dim);
		getNumeClienti(rad->right, names, dim);

	}
}

void main()
{
	int n;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	nodArb* rad = NULL;
	Spectacol s;
	char buffer[20];
	char buffer2[10];
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &s.idSpectacol);
		fscanf(f, "%f", &s.pretBilet);
		fscanf(f, "%s", buffer2);
		s.numeClient = (char*)malloc((strlen(buffer2) + 1) * sizeof(char));
		strcpy(s.numeClient, buffer2);
		fscanf(f, "%s", buffer);
		strcpy(s.dataSustinere, buffer);
		fscanf(f, "%d", &s.durata);
		fscanf(f, "%d", &s.locuri);
		rad = inserareNod(s, rad);
	}
	fclose(f);
	//inordine(rad);
	char data[10] = "10.03.2022";
	int nr = 0;
	Spectacol* vector = (Spectacol*)malloc(n * sizeof(Spectacol));
	//determinare(rad, vector, &nr, "10.03.2020");
	//getSpectacoleByDate(rad, vector, &nr, "10.03.2020");

	for (int i = 0; i < nr; i++) {
		printf("%d %f %s %s %d %d", vector[i].idSpectacol, vector[i].pretBilet, vector[i].dataSustinere, vector[i].numeClient, vector[i].durata, vector[i].locuri);
	}

	for (int i = 0; i < nr; i++) {
		free(vector[i].numeClient);
	}
	free(vector);



	char** names = (char**)malloc(sizeof(char*) * n);
	int dimClienti = 0;
	getNumeClienti(rad, names, &dimClienti);


	Pereche* p = (Pereche*)malloc(sizeof(Pereche) * dimClienti);

	for (int i = 0; i < dimClienti; i++)
	{
		p[i].costTotal = 0;
		p[i].numeClient = (char*)malloc(strlen(names[i]) + 1);
		strcpy(p[i].numeClient, names[i]);
	}

	printf("--------------Costuri Totale----------\n");

	int x = 0;
	getClienti(rad, p, &x);

	for (int i = 0; i < x; i++) {
		printf("%s %f\n", p[i].numeClient, p[i].costTotal);
	}
	//preordine(rad);
	//inordine(rad);
	//dezalocare(rad);



}
















//Linear Probing

#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int cod;
	char* nume;
	float medie;
} student;

typedef struct
{
	student** vect;
	int size;
} hashT;

int functieHash(int cheie, hashT tabela)
{
	return cheie % tabela.size;
}

int inserare(hashT tabela, student* s)
{
	int pozitie;
	if (tabela.vect != NULL)
	{
		pozitie = functieHash((*s).cod, tabela);
		if (tabela.vect[pozitie] == NULL)
			tabela.vect[pozitie] = s;
		else
		{
			int index = 1;
			while (pozitie + index < tabela.size)
			{
				if (tabela.vect[pozitie + index] == NULL)
				{
					tabela.vect[pozitie + index] = s;
					pozitie += index;
					break;
				}
				index++;
			}
		}
	}
	return pozitie;
}

int stergere(hashT tabela, int cod)
{
	int pozitie;
	if (tabela.vect != NULL)
	{
		pozitie = functieHash(cod, tabela);
		if (tabela.vect[pozitie] == NULL)
			return -1;
		else
			if (tabela.vect[pozitie]->cod == cod)
			{
				free(tabela.vect[pozitie]->nume);
				free(tabela.vect[pozitie]);
				tabela.vect[pozitie] = NULL;
			}
			else
			{
				int index = 1;
				while (pozitie + index < tabela.size)
				{
					if (tabela.vect[pozitie + index]->cod == cod)
					{
						pozitie += index;
						free(tabela.vect[pozitie]->nume);
						free(tabela.vect[pozitie]);
						tabela.vect[pozitie] = NULL;
						break;
					}
					index++;
				}
			}

	}
	return pozitie;
}

void traversare(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.size; i++)
			if (tabela.vect[i] != NULL)
			{
				printf("\nPozitie = %d", i);
				printf("\nCod=%d, Nume=%s, Medie=%5.2f",
					tabela.vect[i]->cod, tabela.vect[i]->nume, tabela.vect[i]->medie);
			}
	}
}

void dezalocare(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.size; i++)
			if (tabela.vect[i] != NULL)
			{
				free(tabela.vect[i]->nume);
				free(tabela.vect[i]);
			}
		free(tabela.vect);
	}
}

void main()
{
	hashT tabela;
	tabela.size = 101;
	tabela.vect = (student**)malloc(tabela.size * sizeof(student*));
	for (int i = 0; i < tabela.size; i++)
		tabela.vect[i] = NULL;

	int n;
	/*printf("Nr. studenti=");
	scanf("%d", &n);
	student* s;
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		s = (student*)malloc(sizeof(student));
		printf("\nCod=");
		scanf("%d", &s->cod);
		printf("\nNume=");
		scanf("%s", buffer);
		s->nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s->nume, buffer);
		printf("\nMedie=");
		scanf("%f", &s->medie);

		inserare(tabela, s);
	}*/
	FILE* f = fopen("fisier.txt", "r");
	student* s;
	char buffer[20];
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		s = (student*)malloc(sizeof(student));
		fscanf(f, "%d", &s->cod);
		fscanf(f, "%s", buffer);
		s->nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s->nume, buffer);
		fscanf(f, "%f", &s->medie);
		inserare(tabela, s);
	}
	fclose(f);

	traversare(tabela);

	stergere(tabela, 405);

	printf("\n------dupa stergere-------");

	traversare(tabela);

	dezalocare(tabela);
}

// GRAF


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int id;
	char* denumire;
	int nrLocuitori;
} oras;

typedef struct
{
	int inf;
	struct nodStiva* next;
} nodStiva;

typedef struct
{
	int inf;
	struct nodCoada* next;
} nodCoada;

typedef struct
{
	int idNodStart, idNodFinal, greutateArc;
	struct nodLista* next;
} nodLista;

void push(nodStiva** varf, int val)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf = val;
	nou->next = NULL;
	if (*varf == NULL)
	{
		*varf = nou;
	}
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

int pop(nodStiva** varf, int* val)
{
	if (*varf == NULL)
		return 0;
	else
	{
		*val = (*varf)->inf;
		nodStiva* aux = *varf;
		*varf = (*varf)->next;
		free(aux);
		return 1;
	}
}

void put(nodCoada** prim, nodCoada** ultim, int val)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf = val;
	nou->next = NULL;
	if (*prim == NULL || *ultim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	else
	{
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

int get(nodCoada** prim, nodCoada** ultim, int* val)
{
	if (*prim != NULL && *ultim != NULL)
	{
		*val = (*prim)->inf;
		nodCoada* aux = *prim;
		*prim = (*prim)->next;
		free(aux);
		return 0;
	}
	if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
}

void parcurgereAdancime(int** mat, int* vizitat,
	oras* vect, int nrNoduri, int idNodStart)
{
	for (int i = 0; i < nrNoduri; i++)
		vizitat[i] = 0;

	nodStiva* varf = NULL;

	push(&varf, idNodStart);
	vizitat[idNodStart] = 1;
	while (varf != NULL)
	{
		pop(&varf, &idNodStart);
		printf("%d %s %d\n", idNodStart + 1,
			vect[idNodStart].denumire, vect[idNodStart].nrLocuitori);
		for (int k = 0; k < nrNoduri; k++)
			if (mat[idNodStart][k] != 0 && vizitat[k] == 0)
			{
				push(&varf, k);
				vizitat[k] = 1;
			}
	}
}

void parcurgereLatime(int** mat, int* vizitat,
	oras* vect, int nrNoduri, int idNodStart)
{
	for (int i = 0; i < nrNoduri; i++)
		vizitat[i] = 0;

	nodCoada* prim = NULL, * ultim = NULL;

	put(&prim, &ultim, idNodStart);
	vizitat[idNodStart] = 1;
	while (prim != NULL)
	{
		get(&prim, &ultim, &idNodStart);
		printf("%d %s %d\n", idNodStart + 1,
			vect[idNodStart].denumire, vect[idNodStart].nrLocuitori);
		for (int k = 0; k < nrNoduri; k++)
			if (mat[idNodStart][k] != 0 && vizitat[k] == 0)
			{
				put(&prim, &ultim, k);
				vizitat[k] = 1;
			}
	}
}

nodLista* inserareLista(nodLista* cap, int nodStart, int nodFinal, int greutate)
{
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->idNodStart = nodStart;
	nou->idNodFinal = nodFinal;
	nou->greutateArc = greutate;
	nou->next = NULL;
	if (cap == NULL)
		cap = nou;
	else
	{
		nodLista* temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;
}

void afisareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		printf("(%d-%d-%d) ->", temp->idNodStart, temp->idNodFinal, temp->greutateArc);
		temp = temp->next;
	}
}

void dezalocareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		nodLista* temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}

nodLista* transformListaArce(nodLista* cap, int** mat, int nr)
{
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nr; j++)
			if (mat[i][j] != 0)
			{
				cap = inserareLista(cap, i + 1, j + 1, mat[i][j]);
			}
	return cap;
}

void main()
{
	FILE* f = fopen("fisier.txt", "r");
	int nrNoduri;
	fscanf(f, "%d", &nrNoduri);
	oras* vect = (oras*)malloc(nrNoduri * sizeof(oras));
	char buffer[20];
	for (int i = 0; i < nrNoduri; i++)
	{
		fscanf(f, "%d", &vect[i].id);
		fscanf(f, "%s", buffer);
		vect[i].denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(vect[i].denumire, buffer);
		fscanf(f, "%d", &vect[i].nrLocuitori);
	}

	int** mat = (int**)malloc(nrNoduri * sizeof(int*));
	for (int i = 0; i < nrNoduri; i++)
		mat[i] = (int*)malloc(nrNoduri * sizeof(int));

	for (int i = 0; i < nrNoduri; i++)
		for (int j = 0; j < nrNoduri; j++)
			mat[i][j] = 0;

	int ii, jj, nrArce, greutate;
	fscanf(f, "%d", &nrArce);
	for (int i = 0; i < nrArce; i++)
	{
		fscanf(f, "%d", &ii);
		fscanf(f, "%d", &jj);
		fscanf(f, "%d", &greutate);
		if (ii <= nrNoduri && jj <= nrNoduri)
		{
			mat[ii - 1][jj - 1] = greutate;
			//mat[jj - 1][ii - 1] = greutate;
		}
	}
	fclose(f);

	printf("\nMatrice de adiacenta:\n");
	for (int i = 0; i < nrNoduri; i++)
	{
		for (int j = 0; j < nrNoduri; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}

	nodLista* cap = NULL;
	cap = transformListaArce(cap, mat, nrNoduri);
	afisareLista(cap);
	dezalocareLista(cap);

	int* vizitat = (int*)malloc(nrNoduri * sizeof(int));

	printf("\nNod pornire traversare adancime: ");
	int nodStart;
	scanf("%d", &nodStart);
	parcurgereAdancime(mat, vizitat, vect, nrNoduri, nodStart);

	printf("Nod pornire traversare latime: ");
	scanf("%d", &nodStart);
	parcurgereLatime(mat, vizitat, vect, nrNoduri, nodStart);
}
