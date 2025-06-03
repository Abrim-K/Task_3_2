#include "Vect.h"
#include <iostream>
#include <string>
using namespace std;

template<class T> void SomeFunction(Vect<T> v) {
    std::cout << "Reversive output for " << v.mark() << endl;
    size_t n = v.size();
    for (int i = n - 1; i >= 0; --i)
        std::cout << v[i] << " ";
    std::cout << endl;
}

int main() {
    try {
        string initStr[5] = { "first", "second", "third", "fourth", "fifth" };
        Vect<int> v1(10); v1.mark(string("v1"));
        size_t n = v1.size();
        for (int i = 0; i < n; ++i)
            v1[i] = i + 1;
        v1.show();
        SomeFunction(v1);

        try {
            Vect<string> v2(5);
            v2.mark(string("v2"));
            n = v2.size();
            for (int i = 0; i < n; ++i)
                v2[i] = initStr[i];
            v2.show();
            v2.insert(v2.begin() + 3, "After third");
            v2.show();
            cout << v2[6] << endl;
            v2.push_back("Add_1");
            v2.push_back("Add_2");
            v2.push_back("Add_3");
            v2.show();
            v2.pop_back();
            v2.pop_back();
            v2.show();
        }
        catch (VectError& vre) { vre.ErrMsg(); }

        try {
            Vect<int> v3;
            v3.mark(string("v3"));
            v3.push_back(41);
            v3.push_back(42);
            v3.push_back(43);
            v3.show();
            Vect<int> v4;
            v4.mark(string("v4"));
            v4 = v3;
            v4.show();
            v3.pop_back();
            v3.pop_back();
            v3.show();
            v3.pop_back();
            v3.pop_back();
        }
        catch (VectError& vre) { vre.ErrMsg(); }
    }
    catch (...) { cerr << "Epilogue: error of Main().\n"; }
    return 0;
}