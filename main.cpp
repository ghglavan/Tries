#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class Node{
public:
    // I'm too lazy to implement getters and setters so I return a refference :D
    unordered_map<char,Node*>& getMref(){return m;}
    bool& getisWordref(){return isWord;}

    Node(){isWord = false;}
private:
    // Here we have an unordered map of char and Node* to store the chars in every node and the pointing nodes.
    unordered_map<char,Node*> m;
    // isWord is used to see if a Node is the end of a word.
    bool isWord;

};

class Trie{
    // The root of the tree.
    Node* root;
    // Functions used for recursive calls.
    void addToTree(string::iterator,string::iterator,Node*);
    bool isInTree(string::iterator,string::iterator,Node*);
    void removeFromTree(string::iterator,string::iterator,Node*,int*);
public:

    //Default constructor
    Trie(){root = new Node;};

    // Check if the provided string is in the tree. Not implemented inline.
    bool isInTree(string);
    // Add the provided string to the tree
    void addToTree(string);
    // If the provided string exists in the tree, the function remuves it and returns true, otherwise it returns false.
    bool removeFromTree(string);
};

void Trie::addToTree(string s){
    addToTree(s.begin(),s.end(),root);
}

void Trie::addToTree(string::iterator beg,string::iterator en,Node* r){
    if(beg+1 == en){
        try{
            r->getMref().at(*beg);
            r->getisWordref() = true;
        }
        catch(out_of_range){
            r->getMref()[*beg] = new Node;
            r->getisWordref() = true;
        }
    }else{
        try{
            addToTree(beg+1,en,r->getMref().at(*beg));

        }
        catch(out_of_range){
            r->getMref()[*beg] = new Node;
            addToTree(beg+1,en,r->getMref().at(*beg));
        }
    }
}

bool Trie::isInTree(string s){
    return isInTree(s.begin(),s.end(),root);
}

bool Trie::isInTree(string::iterator beg,string::iterator en,Node*r){
    if(beg+1 == en){
        try{
            r->getMref().at(*beg);
            return r->getisWordref();
        }
        catch(out_of_range){
            return false;
        }
    }else{
        try{
            return isInTree(beg+1,en,r->getMref().at(*beg));
        }
        catch(out_of_range){
            return false;
        }
    }
}

bool Trie::removeFromTree(string s){
    if(!isInTree(s))
        return false;
    int m = 0;
    removeFromTree(s.begin(),s.end(),root,&m);
    return true;
}

void Trie::removeFromTree(string::iterator beg,string::iterator en,Node *r,int *mark){
    if(beg+1 != en){
        removeFromTree(beg+1,en,r->getMref()[*beg],mark);
    }else{
        delete r->getMref().at(*beg);
        r->getMref().erase(*beg);
        return;
    }
    if(r->getMref().size() == 1 && !r->getisWordref() && *mark == 0){
        cout<<"sunt la "<<*beg<<"\n";
        delete r->getMref().at(*beg);
        r->getMref().erase(*beg);
    }else{
        *mark = 1;
    }

}

int main()
{
    Trie t;
    t.addToTree("das");
    t.addToTree("nu");
    t.addToTree("dasdas");
    cout<<t.isInTree("da");
    t.removeFromTree("dasdas");
    cout<<t.isInTree("das");
    return 0;
}
