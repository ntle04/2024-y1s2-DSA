#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED};

typedef struct _slot{
    int key;
    enum Marker indicator;
    int next;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashFind(int key, HashSlot hashTable[]);

int hash(int key)
{
    return (key % TABLESIZE);
}

int main()
{
    int opt;
    int i;
    int key;
    int index;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].next = -1;
        hashTable[i].key = 0;
        hashTable[i].indicator = EMPTY;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Search a key in the hash table  |\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            index = HashInsert(key,hashTable);
            if(index <0)
                printf("Duplicate key\n");
            else if(index < TABLESIZE)
                printf("Insert %d at index %d\n",key, index);
            else
                printf("Table is full.\n");
            break;
        case 2:
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            index = HashFind(key, hashTable);

            if(index!=-1)
                printf("%d is found at index %d.\n",key,index);
            else
                printf("%d is not found.\n",key);
            break;

        case 3:
            printf("index:\t key \t next\n");
            for(i=0;i<TABLESIZE;i++) printf("%d\t%d\t%d\n",i, hashTable[i].key,hashTable[i].next);
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int HashInsert(int key, HashSlot hashTable[])
{
    if(HashFind(key, hashTable)!=-1) //duplicate key
        return -1;
    int index = hash(key);

    if(hashTable[index].indicator == EMPTY){ //desired index is empty
        hashTable[index].key = key;
        hashTable[index].next = -1;
        hashTable[index].indicator = USED;
        return index;
    }

    else{ //when desired index slot is full
        int currentIndex = index;
        while(hashTable[currentIndex].next != -1){
            currentIndex = hashTable[currentIndex].next;
        }
        for(int count=1; count<=TABLESIZE; count++){
            int i = index+count; //iterate through all 37 slots
            if(i >= TABLESIZE)
                i -= TABLESIZE; // loop back to beginning of table
            if(hashTable[i].indicator == EMPTY){
                hashTable[currentIndex].next = i;
                hashTable[i].key = key;
                hashTable[i].next = -1;
                hashTable[i].indicator = USED;
                return i;
            }
        }
        return (TABLESIZE+1); //TABLESIZE exceeded
    }
}

int HashFind(int key, HashSlot hashTable[])
{
    int index = hash(key);
    if(hashTable[index].key == key)
        return index; //key found at desired index
    else{ //desired index slot is full
        while(hashTable[index].next != -1){
            index = hashTable[index].next;
            if(hashTable[index].indicator == EMPTY)
                return -1;
            if(hashTable[index].key == key)
                return index; //key found
        }
        return -1; //non-existing key
    }
}
