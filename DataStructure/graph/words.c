#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <math.h>
#include "Graph.h"
#include "stack.h"

#define WORD_LENGTH 35

typedef struct
{
	char* v;
	size_t vlen;
} _WordArray, * WordArray;

WordArray newArray()
{
	WordArray t = malloc(sizeof(_WordArray));
	assert(t != NULL);
	return t;
}

void arrayInit(WordArray words, size_t N)
{
	words->v = malloc(N * WORD_LENGTH);
	words->vlen = 0;
	assert(words->v != NULL);
}

const char* arrayAt(WordArray words, size_t i)
{
	return words->v + i * WORD_LENGTH;
}

size_t arrayLength(WordArray words)
{
	return words->vlen;
}

void arrayInsert(WordArray words, const char* w)
{
	memcpy(arrayAt(words, words->vlen), w, WORD_LENGTH);
	++words->vlen;
}

bool oneCompare(const char* lp, const char* rp)
{
	bool flag = true;
	while (*lp)
	{
		if (*lp != *rp)
		{
			if (flag)
			{
				flag = false;
			}
			else
			{
				return false;
			}
		}
		++lp; ++rp;
	}
	return true;
}

// strlen(lp) < strlen(rp)
bool lackCompare(const char* lp, const char* rp)
{
	while (*lp)
	{
		if (*lp != *rp)
		{
			return strcmp(lp, rp + 1) == 0;
		}
		++lp; ++rp;
	}
	return true;
}

bool compare(const char* lp, const char* rp)
{
	size_t ln = strlen(lp);
	size_t rn = strlen(rp);
	if (abs(ln - rn) > 1) return false;
	if (ln < rn)
	{
		return lackCompare(lp, rp);
	}
	else if (ln > rn)
	{
		return lackCompare(rp, lp);
	}
	else
	{
		return oneCompare(lp, rp);
	}
}

void insertWord(Graph g, WordArray words, size_t cur)
{
	Edge e;
	for (size_t i = 0; i < arrayLength(words); i++)
	{
		if (compare(arrayAt(words, cur), arrayAt(words, i)))
		{
			e.v = cur;
			e.w = i;
			insertEdge(g, e);
		}
	}
}

void printNext(Graph g, WordArray words)
{
	for (size_t i = 0; i < arrayLength(words); ++i)
	{
		printf("%s:", arrayAt(words, i));
		for (size_t j = i + 1; j < arrayLength(words); ++j)
		{
			if (adjacent(g, i, j))
			{
				printf(" %s", arrayAt(words, j));
			}
		}
		printf("\n");
	}
}

size_t maxLength = 0;

// len start with 1
void findMaxL(Graph g, size_t cur, size_t len)
{
	for (size_t i = cur + 1; i < numOfVertices(g); ++i)
	{
		if (adjacent(g, cur, i))
		{
			findMaxL(g, i, len + 1);
		}
	}
	if (len > maxLength)
	{
		maxLength = len;
	}
}

void findMaxLength(Graph g)
{
	for (size_t i = 0; i < numOfVertices(g); ++i)
	{
		findMaxL(g, i, 1);
	}
}

void printS(WordArray words, stack s)
{
	int cur = StackPop(s);
	if (StackHeight(s) == 0)
	{
		printf(arrayAt(words, cur));
	}
	else
	{
		printS(words, s);
		printf(" -> %s", arrayAt(words, cur));
	}
	StackPush(s, cur);
}

void printStack(WordArray words, stack s)
{
	if (StackHeight(s) == 0) return;
	int cur = StackPop(s);
	printS(words, s);
	printf(" -> %s", arrayAt(words, cur));
	StackPush(s, cur);
}

// len start with 1
void getP(Graph g, WordArray words, size_t cur, stack s)
{
	StackPush(s, cur);
	for (size_t i = cur + 1; i < numOfVertices(g); ++i)
	{
		if (adjacent(g, cur, i))
		{
			getP(g, words, i, s);
		}
	}
	if (StackHeight(s) == maxLength)
	{
		printStack(words, s);
		putchar('\n');
	}
	StackPop(s);
}

void getPath(Graph g, WordArray words)
{
	stack s = newStack();
	for (size_t i = 0; i < numOfVertices(g); ++i)
	{
		getP(g, words, i, s);
	}
	dropStack(s);
}

int main()
{
	size_t N = 0;
	char input[WORD_LENGTH];
	Graph graph;
	WordArray words = newArray();

	printf("Enter a number: ");
	scanf("%d", &N);

	graph = newGraph(N);
	arrayInit(words, N);

	while (N--)
	{
		printf("Enter a word: ");
		scanf("%s", input);
		arrayInsert(words, input);
		insertWord(graph, words, arrayLength(words) - 1);
	}

	putchar('\n');
	printNext(graph, words);
	
	putchar('\n');
	findMaxLength(graph);
	printf("Maximum sequence length: %d\n", maxLength);

	printf("Maximal sequence(s):\n");
	getPath(graph, words);

	freeGraph(graph);
	return 0;
}
