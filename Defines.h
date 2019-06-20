#ifndef DEFINES_H
#define DEFINES_H

#include <map>
#include <set>
#include <list>
#include <queue>
#include <vector>
#include <memory>
#include <algorithm>
#include <QString>


typedef unsigned int u32;

template<typename T>
struct vec2
{
    vec2();
    vec2(T _x, T _y);
    T x, y;
};

//Returns true if s1 is less than s2
struct StringLT
{
    bool operator()(QString s1, QString s2) const
    {
        return QString::compare(s1, s2);
    }
};

template<typename T>
inline vec2<T>::vec2() : x(T(0)), y(T(0)) {}

template<typename T>
inline vec2<T>::vec2(T _x, T _y) : x(_x), y(_y) {}


const static int TILE_ROW_SIZE = 50;

const static int TILE_COL_SIZE = 50;

const static int NUM_TILES_PER_ROW = 8;

const static int NUM_TILES_PER_COL = 8;

const static int NUM_TILES = NUM_TILES_PER_ROW*NUM_TILES_PER_COL;

const static int MAX_TEMP_BOARD = 1000;

#define DEFINE_PTRS(C)							\
typedef std::shared_ptr<C>			C##Ptr;		\
typedef std::shared_ptr<const C>	C##CPtr;	\
typedef std::weak_ptr<C>			C##WPtr;	\
typedef std::weak_ptr<const C>		C##WCPtr;	\
typedef std::unique_ptr<C>			C##APtr;	\
typedef std::unique_ptr<const C>	C##ACPtr;	\
typedef std::unique_ptr<C>			C##UPtr;	\
typedef std::unique_ptr<const C>	C##UCPtr;

#define DEFINE_CLASS_PTR(C)						\
class C;										\
DEFINE_PTRS(C)

#define DEFINE_STRUCT_PTR(C)					\
struct C;										\
DEFINE_PTRS(C)


#define AutoPtr		std::unique_ptr
#define ScopedPtr	std::unique_ptr
#define SharedPtr	std::shared_ptr
#define WeakPtr		std::weak_ptr
#define UniquePtr	std::unique_ptr

#define PLessF		std::less
#define PEqualF		std::equal_to

#define PMap		std::map
#define PSet		std::set
#define PBitSet		std::bitset
#define MapPair		std::pair
#define PList		std::list
#define PArray		std::vector
#define PQueue		std::queue


#define FastArray	std::vector

#define PException	std::exception


#define ForEach(_type, _container, _it) for (_type::iterator _it = (_container).begin(), _end##_it = (_container).end(); _it != _end##_it; ++_it)
#define ForEachC(_type, _container, _it) for (_type::const_iterator _it = (_container).begin(), _end##_it = (_container).end(); _it != _end##_it; ++_it)

#endif // DEFINES_H
