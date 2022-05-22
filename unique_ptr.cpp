// https://lejabque.github.io/cpp-notes/16_smart_pointers.html

template <typename T>
struct unique_ptr {
    unique_ptr()
        : ptr(nullptr) {}
    
    unique_ptr(T* ptr)
        : ptr(ptr) {}
    
    ~unique_ptr() {
        delete ptr;
    }
    
    T& operator*() const {
        return *ptr;
    }
    
    T* operator->() const noexcept {
        return ptr;
    }
    
    T* get() const {
        return ptr;
    }
    
    T* release() {
        T* tmp = ptr;
        ptr = nullptr;
        return tmp;
    }
    
    void reset(T* p) {
        delete ptr;
        ptr = p;
    }
    
    // copy delete
    unique_ptr(unique_ptr const& other) = delete;
    unique_ptr& operator=(unique_ptr const& other) = delete;
    
    // std::move
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        reset(other.release());
        return *this;
    }
    
    unique_ptr(unique_ptr&& other) noexcept
        : ptr(other.release()) {}
    
  private:
    T* ptr;
};

int main(int argc, const char * argv[]) {
    unique_ptr<int> ptr(new int(1));
    return 0;
}
