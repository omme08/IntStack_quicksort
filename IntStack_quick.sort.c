#include<stdio.h>
#include<stdlib.h>
#include"IntStack.h"
#define swap(type,x,y) do{type t = x; x = y; y = t;}while(0)

int Initialize(IntStack* s, int max)
{
	s->ptr = 0;
	if ((s->stk = calloc(max, sizeof(int))) == NULL) {
		s->max = 0;
		return -1;
	}
	s->max = max;
	return 0;
}

int Push(IntStack* s, int x)
{
	if (s->ptr >= s->max)
		return -1;
	s->stk[s->ptr++] = x;
	return 0;
}

int Pop(IntStack* s, int* x)
{
	if (s->ptr <= 0)
		return -1;
	s->ptr--;
	*x = s->stk[s->ptr];
	return 0;
}

int Peek(const IntStack* s, int* x)
{
	if (s->ptr <= 0)
		return -1;
	*x = s->stk[s->ptr - 1];
	return 0;
}

void Clear(IntStack* s)
{
	s->ptr = 0;
}

int Capacity(const IntStack* s)
{
	return s->max;
}

int Size(const IntStack* s)
{
	return s->ptr >= s->max;
}

int IsEmpty(const IntStack* s)
{
	return s->ptr <= 0;
}

int IsFull(const IntStack* s)
{
	return s->ptr >= s->max;
}

int Search(const IntStack* s, int x)
{
	for (int i = s->ptr - 1; i >= 0; i--)
		if (s->stk[i] == x)
			return i;
	return -1;
}

void Print(const IntStack* s)
{
	int i;
	for (int i = 0; i < s->ptr; i++)
		printf("%d", s->stk[i]);
	putchar('\n');
}

void Terminate(IntStack* s)
{
	if (s->stk != NULL)
		free(s->stk);
	s->max = s->ptr = 0;

}

void quick(int a[], int left, int right)
{
	IntStack Istack;
	IntStack rstack;

	Initialize(&Istack, right - left + 1);
	Initialize(&rstack, right - left + 1);

	Push(&Istack, left);
	Push(&rstack, right);

	while (!IsEmpty(&Istack)) {
		int pl = (Pop(&Istack, &left), left);
		int pr = (Pop(&rstack, &right), right);
		int x = a[(left + right) / 2];
		do {
			while (a[pl] < x)
				pl++;
			while (a[pr] > x)
				pr--;
			if (pl <= pr) {
				swap(int, a[pl], a[pr]);
				pl++;
				pr--;
			}
		} while (pl <= pr);

		if (left < pr) {
			Push(&Istack, left);
			Push(&rstack, pr);
		}
		if (pl < right) {
			Push(&Istack, pl);
			Push(&rstack, right);
		}
	}
	Terminate(&Istack);
	Terminate(&rstack);
}

int main(void)
{
	int nx;
	puts("퀵 정렬");
	printf("요소 개수 : ");
	scanf("%d", &nx);
	int* x = calloc(nx, sizeof(int));
	for (int i = 0; i < nx; i++) {
		printf("x[%d] : ", i);
		scanf("%d", &x[i]);
	}
	quick(x, 0, nx - 1);
	puts("오름차순으로 정렬했습니다.");
	for (int i = 0; i < nx; i++)
		printf("x[%d] = %d\n", i, x[i]);
	free(x);
	
	return 0;
}
