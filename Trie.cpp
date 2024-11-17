#include "Trie.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

Trie::Trie() : root(new Node("")), size(0) {}
Trie::~Trie() {
    clear();
    delete root;
}

std::vector<std::string> Trie::split(const std::string& classi) {
    std::vector<std::string> parsed;    // stores parsed comma delimited strings
    std::istringstream stream(classi);
    std::string label;

    // parse the input classification
    while (std::getline(stream, label, ',')) {
        parsed.push_back(label);
    }
    return parsed;
}

void Trie::load(const std::string& filename) {
    std::ifstream file(filename);
    std::string classi;
    while (std::getline(file, classi)) {
        insert(classi);
    }
}

bool Trie::insert(const std::string& classi) {
    // std::vector<std::string> parsed;    // stores parsed comma delimited strings
    // std::istringstream stream(classi);
    // std::string label;

    // // parse the input classification
    // while (std::getline(stream, label, ',')) {
    //     parsed.push_back(label);
    // }
    std::vector<std::string> parsed = split(classi);
    Node* curr = root;


    for (int i = 0; i < parsed.size(); i ++ ) {
        auto it = std::find_if(
            curr->children.begin(), curr->children.end(),
            [&parsed, i](Node* node) { return node->getLabel() == parsed[i]; }
        );
        
        if (it == curr->children.end()) {    // child does not exist yet, then create
            Node* child = new Node(parsed[i]);
            curr->children.push_back(child);
            curr = child;
            size ++ ;
        } else {    //  child already there
            curr = *it;  // move the curr pointer
            if (i == parsed.size() - 1) return 0;
        }
    }
    return 1;
}

bool Trie::erase(const std::string& classi) {
    Node* curr = root;
    Node* prev = root;
    std::vector<std::string> parsed = split(classi);

    for (int i = 0; i < parsed.size(); i ++ ) {
         auto it = std::find_if(
            curr->children.begin(), curr->children.end(),
            [&parsed, i](Node* node) { return node->getLabel() == parsed[i]; }
        );

        if (it == curr->children.end()) {
            return 0;
        } else {
            prev = curr;
            curr = *it;
        }
    }
    
    if (curr->children.empty()) {
        auto it = std::find(prev->children.begin(), prev->children.end(), curr);
        if (it != prev->children.end()) {
            prev->children.erase(it);   // remove the current node from it's parent's children vector
        }
        delete curr;
        return 1;
    } else {
        return 0;
    }
}

void Trie::print() {
    if (!root->children.size()) {
        std::cout << "trie is empty\n";
        return;
    }
    std::vector<std::string> res;
    print_re(root, "", res);

    for (size_t i = 0; i < res.size(); ++i) {
        if (i > 0) {
            std::cout << "_";
        }
        std::cout << res[i]; 
    }
    std::cout << std::endl;
}

void Trie::print_re(Node* node, const std::string& path, std::vector<std::string>& res) {
    if (node == nullptr) return;
    std::string curr_path = path.empty() ? node->getLabel() : path + "," + node->getLabel();

    if (node->children.empty()) {
        res.push_back(curr_path);
    } else {
        for (Node* child : node->children)  {
            print_re(child, curr_path, res);
        }
    }
}

bool Trie::empty() {
    return !root->children.size();
}

void Trie::clear() {
    for (Node* child : root->children) {
        clear_re(child);
    }
    root->children.clear();
}

void Trie::clear_re(Node* node) {
    if (!node) return;

    for (Node* child : node->children) {
        clear_re(child);
    }
    delete node;
}