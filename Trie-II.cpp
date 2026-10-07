                            
#include <bits/stdc++.h> 
using namespace std;

struct Node {

    Node* links[26];
     // Counter for number of
     // words that end at this node
    int cntEndWith = 0;
    // Counter for number of words
    // that have this node as a prefix
    int cntPrefix = 0; 

    bool containsKey(char ch) {

        return (links[ch - 'a'] != NULL); 
    }

    Node* get(char ch) {
        return links[ch - 'a']; 
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }
    void increaseEnd() {
        cntEndWith++; 
    }
    void increasePrefix() {
        cntPrefix++;
    }

    void deleteEnd() {
        cntEndWith--; 
    }
    void reducePrefix() {
        cntPrefix--; 
    }
};

class Trie {
private:
    Node* root; 

public:
    Trie() {
        root = new Node(); 
    }


    void insert(string word) {

        Node* node = root; 

        for (int i = 0; i < word.size(); i++) { 
            if (!node->containsKey(word[i])) {

                node->put(word[i], new Node()); 
            }
            node = node->get(word[i]);
            node->increasePrefix(); 
        }
        node->increaseEnd(); 
    }

    int countWordsEqualTo(string word) {

        Node* node = root;
        for (int i = 0; i < word.size(); i++) { 
            if (node->containsKey(word[i])) { 
                node = node->get(word[i]); 
            } else {
                return 0;
            }
        }
        return node->cntEndWith; 
    }


    int countWordsStartingWith(string word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) { 
            if (node->containsKey(word[i])) { 
                node = node->get(word[i]); 
            } else {
                return 0; 
            }
        }
        return node->cntPrefix; 
    }


    void erase(string word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) { 

            if (node->containsKey(word[i])) { 
                node = node->get(word[i]);
                node->reducePrefix(); 
            } else {
                return; 
            }
        }
        node->deleteEnd(); 
    }
};


int main() {
    Trie trie; 
    trie.insert("apple"); 
    trie.insert("app"); 
    cout << "Inserting strings 'apple', 'app' into Trie"<< endl;
    cout << "Count Words Equal to 'apple': ";
    cout << trie.countWordsEqualTo("apple") << endl; 
    cout << "Count Words Starting With 'app': ";
    cout << trie.countWordsStartingWith("app") << endl; 
    cout << "Erasing word 'app' from trie"<< endl;
    trie.erase("app"); 
    cout << "Count Words Equal to 'apple': ";
    cout << trie.countWordsEqualTo("apple") << endl; 
    cout << "Count Words Starting With 'apple': ";
    cout << trie.countWordsStartingWith("app") << endl; 
    return 0; 
}
                            
                        