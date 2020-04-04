template <typename T>
class unique_ptr{

    T* data;
    public:
    constexpr unique_ptr() noexcept : data{nullptr} {}
    constexpr unique_ptr(nullptr) noexcept : data{nullptr} {}
    explicit unique_ptr(T* ptr) noexcept : data{ptr} {}
    ~unique_ptr() noexcept {delete data;}

    //copy and move constructors
    unique_ptr(unique_ptr& pv) = delete ;
    unique_ptr(unique_ptr&& pv) noexcept : data{pv.release()} {}

    //copy and move assignments
    unique_ptr& operator=(unique_ptr& pv) = delete ; 
    unique_ptr& operator=(unique_ptr&& pv) noexcept {
        reset(pv.release());
        return *this;
    }
    T* get() noexcept const { return data;}
    T* release() noexcept {
        T* tmp = get();
        data = nullptr;
        return tmp; 
    }
    void reset(T* pv) noexcept{
        std::swap(data,pv);
        if(pv != nullptr)
            delete pv;
    }

};
template<typename U, typename ... types>
unique_ptr<U> make_unique(types&&... y){
    unique_ptr<U> obj{new U{std::forward<types>(y)...}};
    return obj;
}

int main(){
    unique_ptr<int> x_obj;
    unique_ptr<int> p = make_unique<int> (3,4,"Azza",x_obj);
}