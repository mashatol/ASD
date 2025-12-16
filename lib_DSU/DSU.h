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
    DSU& operator=(const DSU&) = delete;

  
    DSU(DSU&& other) noexcept;
    DSU& operator=(DSU&& other) noexcept;

    int find(int x);
    void unite(int x, int y);
    bool same(int x, int y);
    int size() const;
    int sets_count() const;
};
