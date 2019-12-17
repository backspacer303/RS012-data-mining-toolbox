#include "Stream.hpp"
#include <SourceNode.hpp>

#include <iostream>

Stream::Stream(){}

// TODO: fix destructor
Stream::~Stream(){

    for (auto pair : mapOfNodes){
        disconnect(pair.second, pair.first);
    }
    for (auto iter = mapOfNodes.begin(); iter != mapOfNodes.end(); iter++){
          mapOfNodes.erase(iter);
      }
}

void Stream::add(Node *node){
    mapOfNodes[node] = nullptr;
}

void Stream::connect_to(Node *node1, Node *node2){
    mapOfNodes[node2] = node1;
    node2->setInputDataTable((node1->RefOutputDataTable()));
}

// TODO: change disconnect function so it disconnects node 2 from all nodes it has connections to
void Stream::disconnect(Node *node1, Node *node2){
    mapOfNodes[node2] = nullptr;
    node2->setInputDataTable(nullptr);
}

void Stream::RunStream(Node *targetNode){
    if(SourceNode* v = dynamic_cast<SourceNode*>(targetNode)) {
    } else {
        RunStream(mapOfNodes[targetNode]);
    }
    targetNode->run();
}

std::map<Node*, Node*> Stream::MapOfNodes() const{
    return mapOfNodes;
}
