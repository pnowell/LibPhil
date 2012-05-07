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
    static intn Compare(const T& left, const T& right) {
        return left < right ? -1 : right < left ? 1 : 0;
    }
};

// ================================================================================================
// Class to simplify keeping tables of things
// ================================================================================================
template<typename T> class CTable {

protected:

    // -- struct used to sort things
    struct SSortRange {
        uintn low, high;

        // -- constructor
        SSortRange(uintn l, uintn h) : low(l), high(h) {
        }
    };

    CDataPtr<int8> mem;
    uintn count;
    uintn alloc;
    uintn expand;

    cpointer GetPointer(uintn idx) const;
    pointer GetPointer(uintn idx);

public:

    enum {
        eDefaultExpand  = 32,
    };

    // -- constructor / destructor
    CTable(uintn exp = eDefaultExpand);
    ~CTable();

    // -- accessors
    uintn Count() const;
    const T* GetElem(uintn idx) const;
    T* GetElem(uintn idx);
    const T& operator[](uintn idx) const;
    T& operator[](uintn idx);

    // -- add an entry to the table
    void Grow(const T& val);
    void Grow();
    void GrowMultiple(const T& val, uintn n);
    void GrowMultiple(uintn n);

    // -- insert an item at the specified index
    void Insert(uintn idx, const T& val);
    void Insert(uintn idx);
    void InsertMultiple(uintn idx, const T& val, uintn n);
    void InsertMultiple(uintn idx, uintn n);

    // -- remove a specific entry from the table
    void Remove(uintn idx);
    void RemoveMultiple(uintn idx, uintn n);

    // -- swap memory with the given table
    void Swap(CTable<T>& other);

    // -- sort the table with the given comparison function
    template<typename C> void Sort();

    // -- binary search for the given element, return where it should be inserted if not found
    template<typename C> nflag Search(const T& key, uintn& index);

    // -- reset the table
    void Clear();
    void Reset();
};

// ------------------------------------------------------------------------------------------------
// Get a pointer to the memory for the given index
// ------------------------------------------------------------------------------------------------
template<typename T> inline cpointer CTable<T>::GetPointer(uintn idx) const {
    return pointer(mem) + sizeof(T) * idx;
}

template<typename T> inline pointer CTable<T>::GetPointer(uintn idx) {
    return pointer(mem) + sizeof(T) * idx;
}

// ================================================================================================
// Constructor
// ================================================================================================
template<typename T> inline CTable<T>::CTable(uintn exp) : mem(NULL), count(0), alloc(0),
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
template<typename T> inline uintn CTable<T>::Count() const {
    return count;
}

template<typename T> inline const T* CTable<T>::GetElem(uintn idx) const {
    Assert_(idx < count, "Index " UintNFmt_ " is out of range " UintNFmt_, idx, count);
    return recast_<const T*>(GetPointer(idx));
}

template<typename T> inline T* CTable<T>::GetElem(uintn idx) {
    Assert_(idx < count, "Index " UintNFmt_ " is out of range " UintNFmt_, idx, count);
    return recast_<T*>(GetPointer(idx));
}

template<typename T> inline const T& CTable<T>::operator[](uintn idx) const {
    return *GetElem(idx);
}

template<typename T> inline T& CTable<T>::operator[](uintn idx) {
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

template<typename T> inline void CTable<T>::GrowMultiple(const T& val, uintn n) {
    InsertMultiple(kNeverIndex, val, n);
}

template<typename T> inline void CTable<T>::GrowMultiple(uintn n) {
    InsertMultiple(kNeverIndex, n);
}

// ================================================================================================
// Add entries to the table at the specified index
// ================================================================================================
template<typename T> inline void CTable<T>::Insert(uintn idx, const T& val) {
    InsertMultiple(idx, val, 1);
}

template<typename T> inline void CTable<T>::Insert(uintn idx) {
    InsertMultiple(idx, 1);
}

template<typename T> inline void CTable<T>::InsertMultiple(uintn idx, const T& val, uintn n) {
    // -- first allocate some new memory, if necessary
    uintn newcount = count + n;
    if(newcount > alloc) {
        // -- get the multiple of expand to allocate that will give us just enough memory
        // -- divide by expand, rounding up, and then multiply by expand again
        uintn newmem = ((newcount - alloc - 1) / expand + 1) * expand;
        alloc += newmem;
        mem = recast_<pointer>(CMemory::ReAlloc(pointer(mem), alloc * sizeof(T)));
    }

    // -- adjust idx
    if(idx >= count)
        idx = count;
    else {
        // -- move the necessary entries
        uintn tomove = (count - idx) * sizeof(T);
        CMemory::Move(GetPointer(idx+n), GetPointer(idx), tomove);
    }

    // -- then construct the memory as a copy of val
    uintn end = idx + n;
    for(uintn i = idx; i < end; ++i)
        new (pointer(mem) + sizeof(T) * i) T(val);

    count = newcount;
}

template<typename T> inline void CTable<T>::InsertMultiple(uintn idx, uintn n) {
    // -- first allocate some new memory, if necessary
    uintn newcount = count + n;
    if(newcount > alloc) {
        // -- get the multiple of expand to allocate that will give us just enough memory
        // -- divide by expand, rounding up, and then multiply by expand again
        uintn newmem = ((newcount - alloc - 1) / expand + 1) * expand;
        alloc += newmem;
        mem = recast_<pointer>(CMemory::ReAlloc(pointer(mem), alloc * sizeof(T)));
    }

    // -- adjust idx
    if(idx >= count)
        idx = count;
    else {
        // -- move the necessary entries
        uintn tomove = (count - idx) * sizeof(T);
        CMemory::Move(GetPointer(idx+n), GetPointer(idx), tomove);
    }

    // -- then construct the memory as a copy of val
    uintn end = idx + n;
    for(uintn i = idx; i < end; ++i)
        new (pointer(mem) + sizeof(T) * i) T();

    count = newcount;
}

// ================================================================================================
// Remove an entry from the table
// ================================================================================================
template<typename T> void CTable<T>::Remove(uintn idx) {
    RemoveMultiple(idx, 1);
}

template<typename T> void CTable<T>::RemoveMultiple(uintn idx, uintn n) {
    if(n == 0)
        return;

    Assert_(idx + n <= count, "Indices [" UintNFmt_ ".." UintNFmt_ ") are out of range " UintNFmt_,
            idx, idx + n, count);

    // -- destroy the elements to be removed
    for(uintn i = idx; i < idx + n; ++i)
        CMemory::Destroy<T>(GetElem(i));

    // -- move the remaining elements down
    if(idx + n < count) {
        uintn tomove = (count - idx - n) * sizeof(T);
        CMemory::Move(GetPointer(idx), GetPointer(idx+n), tomove);
    }

    count -= n;
}

// ================================================================================================
// Swap memory with the given table
// ================================================================================================
template<typename T> void CTable<T>::Swap(CTable<T>& other) {
    pointer tempmem = pointer(mem);
    uintn tempcount = count;
    uintn tempalloc = alloc;

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
    if(count <= 1)
        return;

    CTable<SSortRange> ranges;
    ranges.Grow(SSortRange(0, count-1));

    while(ranges.Count() > 0) {
        uintn idx = ranges.Count() - 1;
        SSortRange r = ranges[idx];
        ranges.Remove(idx);

        T& pivot = *GetElem(r.high);
        uintn store = C::Compare(*GetElem(r.low), pivot) > 0 ? r.low : r.low + 1;
        for(uintn i = r.low; i < r.high; ++i) {
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
        if(store < r.high) {
            T& swap = *GetElem(store);
            T temp = swap;
            swap = pivot;
            pivot = temp;
        }
        
        // -- recurse where necessary
        if(store+1 < r.high)
            ranges.Grow(SSortRange(store+1, r.high));
        if(r.low+1 < store)
            ranges.Grow(SSortRange(r.low, store-1));
    }
}

// ================================================================================================
// Search for the given key (assumes the table is already sorted)
// ================================================================================================
template<typename T> template<typename C> nflag CTable<T>::Search(const T& key, uintn& index) {
    // -- do a binary search to find where this item should be inserted
    uintn low = 0;
    uintn high = count;
    uintn i;
    intn comp;

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
    for(uintn i = 0; i < count; ++i)
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

