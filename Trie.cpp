#include "Trie.hpp"
#include "ece250_socket.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "illegal.cpp"

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
        if (std::any_of(label.begin(), label.end(), ::isupper)) {
            throw illegal_exc();
        }
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
        } else {    //  child already there
            curr = *it;  // move the curr pointer
            if (i == parsed.size() - 1) return 0;
        }
    }
    size ++ ;
    return 1;
}


std::string Trie::classify(std::string input) {
    std::string candidate;
    Node* curr = root;
    std::string res = "";

    if (std::any_of(input.begin(), input.end(), ::isupper)) {
        throw illegal_exc();
    }

    while (!curr->children.empty()) {
        candidate = "";
        for (Node* label : curr->children) {
            candidate += label->getLabel() + ",";   // create the candidate string every time from the children vector for the LLM function
        }
        if (!candidate.empty() && candidate.back() == ',') {
            candidate.pop_back();
        }
        
        std::string label = labelText(input, candidate);
        auto it = find_if(
            curr->children.begin(), curr->children.end(), 
            [&label](Node* node) { return label == node->getLabel();}
        );
        res += (*it)->getLabel() + ",";
        curr = *it;
    }
    
    if (!res.empty() && res.back() == ',') {
            res.pop_back(); // remove the last ","
    }
    return res;
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

        if (it == curr->children.end()) {   // meaning classification already exists
            return 0;
        } else {
            prev = curr;
            curr = *it; // iterate through the trie
        }
    }
    
    if (curr->children.empty()) {
        auto it = std::find(prev->children.begin(), prev->children.end(), curr);
        if (it != prev->children.end()) {
            prev->children.erase(it);   // remove the current node from it's parent's children vector
        }
        delete curr;
        size -- ;
        return 1;
    } else {
        return 0;
    }
}

void Trie::print() {
    if (!root->children.size()) {   // check if the trie is empty
        std::cout << "trie is empty\n";
        return;
    }
    std::vector<std::string> res;
    print_re(root, "", res);

    for (size_t i = 0; i < res.size(); ++i) {
        if (i > 0) {
            std::cout << "_";   // symbol between the classifications
        }
        std::cout << res[i]; 
    }
    std::cout << "_" << std::endl;
}

void Trie::print_re(Node* node, const std::string& path, std::vector<std::string>& res) {
    if (node == nullptr) return;
    std::string curr_path = path.empty() ? node->getLabel() : path + "," + node->getLabel();    // if path is empty, initialize it, or make up a new path if not empty

    if (node->children.empty()) {
        res.push_back(curr_path);   // make up the result string
    } else {
        for (Node* child : node->children)  {
            print_re(child, curr_path, res);     // call itself recursively
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
    root->children.clear(); // starting from the root's children, clear all nodes
    size = 0;
}

void Trie::clear_re(Node* node) {
    if (!node) return;

    for (Node* child : node->children) {
        clear_re(child);    // call itself recursively
    }
    delete node;
}