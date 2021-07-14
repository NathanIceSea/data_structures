#ifndef __BOOK_VECTOR_IMPL_H__
#define __BOOK_VECTOR_IMPL_H__ 1

namespace book {

typedef unsigned int Rank;
const Rank DEFAULT_CAPACITY = 3;

template <typename T>
class Vector {
protected:
    Rank _size;
    Rank _capacity;
    T *_buf;
    // 基于复制的构造方法，数据源区间 src[lo, hi)，重置 size、cap 和 buf
    void copyFrom(T const *src, Rank lo, Rank hi);
    void expand(); // 扩容
    void shrink(); // 收缩
    // 排序算法
    void bubbleSort(Rank lo, Rank hi);
    void selectionSort(Rank lo, Rank hi);
    void mergeSort(Rank lo, Rank hi);
    void quickSort(Rank lo, Rank hi);
    void heapSort(Rank lo, Rank hi);
    void (Vector::*const _sort_fn)(Rank, Rank) = &Vector::heapSort;

public:
    // 构造函数
    // 初始化
    Vector(Rank _c = DEFAULT_CAPACITY)
    {
        _buf = new T[_c];
        _capacity = _c;
        _size = 0;
    }
    // 从数组和区间拷贝初始化元素
    Vector(T const buf[], Rank len) { Vector(buf, 0, len); }
    Vector(T const buf[], Rank lo, Rank hi)
    {
        Rank len = hi - lo;
        Rank capacity = DEFAULT_CAPACITY > len * 2 ? DEFAULT_CAPACITY : len * 2;
        _buf = new T[capacity];
        copyFrom(buf, lo, hi);
        _capacity = capacity;
        _size = len;
    }
    // 从其它向量初始化元素
    Vector(Vector<T> const &v) { Vector(v._buf, 0, v._size); }
    Vector(Vector<T> const &v, Rank lo, Rank hi) { Vector(v._buf, lo, hi); }
    // 析构函数
    ~Vector() { delete[] _buf; }
    // 运算符重载
    T &operator[](Rank r) const;
    Vector<T> &operator=(Vector<T> const &);
    // 只读访问接口
    Rank size() const { return _size; }
    Rank len() const { return _size; }
    bool empty() const { return _size == 0; }
    bool disordered() const;
    // 无序查找
    Rank find(T const &e, Rank lo, Rank hi) const;
    Rank find(T const &e) const { return find(e, 0, _size); }
    // 有序查找
    Rank search(T const &e, Rank lo, Rank hi) const;
    Rank search(T const &e) const { return search(e, 0, _size); }
    // 可变访问接口
    T remove(Rank r);
    Rank remove(Rank lo, Rank hi);
    Rank insert(Rank r, T const &e);
    // 默认作为末尾元素插入
    Rank insert(T const &e) { return insert(_size, e); }
    void sort(Rank lo, Rank hi);
    void sort() { sort(0, _size); }
    void shuffle(Rank lo, Rank hi);
    void shuffle() { shuffle(0, _size); }
    // 无序去重
    Rank deduplicate();
    // 有序去重
    Rank uniquify();
    // 遍历
    void traverse(void (*)(T &));
    template <typename VST>
    void traverse(VST &);
};

template <typename T>
void Vector<T>::copyFrom(T const *src, Rank lo, Rank hi)
{
    _buf = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi) {
        _buf[_size++] = src[lo++];
    }
}

template <typename T>
void Vector<T>::expand() {
    // 容量已满时才进行扩容，且容量不低于默认容量
    if (_size < _capacity) return;
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T *_buf_old = _buf;
    _buf = new T[_capacity *= 2];
    copyFrom(_buf_old, 0, _size);
    delete[] _buf_old;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& v) {
    if (_buf != nullptr) delete[] _buf;
    copyFrom(v._buf, 0, v._size);
    return *this;
}

template <typename T>
void Vector<T>::heapSort(Rank lo, Rank hi)
{
}

} // namespace book

#endif // !__BOOK_VECTOR_IMPL_H__