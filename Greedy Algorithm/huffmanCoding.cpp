#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

// Node structure for Huffman tree
struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// Comparator function for priority queue
struct CompareNodes {
    bool operator()(Node* const& n1, Node* const& n2) {
        return n1->freq > n2->freq;
    }
};

// Function to construct the Huffman tree
Node* buildHuffmanTree(vector<char>& chars, vector<int>& freqs) {
    priority_queue<Node*, vector<Node*>, CompareNodes> pq;

    // Create leaf nodes and insert them into the priority queue
    for (int i = 0; i < chars.size(); ++i) {
        Node* newNode = new Node(chars[i], freqs[i]);
        pq.push(newNode);
    }

    // Construct the Huffman tree
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* internalNode = new Node('$', left->freq + right->freq); // Internal node with '$' data
        internalNode->left = left;
        internalNode->right = right;

        pq.push(internalNode);
    }

    return pq.top();
}

// Function to traverse the Huffman tree and assign codes to characters
void assignHuffmanCodes(Node* root, string code, map<char, string>& huffmanCodes) {
    if (root) {
        if (root->data != '$') { // If the node is a leaf node
            huffmanCodes[root->data] = code;
        }
        assignHuffmanCodes(root->left, code + "0", huffmanCodes);
        assignHuffmanCodes(root->right, code + "1", huffmanCodes);
    }
}

// Function to generate output including the Huffman tree structure and assigned codes
void generateOutput(Node* root, map<char, string>& huffmanCodes) {
    cout << "Huffman Tree: (root: ";
    if (root) {
        if (root->data != '$') {
            cout << root->data;
        } else {
            cout << "(";
            generateOutput(root->left, huffmanCodes);
            cout << ", ";
            generateOutput(root->right, huffmanCodes);
            cout << ")";
        }
    }
    cout << ")" << endl;

    cout << "Code: ";
    for (auto it = huffmanCodes.begin(); it != huffmanCodes.end(); ++it) {
        cout << it->first << ": " << it->second << ", ";
    }
    cout << endl;
}

int main() {
    vector<char> chars = {'a', 'b', 'c', 'd'};
    vector<int> freqs = {4, 2, 1, 3};

    // Construct the Huffman tree
    Node* root = buildHuffmanTree(chars, freqs);

    // Assign Huffman codes to characters
    map<char, string> huffmanCodes;
    assignHuffmanCodes(root, "", huffmanCodes);

    // Generate output
    generateOutput(root, huffmanCodes);

    return 0;
}
