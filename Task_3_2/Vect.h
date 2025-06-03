#ifndef _VECT_
#define _VECT_
#include <iostream>
#include <string>
#include "VectError.h"
using namespace std;

// Template class Vect
template<class T> class Vect {
public:
    explicit Vect() : first(0), last(0) {}
    explicit Vect(size_t _n, const T& _v = T()) {
        Allocate(_n);
        for (size_t i = 0; i < _n; ++i)
            *(first + i) = _v;
    }
    Vect(const Vect&); // конструктор копировани€
    Vect& operator=(const Vect&); // операци€ присваивани€
    ~Vect() {
#ifdef DEBUG
        cout << "Destructor of " << markName << endl;
#endif
        Destroy();
        first = 0; last = 0;
    }

    // установить отладочное им€
    void mark(std::string name) { markName = name; }
    // получить отладочное им€
    std::string mark() const { return markName; }
    size_t size() const; // получить размера вектора
    T* begin() const { return first; } // получить указатель на 1-й элемент
    T* end() const { return last; } // получить указатель на элемент, следующий за последним
    T& operator[](size_t i); // операци€ индексировани€
    void insert(T* _p, const T& _x); // вставка элемента в позицию _p
    void push_back(const T& _x); // вставка элемента в конец вектора
    void pop_back(); // удаление элемента из конца вектора
    void show() const; // вывод в cout содержимого вектора

protected:
    void Allocate(size_t _n) {
        first = new T[_n];
        last = first + _n;
    }
    void Destroy() {
        for (T* p = first; p != last; ++p)
            p->~T();
        delete[] first;
    }
    T* first; // указатель на 1-й элемент
    T* last; // указатель на элемент, следующий за последним
    std::string markName;
};

//  онструктор копировани€
template<class T>
Vect<T>::Vect(const Vect& other) {
    size_t n = other.size();
    Allocate(n);
    for (size_t i = 0; i < n; ++i)
        *(first + i) = *(other.first + i);
    markName = string("Copy of ") + other.markName;
#ifdef DEBUG
    cout << "Copy constructor: " << markName << endl;
#endif
}

// ќпераци€ присваивани€
template<class T>
Vect<T>& Vect<T>::operator=(const Vect& other) {
    if (this == &other) return *this;
    Destroy();
    size_t n = other.size();
    Allocate(n);
    for (size_t i = 0; i < n; ++i)
        *(first + i) = *(other.first + i);
    markName = string("Assigned from ") + other.markName;
    return *this;
}

// ѕолучение размера вектора
template<class T>
size_t Vect<T>::size() const {
    if (first > last)
        throw VectError();
    return (0 == first ? 0 : last - first);
}

// ќпераци€ доступа по индексу
template<class T>
T& Vect<T>::operator[](size_t i) {
    if (i > (size() - 1))
        throw VectRangeErr(0, last - first - 1, i);
    return (*(first + i));
}

// ¬ставка элемента со значением _x в позицию _p
template<class T>
void Vect<T>::insert(T* _p, const T& _x) {
    size_t n = size() + 1; // новый размер
    T* new_first = new T[n];
    T* new_last = new_first + n;
    size_t offset = _p - first;
    for (size_t i = 0; i < offset; ++i)
        *(new_first + i) = *(first + i);
    *(new_first + offset) = _x;
    for (size_t i = offset; i < n - 1; ++i)
        *(new_first + i + 1) = *(first + i);
    Destroy();
    first = new_first;
    last = new_last;
}

// ¬ставка элемента в конец вектора
template<class T>
void Vect<T>::push_back(const T& _x) {
    if (!size()) {
        Allocate(1);
        *first = _x;
    }
    else insert(end(), _x);
}

// ”даление элемента из конца вектора
template<class T>
void Vect<T>::pop_back() {
    if (last == first)
        throw VectPopErr();
    T* p = end() - 1;
    p->~T();
    last--;
}

// ¬ывод в cout содержимого вектора
template<class T>
void Vect<T>::show() const {
    cout << "\n===== Contents of " << markName << " =====" << endl;
    size_t n = size();
    for (size_t i = 0; i < n; ++i)
        cout << *(first + i) << " ";
    cout << endl;
}
#endif