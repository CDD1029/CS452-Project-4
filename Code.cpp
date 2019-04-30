#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;


class Node {
public:

    Node * parent;
    int value[6];
    int numchildren;
    Node * child[6];
    Node(int val){
        value[0]=val;
        parent=NULL;
        numchildren=0;
        for(int i = 0; i < 6; i++){
            child[i] = NULL;
        }
    }
    int numChildren(){return numchildren;}
    void absorb(Node * newChild){
        this->putAChildInIt(newChild);
        if(this->numChildren() > 3){
            Node * left = new Node(this->child[1]->value[1]);
            //ok so what's happening here is that a left node is being made, put the left 2 most elements in there, then shift over the two from current code. this is keeping in mind the value of the parent is the greater of the two nodes.
            left->child[0] = this->child[0];
            left->child[1] = this->child[1];
            left->numchildren = 2;
            this->child[0] = this->child[2];
            this->child[1] = this->child[3];
            this->child[2] = NULL;
            this->child[3] = NULL;
            this->numchildren = 2;
            left->parent = this->parent;
            this->parent = left;
            newChild->parent = left;
            this->parent->absorb(left);

        }

    }
    void putAChildInIt(Node * newNode){
        this->child[this->numChildren()] = newNode;
        this->numchildren++;
        this->reorderChildren();
    }
    void swapChildren(Node * first, Node * last) {
        Node * temp = first;
        first = last;
        last = temp;
    }
    void reorderChildren(){
        for(int x = 0; x < this->numChildren(); x++) {
            Node * max = this->child[0];
            int lastIndexOfInsertionSort = this->numChildren() - x;
            int maxIndex = 0;
            for(int i = 1; i < lastIndexOfInsertionSort; i++) {
                if(this->child[i]->value > max->value) {
                    max = this->child[i];
                    maxIndex = i;
                }
            }
            swapChildren(this->child[lastIndexOfInsertionSort-1],this->child[maxIndex]);

        }
        //do i have to update parent value here??? i dont think i do...
    }
    //  void discard(Node * removeChild);
};

class Tree {
    Node * root;
    void print (Node * start){
        for(int i=0; i<start->numChildren(); i++){
            cout << start->value[i] << " ";
        }
        cout << endl;
        for (int i=0; i<start->numChildren(); i++){
            cout << "    ";
            cout << start->child[i]->value[i] << endl;
        }
    }
    //if doesnt search returns null, make new node, putChildIn root
public:
    Tree(){
        //root = NULL;
        root= new Node(2000);//idk how to deal with null root yet.
    }
    Node * search(int valToFind){
        return searchHelper(root, valToFind);
    }
    Node * searchHelper(Node *n, int valToFind){
        if (n->numChildren()==0){
            return n;
        }
        for(int i=0;i<n->numChildren();i++){
            if (valToFind<=n->value[i])
                return searchHelper(n->child[i],valToFind);
        }
        return n;// return 2000;
    }
    void insert(int valToAdd){
        Node * b=search(valToAdd);
        if (b->value[0]==valToAdd)
            return;
        Node * newNode = new Node(valToAdd);
        if(b->numChildren() < 2){
            b->putAChildInIt(newNode);
            return;
        }
        b->absorb(newNode);

    }
    void discard(int valToKill){
        Node * b=search(valToKill);
        if (b->value[0]!=valToKill)
            return;
        //  b->parent->discard(b);
    }
    void print(){
        cout << root->numChildren() << endl;
    }
};

int main (int argc, char * argv[]) {


    // THE REAL PROGRAM IS HERE

    // Shut down MPI

    Tree *t = new Tree();
    //t->insert(25);
    t->insert(50);
    t->insert(100);
    t->insert(75);
    t->insert(80);

    t->print();

    return 0;
}
