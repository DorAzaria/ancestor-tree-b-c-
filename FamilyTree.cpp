//
// Created by dor on 09/04/2020.
//
#include "FamilyTree.hpp"
#include <iostream>
#include <string>
using namespace std;
using namespace family;

void Tree::insertFather(family::Node *current, string son, string father) {
    if(current == nullptr){
        return;
    }

    if(son.compare(current->name)==0) {
        if(current->father != NULL) {
            throw "ERROR!, father is already exist.\n";
        }
        else{
           Node* newNode = new Node(father);
           newNode->gender = 1;
           root->sizeRight++;
           current->father = newNode;
           current->father->relation = Tree::initRelation(father);
           return;
        }
    }
    this->insertFather(current->father,son,father);
    this->insertFather(current->mother,son,father);
}

Tree Tree::addFather(string son, string father) {
    Node* current = root;
    if(Tree::checkName(current,son)) {
        this->insertFather(current, son, father);
        return *this;
    }
    else {
        throw "not found";
    }
}

void Tree::insertMother(family::Node *current, string son, string mother) {
    if(current == nullptr) {
        return;
    }

    if(son.compare(current->name)==0){
        if(current->mother != NULL) {
            throw "Error!, mother is already exist!\n";
        }
        Node* newNode = new Node(mother);
        newNode->gender = 2;
        root->sizeLeft++;
        current->mother = newNode;
        current->mother->relation = Tree::initRelation(mother);
        return;
    }
    this->insertMother(current->mother,son,mother);
    this->insertMother(current->father,son,mother);
}

Tree Tree::addMother(string son, string mother) {
    Node*current = root;
    if(Tree::checkName(current,son)) {
        this->insertMother(current, son, mother);
        return *this;
    }
    else {
        throw "not found";
    }

}

void Tree::displayPrint(family::Node *root, int space) {
    if(root == NULL)
        return;

    space += 10;

    displayPrint(root->father,space);
    cout << endl;

    for(int i = 10; i < space; i++)
        cout<<" ";
    cout<<root->name<<endl;

    displayPrint(root->mother,space);

}

void Tree::display() {
    Tree::displayPrint(root, 0);
    cout << endl;
}

string Tree::createRelation(family::Node *current, string name, int count) {
    static string res = "";
    if(current == NULL)
        return res;

    if(name.compare(current->name) == 0) {
        if((count >= 0) && (count <= 2)) {
            res = "";
            if (count == 0)
                res += "me";

            if ((count == 1) && (current->gender == 2))
                res += "mother";

            if ((count == 1) && (current->gender == 1))
                res += "father";

            if ((count == 2) && (current->gender == 2))
                res += "grandmother";

            if ((count == 2) && (current->gender == 1))
                res += "grandfather";
            current->relation = res;
            return res;
        }
        else {
            res = "";
            for (int i = 3; i <= count; i++)
                res += "great-";

            if (current->gender == 2)
                res += "grandmother";

            if (current->gender == 1)
                res += "grandfather";

            current->relation = res;
            return res;
        }
    }
        count++;
        createRelation(current->father,name,count);
        createRelation(current->mother,name,count);
        return res;
}

bool Tree::checkName(family::Node *current, string name) {
        if(current == NULL)
            return false;

        if(name.compare(current->name) == 0)
            return true;

        bool res1 = checkName(current->father,name);
        if(res1)
            return true;
        bool res2 = checkName(current->mother,name);
            return res2;
}

string Tree::initRelation(string name) {
    int count = 0;
    Node* current = root;
    if(Tree::checkName(current,name)) {
        string result = createRelation(current, name, count);
        return result;
    }
    else{
        throw "unrelated";
    }
}

string Tree::findRelation(family::Node *current, string name) {
    static string find = "";
    if(current == NULL)
        return find;

    if(name.compare(current->name) == 0) {
        find = "";
        find += current->relation;
    }

    findRelation(current->father,name);
    findRelation(current->mother,name);
    return find;
}

string Tree::relation(string name) {
    Node* current = root;
    if(Tree::checkName(current,name)){
        string result = findRelation(current,name);
        return result;}
    else {
        return "unrelated";
    }
}

string Tree::findName(family::Node *current, string name) {
    static string fname = "";
    if(current == NULL)
        return fname;

    if((current->relation).compare(name) == 0) {
        fname = "";
        fname += current->name;
        return fname;
    }
    findName(current->father,name);
    findName(current->mother,name);
    return fname;
}

bool Tree::checkRelation(family::Node *current, string name) {
    if(current == NULL)
        return false;

    if(name.compare(current->relation) == 0)
        return true;

    bool res1 = checkRelation(current->father,name);
    if(res1)
        return true;
    bool res2 = checkRelation(current->mother,name);
    return res2;
}
string Tree::find(string name) {
    Node* current = root;
    if(Tree::checkRelation(current,name)){
    string result = findName(current,name);
    return result;}
    else {
        throw "Undefined";
    }
}

void Tree::removeFamily(family::Node *current, string name) {
    if(current == NULL)
        return;

    if(name.compare(root->name) == 0) {
        return;
    }
    if(name.compare(current->father->name) == 0) {
        current->father->relation = "unrelated";
        current->father = NULL;
        return;
    }
    if(name.compare(current->mother->name) == 0) {
        current->mother->relation = "unrelated";
        current->mother = NULL;
        return;
    }
    if(current->father != NULL) {
        removeFamily(current->father, name);
    }
    else if(current->mother != NULL) {
        removeFamily(current->mother, name);
    }else {
        throw "cant remove";
    }
}

void Tree::remove(string name) {
    if(root == NULL) {
        throw "bye";
    }else {
        Node *current = root;
        Tree *curr = this;

        if (curr == this || curr == NULL) {
            root->father = nullptr;
            root->mother = nullptr;
            throw std::out_of_range{"the tree is deleted."};
        } else if (current != nullptr) {
            if (Tree::checkName(current, name)) {
                Tree::removeFamily(current, name);
            } else {
                throw invalid_argument(name + " wasn't found");
            }
        }
        delete current;
    }
}