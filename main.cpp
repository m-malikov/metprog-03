#include "GenScatterHierarchy.h"
#include <typeinfo>
#include <iostream>

template <class T>
struct Holder {
	T value_;
};

typedef TypeList<double, int, double> TList;
typedef GenScatterHierarchy<TList, Holder> WidgetInfo;

int main() {
	WidgetInfo obj;
	std::cout <<  typeid(Field<1>(obj)).name() << std::endl;
	std::cout <<  typeid(Field<2>(obj)).name() << std::endl;
	return 0;
}
