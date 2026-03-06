#include<bits/stdc++.h>
using namespace std;
class Node{
public:
    int value;//节点值
    int in;//入度
    vector<Node*> nexts;//指向的邻居节点

    Node(int val) : value(val), in(0){}
};

class Graph{
public:
    unordered_map<int, Node*> nodes;//编号映射节点
};

vector<Node*> sortedTopology(Graph *graph){
    //key:某一个节点
    //value:剩余的入度
    unordered_map<Node*, int> inMap;//用来记录节点和对应的入度的表格

    //入度为0的节点能入队
    queue<Node*> zeroInqueue;

    for(auto& pair : graph->nodes){
        Node* node = pair.second;
        //开始记录入度数
        inMap[node] = node->in;

        if(node->in == 0){
            zeroInqueue.push(node);
        }
    }

    //准备一个装最后结果的容器
    vector<Node*> result;

    //把入度的节点的关联的边都删掉
    while(!zeroInqueue.empty()){
        Node* cur = zeroInqueue.front();
        zeroInqueue.pop();
        result.push_back(cur);

        //开始拆桥
        for(Node* next : cur->nexts){
            inMap[next] = inMap[next] - 1;
            if(inMap[next] == 0){
                zeroInqueue.push(next);
            }
        }
    }
    return result;
}

// 本地测试大厅
int main() {
    // 手动造一个图：A(1) -> B(2), A(1) -> C(3), B(2) -> D(4), C(3) -> D(4)
    // 拓扑序应该是：1, 2, 3, 4 或者 1, 3, 2, 4
    Graph* graph = new Graph();
    Node* nodeA = new Node(1);
    Node* nodeB = new Node(2);
    Node* nodeC = new Node(3);
    Node* nodeD = new Node(4);

    // 连线：A -> B, A -> C
    nodeA->nexts.push_back(nodeB); nodeB->in++;
    nodeA->nexts.push_back(nodeC); nodeC->in++;
    // 连线：B -> D, C -> D
    nodeB->nexts.push_back(nodeD); nodeD->in++;
    nodeC->nexts.push_back(nodeD); nodeD->in++;

    graph->nodes[1] = nodeA;
    graph->nodes[2] = nodeB;
    graph->nodes[3] = nodeC;
    graph->nodes[4] = nodeD;

    vector<Node*> topoResult = sortedTopology(graph);

    cout << "拓扑排序结果: ";
    for (Node* n : topoResult) {
        cout << n->value << " ";
    }
    cout << endl;

    return 0;
}