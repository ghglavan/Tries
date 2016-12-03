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
    // If the provided string exists in the tree, the function removes it and returns true, otherwise it returns false.
    bool removeFromTree(string);
};

void Trie::addToTree(string s){
    addToTree(s.begin(),s.end(),root);
    
    // Another aroach(non-recursive)
    /*
     Node * r = root;
    for(auto it = s.begin(); it < s.end(); it++){
        if(it+1 == s.end()){
            r->getisWordref() = true;
        }
        if(r->getMref().find(*it) == r->getMref().end()){
            r->getMref()[*it] = new Node;
            r = r->getMref()[*it];
        }else{
            r = r->getMref()[*it];
        }
    }
    */
    
    
    
}

void Trie::addToTree(string::iterator beg,string::iterator en,Node* r){
    if(beg+1 == en){
        try{
            r->getMref().at(*beg);
            r->getMref().at(*beg)->getisWordref() = true;
        }
        catch(out_of_range){
            r->getMref()[*beg] = new Node;
            r->getMref()[*beg]->getisWordref() = true;
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
    
    //Another aproach(non-recursive)
    /*
    Node *r = root;
    for(auto c : s){
        if(r->getMref().find(c) == r->getMref().end()){
            return 0;
        }else{
            r = r->getMref().at(c);
        }
    }
    return r->getisWordref();
    */
    
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
    }else if(r->getMref().size() == 1){
        r->getisWordref()= false;
        *mark = 1;

        if( r->getMref().at(*beg)->getMref().size() == 0){
            delete r->getMref().at(*beg);
            r->getMref().erase(*beg);
            *mark = 0;
        }
        return;
    }
    if(r->getMref().size() == 1 && !r->getisWordref() && *mark == 0){
        delete r->getMref().at(*beg);
        r->getMref().erase(*beg);
    }else{
        *mark = 1;
    }


}

int main()
{
   
    return 0;
}
