#pragma once

// -- system includes
#include <new.h>

// -- libs includes
#include "core/cmemory.h"
#include "core/types.h"
#include "core/utils.h"
#include "core/assert.h"

// ================================================================================================
// Class to simplify keeping tables of things
// ================================================================================================
template<typename T> class CTable {

protected:

    pointer mem;
    nuint count;
    nuint alloc;
    nuint expand;

    cpointer GetPointer(nuint idx) const;
    pointer GetPointer(nuint idx);

public:

    enum {
        eDefaultExpand  = 32,
    };

    // -- constructor / destructor
    CTable(nuint exp = eDefaultExpand);
    ~CTable();

    // -- accessors
    nuint Count() const;
    const T* GetElem(nuint idx) const;
    T* GetElem(nuint idx);
    const T& operator[](nuint idx) const;
    T& operator[](nuint idx);

    // -- add an entry to the table
    void Grow(const T& val);
    void Grow();

    // -- remove a specific entry from the table
    void Remove(nuint idx);

    // -- reset the table
    void Clear();
    void Reset();
};

// ------------------------------------------------------------------------------------------------
// Get a pointer to the memory for the given index
// ------------------------------------------------------------------------------------------------
template<typename T> inline cpointer CTable<T>::GetPointer(nuint idx) const {
    return mem + sizeof(T) * idx;
}

template<typename T> inline pointer CTable<T>::GetPointer(nuint idx) {
    return mem + sizeof(T) * idx;
}

// ================================================================================================
// Constructor
// ================================================================================================
template<typename T> inline CTable<T>::CTable(nuint exp) : mem(NULL), count(0), alloc(0),
                                                           expand(exp) {
}

// ================================================================================================
// Destructor
// ================================================================================================
template<typename T> inline CTable<T>::~CTable() {
    Reset();
}

// ================================================================================================
// Accessors
// ================================================================================================
template<typename T> inline nuint CTable<T>::Count() const {
    return count;
}

template<typename T> inline const T* CTable<T>::GetElem(nuint idx) const {
    Assert_(idx < count, "Index %d is out of range %d", idx, count);
    return recast_<const T*>(GetPointer(idx));
}

template<typename T> inline T* CTable<T>::GetElem(nuint idx) {
    Assert_(idx < count, "Index %d is out of range %d", idx, count);
    return recast_<T*>(GetPointer(idx));
}

template<typename T> inline const T& CTable<T>::operator[](nuint idx) const {
    return *GetElem(idx);
}

template<typename T> inline T& CTable<T>::operator[](nuint idx) {
    return *GetElem(idx);
}

// ================================================================================================
// Add an entry to the table
// ================================================================================================
template<typename T> inline void CTable<T>::Grow(const T& val) {
    // -- first allocate some new memory, if necessary
    if(count == alloc) {
        alloc += expand;
        mem = recast_<pointer>(CMemory::ReAlloc(mem, alloc * sizeof(T)));
    }

    // -- then construct the memory as a copy of val
    new (mem + sizeof(T) * count) T(val);
    ++count;
}

template<typename T> inline void CTable<T>::Grow() {
    // -- first allocate some new memory, if necessary
    if(count == alloc) {
        alloc += expand;
        mem = recast_<pointer>(CMemory::ReAlloc(mem, alloc * sizeof(T)));
    }

    // -- then construct the memory with its default constructor
    new (mem + sizeof(T) * count) T();
    ++count;
}

// ================================================================================================
// Remove an entry from the table
// ================================================================================================
template<typename T> void CTable<T>::Remove(nuint idx) {
    Assert_(idx < count, "Index %d is out of range %d", idx, count);

    // -- destroy the element to be removed
    CMemory::Destroy<T>(GetElem(i));

    // -- move the remaining elements down by one index
    if(idx < count - 1) {
        nuint tomove = (count - idx - 1) * sizeof(T);
        CMemory::Move(GetPointer(i), GetPointer(i+1), tomove);
    }
}

// ================================================================================================
// Destroy and clear all current items
// ================================================================================================
template<typename T> inline void CTable<T>::Clear() {
    // -- iterate through the list of currently allocated items and destroy them
    for(nuint i = 0; i < count; ++i)
        CMemory::Destroy<T>(GetElem(i));

    // -- clear the count
    count = 0;
}

// ================================================================================================
// Destroy all our items and free any memory we were using
// ================================================================================================
template<typename T> inline void CTable<T>::Reset() {
    Clear();
    alloc = 0;
    if(mem != NULL) {
        CMemory::Free(mem);
        mem = NULL;
    }
}

