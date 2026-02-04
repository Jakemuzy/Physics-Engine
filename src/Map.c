#include "Map.h"

Map* MapInit()
{
    Map* mp = malloc(sizeof(Map));
    mp->bkts = calloc(SIZE, sizeof(Bucket*));
    return mp;
}

void MapPush(Map* mp, char* key, void* val)
{
    unsigned int hsh = Hash(key);
    if (mp->bkts[hsh]) 
        BucketFree(MapPop(mp, key));


    Bucket* bkt = malloc(sizeof(Bucket));
    bkt->val = val;
    mp->bkts[hsh] = bkt; 
}

void* MapPop(Map* mp, char* key)
{
    unsigned int hsh = Hash(key);
    Bucket* val =  mp->bkts[hsh];
    mp->bkts[hsh] = NULL;
    return val;
}

void* MapLook(Map* mp, char* key)
{
    unsigned int hsh = Hash(key);
    Bucket* val =  mp->bkts[hsh];
    return val->val;
}

void MapFree(Map* mp)
{
    unsigned int i;
    for (i = 0; i < SIZE; i++) {
        if (mp->bkts[i]) 
            BucketFree(mp->bkts[i]);
    }
    free(mp->bkts);
    free(mp);
}



void BucketFree(Bucket* bkt)
{
    free(bkt->val);
    free(bkt);
}



unsigned int Hash(char* key)
{
    unsigned int hash = 5381;
    int c;
    while (c = *key++)
        hash = ((hash <<5) + hash) + c;

    return hash % SIZE;
}

