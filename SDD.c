//Lista Simpla
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include <malloc.h>


typedef struct Masina {
	int cod;
	char* marca;
	float pret;
}Masina;
typedef struct nodLS {
	Masina info;
	struct nodLS* next;
}nodLS;

typedef struct nodArb {
	Masina info;
	struct nodArb* left, * right;
}nodArb;

nodArb* creareNod(Masina m, nodArb* st, nodArb* dr) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.cod = m.cod;
	nou->info.marca = (char*)malloc(strlen(m.marca) + 1);
	strcpy(nou->info.marca, m.marca);
	nou->info.pret = m.pret;

	nou->left = st;
	nou->right = dr;
	return nou;
}
nodArb* inserareArbore(nodArb* rad, Masina m) {
	if (rad != NULL) {
		if (m.cod < rad->info.cod) {
			rad->left = inserareArbore(rad->left, m);
			return rad;
		}
		else
			if (m.cod > rad->info.cod) {
				rad->right = inserareArbore(rad->right, m);
				return rad;
			}
			else return rad;

	}
	else return creareNod(m, NULL, NULL);
}
void preordine(nodArb* rad) {
	if (rad != NULL) {
		printf("\n%d %s %f", rad->info.cod, rad->info.marca, rad->info.pret);
		preordine(rad->left);
		preordine(rad->right);

	}
}
void dezalocareArbore(nodArb* rad) {
	if (rad != NULL) {
		nodArb* st = rad->left;
		nodArb* dr = rad->right;
		free(rad->info.marca);
		free(rad);
		dezalocareArbore(st);
		dezalocareArbore(dr);
	}

}

nodArb* ListToArb(nodArb* rad, nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		rad = inserareArbore(rad, temp->info);
		temp = temp->next;
	}
	return rad;
}
nodLS* inserare(nodLS* cap, Masina m) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.cod = m.cod;
	nou->info.marca = (char*)malloc(strlen(m.marca) + 1);
	strcpy(nou->info.marca, m.marca);
	nou->info.pret = m.pret;

	nou->next = NULL;

	if (cap == NULL)
		cap = nou;
	else {
		nodLS* temp = cap;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = nou;
	}
	return cap;
}

void traversare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("\n%d %s %f", temp->info.cod, temp->info.marca, temp->info.pret);
		temp = temp->next;
	}
}

void dezalocare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		nodLS* temp2 = temp->next;
		free(temp->info.marca);
		free(temp);
		temp = temp2;
	}

}
nodLS* stergereNod(nodLS* cap, float pret) {
	if (cap != NULL && cap->info.pret == pret) {
		nodLS* temp = cap;
		cap = cap->next;
		free(temp->info.marca);
		free(temp);
	}
	else {
		nodLS* temp = cap;
		while (temp->next && temp->next->info.pret != pret) {
			temp = temp->next;
		}

		if (temp->next) {
			nodLS* deSters = temp->next;
			temp->next = deSters->next;
			free(deSters->info.marca);
			free(deSters);
		}
	}
	return cap;
}

int numarNoduriCautate(nodLS* cap, float pret) {
	int nr = 0;
	nodLS* temp = cap;
	while (temp) {
		if (temp->info.pret == pret)
			nr++;
		temp = temp->next;
	}
	return nr;
}

nodLS* stergereMultipla(nodLS* cap, float pret) {
	int nr = numarNoduriCautate(cap, pret);
	for (int i = 0; i < nr; i++)
		cap = stergereNod(cap, pret);
	return cap;
}


Masina* ListToVect(nodLS* cap, Masina* vector, int* nr) {
	nodLS* temp = cap;
	while (temp) {
		vector[*nr].cod = temp->info.cod;
		vector[*nr].marca = (char*)malloc(strlen(temp->info.marca) + 1);
		strcpy(vector[*nr].marca, temp->info.marca);
		vector[*nr].pret = temp->info.pret;
		(*nr)++;
		temp = temp->next;
	}
	return vector;
}
void main() {
	int n;
	char buffer[20];
	Masina m;

	nodLS* cap = NULL;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &m.cod);
		fscanf(f, "%s", buffer);
		m.marca = (char*)malloc(strlen(buffer) + 1);
		strcpy(m.marca, buffer);
		fscanf(f, "%f", &m.pret);
		cap = inserare(cap, m);
		free(m.marca);

	}
	fclose(f);
	traversare(cap);
	//cap = stergereMultipla(cap, 30000);
	//traversare(cap);
	dezalocare(cap);
	printf("\n----------\n");
	printf("\n----------\n");
	nodArb* rad = NULL;
	rad = ListToArb(rad, cap);
	preordine(rad);
	printf("\n----------\n");
	printf("\n----------\n");
	int nr = 0;
	Masina* vector = (Masina*)malloc(sizeof(Masina) * n);
	vector = ListToVect(cap, vector, &nr);
	for (int i = 0; i < nr; i++)
		printf("\n %d %s %f", vector[i].cod, vector[i].marca, vector[i].pret);
	dezalocare(cap);
}

//Lista Dubla

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct Masina {
	int cod;
	char* marca;
	float pret;
}Masina;

typedef struct nodLS {
	Masina info;
	struct nodLS* prev, * next;
}nodLS;

typedef struct heap {
	Masina* vect;
	int dim;
}heap;

void filtrare(heap h, int index) {
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.dim && h.vect[indexSt].pret < h.vect[indexRad].pret)
		indexRad = indexSt;

	if (indexDr < h.dim && h.vect[indexDr].pret < h.vect[indexRad].pret)
		indexRad = indexDr;

	if (indexRad != index) {
		Masina temp = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = temp;

		filtrare(h, indexRad);
	}

}

heap inserareHeap(heap h, Masina m) {
	Masina* vectNou = (Masina*)malloc(sizeof(Masina) * (h.dim + 1));
	for (int i = 0; i < h.dim; i++)
		vectNou[i] = h.vect[i];
	vectNou[h.dim].cod = m.cod;
	vectNou[h.dim].pret = m.pret;
	vectNou[h.dim].marca = (char*)malloc(strlen(m.marca) + 1);
	strcpy(vectNou[h.dim].marca, m.marca);

	free(h.vect);
	(h.dim)++;
	h.vect = vectNou;

	for (int i = (h.dim - 1) / 2; i >= 0; i--)
		filtrare(h, i);

	return h;
}

heap StergereElement(heap h, Masina m) {
	Masina* vectNou = (Masina*)malloc(sizeof(Masina) * (h.dim - 1));
	Masina temp = h.vect[0];
	h.vect[0] = h.vect[h.dim - 1];
	h.vect[h.dim - 1] = temp;

	for (int i = 0; i < h.dim - 1; i++)
		vectNou[i] = h.vect[i];

	free(h.vect[h.dim - 1].marca);
	free(h.vect);
	(h.dim)--;
	h.vect = vectNou;



	for (int i = (h.dim - 1) / 2; i >= 0; i--)
		filtrare(h, i);

	return h;
}

heap conversieLDtoHeap(nodLS* cap, heap h, int* nr) {
	nodLS* temp = cap;

	while (temp) {
		h.vect[*nr].cod = temp->info.cod;
		h.vect[*nr].pret = temp->info.pret;
		h.vect[*nr].marca = (char*)malloc(strlen(temp->info.marca) + 1);
		strcpy(h.vect[*nr].marca, temp->info.marca);
		(*nr)++;
		temp = temp->next;
	}
	return h;
}

void AfisareHeap(heap h) {
	for (int i = 0; i < h.dim; i++) {
		printf("\n%d %s %f", h.vect[i].cod, h.vect[i].marca, h.vect[i].pret);
	}
}
nodLS* inserare(nodLS* cap, nodLS** coada, Masina m) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.cod = m.cod;
	nou->info.marca = (char*)malloc(strlen(m.marca) + 1);
	strcpy(nou->info.marca, m.marca);
	nou->info.pret = m.pret;

	nou->next = NULL;
	nou->prev = NULL;

	if (cap == NULL) {
		cap = nou;
		*coada = nou;
	}
	else {
		nodLS* temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;

	}
	return cap;
}

void traversare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("\n%d %s %f", temp->info.cod, temp->info.marca, temp->info.pret);
		temp = temp->next;
	}


}
void traversareInversa(nodLS* coada) {
	nodLS* temp = coada;
	while (temp) {
		printf("\n%d %s %f", temp->info.cod, temp->info.marca, temp->info.pret);
		temp = temp->prev;
	}


}

void dezalocare(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		nodLS* temp2 = temp->next;
		free(temp->info.marca);
		free(temp);
		temp = temp2;
	}
}

int nrNoduriCautate(nodLS* cap, float pret) {
	int nr = 0;
	nodLS* temp = cap;
	while (temp) {
		if (temp->info.pret == pret)
			nr++;
		temp = temp->next;
	}
	return nr;
}

nodLS* stergereNod(nodLS* cap, nodLS* coada, float pret) {
	if (cap != NULL) {
		nodLS* temp = cap;
		cap = cap->next;
		cap->prev = NULL;
		free(temp->info.marca);
		free(temp);
	}
	else
		if (coada != NULL) {
			nodLS* temp = coada;
			coada = coada->prev;
			coada->next = NULL;
			free(temp->info.marca);
			free(temp);
		}
		else {
			nodLS* temp = cap;
			while (temp->next && temp->next->info.pret != pret) {
				temp = temp->next;
			}
			if (temp->next) {
				nodLS* deSters = temp->next;
				temp->next = deSters->next;
				deSters->prev = temp;
				free(deSters->info.marca);
				free(deSters);
			}
		}
	return cap;
}

nodLS* stergereMultipla(nodLS* cap, nodLS* coada, float pret) {
	int nr = nrNoduriCautate(cap, pret);
	for (int i = 0; i < nr; i++)
		cap = stergereNod(cap, coada, pret);
	return cap;
}
void main() {
	nodLS* cap = NULL, * coada = NULL;
	int n;
	char buffer[20];
	Masina m;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &m.cod);
		fscanf(f, "%s", buffer);
		m.marca = (char*)malloc(strlen(buffer) + 1);
		strcpy(m.marca, buffer);
		fscanf(f, "%f", &m.pret);
		cap = inserare(cap, &coada, m);
		free(m.marca);
	}
	fclose(f);
	//traversare(cap);
	//traversareInversa(coada);
	//cap = stergereMultipla(cap, coada, 30000);
	//traversare(cap);
	heap h;
	h.dim = n;
	h.vect = (Masina*)malloc(sizeof(Masina) * n);
	int nr = 0;
	h = conversieLDtoHeap(cap, h, &nr);
	for (int i = (h.dim - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	//h = StergereElement(h, m);
	AfisareHeap(h);
	dezalocare(cap);
}


//Chaining

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct Masina {
	int cod;
	char* marca;
	float pret;
}Masina;

typedef struct nodLS {
	Masina info;
	struct nodLS* next;

}nodLS;

typedef struct hashT {
	nodLS** vect;
	int dim;
}hashT;


nodLS* inserareLista(nodLS* cap, Masina fac) {
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.marca = (char*)malloc(strlen(fac.marca) + 1);
	strcpy(nou->info.marca, fac.marca);
	nou->info.cod = fac.cod;
	nou->info.pret = fac.pret;

	nou->next = NULL;

	if (cap == NULL) {
		cap = nou;
	}
	else {
		nodLS* temp = cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = nou;

	}
	return cap;

}
int stergereNod(hashT tabela, char denumire[20], float pret) {
	int pozitie = 0;
	if (tabela.vect != NULL) {
		pozitie = functieHash(tabela, denumire);
		nodLS* temp = tabela.vect[pozitie];
		if (temp == NULL)
			return -1;
		else {
			if (tabela.vect[pozitie]->info.pret == pret) {
				if (temp->next == NULL) {
					free(temp->info.marca);
					free(temp);
					tabela.vect[pozitie] = NULL;
				}
				else {
					nodLS* temp2 = temp->next;
					free(temp->info.marca);
					free(temp);
					tabela.vect[pozitie] = temp2;

				}

			}
			else {
				while (temp->next && temp->next->info.pret != pret)
					temp = temp->next;
				if (temp->next) {
					nodLS* deSters = temp->next;
					if (deSters->next) {
						temp->next = deSters->next;
						free(deSters->info.marca);
						free(deSters);
					}
					else {
						temp->next = NULL;
						free(deSters->info.marca);
						free(deSters);
					}
				}
				else return -1;
			}
		}

	}
	return pozitie;


}
int functieHash(hashT tabela, char nume[20]) {
	return nume[0] % tabela.dim;
}

int inserareTabela(hashT tabela, Masina fac) {
	int pozitie = 0;
	if (tabela.vect != NULL) {
		pozitie = functieHash(tabela, fac.marca);
		tabela.vect[pozitie] = inserareLista(tabela.vect[pozitie], fac);
	}
	return pozitie;
}


void traversareLista(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		printf("\n %d, %s, %f", temp->info.cod, temp->info.marca, temp->info.pret);
		temp = temp->next;
	}
}

void traversareTabela(hashT tabela) {
	if (tabela.vect != NULL) {
		for (int i = 0; i < tabela.dim; i++) {
			if (tabela.vect[i] != NULL) {
				printf("\nSublista %d: ", i);
				traversareLista(tabela.vect[i]);
			}
		}
	}
}

void dezalocareLista(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {

		nodLS* temp2 = temp->next;
		free(temp->info.marca);
		free(temp);
		temp = temp2;
	}
}

void dezalocareTabela(hashT tabela) {
	if (tabela.vect != NULL) {
		for (int i = 0; i < tabela.dim; i++)
			if (tabela.vect[i] != NULL) {

				dezalocareLista(tabela.vect[i]);
			}
		free(tabela.vect);
	}
}
void main() {
	hashT tabela;
	tabela.dim = 101;
	tabela.vect = (nodLS**)malloc(sizeof(nodLS*) * tabela.dim);
	for (int i = 0; i < tabela.dim; i++)
		tabela.vect[i] = NULL;
	char buffer[20];
	Masina fac;
	int n;


	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &fac.cod);
		fscanf(f, "%s", buffer);
		fac.marca = (char*)malloc(strlen(buffer) + 1);
		strcpy(fac.marca, buffer);
		fscanf(f, "%f", &fac.pret);
		inserareTabela(tabela, fac);
		free(fac.marca);
	}
	fclose(f);
	stergereNod(tabela, "BMW", 30000);
	int nr = 0;
	traversareTabela(tabela);
	//stergere(tabela, "FAC", 300);
}

//Linear Probing

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct Masina {
	int cod;
	char* marca;
	float pret;

}Masina;

typedef struct hashT {
	Masina** vect;
	int dim;

}hashT;

int functieDispersie(hashT tabela, char nume[20])
{
	return nume[0] % tabela.dim;
}


int inserare(hashT tabela, Masina* c)
{
	int pozitie = 0;
	if (tabela.vect != NULL)
	{
		pozitie = functieDispersie(tabela, (*c).marca);
		if (tabela.vect[pozitie] == NULL)
		{
			tabela.vect[pozitie] = c;
		}
		else
		{
			int index = 1;
			while (pozitie + index < tabela.dim)
			{
				if (tabela.vect[pozitie + index] == NULL)
				{
					tabela.vect[pozitie + index] = c;
					pozitie += index;
					break;
				}
				index++;
			}
		}
	}
	return pozitie;
}

void traversareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.dim; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				printf("\npozitie = %d", i);
				printf("\nCod: %d,Marca: %s, Pret: %f",
					tabela.vect[i]->cod, tabela.vect[i]->marca, tabela.vect[i]->pret);
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
				free(tabela.vect[i]->marca);
				free(tabela.vect[i]);
			}
		}
		free(tabela.vect);
	}
}


int stergere(hashT tabela, char marca[20]) {
	int pozitie = 0;
	if (tabela.vect != NULL) {
		pozitie = functieDispersie(tabela, marca);
		if (tabela.vect[pozitie] == NULL)

			return -1;
		else
			if (tabela.vect[pozitie] != NULL) {
				free(tabela.vect[pozitie]->marca);
				free(tabela.vect[pozitie]);
				tabela.vect[pozitie] = NULL;
			}


			else {
				int index = 1;
				while (pozitie + index < tabela.dim) {
					if (tabela.vect[pozitie + index] == NULL)
					{
						return -1;
					}
					else {
						free(tabela.vect[pozitie + index]->marca);
						free(tabela.vect[pozitie + index]);
						tabela.vect[pozitie + index] = NULL;
						pozitie += index;
						break;

					}
					index++;
				}
			}
	}
	return pozitie;
}
int nrCautate(hashT tabela, char marca[20]) {
	int nr = 0;
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.dim; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				if (strcmp(tabela.vect[i]->marca, marca) == 0)
					nr++;
			}
		}
	}
	return nr;
}

void stergereMultipla(hashT tabela, char marca[20]) {
	int numar = nrCautate(tabela, marca);
	for (int i = 0; i < tabela.dim; i++)
		stergere(tabela, marca);
}


void main() {
	hashT tabela;
	tabela.dim = 101;
	tabela.vect = (Masina**)malloc(tabela.dim * sizeof(Masina*));
	for (int i = 0; i < tabela.dim; i++)
	{
		tabela.vect[i] = NULL;
	}
	Masina* c;
	char buffer[20];
	int n;

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		c = (Masina*)malloc(sizeof(Masina));
		fscanf(f, "%d", &c->cod);
		fscanf(f, "%s", buffer);
		c->marca = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c->marca, buffer);
		fscanf(f, "%f", &c->pret);


		inserare(tabela, c);
	}
	fclose(f);
	stergereMultipla(tabela, "BMW");
	traversareTabela(tabela);
	dezalocareTabela(tabela);


}

// Arbore ABC

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct Masina {
	int cod;
	char* marca;
	float pret;
}Masina;

typedef struct nodArb {
	Masina info;
	struct nodArb* left, * right;
}nodArb;

typedef struct heap {
	Masina* vect;
	int dim;
}heap;

void filtrare(heap h, int index) {
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;
	if (indexSt < h.dim && h.vect[indexSt].pret < h.vect[indexRad].pret)
		indexRad = indexSt;
	if (indexDr < h.dim && h.vect[indexDr].pret < h.vect[indexRad].pret)
		indexRad = indexDr;

	if (indexRad != index) {
		Masina m = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = m;

		filtrare(h, indexRad);
	}

}

heap inserareHeap(heap h, Masina m) {
	Masina* vectNou = (Masina*)malloc(sizeof(Masina) * (h.dim + 1));
	for (int i = 0; i < h.dim; i++)
		vectNou[i] = h.vect[i];
	vectNou[h.dim] = m;
	free(h.vect);
	(h.dim)++;
	h.vect = vectNou;

	for (int i = (h.dim - 1) / 2; i >= 0; i--)
		filtrare(h, i);

}

void afisareHeap(heap h) {
	for (int i = 0; i < h.dim; i++)
		printf("\n%d %s %f", h.vect[i].cod, h.vect[i].marca, h.vect[i].pret);

}

Masina* ArbToVect(nodArb* rad, Masina* vect, int* nr) {
	if (rad != NULL) {
		vect[*nr] = rad->info;
		(*nr)++;
		vect = ArbToVect(rad->left, vect, nr);
		vect = ArbToVect(rad->right, vect, nr);
	}
	return vect;
}

nodArb* creare(Masina m, nodArb* st, nodArb* dr) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.cod = m.cod;
	nou->info.pret = m.pret;
	nou->info.marca = (char*)malloc(strlen(m.marca) + 1);
	strcpy(nou->info.marca, m.marca);

	nou->right = dr;
	nou->left = st;

	return nou;

}

nodArb* inserareArbore(nodArb* rad, Masina m) {
	if (rad != NULL) {
		if (m.cod < rad->info.cod) {
			rad->left = inserareArbore(rad->left, m);
			return rad;
		}
		else
			if (m.cod > rad->info.cod) {
				rad->right = inserareArbore(rad->right, m);
				return rad;
			}
			else return rad;

	}
	else return creare(m, NULL, NULL);
}

float minim(nodArb* rad) {

	float min = rad->info.pret;

	if (rad->left) {
		float temp = minim(rad->left);
		if (temp < min)
			min = temp;
	}
	if (rad->right) {
		float temp = minim(rad->right);
		if (temp < min)
			min = temp;
	}

	return min;

}

nodArb* stergereFrunze(nodArb* rad) {
	if (rad == NULL)
		return NULL;
	if (rad->left == NULL && rad->right == NULL) {
		free(rad->info.marca);
		free(rad);
		return NULL;
	}
	rad->left = stergereFrunze(rad->left);
	rad->right = stergereFrunze(rad->right);
	return rad;

}

nodArb* stergereFrunze2(nodArb* rad) {
	if (rad != NULL) {

		if (rad->left == NULL && rad->right == NULL) {
			free(rad->info.marca);
			free(rad);
			return NULL;
		}
		rad->left = stergereFrunze2(rad->left);
		rad->right = stergereFrunze2(rad->right);
	}
	else return NULL;
	return rad;
}

void preordine(nodArb* rad) {
	if (rad != NULL) {
		printf("\n%d %s %f", rad->info.cod, rad->info.marca, rad->info.pret);
		preordine(rad->left);
		preordine(rad->right);
	}
}
void inordine(nodArb* rad) {
	if (rad != NULL) {
		inordine(rad->left);
		printf("\n%d %s %f", rad->info.cod, rad->info.marca, rad->info.pret);
		inordine(rad->right);
	}
}
void dezalocareArbore(nodArb* rad) {
	if (rad != NULL) {
		nodArb* st = rad->left;
		nodArb* dr = rad->right;
		free(rad->info.marca);
		free(rad);
		dezalocareArbore(st);
		dezalocareArbore(dr);


	}
}

nodArb* stergeRad(nodArb* rad)
{
	nodArb* aux = rad;
	if (rad->stanga != NULL)
	{
		rad = aux->stanga;
		if (aux->dreapta != NULL)
		{
			nodArb* maxS = aux->stanga;
			while (maxS->dreapta != NULL)
				maxS = maxS->dreapta;
			maxS->dreapta = aux->dreapta;
		}
	}
	else
		if (aux->dreapta != NULL)
			rad = aux->dreapta;
		else
			rad = NULL;
	free(aux->info.denumire);
	free(aux);
	return rad;
}

nodArb* stergeNodRecursiv(nodArb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie < rad->info.id)
			rad->stanga = stergeNodRecursiv(rad->stanga, cheie);
		else
			if (cheie > rad->info.id)
				rad->dreapta = stergeNodRecursiv(rad->dreapta, cheie);
			else
				rad = stergeRad(rad);
		return rad;
	}
	else
		return NULL;
}

nodArb* stergeDupaDenumire(nodArb* rad, char* denumire)
{
	if (rad != NULL)
	{
		if (strcmp(rad->info.denumire, denumire) == 0)
		{
			rad = stergeNodRecursiv(rad, rad->info.id);
			return rad;
		}
		else
		{
			rad->stanga = stergeDupaDenumire(rad->stanga, denumire);
			rad->dreapta = stergeDupaDenumire(rad->dreapta, denumire);
			return rad;
		}
	}
	else
		return NULL;
}

void main() {
	int n;
	Masina m;
	nodArb* rad = NULL;
	char buffer[20];

	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &m.cod);
		fscanf(f, "%s", buffer);
		m.marca = (char*)malloc(strlen(buffer) + 1);
		strcpy(m.marca, buffer);
		fscanf(f, "%f", &m.pret);
		rad = inserareArbore(rad, m);
		free(m.marca);

	}
	fclose(f);
	heap h;
	h.dim = n;
	h.vect = (Masina*)malloc(sizeof(Masina) * h.dim);
	int nr = 0;
	//h.vect = ArbToVect(rad, h.vect, &nr);

	//for (int i = (h.dim - 1) / 2; i >= 0; i--)
	//	filtrare(h, i);
	//afisareHeap(h);

	Masina* vector = (Masina*)malloc(sizeof(Masina) * n);
	vector = ArbToVect(rad, vector, &nr);
	//for (int i = 0; i < nr; i++)
		//printf("\n%d %s %f", vector[i].cod, vector[i].marca, vector[i].pret);
	h.dim = nr;
	h.vect = (Masina*)malloc(sizeof(Masina) * h.dim);
	h.vect = vector;
	for (int i = (h.dim - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	//afisareHeap(h);
	//float MIN = minim(rad);
	//printf("%f", MIN);
	//preordine(rad);
	//dezalocareArbore(rad);
	//inordine(rad);
	rad = stergereFrunze2(rad);
	preordine(rad);

}

//Heap

#define _CRT_SECURE_NO_WARNIINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct Masina {
	int cod;
	float pret;
	char* marca;
	float taxe;
}Masina;

typedef struct heap {
	Masina* vect;
	int dim;
}heap;

typedef struct nodArb {
	Masina info;
	struct nodArb* left, * right;

}nodArb;

nodArb* creare(Masina m, nodArb* st, nodArb* dr) {
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.cod = m.cod;
	nou->info.pret = m.pret;
	nou->info.taxe = m.taxe;
	nou->info.marca = (char*)malloc(strlen(m.marca) + 1);
	strcpy(nou->info.marca, m.marca);

	nou->left = st;
	nou->right = dr;

	return nou;
}
nodArb* inserareArbore(Masina m, nodArb* rad) {
	if (rad != NULL) {
		if (m.cod < rad->info.cod) {
			rad->left = inserareArbore(m, rad->left);
			return rad;
		}
		else
			if (m.cod > rad->info.cod) {
				rad->right = inserareArbore(m, rad->right);
				return rad;
			}
			else return rad;

	}
	else return creare(m, NULL, NULL);
}
void inordine(nodArb* rad) {
	if (rad != NULL) {
		inordine(rad->left);
		printf("\n%d  %s %f %f", rad->info.cod, rad->info.marca, rad->info.pret, rad->info.taxe);
		inordine(rad->right);
	}
}
void dezalocareArbore(nodArb* rad) {
	if (rad != NULL) {
		nodArb* st = rad->left;
		nodArb* dr = rad->right;
		free(rad->info.marca);
		free(rad);
		dezalocareArbore(st);
		dezalocareArbore(dr);

	}
}

nodArb* heapToArb(heap h, nodArb* rad) {
	//rad = creare(h.vect[2], NULL, NULL);
	for (int i = 1; i < h.dim; i++) {
		rad = inserareArbore(h.vect[i], rad);
	}
	return rad;

}
void filtrare(heap h, int index) {
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.dim && h.vect[indexSt].pret * h.vect[indexSt].taxe < h.vect[indexRad].pret * h.vect[indexRad].taxe)
		indexRad = indexSt;
	if (indexDr < h.dim && h.vect[indexDr].pret * h.vect[indexDr].taxe < h.vect[indexRad].pret * h.vect[indexRad].taxe)
		indexRad = indexDr;

	if (index != indexRad) {
		Masina temp = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = temp;

		for (int i = (h.dim - 1) / 2; i >= 0; i--)
			filtrare(h, i);
	}

}
heap inserare(heap h, Masina m) {
	Masina* vectNou = (Masina*)malloc(sizeof(Masina) * (h.dim + 1));
	for (int i = 0; i < h.dim; i++)
		vectNou[i] = h.vect[i];
	vectNou[h.dim] = m;

	free(h.vect);
	(h.dim)++;
	h.vect = vectNou;
	for (int i = (h.dim - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;

}
heap extragere(heap h, Masina* m) {
	Masina* vectNou = (Masina*)malloc(sizeof(Masina) * (h.dim - 1));
	Masina temp = h.vect[0];
	h.vect[0] = h.vect[h.dim - 1];
	h.vect[h.dim - 1] = temp;
	*m = h.vect[h.dim - 1];
	(h.dim)--;
	for (int i = 0; i < h.dim; i++)
		vectNou[i] = h.vect[i];
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.dim - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;


}

void afisareHeap(heap h) {
	for (int i = 0; i < h.dim; i++)
		printf("\n%d %s %f %f", h.vect[i].cod, h.vect[i].marca, h.vect[i].pret, h.vect[i].taxe);
}
void dezalocareHeap(heap h) {
	for (int i = 0; i < h.dim; i++) {
		free(h.vect[i].marca);
	}
	free(h.vect);

}

void main() {
	heap h;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &h.dim);
	h.vect = (Masina*)malloc(sizeof(Masina) * h.dim);
	for (int i = 0; i < h.dim; i++) {
		fscanf(f, "%d", &h.vect[i].cod);
		fscanf(f, "%s", buffer);
		h.vect[i].marca = (char*)malloc(strlen(buffer) + 1);
		strcpy(h.vect[i].marca, buffer);
		fscanf(f, "%f", &h.vect[i].pret);
		fscanf(f, "%f", &h.vect[i].taxe);

	}
	fclose(f);
	for (int i = (h.dim - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	//afisareHeap(h);
	Masina m;
	m.cod = 1000;
	m.pret = 550.33;
	m.taxe = 1.12;
	m.marca = "DACIA";

	h = inserare(h, m);
	//afisareHeap(h);
	Masina c;
	h = extragere(h, &c);
	//printf("\n%s", c.marca);
	//dezalocareHeap(h);

	nodArb* rad = NULL;
	rad = heapToArb(h, rad);
	inordine(rad);
}

// Arbore AVL
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int id;
	char* denumire;
	float salariu;
} job;

typedef struct
{
	int BF;
	job info;
	struct nodArb* stanga, * dreapta;
} nodArb;

typedef struct
{
	job info;
	struct nodLista* next;
} nodLista;

nodArb* creareNod(job j, nodArb* st, nodArb* dr)
{
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.id = j.id;
	nou->info.denumire = (char*)malloc((strlen(j.denumire) + 1) *
		sizeof(char));
	strcpy(nou->info.denumire, j.denumire);
	nou->info.salariu = j.salariu;
	nou->stanga = st;
	nou->dreapta = dr;
	return nou;
}

nodArb* inserareNod(job j, nodArb* rad)
{
	if (rad != NULL)
	{
		if (j.id < rad->info.id)
		{
			rad->stanga = inserareNod(j, rad->stanga);
			return rad;
		}
		else
			if (j.id > rad->info.id)
			{
				rad->dreapta = inserareNod(j, rad->dreapta);
				return rad;
			}
			else
				return rad;
	}
	else
		return creareNod(j, NULL, NULL);
}

void preordine(nodArb* rad)
{
	if (rad != NULL)
	{
		printf("\nId = %d, Denumire = %s, Salariu = %5.2fy, BF = %d",
			rad->info.id, rad->info.denumire, rad->info.salariu, rad->BF);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}

void inordine(nodArb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->stanga);
		printf("\nId = %d, Denumire = %s, Salariu = %5.2f, BF = %d",
			rad->info.id, rad->info.denumire, rad->info.salariu, rad->BF);
		inordine(rad->dreapta);
	}
}

nodArb* cautareJob(nodArb* rad, int id)
{
	if (rad != NULL)
	{
		if (id == rad->info.id)
			return rad;
		else
			if (id < rad->info.id)
				return cautareJob(rad->stanga, id);
			else
				return cautareJob(rad->dreapta, id);
	}
	else
		return NULL;
}

void postordine(nodArb* rad)
{
	if (rad != NULL)
	{
		postordine(rad->stanga);
		postordine(rad->dreapta);
		printf("\nId = %d, Denumire = %s, Salariu = %5.2f, BF = %d",
			rad->info.id, rad->info.denumire, rad->info.salariu, rad->BF);
	}
}

void dezalocare(nodArb* rad)
{
	if (rad != NULL)
	{
		nodArb* st = rad->stanga;
		nodArb* dr = rad->dreapta;
		free(rad->info.denumire);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}

void conversieArboreVector(nodArb* rad, job* vect, int* nr)
{
	if (rad != NULL)
	{
		vect[*nr] = rad->info;
		(*nr)++;
		conversieArboreVector(rad->stanga, vect, nr);
		conversieArboreVector(rad->dreapta, vect, nr);
	}
}

void salvareNoduriFrunzaVector(nodArb* rad, job* vect, int* nr)
{
	if (rad != NULL)
	{
		if (rad->stanga == NULL && rad->dreapta == NULL)
		{
			vect[*nr] = rad->info;
			(*nr)++;
		}
		salvareNoduriFrunzaVector(rad->stanga, vect, nr);
		salvareNoduriFrunzaVector(rad->dreapta, vect, nr);
	}
}

void nrJoburiSalariuPrag(nodArb* rad, float prag, int* nr)
{
	if (rad != NULL)
	{
		if (rad->info.salariu >= prag)
			(*nr)++;
		nrJoburiSalariuPrag(rad->stanga, prag, nr);
		nrJoburiSalariuPrag(rad->dreapta, prag, nr);
	}
}

int maxim(int a, int b)
{
	int max = a;
	if (max < b)
		max = b;
	return max;
}

int inaltimeArbore(nodArb* rad)
{
	if (rad != NULL)
		return 1 + maxim(inaltimeArbore(rad->stanga),
			inaltimeArbore(rad->dreapta));
	else
		return 0;
}

nodArb* stergeRad(nodArb* rad)
{
	nodArb* aux = rad;
	if (rad->stanga != NULL)
	{
		rad = aux->stanga;
		if (aux->dreapta != NULL)
		{
			nodArb* maxS = aux->stanga;
			while (maxS->dreapta != NULL)
				maxS = maxS->dreapta;
			maxS->dreapta = aux->dreapta;
		}
	}
	else
		if (aux->dreapta != NULL)
			rad = aux->dreapta;
		else
			rad = NULL;
	free(aux->info.denumire);
	free(aux);
	return rad;
}

nodArb* stergeNodRecursiv(nodArb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie < rad->info.id)
			rad->stanga = stergeNodRecursiv(rad->stanga, cheie);
		else
			if (cheie > rad->info.id)
				rad->dreapta = stergeNodRecursiv(rad->dreapta, cheie);
			else
				rad = stergeRad(rad);
		return rad;
	}
	else
		return NULL;
}

nodArb* stergeDupaDenumire(nodArb* rad, char* denumire)
{
	if (rad != NULL)
	{
		if (strcmp(rad->info.denumire, denumire) == 0)
		{
			rad = stergeNodRecursiv(rad, rad->info.id);
			return rad;
		}
		else
		{
			rad->stanga = stergeDupaDenumire(rad->stanga, denumire);
			rad->dreapta = stergeDupaDenumire(rad->dreapta, denumire);
			return rad;
		}
	}
	else
		return NULL;
}

void calculBF(nodArb* rad)
{
	if (rad != NULL)
	{
		rad->BF = inaltimeArbore(rad->dreapta) - inaltimeArbore(rad->stanga);
		calculBF(rad->stanga);
		calculBF(rad->dreapta);
	}
}

nodLista* inserareLista(nodLista* cap, job j)
{
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->info.id = j.id;
	nou->info.denumire = (char*)malloc((strlen(j.denumire) + 1) * sizeof(char));
	strcpy(nou->info.denumire, j.denumire);
	nou->info.salariu = j.salariu;
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

void traversareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		printf("\nId = %d, Denumire = %s, Salariu = %5.2f",
			temp->info.id, temp->info.denumire, temp->info.salariu);
		temp = temp->next;
	}
}

void dezalocareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		nodLista* temp2 = temp->next;
		free(temp->info.denumire);
		free(temp);
		temp = temp2;
	}
}

void salvareListaDenumire(nodArb* rad, nodLista** cap, char litera)
{
	if (rad != NULL)
	{
		if (rad->info.denumire[0] == litera)
			*cap = inserareLista(*cap, rad->info);
		salvareListaDenumire(rad->stanga, cap, litera);
		salvareListaDenumire(rad->dreapta, cap, litera);
	}
}

nodArb* rotatie_dreapta(nodArb* rad)
{
	printf("\nRotatie dreapta\n");
	nodArb* nod1 = rad->stanga;
	rad->stanga = nod1->dreapta;
	nod1->dreapta = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_stanga(nodArb* rad)
{
	printf("\nRotatie stanga\n");
	nodArb* nod1 = rad->dreapta;
	rad->dreapta = nod1->stanga;
	nod1->stanga = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_dreapta_stanga(nodArb* rad)
{
	printf("\nRotatie dreapta-stanga\n");
	nodArb* nod1 = rad->dreapta;
	nodArb* nod2 = nod1->stanga;
	nod1->stanga = nod2->dreapta;
	nod2->dreapta = nod1;
	rad->dreapta = nod2->stanga;
	nod2->stanga = rad;
	rad = nod2;
	return rad;
}

nodArb* rotatie_stanga_dreapta(nodArb* rad)
{
	printf("\nRotatie stanga-dreapta\n");
	nodArb* nod1 = rad->stanga;
	nodArb* nod2 = nod1->dreapta;
	nod1->dreapta = nod2->stanga;
	nod2->stanga = nod1;
	rad->stanga = nod2->dreapta;
	nod2->dreapta = rad;
	rad = nod2;
	return rad;
}

nodArb* reechilibrare(nodArb* rad)
{
	calculBF(rad);
	nodArb* stanga = rad->stanga;
	nodArb* dreapta = rad->dreapta;
	if (rad->BF <= -2 && stanga->BF <= -1)
	{
		rad = rotatie_dreapta(rad);
		calculBF(rad);
	}
	else
		if (rad->BF <= -2 && stanga->BF >= 1)
		{
			rad = rotatie_stanga_dreapta(rad);
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
	return rad;
}



void main()
{
	int n;
	nodArb* rad = NULL;
	char buffer[20];
	job j;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &j.id);
		fscanf(f, "%s", buffer);
		j.denumire = (char*)malloc((strlen(buffer) + 1) *
			sizeof(char));
		strcpy(j.denumire, buffer);
		fscanf(f, "%f", &j.salariu);

		rad = inserareNod(j, rad);
		free(j.denumire);

		rad = reechilibrare(rad);
	}
	fclose(f);
	//calculBF(rad);


	printf("\n--------preordine----------\n");
	preordine(rad);
	printf("\n--------inordine----------\n");
	inordine(rad);
	printf("\n--------postordine----------\n");
	postordine(rad);

	nodArb* nodCautat = NULL;
	nodCautat = cautareJob(rad, 66);
	printf("\nJobul cautat este %s", nodCautat->info.denumire);

	printf("\n--------Conversie vector----------\n");
	job* vect = (job*)malloc(n * sizeof(job));
	int nr = 0;
	//conversieArboreVector(rad, vect, &nr);
	salvareNoduriFrunzaVector(rad, vect, &nr);
	for (int i = 0; i < nr; i++)
		printf("\nId = %d, Denumire = %s, Salariu = %5.2f",
			vect[i].id, vect[i].denumire, vect[i].salariu);

	free(vect);

	int nrJoburi = 0;
	nrJoburiSalariuPrag(rad, 3000, &nrJoburi);
	printf("\nNr. joburi cu salariu peste prag: %d", nrJoburi);

	printf("\nInaltime arbore: %d", inaltimeArbore(rad));

	int gradEchilibru = inaltimeArbore(rad->dreapta) -
		inaltimeArbore(rad->stanga);
	if (gradEchilibru <= 1 && gradEchilibru >= -1)
		printf("\nArbore echilibrat!");
	else
		printf("\nArbore neechilibrat!");

	//printf("\nDupa stergere:\n");
	//rad = stergeRad(rad);
	//preordine(rad);

	printf("\nDupa stergere:\n");
	rad = stergeNodRecursiv(rad, 99);
	//rad = stergeDupaDenumire(rad, "Pictor");
	//calculBF(rad);
	rad = reechilibrare(rad);
	preordine(rad);

	nodLista* cap = NULL;
	salvareListaDenumire(rad, &cap, 'A');
	traversareLista(cap);
	dezalocareLista(cap);

	dezalocare(rad);
}

//Grafuri


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

// Coada
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int varsta;
	char* nume;
	float medie;
	//int nrNote;
	//int *vectNote;
} student;

typedef struct
{
	student inf;
	struct nodCoada* next;
} nodCoada;

void put(nodCoada** prim, nodCoada** ultim, student s)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.varsta = s.varsta;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->next = NULL;
	if (*prim == NULL && *ultim == NULL)
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

int get(nodCoada** prim, nodCoada** ultim, student* s)
{
	if (*prim != NULL && *ultim != NULL)
	{
		(*s).varsta = (*prim)->inf.varsta;
		(*s).nume = (char*)malloc((strlen((*prim)->inf.nume) + 1) * sizeof(char));
		strcpy((*s).nume, (*prim)->inf.nume);
		(*s).medie = (*prim)->inf.medie;
		nodCoada* aux = *prim;
		*prim = (*prim)->next;
		free(aux->inf.nume);
		free(aux);
		return 0;
	}
	else
		if (*prim == NULL) {
			*ultim = NULL;
			return -1;
		}
}

void traversare(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp)
	{
		printf("\nVarsta = %d, Nume = %s, Medie = %5.2f", temp->inf.varsta, temp->inf.nume, temp->inf.medie);
		temp = temp->next;
	}
}

void conversieCoadaVector(nodCoada** prim, nodCoada** ultim, student* vect, int* nr)
{
	student s;
	while (get(prim, ultim, &s) == 0)
	{
		vect[*nr] = s;
		(*nr)++;
	}
}

void main()
{
	int n;
	printf("Nr. studenti=");
	scanf("%d", &n);

	nodCoada* prim = NULL, * ultim = NULL;
	student s;
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("\nVarsta=");
		scanf("%d", &s.varsta);
		printf("\nNume=");
		scanf("%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		printf("\nMedie=");
		scanf("%f", &s.medie);
		put(&prim, &ultim, s);
	}
	traversare(prim);

	student s1;
	get(&prim, &ultim, &s1);
	printf("\nStudentul extras se numeste %s ", s1.nume);
	free(s1.nume);

	/*while (get(&prim, &ultim, &s1)==0)
		free(s1.nume);*/

	printf("\n----vector---------\n");

	student* vect = (student*)malloc(n * sizeof(student));
	int nr = 0;
	conversieCoadaVector(&prim, &ultim, vect, &nr);
	for (int i = 0; i < nr; i++)
		printf("\nVarsta = %d, Nume = %s, Medie = %5.2f", vect[i].varsta, vect[i].nume, vect[i].medie);
	for (int i = 0; i < nr; i++)
		free(vect[i].nume);
	free(vect);
}

// Stiva
#include <stdio.h>
#include <malloc.h>
#include <string.h>

//Structura stiva este un caz particular de lista simpla care respecta principiul LIFO (Last In First Out)
//informatie utila nod stiva
typedef struct
{
	int cod;
	char* titlu;
	float pret;
	//int nrAutori;
	//char **numeAutori;
} carte;

//definire structura nod stiva (informatie utila de tip carte si pointer de legatura next)
typedef struct
{
	carte inf;
	struct nodStiva* next; //la fel ca la lista simpla
} nodStiva;

//definire structura nod lista simpla pentru conversie stiva-lista
typedef struct
{
	carte inf;
	struct nodLista* next;
} nodLista;

//functie folosita pentru inserarea unui nod in stiva
//adresa de inceput (primul element al stivei) se numeste "varf" (echivalent cu "cap" de la lista)
//varful se trimite cu doua ** din cauza ca metoda returneaza void si este nevoie de returnarea varfului modificat
//inserarea se face inaintea primului element, adica varful se actualizeaza dupa fiecare inserare
void push(nodStiva** varf, carte c)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf.cod = c.cod;
	nou->inf.titlu = (char*)malloc((strlen(c.titlu) + 1) * sizeof(char));
	strcpy(nou->inf.titlu, c.titlu);
	nou->inf.pret = c.pret;
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

//functie de extragere a unui nod din stiva
//returneaza int cu valoare 0 daca extragerea se face cu succes si -1 in caz contrar
//varful se actualizeaza la fiecare extragere deoarece se extrage mereu primul element
//se pastreaza in pointerul "val" informatia utila din nodul extras
//extragerea se face cu stergerea nodului din structura
int pop(nodStiva** varf, carte* val)
{
	if (*varf == NULL)
		return -1;
	else
	{
		(*val).cod = (*varf)->inf.cod;
		(*val).titlu = (char*)malloc((strlen((*varf)->inf.titlu) + 1) * sizeof(char));
		strcpy((*val).titlu, (*varf)->inf.titlu);
		(*val).pret = (*varf)->inf.pret;
		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp->inf.titlu);
		free(temp);
		return 0;
	}
}

//functie de afisare a structurii stiva
void traversare(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp)
	{
		printf("\nCod = %d, Titlu = %s, Pret = %5.2f", temp->inf.cod, temp->inf.titlu, temp->inf.pret);
		temp = temp->next;
	}
}

//functie de afisare a structurii lista simpla
void traversareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		printf("\nCod = %d, Titlu = %s, Pret = %5.2f", temp->inf.cod, temp->inf.titlu, temp->inf.pret);
		temp = temp->next;
	}
}

void dezalocareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		nodLista* temp2 = temp->next;
		free(temp->inf.titlu);
		free(temp);
		temp = temp2;
	}
}

//functie de conversie din stiva de carti in vector de carti
void conversieStivaVector(nodStiva** varf, carte* vect, int* nr)
{
	carte val;
	while (pop(varf, &val) == 0) //atat timp cat se extrage cu succes din stiva se insereaza in vector
	{
		vect[*nr] = val;
		(*nr)++;
	}
}

//functie de inserare nod in lista simpla
void inserareLista(nodLista** cap, carte val)
{
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->inf.cod = val.cod;
	nou->inf.titlu = (char*)malloc((strlen(val.titlu) + 1) * sizeof(char));
	strcpy(nou->inf.titlu, val.titlu);
	nou->inf.pret = val.pret;
	nou->next = NULL;
	if (*cap == NULL)
		*cap = nou;
	else
	{
		nodLista* temp = *cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}

//functie de conversie stiva in lista simpla
void conversieStivaListaSimpla(nodStiva** varf, nodLista** cap)
{
	carte val;
	while (pop(varf, &val) == 0)
	{
		inserareLista(cap, val);
	}
}

void main()
{
	nodStiva* varf = NULL;
	int n;
	carte c;
	printf("Nr. carti=");
	scanf("%d", &n);
	char buffer[30];
	for (int i = 0; i < n; i++)
	{
		printf("\nCod=");
		scanf("%d", &c.cod);
		printf("\nTitlu=");
		scanf(" %[^\n]s", buffer);
		c.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.titlu, buffer);
		printf("\nPret=");
		scanf("%f", &c.pret);

		push(&varf, c);
	}
	traversare(varf);

	carte val;
	pop(&varf, &val);
	printf("\nCartea extrasa are codul %d si titlul %s", val.cod, val.titlu);
	free(val.titlu);

	//dezalocare stiva
	/*while (pop(&varf, &val) == 0)
		free(val.titlu);*/

	printf("\n--------Conversie stiva vector--------\n");
	carte* vect = (carte*)malloc(n * sizeof(carte));
	int nr = 0;
	conversieStivaVector(&varf, vect, &nr);
	for (int i = 0; i < nr; i++)
		printf("\nCod = %d, Titlu = %s, Pret = %5.2f", vect[i].cod, vect[i].titlu, vect[i].pret);
	for (int i = 0; i < nr; i++)
		free(vect[i].titlu);
	free(vect);

	/*printf("\n--------Conversie stiva lista--------\n");
	nodLista* cap = NULL;
	conversieStivaListaSimpla(&varf, &cap);
	traversareLista(cap);
	dezalocareLista(cap);*/
}