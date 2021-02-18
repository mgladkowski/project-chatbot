#include "graphnode.h"

#include "graphedge.h"
#include <iostream>

GraphNode::GraphNode(int id) {
    _id = id;
    std::cout << "GraphNode constructor" << std::endl;
}

GraphNode::~GraphNode() {

    std::cout << "GraphNode destructor" << std::endl;
}

void GraphNode::AddToken(std::string token) {
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge) {

    // storing in vector the non-owned (raw) edges of parent nodes
    _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge) {

    // moving to vector the edges owned (unique ptr) by a child
    _childEdges.push_back(std::move(edge));
}

void GraphNode::MoveChatbotHere(ChatBot chatbot) {

    _chatBot = std::move(chatbot);
    _chatBot.SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode) {

    newNode->MoveChatbotHere(std::move(_chatBot));
}

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index) {

    // still returning a raw pointer, just have to get() it from the unique_ptr
    return _childEdges[index].get();
}