#ifndef _MAP_H__

#define _MAP_H__

#include <stdlib.h>

#define SIZE 109

typedef struct Bucket {
    void* val; 
} Bucket;

typedef struct Map {
    Bucket** bkts;
} Map;


Map*  MapInit();
void  MapPush(Map* mp, char* key, void* val);
void* MapPop(Map* mp, char* key);
void* MapLook(Map* mp, char* key);
void  MapFree(Map* mp);

void  BucketFree(Bucket* bkt);

unsigned int Hash(char* val);

#endif
