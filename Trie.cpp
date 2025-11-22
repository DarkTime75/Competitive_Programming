#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    TrieNode* links[26];
    bool end;
    bool containsKey(char ch) {
        return links[ch - 'a'] != nullptr;
    }

    TrieNode* get(char ch) {
        return links[ch - 'a'];
    }

    void put(char ch) {
        links[ch - 'a'] = new TrieNode();
    }

    bool isEnd() {
        return end;
    }

    void setEnd() {
        end = true;
    }
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode *p = root;
        for (char ch : word) {
            if (!p->containsKey(ch)) p->put(ch);
            p = p->get(ch);
        }

        p->setEnd();
    }
    
    bool search(string word) {
        TrieNode *p = root;
        for (char ch : word) {
            if (!p->containsKey(ch)) return false;
            p = p->get(ch);
        }

        return p->isEnd();
    }
    
    bool startsWith(string prefix) {
        TrieNode *p = root;
        for (char ch : prefix) {
            if (!p->containsKey(ch)) return false;
            p = p->get(ch);
        }

        return true;
    }
};