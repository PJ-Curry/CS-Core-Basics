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
    Node* to;
    Edge(int w, Node* t) : weight(w), to(t){}
};

//建立一个新类 把节点和边联系到一起 同时知道边长和到达的地点
class NodeRecord{
public:
    Node* node;
    int distance;
    NodeRecord(Node* n,int d) : node(n), distance(d){}
};

struct RecordComparator{
    bool operator()(const NodeRecord& a, const NodeRecord& b){
        return a.distance > b.distance; 
    }
};//小根堆的比较器

//STL自带堆
unordered_map<Node*, int> dijkstra_STL(Node* head){
    //记录起点到每个点的最短绝对距离
    unordered_map<Node*, int> distanceMap;
    //建立封锁名单(已经确定了的最小值，以后不用再参与运算)
    unordered_set<Node*> selectedNodes;

    //直接申请一个优先队列 小根堆
    priority_queue<NodeRecord, vector<NodeRecord>, RecordComparator> minHeap;

    distanceMap[head] = 0;
    minHeap.push(NodeRecord(head, 0));

    while(!minHeap.empty()){
        NodeRecord record = minHeap.top();
        minHeap.pop();

        Node* cur = record.node;
        int distance = record.distance;

        //判断是否有更短的记录 如果已经在selectnode里 就直接删掉
        if (selectedNodes.find(cur) != selectedNodes.end()){
            continue; //continue的作用对象永远是循环
        }

        //查看邻居
        for(Edge* edge : cur->edges){
            Node* toNode = edge->to;
            int newDistance = distance + edge->weight;

            if(distanceMap.find(toNode) == distanceMap.end() || newDistance < distanceMap[toNode]){
                distanceMap[toNode] = newDistance;

                minHeap.push(NodeRecord(toNode, newDistance));
            }
        }
        selectedNodes.insert(cur);//该节点其实早就被认定为最短了 但他的作用还未结束 还要作为父节点的跳板 看看自己到其他节点和父亲到其他节点比较一下
    }
    return distanceMap;
}