#pragma once

// -- system includes
#include <new>

// -- libs includes
#include "core/cmemory.h"
#include "core/types.h"
#include "core/utils.h"
#include "core/assert.h"
#include "containers/cdataptr.h"

// ================================================================================================
// Default comparison function (only assumes less-than is implemented)
// ================================================================================================
template<typename T> struct CompareBasicTypes {
    static nint Compare(const T& left, const T& right) {
        return left < right ? -1 : right < left ? 1 : 0;
    }
};

// ================================================================================================
// Class to simplify keeping tables of things
// ================================================================================================
template<typename T> class CTable {

protected:

    CDataPtr<int8> mem;
    nuint count;
    nuint alloc;
    nuint expand;

    cpointer GetPointer(nuint idx) const;
    pointer GetPointer(nuint idx);

    // -- protected sort with indices
    template<typename C> void SortRecurse(nuint low, nuint high);

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

    // -- insert an item at the specified index
    void Insert(nuint idx, const T& val);
    void Insert(nuint idx);
    void InsertMultiple(nuint idx, const T& val, nuint n);
    void InsertMultiple(nuint idx, nuint n);

    // -- remove a specific entry from the table
    void Remove(nuint idx);
    void RemoveMultiple(nuint idx, nuint n);

    // -- swap memory with the given table
    void Swap(CTable<T>& other);

    // -- sort the table with the given comparison function
    template<typename C> void Sort();

    // -- binary search for the given element, return where it should be inserted if not found
    template<typename C> nflag Search(const T& key, nuint& index);

    // -- reset the table
    void Clear();
    void Reset();
};

// ------------------------------------------------------------------------------------------------
// Get a pointer to the memory for the given index
// ------------------------------------------------------------------------------------------------
template<typename T> inline cpointer CTable<T>::GetPointer(nuint idx) const {
    return pointer(mem) + sizeof(T) * idx;
}

template<typename T> inline pointer CTable<T>::GetPointer(nuint idx) {
    return pointer(mem) + sizeof(T) * idx;
}

// ------------------------------------------------------------------------------------------------
// Sort the elements in [low, high)
// ------------------------------------------------------------------------------------------------
template<typename T> template<typename C>
void CTable<T>::SortRecurse(nuint low, nuint high) {
    T& pivot = *GetElem(high);
    nuint store = C::Compare(*GetElem(low), pivot) > 0 ? low : low + 1;
    for(nuint i = low; i < high; ++i) {
        T& left = *GetElem(i);
        if(C::Compare(left, pivot) < 0) {
            T& swap = *GetElem(store);
            T temp = swap;
            swap = left;
            left = temp;
            ++store;
        }
    }

    // -- if the store spot is less than the pivot, swap them as well
    if(store < high) {
        T& swap = *GetElem(store);
        T temp = swap;
        swap = pivot;
        pivot = temp;
    }
    
    // -- recurse where necessary
    if(store+1 < high)
        SortRecurse<C>(store+1, high);
    if(low+1 < store)
        SortRecurse<C>(low, store-1);
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
// Add entries to the table at the end
// ================================================================================================
template<typename T> inline void CTable<T>::Grow(const T& val) {
    InsertMultiple(kNeverIndex, val, 1);
}

template<typename T> inline void CTable<T>::Grow() {
    InsertMultiple(kNeverIndex, 1);
}

template<typename T> inline void CTable<T>::GrowMultiple(const T& val, nuint n) {
    InsertMultiple(kNeverIndex, val, n);
}

template<typename T> inline void CTable<T>::GrowMultiple(nuint n) {
    InsertMultiple(kNeverIndex, n);
}

// ================================================================================================
// Add entries to the table at the specified index
// ================================================================================================
template<typename T> inline void CTable<T>::Insert(nuint idx, const T& val) {
    InsertMultiple(idx, val, 1);
}

template<typename T> inline void CTable<T>::Insert(nuint idx) {
    InsertMultiple(idx, 1);
}

template<typename T> inline void CTable<T>::InsertMultiple(nuint idx, const T& val, nuint n) {
    // -- first allocate some new memory, if necessary
    nuint newcount = count + n;
    if(newcount > alloc) {
        // -- get the multiple of expand to allocate that will give us just enough memory
        // -- divide by expand, rounding up, and then multiply by expand again
        nuint newmem = ((newcount - alloc - 1) / expand + 1) * expand;
        alloc += newmem;
        mem = recast_<pointer>(CMemory::ReAlloc(pointer(mem), alloc * sizeof(T)));
    }

    // -- adjust idx
    if(idx >= count)
        idx = count;
    else {
        // -- move the necessary entries
        nuint tomove = (count - idx) * sizeof(T);
        CMemory::Move(GetPointer(idx+n), GetPointer(idx), tomove);
    }

    // -- then construct the memory as a copy of val
    nuint end = idx + n;
    for(nuint i = idx; i < end; ++i)
        new (pointer(mem) + sizeof(T) * i) T(val);

    count = newcount;
}

template<typename T> inline void CTable<T>::InsertMultiple(nuint idx, nuint n) {
    // -- first allocate some new memory, if necessary
    nuint newcount = count + n;
    if(newcount > alloc) {
        // -- get the multiple of expand to allocate that will give us just enough memory
        // -- divide by expand, rounding up, and then multiply by expand again
        nuint newmem = ((newcount - alloc - 1) / expand + 1) * expand;
        alloc += newmem;
        mem = recast_<pointer>(CMemory::ReAlloc(pointer(mem), alloc * sizeof(T)));
    }

    // -- adjust idx
    if(idx >= count)
        idx = count;
    else {
        // -- move the necessary entries
        nuint tomove = (count - idx) * sizeof(T);
        CMemory::Move(GetPointer(idx+n), GetPointer(idx), tomove);
    }

    // -- then construct the memory as a copy of val
    nuint end = idx + n;
    for(nuint i = idx; i < end; ++i)
        new (pointer(mem) + sizeof(T) * i) T();

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
    pointer tempmem = pointer(mem);
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
// A quick sort using the provided static comparison function
// ================================================================================================
template<typename T> template<typename C> inline void CTable<T>::Sort() {
    if(count > 1)
        SortRecurse<C>(0, count-1);
}

// ================================================================================================
// Search for the given key (assumes the table is already sorted)
// ================================================================================================
template<typename T> template<typename C> nflag CTable<T>::Search(const T& key, nuint& index) {
    // -- do a binary search to find where this item should be inserted
    nuint low = 0;
    nuint high = count;
    nuint i;
    nint comp;

    // -- while our range is non-empty
    while(low < high) {
        // -- get the midpoint (rounding down) of the range
        i = (low + high) >> 1;

        // -- compare the current element against the key
        comp = C::Compare(*GetElem(i), key);

        // -- if they're equal, we're done
        if(comp == 0) {
            index = i;
            return true;
        }

        // -- if the current element is less, adjust low
        if(comp < 0)
            low = i+1;

        // -- otherwise adjust high
        else
            high = i;
    }

    index = low;
    return false;
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
    if(pointer(mem) != NULL) {
        CMemory::Free(pointer(mem));
        mem = NULL;
    }
}

