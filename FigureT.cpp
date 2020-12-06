#include <iostream>
#include <memory>
#include <algorithm>

template<typename T>
struct Rectangle {//Шаблон Прямоуголньника
    using coords = std::pair<T, T>;//Вершины фигуры
    coords a, b, c, d;
};
