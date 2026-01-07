#ifndef _HASH_ITEM
#define _HASH_ITEM

template <typename T>
struct HashItem
{
    HashItem()
    {
    }

    HashItem( T newData, int newKey )
    {
        data = newData;
        key = newKey;
    }

    T data;
    int key;
};

#endif
