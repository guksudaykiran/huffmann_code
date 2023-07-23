#include<bits/stdc++.h>
using namespace std;

class Node{
    public:

    char ch;
    int f;
    Node* left;
    Node* right;
};

Node* getNode(char ch,int f,Node *l,Node *r){
    Node* node=new Node();
    node->ch=ch;
    node->f=f;
    node->left=l;
    node->right=r;

    return node;
}

class comp{
    public:

    bool operator()(Node *a, Node *b){
        return a->f > b->f;
    }
};

void encode(Node* root,string str,unordered_map<char,string> &en){
    if(root==NULL){
        return;
    }

    if(!root->left && !root->right){
        en[root->ch]=str;
    }

    encode(root->left,str+"0",en);
    encode(root->right,str+"1",en);

    return;
}

string decode(Node* root,string h){
    string s;

    int i=0;

    while(i<h.size()){
        Node* temp=root;
        while(i<h.size()){
            if(!temp->left && !temp->right){
                break;
            }
            if(h[i]=='0'){
                temp=temp->left;
            }else{
                temp=temp->right;
            }
            i++;
        }
        s+=temp->ch;
    }

    return s;
}

void build_huffmann(string s){

    unordered_map<char,int> mp;
    for(auto it : s){
        mp[it]++;
    }

    priority_queue<Node*,vector<Node*>,comp> pq;

    for(auto it : mp){
        pq.push(getNode(it.first,it.second,NULL,NULL));
    }

    while(pq.size()>1){
        Node *a=pq.top();pq.pop();
        Node *b=pq.top();pq.pop();
        pq.push(getNode('\0',a->f+b->f,a,b));
    }

    unordered_map<char,string> en;
    Node* huff_tree=pq.top();

    encode(huff_tree,"",en);

    cout<<endl;
    cout<<"*******"<<endl;
    cout<<"char encoding: "<<endl;
    for(auto it : en){
        cout<<it.first<<"->"<<it.second<<endl;
    }
    cout<<"*******"<<endl;
    cout<<endl;

    string huff_binary_code;
    for(auto it : s){
        huff_binary_code+=en[it];
    }

    cout<<endl;
    cout<<"*******"<<endl;
    cout<<"huffmann code : "<<endl;
    cout<<huff_binary_code<<endl;
    cout<<"*******"<<endl;
    cout<<endl;

    string h_d=decode(huff_tree,huff_binary_code);

    cout<<endl;
    cout<<"*******"<<endl;
    cout<<"decoded huffmann code : "<<endl;
    cout<<h_d<<endl;
    cout<<"*******"<<endl;
    cout<<endl;

    return;
}

 
int main(){

    cout<<"input string: "<<endl;
    string s;
    cin>>s;

    build_huffmann(s);

    return 0;
}