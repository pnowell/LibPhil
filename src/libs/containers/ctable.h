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
    void GrowMultiple(const T& val, nuint n);
    void GrowMultiple(nuint n);

    // -- remove a specific entry from the table
    void Remove(nuint idx);
    void RemoveMultiple(nuint idx, nuint n);

    // -- swap memory with the given table
    void Swap(CTable<T>& other);

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
    Assert_(idx < count, "Index " NUintFmt_ " is out of range " NUintFmt_, idx, count);
    return recast_<const T*>(GetPointer(idx));
}

template<typename T> inline T* CTable<T>::GetElem(nuint idx) {
    Assert_(idx < count, "Index " NUintFmt_ " is out of range " NUintFmt_, idx, count);
    return recast_<T*>(GetPointer(idx));
}

template<typename T> inline const T& CTable<T>::operator[](nuint idx) const {
    return *GetElem(idx);
}

template<typename T> inline T& CTable<T>::operator[](nuint idx) {
    return *GetElem(idx);
}

// ================================================================================================
// Add entries to the table
// ================================================================================================
template<typename T> inline void CTable<T>::Grow(const T& val) {
    GrowMultiple(val, 1);
}

template<typename T> inline void CTable<T>::Grow() {
    GrowMultiple(1);
}

template<typename T> inline void CTable<T>::GrowMultiple(const T& val, nuint n) {
    // -- first allocate some new memory, if necessary
    nuint newcount = count + n;
    if(newcount > alloc) {
        // -- get the multiple of expand to allocate that will give us just enough memory
        // -- divide by expand, rounding up, and then multiply by expand again
        nuint newmem = ((newcount - alloc - 1) / expand + 1) * expand;
        alloc += newmem;
        mem = recast_<pointer>(CMemory::ReAlloc(mem, alloc * sizeof(T)));
    }

    // -- then construct the memory as a copy of val
    for(nuint i = count; i < newcount; ++i)
        new (mem + sizeof(T) * i) T(val);

    count = newcount;
}

template<typename T> inline void CTable<T>::GrowMultiple(nuint n) {
    // -- first allocate some new memory, if necessary
    nuint newcount = count + n;
    if(newcount > alloc) {
        // -- get the multiple of expand to allocate that will give us just enough memory
        // -- divide by expand, rounding up, and then multiply by expand again
        nuint newmem = ((newcount - alloc - 1) / expand + 1) * expand;
        alloc += newmem;
        mem = recast_<pointer>(CMemory::ReAlloc(mem, alloc * sizeof(T)));
    }

    // -- then construct the memory as a copy of val
    for(nuint i = count; i < newcount; ++i)
        new (mem + sizeof(T) * count) T();

    count = newcount;
}

// ================================================================================================
// Remove an entry from the table
// ================================================================================================
template<typename T> void CTable<T>::Remove(nuint idx) {
    RemoveMultiple(idx, 1);
}

template<typename T> void CTable<T>::RemoveMultiple(nuint idx, nuint n) {
    if(n == 0)
        return;

    Assert_(idx + n <= count, "Indices [" NUintFmt_ ".." NUintFmt_ ") are out of range " NUintFmt_,
            idx, idx + n, count);

    // -- destroy the elements to be removed
    for(nuint i = idx; i < idx + n; ++i)
        CMemory::Destroy<T>(GetElem(i));

    // -- move the remaining elements down
    if(idx + n < count) {
        nuint tomove = (count - idx - n) * sizeof(T);
        CMemory::Move(GetPointer(idx), GetPointer(idx+n), tomove);
    }

    count -= n;
}

// ================================================================================================
// Swap memory with the given table
// ================================================================================================
template<typename T> void CTable<T>::Swap(CTable<T>& other) {
    pointer tempmem = mem;
    nuint tempcount = count;
    nuint tempalloc = alloc;

    mem = other.mem;
    count = other.count;
    alloc = other.alloc;

    other.mem = tempmem;
    other.count = tempcount;
    other.alloc = tempalloc;
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

