#include "ece250_socket.h"
#include <iostream>
#include <sstream>
#include "Trie.hpp"
#include "illegal.cpp"

int main() {
    int size, type;
    std::string cmd;
    Trie trie;

    while (std::cin >> cmd) {
        try {
            if (cmd == "LOAD") {
                std::string filename;
                std::cin >> filename;
                trie.load(filename);
                std::cout << "success\n";
            } else if (cmd == "INSERT") {
                std::string classi;
                std::cin.ignore();
                std::getline(std::cin, classi);
                bool flag = trie.insert(classi);
                if (flag) {
                    std::cout << "success\n";
                } else {
                    std::cout << "failure\n";
                }
            } else if (cmd == "CLASSIFY") {
                std::string input;
                std::cin.ignore();
                std::getline(std::cin, input);
                std::cout << trie.classify(input) << "\n";
            } else if (cmd == "ERASE") {
                std::string classi;
                std::cin.ignore();
                std::getline(std::cin, classi);
                bool flag = trie.erase(classi);
                if (flag) {
                    std::cout << "success\n";
                } else {
                    std::cout << "failure\n";
                }
            } else if (cmd == "PRINT")  {
                trie.print();
            } else if (cmd == "EMPTY") {     
                bool flag = trie.empty();
                if (flag) {
                    std::cout << "empty 1\n";
                } else {
                    std::cout << "empty 0\n";
                }
            } else if (cmd == "CLEAR") {       
                trie.clear();
                std::cout << "success\n";
            } else if (cmd == "SIZE") { 
                std::cout << "number of classifications is " << trie.getSize() << "\n";
            } 
        } catch (const illegal_exc& e) {
            std::cout << e.what() << std::endl;
        }
    }
        
}




// #include "ece250_socket.h"
// #include <iostream>
// #include <sstream> //new include!

// int main()
// {
// 	//Just for fun, let's reclassify "Dog"
// 	std::string text_to_classify = "Dog";
// 	std::string candidate_labels = "animal,plant,technology,no thing";
// 	std::cout << labelText(text_to_classify,candidate_labels) << std::endl;

// 	//OK, now let's split a string. In fact, let's split candidate_labels
	
// 	//step 1: make a new stringstring with the contents of our candidate_labels 
// 	std::istringstream stream(candidate_labels); //I could have named it anything, like stringin or something
	
// 	//step 2: make a temporary string that we will use to store the extracted parts
// 	std::string single_label;
	
// 	//step 3: use the getline function with the comma sent in as a delimiter to read the string parts
// 	while(std::getline(stream,single_label,',')){
// 		std::cout << single_label << std::endl; //and let's print it just to make sure it worked
// 	}
	
// 	return 0;
// }
