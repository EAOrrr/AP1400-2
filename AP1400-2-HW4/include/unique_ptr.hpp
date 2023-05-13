#include"unique_ptr.h"
template<class T>
UniquePtr<T>::UniquePtr():_p(nullptr){};

template<class T>
UniquePtr<T>::UniquePtr(T* &&p){
    _p = std::move(p);
}

template<class T>
UniquePtr<T>::UniquePtr(UniquePtr<T> && other){
    _p = std::exchange(other._p, nullptr);
}

template<class T>
UniquePtr<T>::~UniquePtr(){
    if(_p != nullptr){
        delete _p;
    }
}

template<class T>
T* UniquePtr<T>::get(){
    return _p;
}

template<class T>
void UniquePtr<T>::reset(){
    if(_p != nullptr) delete _p;
    _p = nullptr;
}

template<class T>
void UniquePtr<T>::reset(T* &&newOne){
    if(_p != nullptr) delete _p;
    _p = std::exchange(newOne, nullptr);
}

template<class T>
T* UniquePtr<T>::release(){
    T* temp = std::exchange(_p, nullptr);
    return temp;
}

template<class T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other){
    if(&other == this) return *this;
    if(_p != nullptr){
        delete _p;
    }
    _p = std::exchange(other._p, nullptr);
    return *this;
}

template<class T>
T* UniquePtr<T>::operator->(){
    return _p;
}

template<class T>
T& UniquePtr<T>::operator*(){
    return *_p;
}

template<class T>
UniquePtr<T>::operator bool() const{
    if(_p == nullptr) return false;
    return true;
}

template<class T>
UniquePtr<T>  make_unique(T&& value){
    return UniquePtr(new T{value});
}