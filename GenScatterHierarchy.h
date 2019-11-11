#include "TypeList.h"

template <typename TL, template <class> class Unit>
class GenScatterHierarchy;

template <typename ...Args, template <class> class Unit>
class GenScatterHierarchy<TypeList<Args...>, Unit>
	: public GenScatterHierarchy<typename TypeList<Args...>::Head, Unit>,
	  public GenScatterHierarchy<typename TypeList<Args...>::Tail, Unit> {
public:
	typedef TypeList<Args...> TList;
	typedef GenScatterHierarchy<typename TypeList<Args...>::Head, Unit> LeftBase;
	typedef GenScatterHierarchy<typename TypeList<Args...>::Tail, Unit> RightBase;

	template <typename T> 
	struct Rebind {
		typedef Unit<T> Result;
    	};
};

template <class AtomicType, template <class> class Unit>
class GenScatterHierarchy: public Unit<AtomicType> {
public:
	typedef Unit<AtomicType> LeftBase;	

	template <typename T> 
	struct Rebind {
		typedef Unit<T> Result;
    	};
};

template<template <class> class Unit>
class GenScatterHierarchy<NullType, Unit> {};


template <class H, int i> struct FieldHelper;

template <class H>
struct FieldHelper<H, 0> {
    typedef typename H::TList::Head ElementType;
    typedef typename H::template Rebind<ElementType>::Result UnitType;
    
    typedef typename H::LeftBase LeftBase;
    
    static UnitType& Do(H& obj) {
        LeftBase& leftBase = obj;
        return leftBase;
    }
};

template <class H, int i>
struct FieldHelper {
    typedef typename TypeAt<i, typename H::TList>::ElementType ElementType;
    typedef typename H::template Rebind<ElementType>::Result UnitType;
    
    typedef typename H::RightBase RightBase;

    static UnitType& Do(H& obj) {
        RightBase& rightBase = obj;
        return FieldHelper<RightBase, i - 1>::Do(rightBase);
    }
};

template <int i, class H>
typename FieldHelper<H, i>::UnitType&
Field(H& obj) {
	return FieldHelper<H, i>::Do(obj);
} 
