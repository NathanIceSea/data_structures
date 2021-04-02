#ifndef __VECTOR_BOOK_IMPL_H__
#define __VECTOR_BOOK_IMPL_H__ 1

namespace book {

typedef unsigned int Rank;
const Rank DEFAULT_CAPACITY = 3;

template <typename T>
class Vector {
protected:
    Rank _size;
    Rank _capacity;
    T *_buf;
    void copy_from(T const *buf, Rank lo, Rank hi);
    void expand(); // 扩容
    void shrink(); // 收缩
    void sort();   // 排序
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
    Vector(Rank _c = DEFAULT_CAPACITY) {
        _buf = new T[_c];
        _capacity = _c;
        _size = 0;
    }
    // 从数组和区间拷贝初始化元素
    Vector(T const buf[], Rank len) { Vector(buf, 0, len); }
    Vector(T const buf[], Rank lo, Rank hi) {
        copy_from(buf, lo, hi);
        Rank len = hi - lo;
        _buf = new T[len];
        _capacity = DEFAULT_CAPACITY > len ? DEFAULT_CAPACITY : len;
        _size = len;
    }
    // 从其它向量初始化元素
    Vector(Vector<T> const &v) { Vector(v._buf, 0, v._size); }
    Vector(Vector<T> const &v, Rank lo, Rank hi) { Vector(v._buf, lo, hi); }
// 析构函数
    ~Vector() { delete[] _buf; }
// 只读访问接口
    Rank size() const { return _size; }
    Rank len() const { return _size; }
    bool empty() const { return _size == 0; }
    bool disordered() const;
};

template <typename T>
void Vector<T>::heapSort(Rank lo, Rank hi) {

}

} // namespace book

#endif // !__VECTOR_BOOK_IMPL_H__