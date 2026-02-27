//图的常用代码模版 面试时候用的 考研时候有极简版本 这个能应付各种情况
#include<bits/stdc++.h>
using namespace std;

class Node;
class Edge;

//1.边结构
class Edge{
public:
    int weight;
    Node *from;
    Node *to;

    Edge(int w, Node *f, Node *t) : weight(w), from(f), to(t){}
};

//2.点结构
class Node{
public:
    int value;     //点的编号或值
    int in;        //入度
    int out;       //出度
    vector<Node*> nexts; //从自己出发能一步走到的点
    vector<Edge*> edges; //从自己出发的边

    Node(int val) : value(val), in(0), out(0){}
};

//3.图的总体结构
class Graph{
public:
    //点集：Key是点的编号，Value是真正的Node节点指针
    unordered_map<int, Node*> nodes;

    //边集：图里所有的边都在这
    unordered_set<Edge*> edges;

    //析构函数
    ~Graph(){
        for(auto& pair : nodes) delete pair.second;
        for(Edge* edge : edges) delete edge;
    }
};

//自己创建接口函数
Graph* createGraph(const vector<vector<int>>& matrix){
    Graph *graph = new Graph();
    for(int i = 0; i < matrix.size(); i++)
    {
        int from = matrix[i][0];
        int to = matrix[i][1];
        int weight = matrix[i][2];

        //安排点：安排起点 若是没有就新创建一个
        if(graph->nodes.count(from) == 0)
        {
            graph->nodes[from] = new Node(from);
        }
        //同理 看看终点有没有被登记
        if(graph->nodes.count(to) == 0)
        {
            graph->nodes[to] = new Node(to);
        }

        Node* fromNode = graph->nodes[from];//增加快捷方式
        Node* toNode = graph->nodes[to];

        Edge* newEdge = new Edge(weight, fromNode, toNode);//创建边实体 把权重 起点实体 终点实体塞进去

        //开始织网 节点都创建完了 就要创建他们之间的关系了
        fromNode->nexts.push_back(toNode);//起点的邻居多了个节点
        fromNode->out++;//起点的出度+1
        fromNode->edges.push_back(newEdge);//起点出发的边多了条新边

        toNode->in++;//终点被别人指了 入度+1

        graph->edges.insert(newEdge);//扔给Graph这个大集装箱
    }
    return graph;
}

//BFS核心算法 只需要传入一个初始节点start 这是简易版本
void bfs_lightweight(const vector<vector<int>>& graph, int start){
    int n = graph.size();

    queue<int> q;
    
    //创建黑名单 从0到n-1全都是连续的
    vector<bool> visited(n, false);

    q.push(start);
    visited[start] = true;

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        cout << "正在访问节点编号" << cur << endl;

        for(int next : graph[cur])
        {
            if(!visited[next])
            {
                q.push(next);
                visited[next] = true;
            }
        }
    }
}

void bfs(Node *startNode)//模版套路版本
{
    if(startNode == NULL)
    {
        return;
    }
    queue<Node*> q;
    //防止死循环的 哈希名单
    unordered_set<Node*> visitedSet;

    q.push(startNode);
    visitedSet.insert(startNode);

    //只要队列里还有人 就要一直循环
    while(!q.empty())
    {
        //从队列里拿出来一个节点
        Node *cur = q.front();
        q.pop();

        cout << "正在访问节点：" << cur->value << endl;

        for(Node *next : cur->nexts)
        {
            if(visitedSet.find(next) == visitedSet.end())
            {
                q.push(next);
                visitedSet.insert(next);//立刻拉进黑名单，防止别人重复排
            }
        }
    }
}

//深度优先遍历 对于元素的处理 是进入栈的时候处理 对于宽度优先遍历 是在被弹出队列之后处理
//套路版本
void dfs(Node* startNode)
{
    if(startNode == NULL)
    {
        return;
    }
    stack<Node*> st;//手动准备一个栈
    unordered_set<Node*> visitedSet;//哈希表黑名单
    
}