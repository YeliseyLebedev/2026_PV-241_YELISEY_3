#ifndef SMARTPTR_H
#define SMARTPTR_H

template <typename T>
class SmartPtr
{
private:
    T* ptr;

public:
    explicit SmartPtr(T* p = nullptr) : ptr(p) {}

    ~SmartPtr() {
        delete ptr;
    }

    SmartPtr(const SmartPtr& other) = delete;
    SmartPtr& operator=(const SmartPtr& other) = delete;

    SmartPtr(SmartPtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    SmartPtr& operator=(SmartPtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    T* get() const { return ptr; }

    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    explicit operator bool() const { return ptr != nullptr; }

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};

#endif