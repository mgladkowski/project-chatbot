#include "graphnode.h"

#include "graphedge.h"

GraphNode::GraphNode(int id) {
    _id = id;
}

GraphNode::~GraphNode() {}

void GraphNode::AddToken(std::string token) {
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge) {
    // storing in vector the non-owned edges of parent nodes
    _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge) {
    // moving to vector the edges owned by a child
    _childEdges.push_back(std::move(edge));
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere(ChatBot *chatbot) {
    _chatBot = chatbot;
    _chatBot->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode) {
    newNode->MoveChatbotHere(_chatBot);
    _chatBot = nullptr; // invalidate pointer at source
}
////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index) {

    // still returning an unowned pointer, just have to get() it from the unique_ptr
    return _childEdges[index].get();
}