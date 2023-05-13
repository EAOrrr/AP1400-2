#ifndef UNIQUE_PTR
#define UNIQUE_PTR
#include<utility>
template<class T>
class UniquePtr{
    private:
        T* _p;
    public:
        UniquePtr();
        UniquePtr(const UniquePtr& other) = delete;
        UniquePtr(UniquePtr &&other);
        UniquePtr(T* && p);
        ~UniquePtr();
        T* get();
        void reset();
        void reset(T*&& newOne);
        T* release();
        void operator=(const UniquePtr& other) = delete;
        UniquePtr& operator=(UniquePtr&& other);
        T* operator->();
        T& operator*();
        explicit operator bool() const;
        
};
template<class T>
UniquePtr<T> make_unique(T && value);
// function declaration before definition
// so Function implementation after Function prototype
#include"unique_ptr.hpp"

#endif //UNIQUE_PTR