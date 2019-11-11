struct NullType {};

template<typename ...Args>
struct TypeList {
    typedef NullType Head;
    typedef NullType Tail;
};

typedef TypeList<> EmptyTypeList;

template<typename H>
struct TypeList<H> {
	typedef H Head;
	typedef NullType Tail;
};

template<typename H, typename ...T>
struct TypeList<H, T...> {
    typedef H Head;
    typedef TypeList<T...> Tail;
};

template<unsigned int N, typename ...Args>
struct TypeAt;

template<typename ...Args>
struct TypeAt<0, TypeList<Args...>> {
    typedef typename TypeList<Args...>::Head ElementType;
};

template<unsigned int N, typename ...Args>
struct TypeAt<N, TypeList<Args...>> {
    typedef typename TypeAt<N - 1, typename TypeList<Args...>::Tail>::ElementType ElementType;
};
