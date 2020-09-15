//**************************************************************************
//*        File Name : segmentTree.cpp
//*           Author : ljx                                                  
//*          mail : 794035516@qq.com                                       
//*     Created Time : 2020年09月15日 星期二 00时25分35秒
//**************************************************************************
                                                                            
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;

class Tree{
public:
 typedef struct node{
  int data;
  int ls,rs;
  node* left_child;
  node* right_child;
  node(int m_data,int m_ls,int m_rs):data(m_data),ls(m_ls),rs(m_rs),left_child(nullptr),right_child(nullptr){}
 }*pNode;
 
 pNode buildIntervalTree(int* arr,int ls,int rs){
  if(ls + 1 == rs){
   pNode head = new node(arr[ls],ls,rs);
   return head;
  }
  int mid = (ls + rs)/2;
  pNode left = buildIntervalTree(arr,ls,mid);
  pNode right = buildIntervalTree(arr,mid,rs);
  pNode head = new node(min(left->data,right->data), ls,rs);
  head->left_child = left;
  head->right_child = right;
  return head;
 }
 
 void preorderPrint(pNode head){
  if(head == nullptr){
   return;
  }
  cout<<head->data<<"\t";
  preorderPrint(head->left_child);
  preorderPrint(head->right_child);
  return;
 }

 void inorderPrint(pNode head){
  if(head == nullptr){
   return;
  }
  inorderPrint(head->left_child);
  cout<<head->data<<"\t";
  inorderPrint(head->right_child);
  return;
 }

 void postorderPrint(pNode head){
  if(head == nullptr){
   return;
  }
  postorderPrint(head->left_child);
  postorderPrint(head->right_child);
  cout<<head->data<<"\t";
  return;
 }

 void print(int* arr,int len,pNode head){
  cout<<"数组: "<<endl;
  for(int i = 0;i < len;i++){
   cout<<arr[i]<<"\t";
  }
  cout<<endl<<"前序便利"<<endl;
  preorderPrint(head);
  cout<<endl<<"中序便利"<<endl;
  inorderPrint(head);
  cout<<endl<<"后序便利"<<endl;
  postorderPrint(head);
  cout<<endl;
 }

 int queryRange(pNode head,int ls,int rs){
	if(ls <= head->ls && rs >= head->rs){
		return head->data; 
	}
	if(ls >= head->right_child->ls){
		return queryRange(head->right_child,ls,rs);
	}
	if(rs <= head->left_child->rs){
		return queryRange(head->left_child,ls,rs);
	}
	return min(queryRange(head->left_child,ls,rs), queryRange(head->right_child,ls,rs));
 }
};

int main(){
 int len;
 int arr[100];
 int flag = true;
 while(true){
  memset(arr,0,sizeof(arr));
  cout<<"输入数组长度，(-1结束)"<<endl;
  cin>>len;
  if(len == -1){
	break;
  }
  for(int i = 0;i < len;i++){
   cin>>arr[i];
  }
  Tree t;
  Tree::pNode head = t.buildIntervalTree(arr,0,len);
  cout<<"head->data: "<<head->data<<endl;
  t.print(arr,len,head);
  cout<<"输入查询区间: ";
  int ls = 0;
  int rs = 0;
  cin>>ls>>rs;
  int query = t.queryRange(head,ls,rs);
  cout<<"区间最小值: "<<query<<endl;
 }
 return 0;
}
