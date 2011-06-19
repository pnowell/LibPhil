#pragma once

// -- libs includes
#include "core/types.h"

// ================================================================================================
// The pointer type that works for both data and runtime as it can be set to either
// an absolute address or a relative address
// ================================================================================================
template<typename T> class CDataPtr {

public:

    enum EMode {
        eAbsolute   = 0,
        eRelative   = 1
    };

protected:

    uint64 data;

public:

    // -- constructor
    CDataPtr(T* p = NULL);

    // -- acting as a normal pointer
    T* operator->() const;
    operator T*() const;
    const CDataPtr<T>& operator=(T* other);
    const CDataPtr<T>& operator=(const CDataPtr<T>& other);

    // -- types of casts
    template<typename S>
    const CDataPtr<T>& StCast(const CDataPtr<S>& other);
    template<typename S>
    const CDataPtr<T>& ReCast(const CDataPtr<S>& other);

    // -- basic mutator and accessor
    void SetRel(T* p);
    void SetAbs(T* p);
    T* Get() const;
};

// ================================================================================================
// Constructor
// ================================================================================================
template<typename T>
inline CDataPtr<T>::CDataPtr(T* p) {
    SetAbs(p);
}

// ================================================================================================
// Operators to act as a normal pointer
// ================================================================================================
template<typename T>
inline T* CDataPtr<T>::operator->() const {
    return Get();
}

template<typename T>
inline CDataPtr<T>::operator T*() const {
    return Get();
}

template<typename T>
inline const CDataPtr<T>& CDataPtr<T>::operator=(T* other) {
    SetAbs(other);
    return *this;
}

template<typename T>
inline const CDataPtr<T>& CDataPtr<T>::operator=(const CDataPtr<T>& other) {
    SetAbs(other.Get());
    return *this;
}

// ================================================================================================
// Types of casts
// ================================================================================================
template<typename T> template<typename S>
inline const CDataPtr<T>& CDataPtr<T>::StCast(const CDataPtr<S>& other) {
    return *this;
}

template<typename T> template<typename S>
inline const CDataPtr<T>& CDataPtr<T>::ReCast(const CDataPtr<S>& other) {
    return *this;
}

// ================================================================================================
// Relative pointer assignment
// ================================================================================================
template<typename T>
inline void CDataPtr<T>::SetRel(T* p) {
    data = (uint64(recast_<puint>(p)) << 1) | 1;
}

template<typename T>
inline void CDataPtr<T>::SetAbs(T* p) {
    data = uint64(recast_<puint>(p)) << 1;
}

template<typename T>
inline T* CDataPtr<T>::Get() const {
    uint64 rel = data & 1;
    return recast_<T*>((data >> 1) + rel * recast_<puint>(this));
}

