#include "HashNode.hpp"

HashNode::HashNode(Node* node)
{
    dataNode = node;
    prevLink = nullptr;
    nextLink = nullptr;
}
