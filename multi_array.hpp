#ifndef __DYNAMIC_GRID__
#define __DYNAMIC_GRID__
    #include <cstdarg>
    #include <vector>
    #include <iostream>
    using namespace std;

    template<typename T, int... D>
    class grid;

    template<typename T, int... D>
    class grid_iter {
        public:
        grid<T, D...>* source;
        int index = -1, generation = -1, prev_dimensions = -1, cached_dimensions = -1;

        grid_iter(grid<T, D...>* pointer, int index) {
            this->source = pointer;
            this->index = index;
            this->generation = 0;
            initialize(index);
        }

        grid_iter(grid<T, D...>* pointer, int index, int generation, int prev_dimensions, int cached_dimensions) {
            this->source = pointer;
            this->index = index;
            this->generation = generation;
            this->prev_dimensions = prev_dimensions;
            this->cached_dimensions = cached_dimensions;
        }

        operator T () {
            grid<T, D...>* source = this->source;
            int prev_dimensions = this->prev_dimensions;
            delete this;
            return *(source->pointer + prev_dimensions);
        }

        grid_iter<T, D...>& operator = (T value) {
            *(source->pointer + prev_dimensions) = value;
            return *this;
        }

        grid_iter<T, D...>& operator[](int index) {
            initialize(index);
            return *this;
        }

        void initialize(int index) {
            if (generation == 1) {
                prev_dimensions = (source->dimensions[generation - 1] * index) + this->index;
                cached_dimensions = source->dimensions[generation - 1] * source->dimensions[generation];
            } else {
                prev_dimensions = (index * cached_dimensions) + prev_dimensions;
                cached_dimensions = cached_dimensions * source->dimensions[generation];
            }

            generation++;
            this->index = index;
        }
    };

    template<typename T, int... D>
    class grid {
        public:
        int dimensions[sizeof...(D)]{ D... };
        T* pointer = nullptr;
        int length = -1;

        ~grid() {
            delete[] pointer;
        }

        grid() {
            length = dimensions[0];

            for (size_t i = 1; i < sizeof...(D); i++)
                length *= dimensions[i];

            pointer = new T[length]();
        }

        grid_iter<T, D...>& operator[](int index) {
            return *new grid_iter<T, D...>(this, index);
        }
    };

#endif
