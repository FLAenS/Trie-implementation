#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>

class Node {
private:
    std::string label;
    
public:
    Node(std::string name);
    ~Node();
    std::vector<Node*> children;
    std::string getLabel() {return label;}
};

#endif