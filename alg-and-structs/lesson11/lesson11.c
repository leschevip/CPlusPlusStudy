#include <stdio.h>

typedef int boolean;

#define NULL 0
#define false 1 != 1
#define true 1 == 1

typedef struct {
    char* dataLow;
    char* dataUp;
    int size;
} Alphabet;

const char* DECRYPT_TYPE = "decrypt";
const char* ENCRYPT_TYPE = "encrypt";


char cizarTryToReplace(char* letters, int letterIdx, int lettersSize, char letter, int lag)
{
	if (*(letters + letterIdx) == letter)
	{
		int n = letterIdx + lag;
		if (n >=0 && n < lettersSize )
		{
			return *(letters + n);
		}
		else if (n >= lettersSize)
		{
			return *(letters + n - lettersSize);
		}
		else
		{
			return *(letters + n + lettersSize);
		}
	}

	return '\0';
}

char* encryptDecryptCizar(Alphabet* a, char *message, int lag)
{
	int count = 0;
	while(message[count] != '\0')
	{
		count++;
	}
	char* enMessage = (char*)malloc(sizeof(char)*(count + 1));
	for(int i = 0; i <= count; i++)
		enMessage[i] = message[i];

	int idx = 0;
	for (int idx = 0; idx < count; idx++)
	{
		for (int k = 0; k < a->size; k++)
		{
			char s = '\0';
			s = cizarTryToReplace(a->dataLow, k, a->size, message[idx], lag);
			if (s == '\0')
				s = cizarTryToReplace(a->dataUp, k, a->size, message[idx], lag);

			if (s != '\0')
				enMessage[idx] = s;
		}
	}

	return enMessage;
}

char get2dChar(char** array, const int row, const int col) {
    return *((*(array + row)) + col);

}

void print2dCharArray(char** array, const int row, const int col) {
    char format[7];
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printf("[%c]", get2dChar(array, i, j));
        }
        printf("\n");
    }
}

char** putMessageToArray(const char* message, int messageLength, int rows, int columns)
{
	int idx = 0;
	char** a = (char**)malloc(rows*sizeof(char*));
	for (int i=0; i<rows; i++)
	{
		a[i] = (char*)malloc(columns*sizeof(char));
		int k = 0;
		while (idx < (i+1)*columns)
		{
			a[i][k] = idx <= messageLength ? message[idx] : '\0';
			k++;
			idx++;
		}
	}

	return a;
}

char* readMessageFromArray(const char** m, int messageLength, int rows, int columns)
{
	char* message = (char*)malloc(sizeof(char)*messageLength + 1);
	int idx = 0;
	for (int i=0; i < columns; i++)
	{
		for (int j=0; j < rows; j++)
		{
			message[idx++] = m[j][i];
		}
	}
	message[idx] = '\0';

	return message;
}

char* encryptDecryptByPermutations(const char* message, int columns, char* type, boolean isDebug)
{
	if (isDebug)
		printf("before: %s\n", message);

	if (message == NULL)
	{
		printf("message is empty\n");
		return NULL;
	}

	// длинна сообщения
	int count = 0;
	while(message[count] != '\0')
	{
		count++;
	}

	if (count % columns != 0)
	{
		printf("column number is incorrect\n");
		return NULL;
	}
	int r = 0;
	int c = 0;

	if (type == ENCRYPT_TYPE)
	{
		r = count / columns;
		c = columns;
	}
	else if (type == DECRYPT_TYPE)
	{
		r = columns;
		c = count / columns;
	}
	else
	{
		printf("Unknown operation: %s", type);
		return NULL;
	}

	// заполняем массив сообщением, и добиваем пустыми символами ячейки оставшиеся после конца сообщения
	char** m = putMessageToArray(message, count, r, c);
	if (isDebug)
		print2dCharArray(m, r, c);

	// читаем сообщение по стоблцам
	char* newMessage = readMessageFromArray(m, count, r, c);
	if (isDebug)
		printf("encrypted: %s\n", newMessage);

	for (int i = 0; i < r; i++)
		free(m[i]);
	free(m);

	return newMessage;
}


Alphabet* initAlphabet()
{
	Alphabet* a = (Alphabet*)malloc(sizeof(Alphabet));
	a->size = 26;
	a->dataUp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	a->dataLow = "abcdefghijklmnopqrstuvwxyz";
	return a;
}

void Task1()
{
	printf("Task1:\n");
	Alphabet* a = initAlphabet();
	char* mes = "THIS is a SECRET messaGe";
	printf("before: %s\n", mes);
	char* encrypted = encryptDecryptCizar(a, mes, 3);
	printf("encrypted: %s\n", encrypted);
	mes = encryptDecryptCizar(a, encrypted, -3);
	printf("decrypted: %s\n", mes);
	free(a);
}

void Task2()
{
	printf("Task2:\n");
	char* mes = "THIS IS A SECRET MESSAGE";
	const int COL_COUNTS = 6;
	char* encrypted = encryptDecryptByPermutations(mes, COL_COUNTS, ENCRYPT_TYPE, true);
	char* decrypted = encryptDecryptByPermutations(encrypted, COL_COUNTS, DECRYPT_TYPE, true);
}

int main(int argv, char** argc)
{
	Task1();
	Task2();
}
