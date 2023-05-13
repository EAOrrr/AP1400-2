#include"shared_ptr.h"

template<typename valueType>
SharedPtr<valueType>::SharedPtr():_p{nullptr}, shared_count{nullptr}{};

template<typename valueType>
SharedPtr<valueType>::SharedPtr(valueType*&& ptr):_p{std::exchange(ptr, nullptr)}{
    if(_p == nullptr){
        shared_count = nullptr;
    }
    else{
        shared_count = new size_t{1};
    }
};

template<typename valueType>
SharedPtr<valueType>::SharedPtr(SharedPtr& another){
    _p = another._p;
    if(_p != nullptr){
        if(another.shared_count == nullptr){
            another.shared_count = new size_t{1};
        }
        shared_count = another.shared_count;
        ++(*shared_count);
    }
}

template<typename valueType>
SharedPtr<valueType>::SharedPtr(SharedPtr&& another){
    _p = std::exchange(another._p, nullptr);
    shared_count = std::exchange(another._p, nullptr);
}

template<typename valueType>
SharedPtr<valueType>::~SharedPtr(){
    if(shared_count != nullptr){
        --(*shared_count);
        if(*shared_count < 1){
            delete _p;
            delete shared_count;
        }
    }
    _p = nullptr;
    shared_count = nullptr;
}

template<typename valueType>
size_t SharedPtr<valueType>::use_count() const{
    if(shared_count == nullptr) return 0;
    return *shared_count;
}

template<typename valueType>
valueType* SharedPtr<valueType>::get(){
    return _p;
}

template<typename valueType>
void SharedPtr<valueType>::reset(){
    if(shared_count != nullptr){
        --(*shared_count);
        if(*shared_count < 1){
            delete _p;
            delete shared_count;
        }
    }
    _p = nullptr;
    shared_count = nullptr;
}
template<typename valueType>
void SharedPtr<valueType>::reset(valueType*&& ptr){
    if(ptr == nullptr){
        reset();
    }
    else{
        if(shared_count != nullptr){
            --*shared_count;
            if(*shared_count < 1){
                delete _p;
                delete shared_count;
            }
        }
        _p = std::exchange(ptr, nullptr);
        shared_count = new size_t{1};
    }

}

template<typename valueType>
valueType* SharedPtr<valueType>::operator->(){
    return _p;
}

template<typename valueType>
valueType& SharedPtr<valueType>::operator*(){
    return *_p;
}

template<typename valueType>
SharedPtr<valueType>& SharedPtr<valueType>::operator=(SharedPtr<valueType>& another){
    if(&another == this) return *this;
    if(shared_count != nullptr){
        --(*shared_count);
        if(*shared_count < 1){
            delete _p;
            delete shared_count;
        }
    }
    _p = another._p;
    shared_count = another.shared_count;
    ++*shared_count;
    return *this;
}

template<typename valueType>
SharedPtr<valueType>& SharedPtr<valueType>::operator=(SharedPtr<valueType>&& another){
    if(&another == this) return *this;
    if(shared_count != nullptr){
        --(*shared_count);
        if(*shared_count < 1){
            delete _p;
            delete shared_count;
        }
    }
    _p = std::exchange(another._p, nullptr);
    shared_count = std::exchange(another.shared_count, nullptr);
    return *this;
}

template<typename valueType>
SharedPtr<valueType>::operator bool() const{
    if(_p == nullptr) return false;
    return true;
}

template<typename valueType>
SharedPtr<valueType> make_shared(valueType&& value){
    return SharedPtr(new valueType{std::forward<valueType>(value)});
}