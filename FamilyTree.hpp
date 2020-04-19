#ifndef ANCESTOR_TREE_B_FAMILYTREE_HPP
#define ANCESTOR_TREE_B_FAMILYTREE_HPP

#include <string>
using namespace std;

namespace family {

    class Node {
    public:
            string name;
            string relation;
            int treeFound;
            int gender;
            int sizeRight, sizeLeft;
            Node *father;
            Node *mother;
            //a Node constructor
            Node(string data) {
                this->name = data;
                this->mother = nullptr;
                this->father = nullptr;
            }
    };

    class Tree {
    public:
        //create a new tree & insert root
        Node* root;
        Tree(string rootName) {
            Node* newNode = new Node(rootName);
            this->root = newNode;
            this->root->relation = initRelation(rootName);
            this->root->treeFound = 1;
        }
        Tree addFather(string son, string father);
        Tree addMother(string son, string mother);
        void display();
        void remove(string name);
        string relation(string name);
        string find(string name);
    private:
        void insertFather(Node* root, string son, string father);
        void insertMother(Node* root, string son, string mother);
        void displayPrint(Node* root, int count);
        void removeFamily(Node* current, string name);
        bool checkName(Node* current, string name);
        bool checkRelation(Node* current, string name);
        string initRelation(string name);
        string createRelation(Node* current, string name, int count);
        string findRelation(Node* current, string name);
        string findName(Node* current,string name);
    };
}
#endif
