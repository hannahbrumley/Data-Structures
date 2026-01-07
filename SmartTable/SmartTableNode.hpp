#ifndef _SMART_TABLE_NODE
#define _SMART_TABLE_NODE

template <typename T>
struct SmartTableNode
{
    SmartTableNode()
    {
        used = false;
    }

    SmartTableNode& operator=( const T& newData )
    {
        data = newData;
        used = true;
        return *this;
    }

    SmartTableNode& operator=( const SmartTableNode<T>& other )
    {
        if ( this == &other ) { return *this; }
        data = other.data;
        used = other.used;
    }

    T data;
    bool used;
};

#endif
