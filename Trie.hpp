#ifndef TRIE_HPP
#define TRIE_HPP

#include "Node.hpp"
#include <iostream>
#include <vector>
#include <string>

class Trie {
private:
    Node* root;
    int size;
    std::vector<std::string> split(const std::string& classi);

public:
    Trie();
    ~Trie();

    void load(const std::string& filename);
    bool insert(const std::string& classi);

    bool erase(const std::string& classi);
    void print();
    void print_re(Node* node, const std::string& path, std::vector<std::string>& res);
    bool empty();
    void clear();
    void clear_re(Node* node);
};

#endif