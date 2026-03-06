//Kruska的代码实现有一点很要紧：判断是否成环 即点集要覆盖所有点 但在覆盖的过程中 不能有重复 即要用到并查集的概念
#include<bits/stdc++.h>
using namespace std;
class Node{
public:
    int value;
    Node(int val) : value(val){}
};

class Edge{
public:
    int weight;
    Node* from;
    Node* to;
    Edge(int w, Node* f, Node* t) : weight(w), from(f), to(t){}
};

//建立并查集：防止出现环
class UnionFind{
private:
    //记录自己的大哥是谁，Key是小弟，Value是大哥
    unordered_map<Node* ,Node*> fatherMap;
public:
    //初始化：最开始每个人都是独立的 自己就是大哥
    void makeSets(const vector<Node*>& nodes){
        for(Node* node : nodes){
            fatherMap[node] = node;
        }
    }

    //找到真正的老大哥
    Node *findFather(Node* node){
        Node* father = fatherMap[node];
        if(father != node){
            father = findFather(father);
        }
        fatherMap[node] = father;
        return father;
    }
    //查验身份 判断两个人的老大哥是不是同一个人
    bool isSameSet(Node* a,Node* b){
        return findFather(a) == findFather(b);
    }

    //合并操作
    void unionSet(Node* a,Node* b){
        Node* aHead = findFather(a);
        Node* bHead = findFather(b);
        if(aHead != bHead){
            fatherMap[aHead] = bHead;
        }
    }
};
//数字比较器 Kruskal要从边全权最小的开始找
struct EdgeComparator{
    //重载运算符
    bool operator()(Edge* a, Edge* b){
        return a->weight > b->weight;
    }
};

//开始实现Kruskal算法 传入所有的节点和所有边
unordered_set<Edge*> kruskalMST(const vector<Node*>& nodes, const vector<Edge*>& edges){
    UnionFind uf;
    uf.makeSets(nodes);

    //声明一个小根堆
    priority_queue<Edge*, vector<Edge*>, EdgeComparator> minHeap;

    for(Edge* edge : edges){
        minHeap.push(edge);
    }

    //准备一个装结果的容器
    unordered_set<Edge*> result;

    while(!minHeap.empty()){
        Edge* curEdge = minHeap.top();
        minHeap.pop();
        if(!uf.isSameSet(curEdge->from, curEdge->to)){//这条边连接的两个节点是否在一个集合内
            result.insert(curEdge);
            uf.unionSet(curEdge->from, curEdge->to);
        }
    }   
    return result; 
}