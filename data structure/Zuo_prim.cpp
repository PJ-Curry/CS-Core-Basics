#include<bits/stdc++.h>
using namespace std;
class Edge;
class Node{
public:
    int value;
    vector<Edge*> edges;
    Node(int val) : value(val){}
};
class Edge{
public:
    int weight;
    Node* from;
    Node* to;
    Edge(int w, Node* f,Node* t) : weight(w), from(f), to(t){}
};

struct EdgeComparator{
    bool operator()(Edge* a,Edge* b){
        return a->weight > b->weight;
    }
};

/*
1.要有一个集合set 来标注已经点亮的城市名单
2.有小根堆来存放边
3.防环 通过set来判断
4.循环
*/
unordered_set<Edge*> primMST(Node* startNode){
    //解锁的所有路都存放在这里
    priority_queue<Edge*, vector<Edge*>, EdgeComparator> minHeap;
    unordered_set<Node*> conqueredSet;
    unordered_set<Edge*> result;

    //1.随机选取一个点放进set集合
    conqueredSet.insert(startNode);
    //2.把该大本营连接的所有边，全都放进去
    for(Edge* edge : startNode->edges){
        minHeap.push(edge);
    }
    while(!minHeap.empty()){
        Edge* curEdge = minHeap.top();
        minHeap.pop();

        //看看这条路通向哪里
        Node* toNode = curEdge->to;

        if(conqueredSet.find(toNode) == conqueredSet.end()){
            conqueredSet.insert(toNode);
            result.insert(curEdge);

            for(Edge* nextEdge : toNode->edges){
                minHeap.push(nextEdge);
            }
        }
    }
    return result;
}