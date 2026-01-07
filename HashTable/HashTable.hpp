#ifndef _HASH_TABLE_TESTER
#define _HASH_TABLE_TESTER

#include "HashItem.hpp"
#include "../SmartTable/SmartTable.hpp"
#include "../../Utilities/Logger.hpp"

//! An enumeration to define what kind of collision method the hash table is using.
enum class CollisionMethod {
    LINEAR,
    QUADRATIC,
    DOUBLE_HASH
};

template <typename T>
class HashTable
{
public:
    HashTable( int size );
    HashTable();
    ~HashTable();

    //! Set the collision method the hash table uses
    void SetCollisionMethod( CollisionMethod method );

    //! Add a new item to the hash table with an integer key and any data type for the data
    void Push( int key, T data );

    //! Retrieve data from the table with a given key, throws exception if not found
    T& Get( int key );

    //! Returns the amount of items stored in the hash table
    int Size();

private:
    //! Primary hash to convert an integer key into an array index
    int Hash1( int key );

    //! Collision method that steps forward by 1 each time
    int LinearProbe( int originalIndex, int collisionCount );

    //! Collision method that steps forward by c^2 each time
    int QuadraticProbe( int originalIndex, int collisionCount );

    //! Collision method that uses a second hash to figure step size
    int Hash2( int key, int collisionCount );

    //! Hash table's current collision method
    CollisionMethod m_method;

    //! Internal array that may contain gaps
    SmartTable<HashItem<T>> m_table;

    friend class HashTableTester;
};

/* -----------------------------------------------------------------------------------------*/
/* ------------------------------------------------------------------------------ HashTable */
/**
- Set a default collision method
- Allocate memory for the base table, use a default value since none was specified
*/
template <typename T>
HashTable<T>::HashTable()
{
    m_method = CollisionMethod::LINEAR;
    m_table.AllocateMemory( 5 );
}

/* -----------------------------------------------------------------------------------------*/
/* ------------------------------------------------------------------------------ HashTable */
/**
- Set a default collision method
- Allocate memory in the table given the size passed in
*/
template <typename T>
HashTable<T>::HashTable( int size )
{
    m_method = CollisionMethod::LINEAR;
    m_table.AllocateMemory( size );
}

/* -----------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------- ~HashTable */
template <typename T>
HashTable<T>::~HashTable()
{
    // Nothing to do
}

/* -----------------------------------------------------------------------------------------*/
/* --------------------------------------------------------------------- SetCollisionMethod */
/**
Set the private member variable m_method based on the method parameter value
*/
template <typename T>
void HashTable<T>::SetCollisionMethod( CollisionMethod method )
{
    m_method = method;
}

/* -----------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- Push */
/**
    @param      key         A unique identifier key for the data
    @param      data          The data to be stored

    Add new item to the hash table. The key will be used to generate an index where the data will be
    placed in the table.

    * A. ERROR CHECK: If the m_table is full, then throw an exception.

    * B. GENERATING AN INDEX:
        1. Generate an index using Hash1, passing in the key value. Store the index in a variable `originalIndex`.
        2. Create a variable for the collisionCount, initialize it to 0.
        3. Create a variable `newIndex`, assign it the value of `originalIndex`.
        4. While `m_table.ItemAtIndex( newIndex )` equals TRUE, then there is a collision. Go to (C).
            If there is not a collision, go to (D).

    * C. DEALING WITH COLLISIONS:
        1. Add 1 to the collisionCount.
        2. Determine which collision method is being used...
            2a. LINEAR: Generate a new value for the `newIndex` variable. Call the `LinearProbe` function, passing in the `originalIndex` and `collisionCount`. Bind the index to the array size of the table using the modulus operator.
                `newIndex = LinearProbe( originalIndex, collisionCount ) % arraySize;`
            2b. QUADRATIC: Generate a new value for the `newIndex` variable. Call the `QuadraticProbe` function, passing in the `originalIndex` and `collisionCount`. Bind the index to the array size of the table using the modulus operator.
                `newIndex = QuadraticProbe( originalIndex, collisionCount ) % arraySize;`
            2c. DOUBLE_HASH: Generate a new value for the `newIndex` variable. Call the `Hash2` function, passing in the `kry` and the `collisionCount`.
                `newIndex = Hash2( key, collisionCount ) % arraySize;`

    * D. INSERTING DATA TO INDEX:
        1. Create a HashItem<T> with the data and key set up.
        2. Call m_table's PushAt function, passing in the HashItem<T> variable as the first argument, and the `newIndex` as the second argument.
*/
template <typename T>
void HashTable<T>::Push( int key, T data )
{
    
    //throw NotImplementedException("HashTable::Push"); // Erase this once you work on this function
    
    if (m_table.IsFull())
    {
        throw StructureFullException("HashTable<T>::Push", "Structure is full!"); 
    }

    int originalIndex = Hash1(key); 
    int collisionCount = 0; 
    int newIndex = originalIndex; 

    while (m_table.ItemAtIndex(newIndex) )
    {
        collisionCount++; 

        if (m_method == CollisionMethod::LINEAR)
        {
            newIndex = LinearProbe(originalIndex, collisionCount) % m_table.ArraySize();
        }
        
        else if (m_method == CollisionMethod::QUADRATIC)
        {
            newIndex = QuadraticProbe(originalIndex, collisionCount) % m_table.ArraySize();
        }

        else if (m_method == CollisionMethod::DOUBLE_HASH)
        {
            newIndex = Hash2(key, collisionCount) % m_table.ArraySize();
        }

        
    }

    HashItem<T> newItem =  HashItem<T>(data, key); 
    m_table.PushAt(newItem, newIndex); 
}

/* -----------------------------------------------------------------------------------------*/
/* ------------------------------------------------------------------------------------ Get */
/**
    @param      key     The key of the item to search for
    @return             A reference to the data

    * ERROR CHECK: If the table is empty, throw a `StructureEmptyException` exception.

    * FOR LOOP: Use a for loop to iterate from `i` to `m_table.ArraySize()`. Within the array...
        * Use `m_table.ItemAtIndex(i)` to see if there is an item at this index. If there is, then --
        * Use `m_table.GetAt(i)` to get the item at this index. If that item's `key` matches the parameter `key`, then return this item.

    * END OF FUNCTION: If we've reached the end of the function and nothing was returned, this means that
        the key does not exist in the hash table. In this case, throw a `ItemNotFoundException` exception.
*/
template <typename T>
T& HashTable<T>::Get( int key )
{
    //throw NotImplementedException("HashTable::Get"); // Erase this once you work on this function

    if (m_table.IsEmpty())
    {
        throw StructureEmptyException("HashTable<T>::Get", "Structure is Empty!"); 
    }

    for (int i = 0; i < m_table.ArraySize(); i++)
    {
        if (m_table.ItemAtIndex(i) && m_table.GetAt(i).key == key)
        {
            return m_table.GetAt(i).data; 
        }
    }\

    throw ItemNotFoundException("HashTable<T>::Get", "Could not find item with key!"); 
}

/* -----------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- Size */
/**
    @return     The amount of items currently stored in the hash table (can use `m_table.Size()` to get the amount).
*/
template <typename T>
int HashTable<T>::Size()
{
    return m_table.Size(); 
}

/* -----------------------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------------- Hash1 */
/**
    @param      key         The key to hash into an index value for the table array.
    @return                 A valid index value between [0, m_table.ArraySize()-1].

    Generate the index by taking the `key` and using modulus to bound it to the array size:
    `return ( key % m_table.ArraySize() );`
*/
template <typename T>
int HashTable<T>::Hash1( int key )
{
    return (key % m_table.ArraySize()); 
}

/* -----------------------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------- LinearProbe */
/**
    @param      originalIndex       The original index that was generated.
    @param      collisionCount      The amount of collisions there has been.
    @return                         A new index value calculated from the original index and collision count.

    Take the original index and offset it by the collision count to get the new index value:
    `return ( originalIndex + collisionCount );`
*/
template <typename T>
int HashTable<T>::LinearProbe( int originalIndex, int collisionCount )
{
    return (originalIndex + collisionCount); 
}

/* -----------------------------------------------------------------------------------------*/
/* ------------------------------------------------------------------------- QuadraticProbe */
/**
    @param      originalIndex       The original index that was generated.
    @param      collisionCount      The amount of collisions there has been.
    @return                         A new index value calculated from the original index and collision count.

    Take the original index and offset it by the collision count squared to get the new index value:
    `return ( originalIndex + ( collisionCount * collisionCount ) );`
*/
template <typename T>
int HashTable<T>::QuadraticProbe( int originalIndex, int collisionCount)
{
    return (originalIndex + (collisionCount * collisionCount)); 
}

/* -----------------------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------------- Hash2 */
/**
    @param      originalIndex       The original index that was generated.
    @param      collisionCount      The amount of collisions there has been.
    @return                         A new index value calculated from the original key and collision count.

    Generate a new index by using the Hash1 function on the key to get the original index, then
    use the collisionCount to hash a step forward value, then return the originalIndex plus the step forward value.

    1. Create an `originalIndex` integer variable, assign it the return value of `Hash1(key)`.
    2. Create a `stepForward` integer variable, assign it to this equation: `collisionCount * ( 3 - key % 3 )`.
    3. Return the result of `originalIndex + stepForward`.
*/
template <typename T>
int HashTable<T>::Hash2( int key, int collisionCount )
{
    

    int originalIndex = Hash1(key); 
    int stepForward = collisionCount * (3 - key % 3); 

    return originalIndex + stepForward; 
}

#endif
