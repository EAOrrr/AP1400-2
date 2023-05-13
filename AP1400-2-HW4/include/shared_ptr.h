#ifndef SHARED_PTR
#define SHARED_PTR

template<typename valueType>
class SharedPtr{
    public:
        SharedPtr();
        SharedPtr(valueType* &&ptr);
        SharedPtr(SharedPtr& another);
        SharedPtr(SharedPtr&& another);
        ~SharedPtr();
        valueType* get();
        size_t use_count() const;
        void reset();
        void reset(valueType*&& ptr);
        SharedPtr& operator=(SharedPtr& another);
        SharedPtr& operator=(SharedPtr&& another);
        valueType* operator->();
        valueType& operator*();
        explicit operator bool() const;
    private:
        valueType* _p;
        size_t* shared_count;
};

template<typename valueType>
SharedPtr<valueType> make_shared(valueType&& value);
#include"shared_ptr.hpp"
#endif //SHARED_PTR