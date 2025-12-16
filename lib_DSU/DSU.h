#pragma once
#include <stdexcept>

class DSU {
private:
    int* _parent;
    int* _rank;
    int _size;

public:
    explicit DSU(int n);
    ~DSU();

    DSU(const DSU&) = delete;
    DSU& operator=(const DSU&) = delete;//

  
    DSU(DSU&& other) noexcept;
    DSU& operator=(DSU&& other) noexcept; ////

    int find(int x);
    void unite(int x, int y);
    bool same(int x, int y);
    int size() const;
    int sets_count() const;
};

inline DSU::DSU(int n) : _size(n) {
    if (n <= 0) {
        throw std::invalid_argument("DSU size must be positive");
    }

    _parent = new int[n];
    _rank = new int[n];

    for (int i = 0; i < n; ++i) {
        _parent[i] = i;
        _rank[i] = 0;
    }
}

inline DSU::~DSU() {
    delete[] _parent;
    delete[] _rank;
}

inline DSU::DSU(DSU&& other) noexcept
    : _parent(other._parent), _rank(other._rank), _size(other._size) {
    other._parent = nullptr;
    other._rank = nullptr;
    other._size = 0;
}

inline DSU& DSU::operator=(DSU&& other) noexcept {
    if (this != &other) {
        delete[] _parent;
        delete[] _rank;

        _parent = other._parent;
        _rank = other._rank;
        _size = other._size;

        other._parent = nullptr;
        other._rank = nullptr;
        other._size = 0;
    }
    return *this;
}

inline int DSU::find(int x) {
    if (x < 0 || x >= _size) {
        throw std::out_of_range("DSU index out of range in find");
    }

    if (_parent[x] != x) {
        _parent[x] = find(_parent[x]); 
    }
    return _parent[x];
}

inline void DSU::unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) return; 

 
    if (_rank[rootX] < _rank[rootY]) {
        _parent[rootX] = rootY;
    }
    else if (_rank[rootX] > _rank[rootY]) {
        _parent[rootY] = rootX;
    }
    else {
        _parent[rootY] = rootX;
        _rank[rootX]++;
    }
}


inline bool DSU::same(int x, int y) {
    return find(x) == find(y);
}


inline int DSU::size() const {
    return _size;
}


inline int DSU::sets_count() const {
    int count = 0;
    for (int i = 0; i < _size; ++i) {
        if (_parent[i] == i) {
            count++;
        }
    }
    return count;
}