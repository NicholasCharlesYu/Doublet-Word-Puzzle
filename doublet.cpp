#include "MinHeap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

struct Node {
    string nodeName_;
    vector<Node*> neighbors;
    int h;
    int g;
    bool explored;
    Node* parent;

    Node(string nodeName) : nodeName_(nodeName), parent(nullptr), explored(false), g(0) {}
};

// calculate the heuristic value
int hValue(string currentWord, string endWord) {
    int diffLetter = 0;
    for (int i = 0; i < currentWord.length(); i++) {
        // compare how many letters differ from end word
        if (currentWord[i] != endWord[i]) {
            diffLetter++;
        }
    }
    return diffLetter;
}

// creates graph
map<string, Node*> graph(string filename, string endWord) {
    ifstream ifile(filename);
    if (!ifile) {
        exit(1);
    }

    map<string, Node*> wordList;
    int n;
    ifile >> n;
    string in;

    // transform all words to lowercase, create nodes,
    // heuristic & put in graph
    while (ifile >> in) {
        transform(in.begin(), in.end(), in.begin(), ::tolower);
        Node* tempNode = new Node(in);
        tempNode->h = hValue(in, endWord);
        wordList[in] = tempNode;
    }

    // create permutations of each word
    for (map<string, Node*>::iterator it = wordList.begin(); it != wordList.end(); it++) {
        Node* currNode = it->second;
        for (int j = 0; j < currNode->nodeName_.length(); j++) {
            for (char k = 'a'; k <= 'z'; k++) {
                if (currNode->nodeName_[j] != k) {
                    string temp = currNode->nodeName_;
                    temp[j] = k;
                    // if permutation exists in list, add as neighbor
                    if (wordList.find(temp) != wordList.end()) {
                        currNode->neighbors.push_back(wordList[temp]);
                    }
                }
            }
        }
    }
    return wordList;
}

void aStar(string startingWord, string endWord, map<string, Node*> graph_) {
    // track expansions
    int expansions = 0;

    MinHeap<string> minHeap(2);

    // initialize head node
    Node* u = graph_[startingWord];
    u->g = 0;
    int f = u->h + u->g;
    minHeap.add(startingWord, f * (startingWord.length() + 1) + u->h);

    // tracks if end is found
    bool endFound = false;

    while (!minHeap.isEmpty()) {
        if (endFound == true) {
            break;
        }
        // get top priority node and pop it
        string v = minHeap.peek();
        minHeap.remove();

        // find current node and set it as explored
        Node* vNode = graph_[v];

        // if node is explored, skip
        if (vNode->explored == true) {
            continue;
        }

        // if current node is end node, end
        if (v == endWord) {
            endFound = true;
            break;
        }

        // increment expansions each time node is popped
        expansions++;
        vNode->explored = true;

        // check all neighbor nodes
        for (int i = 0; i < vNode->neighbors.size(); i++) {
            // if neighbor is not explored
            if (!vNode->neighbors[i]->explored) {
                // node g is unassigned or found lesser g value
                if (vNode->neighbors[i]->g == 0 || vNode->g + 1 < vNode->neighbors[i]->g) {
                    vNode->neighbors[i]->g = vNode->g + 1;
                    vNode->neighbors[i]->parent = vNode;

                    // find priority
                    int tempF = (vNode->neighbors[i]->g + vNode->neighbors[i]->h);
                    int tempPriority = tempF * (vNode->neighbors[i]->nodeName_.length() + 1) + vNode->neighbors[i]->h;

                    // add to minheap
                    minHeap.add(vNode->neighbors[i]->nodeName_, tempPriority);
                }
            }
        }
    }

    if (graph_[endWord]->parent == nullptr) {
        cout << "No transformation" << endl;
    } else {
        int steps = 0;
        Node* temp = graph_[endWord];
        while (temp->parent != nullptr) {
            steps++;
            temp = temp->parent;
        }
        cout << steps << endl;
    }
    cout << expansions << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "wrong amount of args" << endl;
        return 1;
    }

    string startWord = argv[1];
    string endWord = argv[2];
    // make all lower case
    transform(startWord.begin(), startWord.end(), startWord.begin(), ::tolower);
    transform(endWord.begin(), endWord.end(), endWord.begin(), ::tolower);
    map<string, Node*> g1 = graph(argv[3], endWord);
    aStar(startWord, endWord, g1);

    // deallocate memory
    for (map<string, Node*>::iterator it = g1.begin(); it != g1.end(); it++) {
        delete it->second;
    }
    return 0;
}