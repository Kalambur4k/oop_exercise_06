#include <stdexcept>
#include "stack.cpp"

template <class T, size_t BLOCK_SIZE>
class TAllocator {
public:

    T *allocate()
    {
        int idx;
        if ( !free.Empty() ) {
            idx = free.Pop();
        } else if ( last < BLOCK_SIZE ) {
            idx = last++;
        } else {
            throw std::runtime_error("Allocator has no more free blocks");
        }
        return &block[idx];
    }

    void deallocate(T *ptr)
    {
        int idx = ptr - &block[0];
        free.Push( idx );
    }

private:
    T block[BLOCK_SIZE];
    TStack<int> free;
    int last = 0;

};
