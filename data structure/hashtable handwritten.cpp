#include<iostream>
#include<vector>
using namespace std;

//定义哈希表节点
struct Node
{
    int key,value;
    Node *next;
    Node(int k,int v):key(k),value(v),next(nullptr){}
};

class HashTable
{
private:
    static const int SIZE = 10007;
    vector<Node*> table;

    //哈希函数
    int hash(int key)
    {
        return (key%SIZE+SIZE)%SIZE;//保证非负
    }

public:
    HashTable()
    {
        table.resize(SIZE,nullptr);
    }

    //插入 更新
    void insert(int key,int value)
    {
        int idx=hash(key);
        Node *cur=table[idx];
        //如果已经存在该key 就直接更新value
        while(cur)
        {
            if(cur->key==key)
            {
                cur->value = value;
                return;
            }
            cur = cur->next;
        }
        Node* newNode = new Node(key, value);
        newNode -> next = table[idx];
        table[idx] = newNode;
    }

    // 查询
    bool find(int key, int &value) 
    {
        int idx = hash(key);
        Node* cur = table[idx];
        while (cur)
        {
            if (cur->key == key) 
            {
                value = cur->value;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    // 删除（可选实现）
    bool erase(int key) 
    {
        int idx = hash(key);
        Node* cur = table[idx];
        Node* prev = nullptr;
        while (cur) 
        {
            if (cur->key == key) 
            {
                if (prev) prev->next = cur->next;
                else table[idx] = cur->next;
                delete cur;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }
};