#include <iostream>
#include <memory>
#include <algorithm>

template<typename T>
struct Rectangle {//������ ���������������
    using coords = std::pair<T, T>;//������� ������
    coords a, b, c, d;
};
