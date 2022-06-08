
typedef int boolean;

#define NULL 0
#define false 1 != 1
#define true 1 == 1


typedef struct {
    char* data;
    char* key;
} HashValue;

typedef struct {
	HashValue** table;
	int size;
} HashTableChars;

HashValue *nullItem;

HashValue* newValue(const char *key, const char* data) {
	HashValue *v = (HashValue*) malloc(sizeof(HashValue));
    if (!v) {
        printf("Out of memory \n");
        return NULL;
    }
    v->data = data;
    v->key = key;
    return v;
}

void initialize(const HashTableChars *hash, int idx) {
    for (int i = idx; i < hash->size; ++i) {
        hash->table[i] = NULL;
    }
}

boolean isFull(const HashTableChars *hash) {
    for (int i = 0; i < hash->size; ++i) {
        if (hash->table[i] == NULL || hash->table[i] == nullItem)
            return false;
    }
    return true;
}

int hashFunc(const char* str) {
    int sum = 0;
    int idx = 0;
    while (str[idx] != '\0')
    	sum += (unsigned char)(str[idx++]);
	return sum;
}

int linearProbe(int val, int size) {
    ++val;
    val %= size;
    return val;
}


HashTableChars* CreateHash(int capacity)
{
	if (capacity < 30*255)
	{
		printf("capacity can't be less than 7650");
		return NULL;
	}
	HashTableChars* newHash = (HashTableChars*)malloc(sizeof(HashTableChars));
	newHash->table = (HashValue**) calloc(capacity, sizeof(HashValue*));
	newHash->size = capacity;
	return newHash;
}

HashTableChars* increaseCapacity(HashTableChars *hash) {

	int newSize = hash->size*2;

	HashTableChars* newHash = CreateHash(newSize);
    int i;
    for (i = 0; i < hash->size; i++)
        insertNode(hash, hash->table[i]->data);
    initialize(newHash, i);

    free(hash->table);
    free(hash);

    return newHash;
}

boolean insertNode(HashTableChars *hash, const char *key, const char* data) {
	HashValue *node = newValue(key, data);
    if (!node) return false;

    int hashVal = hashFunc(node->key);
    if (isFull(hash))
    	hash = increaseCapacity(hash);
    while (hash->table[hashVal] && hash->table[hashVal] != nullItem) {
        hashVal = linearProbe(hashVal, hash->size);
    }
    hash->table[hashVal] = node;
    return true;
}

boolean EqualStr(const char *first, const char *second)
{
	int idx = 0;
	char * tmp = first[idx];
	while (tmp != '\0')
	{
		if (first[idx] != second[idx])
			break;

		idx++;
		tmp = first[idx];
	}

	return second[idx] == '\0';
}

HashValue* findNode(HashTableChars *hash, const char* key) {

    int hashVal = hashFunc(key);
    while (hash->table[hashVal]) {
        if (EqualStr(hash->table[hashVal]->key, key)) {
            return hash->table[hashVal];
        }
        hashVal = linearProbe(hashVal, hash->size);
    }
    return NULL;
}

HashValue* deleteNode(HashTableChars *hash, char* key) {
    int hashVal = hashFunc(key);
    while (hash->table[hashVal]) {
        if (EqualStr(hash->table[hashVal]->key, key)) {
        	HashValue *temp = hash->table[hashVal];
        	hash->table[hashVal] = nullItem;
            return temp;
        }
        hashVal = linearProbe(hashVal, hash->size);
    }
    return NULL;
}

void printNode(HashValue *v) {
    if (!v) {
        printf("[*,*]");
        return;
    }
    printf("[k=%s,d=%s]", v->key, v->data);
}

void printHashTable(HashTableChars * hash) {
    for (int i = 0; i < hash->size; ++i) {
    	if (hash->table[i] != nullItem && hash->table[i] != NULL )
    		printNode(hash->table[i]);
    }
    printf("\n");
}


void combineSumFrom(int sum, int* denom, int size)
{
	int current = sum;
	int* counter = (int*)malloc(sizeof(int)*size);
	for(int i = 0; i < size; i++)
		counter[i] = 0;

	for(int i = 0; i < size; i++)
	{
		while (current - denom[i] >= 0)
		{
			current -= denom[i];
			counter[i]++;
		}
	}

	printInfo(sum, denom, counter, size);

	free(counter);

}

void printInfo(int sum, int* denom, int* counter, int size)
{
	printf("value: %d\n", sum);
	printf("denomination: ");
	for(int i = 0; i < size; i++)
		printf("[%d]", denom[i]);
	printf("\n");
	printf("coins count:  ");
	for(int i = 0; i < size; i++)
		printf("[%d]", counter[i]);

}


int main(int argv, char** argc)
{
	HashTableChars * hash = CreateHash(30*255);
	nullItem = newValue('\0', '\0');

	insertNode(hash, "Hi", "Hello World");
	insertNode(hash, "Game", "Andre Lamot. Notices for game programming");
	printHashTable(hash);
	printNode(findNode(hash, "Game"));
	printf("\n\n");

	int sum = hashFunc("Hello World");
	printf("Hello World : %d\n", sum);

	// задан сразу отсортированный массив
	int denom[] = {50, 10, 5, 2, 1};
	const int SZ = 5;
	int val = 98;
	combineSumFrom(val, denom, SZ);


	return 0;
}
