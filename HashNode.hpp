#ifndef _HN
#define _HN

class HashNode{
public:
    HashNode(Node* node);

    Node* getPrevLink() {return prevHash;}
    Node* getNextLink() {return nextLink;}
    void setPrevLink()

private:
    Node* dataNode;
    Node* prevLink;
    Node* nextLink;





};








#endif // _HN
