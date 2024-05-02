#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <chrono>
#include <cstdint> // Include for uint32_t
#include <bitset> // Include for bitset

using namespace std;

class Node {
public:
    char ch;
    uint32_t freq; // Replace int with uint32_t
    bool isLeafNode;
    Node* left, * right;

    Node() {
    }
    //If Node is created with only 2 parameter, the node is a leafnode
    Node(char ch, uint32_t freq) { // Replace int with uint32_t
        this->ch = ch;
        this->freq = freq;
        this->left = nullptr;
        this->right = nullptr;
        this->isLeafNode = true;

    }
    //If Node is created with only 4 parameter, which means it has child node in left and right, the node is a parent node 
    Node(char ch, uint32_t freq, Node* left, Node* right) { // Replace int with uint32_t
        this->ch = ch;
        this->freq = freq;
        this->left = left;
        this->right = right;
        this->isLeafNode = false;
    }
};

// Custom comparator for priority queue
struct GreaterFreq {
    bool operator()(const Node* struct1, const Node* struct2) {
        return (struct1->freq > struct2->freq); // Greater frequency has higher priority
    }
};

//Get Total Number of Bits
uint32_t computeBits(map<char, uint32_t> freq, map<char, bitset<8>> huffmanCode) { // Replace int with uint32_t
    uint32_t totalBits = 0;
    for (auto pair : huffmanCode) {
        totalBits += pair.second.count() * freq[pair.first]; // Count set bits (1s) in bitset
    }
    return totalBits;
}

//Get Encoded Binary String
bitset<8> getBinaryString(map<char, bitset<8>> huffmanCode, string plaintext) { // Use bitset<8> instead of string
    bitset<8> binary;
    for (int i = 0; i < plaintext.size(); i++) {
        binary |= huffmanCode[plaintext[i]]; // OR operation to append Huffman code bits
    }
    return binary;
}

//Traverse to each Node in Huffman Tree starting from root node going to the leaf node to get the huffman code
void getHuffmanCode(Node* root, bitset<8> str, map<char, bitset<8>>& huffmanCode) { // Use bitset<8> instead of string
    //If root is Null then return.
    if (!root) {
        return;
    }
    //If Node is a leafNode, which means it is the last node, save the str as huffman code
    if (root->isLeafNode) {
        huffmanCode[root->ch] = str;
    }
    else {
        getHuffmanCode(root->left, str << 1, huffmanCode); //Node is still a parent node, traverse going left and shift left by 1
        str.set(0); // Set the least significant bit to 1
        getHuffmanCode(root->right, str, huffmanCode); //Node is still a parent node, traverse going right
    }
}


vector<Node*> nodesArray;
void buildHuffmanTree(string plaintext, string filename)
{
    //Key Value Pair Map where Key is the Character and Value is the Frequency
    //Iterate through each character in plain text and get each character frequency.
    //If char key in freq[char], increment value by 1
    map<char, uint32_t> freq; // Replace int with uint32_t
    for (int i = 0; i < plaintext.size(); i++) {
        freq[plaintext[i]]++;
    }

    // Priority queue to store nodes with custom comparator
    priority_queue<Node*, vector<Node*>, GreaterFreq> nodesQueue;

    //Iterate through all char in freq key value pair
    //This will insert each char as leaf node (isLeafNode = true) in nodesArray then insert them in nodesQueue
    for (auto pair : freq) {
        //pair.first = Key/Char while pair.second = Value/Frequency count
        Node* newNode = new Node(pair.first, pair.second);
        nodesArray.push_back(newNode);
        nodesQueue.push(newNode);
    }

    //Iterate through the queue until only the root node remains
    while (nodesQueue.size() > 1) {
        Node* left = nodesQueue.top(); // extract minimum node (lowest freq in queue) and put it to left variable
        nodesQueue.pop(); // delete the minimum node from queue
        Node* right = nodesQueue.top();  // extract minimum node (lowest freq in queue) and put it to right variable
        nodesQueue.pop(); // delete the minimum node from queue
        uint32_t sum = left->freq + right->freq; //add left and right node frequency

        Node* newNode = new Node('\0', sum, left, right); //Create New Node where isLeafNode = false which means it is a parent node
        nodesArray.push_back(newNode); //insert to nodeArray
        nodesQueue.push(newNode); //insert to queue
    }

    //Get the root node
    Node* root = nodesQueue.top();
    nodesQueue.pop();

    //Get HuffManCode Code 
    map<char, bitset<8>> huffmanCode; // Use bitset<8> instead of string
    getHuffmanCode(root, bitset<8>(), huffmanCode);

    //Create File for output
    ofstream MyFile(filename + ".zip301");
    for (auto pair : huffmanCode) {
        if (pair.first == '\n') {
            MyFile << pair.second << " newline" << endl;
        }
        else if (pair.first == ' ') {
            MyFile << pair.second << " space" << endl;
        }
        else if (pair.first == '\r') {
            MyFile << pair.second << " return" << endl;
        }
        else if (pair.first == '\t') {
            MyFile << pair.second << " tab" << endl;
        }
        else {
            MyFile << pair.second << " " << pair.first << endl;
        }
    }
    MyFile << "*****" << endl;
    uint32_t totalBytes = computeBits(freq, huffmanCode); // get total bits
    MyFile << totalBytes << endl;

    bitset<8> binary = getBinaryString(huffmanCode, plaintext);

    int getCount = binary.size() / 8; //get the number of 8 bits binary that we can get from encoded binary string
    int lastSubstringLength = binary.size() % 8; //check if last substring is exactly 8 bits
    int j = 0;
    for (int i = 0; i < getCount; i++) {
        char ch;
        int num = (int)(binary.to_ulong() >> (binary.size() - j - 8)); // Get the next 8 bits from the end
        ch = num; //convert int to char or raw bytes
        MyFile << ch; //print to file
        j += 8;
    }
    //If last sub binary is not 8 bits. Add succeeding 0 to the end
    if (lastSubstringLength > 0) {
        int neededZero = 8 - lastSubstringLength;
        binary <<= neededZero; // Shift left to align to 8 bits
        char ch;
        int num = (int)(binary.to_ulong() >> (binary.size() - 8)); // Get the last 8 bits
        ch = num; //convert int to char or raw bytes
        MyFile << ch;
    }
    cout << "Zip301 Generated.\n";
}

int main(int argc, char** argv)
{

    auto starttime = chrono::high_resolution_clock::now();

    //Catches error conditions Check if filename included as parameter
    if (argc != 2) {
        cout << "You need to include a filename on the command line.\n";
        return -1;
    }

    string filename = argv[1];//Fetches the file name
    ifstream file(filename); // Open file for reading

    string delimiter = ".";
    string name = filename.substr(0, filename.find(delimiter));
    string extension = filename.substr(1, filename.find(delimiter));

    //Catches error conditions Check if file exist
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return -1;
    }
    string file_contents;
    string input;//store the inputs or the lines from the file
    while (getline(file, input))
    {
        //Add to file_content to get the whole plain text in file
        file_contents += input;
    }

    buildHuffmanTree(file_contents, name);

    auto endtime = chrono::high_resolution_clock::now();
    chrono::duration<double> time = endtime - starttime;
    cout << time.count() << "s";

    file.close();
    return 0;
}
