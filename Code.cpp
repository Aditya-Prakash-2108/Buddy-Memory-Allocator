#include <stdio.h>
#include <string.h>
#define MAX_POWERS 11
int powers[MAX_POWERS] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512,
1024};
typedef struct Block
{
char pname[255];
int memory;
int frag;
int free;
} Block;
Block blocks[255];
int blockCount = 0;
void printBlocks()
{
printf("************* Memory *************\n");
for (int i = 0; i < blockCount; i++)
{
printf("Block-%d: %-4s - %dM", i + 1, blocks[i].pname,
blocks[i].memory + blocks[i].frag);
if (blocks[i].free == 0)
{
printf(" (Internal Frag = %dM)\n", blocks[i].frag);
}
else
{
printf("\n");
}
}
printf("**********************************\n");
}
int isPerfectPower(int value)
{
8
for (int i = 0; i < MAX_POWERS; i++)
if (powers[i] == value)
return 1;
return 0;
}
int findNearestGreaterPower(int amount)
{
int index = 0;
while (amount > powers[index])
{
index++;
if (index == MAX_POWERS)
{
break;
}
}
if (index < MAX_POWERS)
{
return powers[index];
}
return 0;
}
int findNearestLowerPower(int amount)
{
int index = 0;
while (amount >= powers[index])
{
index++;
if (index == MAX_POWERS)
{
break;
}
}
if (index < MAX_POWERS && index > 1)
{
return powers[index - 1];
}
return 0;
}
void addBlock(const char *pname, int blockSize, int amount)
9
{
strcpy(blocks[blockCount].pname, pname);
blocks[blockCount].memory = amount;
blocks[blockCount].frag = blockSize - amount;
blocks[blockCount].free = 0;
blockCount++;
}
void addFreeBlock(int blockSize)
{
strcpy(blocks[blockCount].pname, "free");
blocks[blockCount].memory = blockSize;
blocks[blockCount].frag = 0;
blocks[blockCount].free = 1;
blockCount++;
}
int findSmallestFreeBlock(int blockSize)
{
int foundIndex = -1;
for (int i = 0; i < blockCount; i++)
{
if (blocks[i].free == 1 && blocks[i].memory >= blockSize)
{
if (foundIndex == -1)
{
foundIndex = i;
}
else
{
if (blocks[i].memory < blocks[foundIndex].memory)
{
foundIndex = i;
}
}
}
}
return foundIndex;
}
int findExactFreeBlock(int blockSize)
{
10
for (int i = 0; i < blockCount; i++)
{
if (blocks[i].free == 1 && blocks[i].memory == blockSize)
return i;
}
return -1;
}
int findExactFreeBlockButNotTheGivenBlock(int blockSize, int index)
{
for (int i = 0; i < blockCount; i++)
{
if (blocks[i].free == 1 &&
blocks[i].memory == blockSize &&
i != index)
return i;
}
return -1;
}
void removeBlock(int index)
{
blockCount--;
for (int i = index; i < blockCount; i++)
{
blocks[i] = blocks[i + 1];
}
}
void mergeEqualSizeFreeBlocks()
{
int other = -1;
do
{
for (int i = 0; i < blockCount; i++)
{
if (blocks[i].free == 1)
{
other =
findExactFreeBlockButNotTheGivenBlock(blocks[i].memory, i);
if (other > 0)
{
11
blocks[i].memory += blocks[other].memory;
break;
}
}
}
if (other > 0)
{
removeBlock(other);
}
} while (other > 0);
}
int findBlockWithProcessName(const char *pname)
{
for (int i = 0; i < blockCount; i++)
{
if (strcmp(blocks[i].pname, pname) == 0)
return i;
}
return -1;
}
void freeBlock(int index)
{
strcpy(blocks[index].pname, "free");
blocks[index].memory += blocks[index].frag;
blocks[index].frag = 0;
blocks[index].free = 1;
}
int main()
{
int choice;
char pname[255];
int amount;
// first free block
strcpy(blocks[0].pname, "free");
blocks[0].memory = 1024;
blocks[0].frag = 0;
blocks[0].free = 1;
blockCount++;
12
printBlocks();
while (1)
{
printf("> Enter 0(EXIT), 1(request), 2(release): ");
scanf("%d", &choice);
if (choice == 0)
{
printf("!!! THE END !!!\n");
break;
}
// request allocation
if (choice == 1)
{
printf("Enter process name and requested space(M): ");
scanf("%s %d", pname, &amount);
// find nearest power value
int blockSize = findNearestGreaterPower(amount);
if (blockSize > 0)
{
int foundIndex = findSmallestFreeBlock(blockSize);
if (foundIndex == -1)
{
printf("No enough space for the request!\n");
}
else
{
// exact match
if (blockSize == blocks[foundIndex].memory)
{
strcpy(blocks[foundIndex].pname, pname);
blocks[foundIndex].memory = amount;
blocks[foundIndex].frag = blockSize -
amount;
blocks[foundIndex].free = 0;
}
else
{
// "Large Block found, need to divide
addBlock(pname, blockSize, amount);
13
blocks[foundIndex].memory -= blockSize;
int remainingBlockSize =
blocks[foundIndex].memory;
if (!isPerfectPower(remainingBlockSize))
{
int nearBlockSize =
findNearestLowerPower(remainingBlockSize);
// near lower
blocks[foundIndex].memory =
nearBlockSize;
remainingBlockSize -= nearBlockSize;
// add free blocks upto perfect power of
2 found
while
(!isPerfectPower(remainingBlockSize))
{
nearBlockSize =
findNearestLowerPower(remainingBlockSize);
addFreeBlock(nearBlockSize);
remainingBlockSize -= nearBlockSize;
}
// add last perfect power of 2 block
addFreeBlock(remainingBlockSize);
}
}
}
printBlocks();
}
else
{
printf("No enough space for the request!\n");
}
}
// release block and merge the blocks to make bigger power
else if (choice == 2)
{
printf("Enter process name: ");
14
scanf("%s", pname);
int ind = findBlockWithProcessName(pname);
if (ind == -1)
{
printf("Invalid process name\n");
printBlocks();
}
else
{
freeBlock(ind);
mergeEqualSizeFreeBlocks();
printBlocks();
}
}
else
{
printf("Invalid choice\n");
}
}
return 0;
}
