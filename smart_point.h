#ifndef _SMART_POINT_
#define _SMART_POINT_

#include <iostream>

namespace luo {

//宏定义函数，简化代码
#define COMPARE(_op_)                                           \
bool operator _op_ (const SmartPointer& o) const {              \
    return mPointer _op_ o.mPointer;                            \
}                                                               \
bool operator _op_ (const T* o) const {                         \
    return mPointer _op_ o;                                     \
}
                                            
template <typename T>
class SmartPointer {
public:
    //ctor
    SmartPointer():mPointer(NULL) {
        //for test
        std::cout<<"create unknow smart pointer."<<std::endl;
    }
    SmartPointer(T *p):mPointer(p) {
        if (mPointer) mPointer->incRefCount();
        //for test
        std::cout<<"create smart pointer at "<<static_cast<const void*>(p)<<std::endl;
    }

    //dtor
    ~SmartPointer() {
        //for test
        std::cout<<"release smart pointer at "<<static_cast<const void*>(mPointer)<<std::endl;
        if(mPointer && mPointer->decRefCount() == 0) delete mPointer;
    }

    //copy
    SmartPointer(const SmartPointer &other):mPointer(other.mPointer) {
        if (mPointer) mPointer->incRefCount();
        //for test
        std::cout<<"copy smart pointer at "<<static_cast<const void*>(other.mPointer)<<std::endl;

    }

    //Assignment
    SmartPointer &operator = (const SmartPointer &other) {
        //创建临时对象
        T *temp(other.mPointer);
        if (temp) temp->incRefCount();

        //销毁原对象
        if (mPointer && mPointer->decRefCount() == 0) delete mPointer;

        mPointer = temp;
        return *this;
    }

    //重载运算符
    T& operator* () const {return *mPointer;}
    T* operator-> () const {return mPointer;}

    COMPARE(==);
    COMPARE(!=);
private:
    T *mPointer;
};   

class RefBase
{
public:
    RefBase():mCount(0) {}
    void incRefCount() {
        mCount++;
    }
    int decRefCount() {
        return --mCount;
    }

    int getRefCount() {
        return mCount;
    }

    virtual ~RefBase() {}
private:
    int mCount;
};
}
#endif //_SMART_POINT_