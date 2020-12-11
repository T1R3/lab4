// lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <locale.h>
#define N 5

void newMat(int* mas) {
	srand(time(0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) {
				mas[N * i + j] = 0;
			}
			if (i < j) {
				mas[N * i + j] = rand() % 2;
				mas[j * N + i] = mas[N * i + j];
			}
		}
	}
}

void printMat(int* mas) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", mas[N * i + j]);
		}
		printf("\n");
	}
}

void DFS(int s, int* G, int* num) {
	num[s] = 1;
	printf("%d ", s);

	for (int i = 0; i < N; i++) {
		if (G[N * s + i] == 1 && num[i] == 0) {
			DFS(i, G, &num[0]);
		}
	}
}

struct stack {
	int elem[N];
	int top;
};

void init(struct stack* stk) {
	stk->top = 0;
}

void push(struct stack* stk, int k) {
	if (stk->top < N) {
		stk->elem[stk->top] = k;
		stk->top++;
	}
	else {
		printf("Стек полон, количество элементов: %d! \n", stk->top);
	}
}

int pop(struct stack* stk) {
	int elem;
	if ((stk->top) > 0) {
		stk->top--;
		elem = stk->elem[stk->top];
		return elem;
	}
	else {
		printf("Стек пуст!");
		return 0;
	}
}

void DFSstack(struct stack* stk, int s, int* G, int* num) {
	int i = 0;
	num[s] = 1;
	printf("%d ", s);
	push(stk, s);

	while (stk->top != 0) {
		for (i; i < N; i++) {
			if (G[N * s + i] == 1 && num[i] == 0) {
				num[i] = 1;
				printf("%d ", i);
					push(stk, i);
					
			}
			if (i == N) {
				s = pop(stk);
			}
		}
	}
}

typedef struct Node {
	int value;
	struct Node* next;
}Spisok;

Spisok* create(int name)
{
	// Выделение памяти под корень списка
	Spisok* tmp = (Spisok*)malloc(sizeof(Spisok));
	// Присваивание имя вершине
	tmp->value = name;
	// Присваивание указателю на следующий элемент значения NULL
	tmp->next = NULL;
	return(tmp);
}
void addElem(int data, Spisok* head) {
	// Выделение памяти под корень списка
	Spisok* tmp = (Spisok*)malloc(sizeof(Spisok));
	// Присваивание значения узлу
	tmp->value = data;
	// Присваивание указателю на следующий элемент значения NULL
	tmp->next = NULL;
	// Присваивание новому указателю указателя head. 
	// Присваивание выполняется для того, чтобы не потерять указатель на «голову» списка
	Spisok* p = head;
	// Сдвиг указателя p в самый конец первоначального списка
	while (p->next != NULL)
		p = p->next;
	// Присваивание указателю p -> next значения указателя tmp (созданный новый узел)
	p->next = tmp;
}
void print(Spisok* head) {
	Spisok* s = head;
	if (s != NULL) {					//номер вершины
		printf("%d:  ", s->value);			
		s = s->next;
	}
	while (s != NULL)					//номера узлов
	{
		// Вывод значения узла
		printf("%d ", s->value);
		// Сдвиг указателя к следующему узлу
		s = s->next;
	}
}
void spisokSmej(int(&Matrix)[N][N], Spisok* G_S[N]) {
	for (int i = 0; i < N; i++) {
		Node* tmp = create(i);
		for (int j = 0; j < N; j++) {
			if (Matrix[i][j] == 1)
				addElem(j, tmp);
		}
		G_S[i] = tmp;
	}
	for (int i = 0; i < N; i++) {
		print(G_S[i]);
		printf("\n");
	}
	printf("\n");
}

void DFSsp(Spisok* (&P)[N], int ver, int* num) {
	num[ver] = 1;
	printf("%d ", ver);
	Spisok* s = P[ver];
	s = s->next;
	while (s != NULL) {
		if (num[s->value] == 0) {
			DFSsp(P, s->value, &num[0]);
		}
		s = s->next;
	}
}

//void SpisokSmej(spisok** create, int name, int(&Matrix)[N][N], spisok* G_S[N], int data) {
//	spisok* head;
//	for (int i = 0; i < N; i++) {
//		(*create) = new spisok;
//		(*create)->value = name;
//		(*create)->next = NULL;
//
//		for (int j = 0; j < N; j++) {
//			if (Matrix[i][j] == 1) {
//				(*create) = new spisok;
//				(*create)->value = data;
//				(*create)->next = NULL;
//
//				spisok* p = head;
//				while (p->next != NULL) {
//					p = p->next;
//					p->next = *create;
//				}
//			}
//		}
//		G_S[i] = *create;
//	}
//	for (int i = 0; i < N; i++) {
//		print(G_S[i]);
//		printf("\n");
//	}
//	printf("\n");
//}


int main() {
	int G[N][N], num[N], s;
	setlocale(LC_ALL, "rus");
	struct stack* stk;
	stk = new stack;
	Spisok* G_S1[N];

	newMat(&G[0][0]);
	printMat(&G[0][0]);

	for (int i = 0; i < N; i++) {
		num[i] = 0;
	}

	printf("Введите номер вершины для начала обхода: ");
	scanf("%d", &s);
	printf("Результат с рекурсией: ");
	DFS(s, &G[0][0], &num[0]);
	printf("\n\n");

	for (int i = 0; i < N; i++) {
		num[i] = 0;
	}

	printf("Представление графа в виде списка смежности: \n");
	spisokSmej(G, G_S1);

	printf("Введите номер вершины для начала обхода: ");
	scanf("%d", &s);
	DFSsp(G_S1, s, &num[0]);

	for (int i = 0; i < N; i++) {
		num[i] = 0;
	}


	init(stk);
	printf("\n\nВведите номер вершины для начала обхода: ");
	scanf("%d", &s);
	printf("Результат без рекурсии: ");
	DFSstack(stk, s, &G[0][0], &num[0]);
	printf("\n\n");





}