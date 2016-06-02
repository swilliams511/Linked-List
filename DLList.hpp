#ifndef DLLIST
#define DLLIST


#include "Node.hpp"

class DLList {
public:
    DLList();
    DLList(std::string name);
    ~DLList();
    DLList* copy();
    DLList* copy(std::string name);

    void insert_from_file(std::string fileName);

    //node is created "new" in insert based on passed parameters. A different
    //set of functions could need to be written if you wanted to create the
    //new node in main and pass that to the insert
    bool insert_front(int value, std::string name); //puts the node at the head value
    bool insert_back(int value, std::string name);  //puts the node at the tail value
    bool insert_kth(int k, int value, std::string name); //puts the node at the specified position

    //node is deleted to match the "new" in insert
    bool delete_front();
    bool delete_back();
    bool delete_node(int value, std::string name);//searches for node based on parameters then deletes it
    bool delete_kth(int k);

    bool inList(int value, std::string name); //check if the node is in the list

    //sequential searches
    Node* getNode(int value, std::string name); //find the node in the list and gives its address
    Node* getNode(int value);
    Node* getNode(std::string name);
    Node* getKthNode(int v);

    void sortList();
    bool isListSorted();
    void reverse(); //trivial since you can start at tail and get prev til nullptr
    void print();
    //getters/setters
    Node* getHead() {return head;}
    void setHead(Node* v) {head = v;}
    Node* getTail() {return tail;}
    void setTail(Node* v) {tail = v;}
    int getNumNodes() {return numNodes;}
    void setNumNodes(int v) {numNodes = v;}

    std::string getListName() {return listName;}
    void setListName(std::string v) {listName = v;}



private:
    std::string listName;
    Node* head;
    Node* tail;
    int numNodes;
    //quick sort helper functions
    void qsort(Node* left, Node* right);
    Node* partition(Node* left, Node* right);



};



#endif // DLLIST
