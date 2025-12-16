#include "DSU.h"

DSU::DSU(int n) : _size(n) {
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
DSU::~DSU() {
    delete[] _parent;
    delete[] _rank;
}

DSU::DSU(DSU&& other) noexcept
    : _parent(other._parent), _rank(other._rank), _size(other._size) {
    other._parent = nullptr;
    other._rank = nullptr;
    other._size = 0;
}

DSU& DSU::operator=(DSU&& other) noexcept {
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

int DSU::find(int x) {
    if (x < 0 || x >= _size) {
        throw std::out_of_range("DSU index out of range in find");
    }

    if (_parent[x] != x) {
        _parent[x] = find(_parent[x]);
    }
    return _parent[x];
}

void DSU::unite(int x, int y) {
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


bool DSU::same(int x, int y) {
    return find(x) == find(y);
}


int DSU::size() const {
    return _size;
}


int DSU::sets_count() const {
    int count = 0;
    for (int i = 0; i < _size; ++i) {
        if (_parent[i] == i) {
            count++;
        }
    }
    return count;
}