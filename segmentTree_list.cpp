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
  int data; //存储的数据
  int ls,rs;    //（左，右）区间
  node* left_child;    //左节点
  node* right_child;
  node(int m_data,int m_ls,int m_rs):data(m_data),ls(m_ls),rs(m_rs),left_child(nullptr),right_child(nullptr){}
 }*pNode;
 
 /*
	@params   arr数组，ls,rs（左右区间）
	*/
 pNode buildIntervalTree(int* arr,int ls,int rs){
	 //刚好一个，构建节点
  if(ls + 1 == rs){
   pNode head = new node(arr[ls],ls,rs);
   return head;
  }
  int mid = (ls + rs)/2;
  //分治构建左右节点
  pNode left = buildIntervalTree(arr,ls,mid);
  pNode right = buildIntervalTree(arr,mid,rs);
  //回溯构建父亲节点
  pNode head = new node(min(left->data,right->data), ls,rs);
  head->left_child = left;
  head->right_child = right;
  //最后返回构建根节点
  return head;
 }
 
//前序便利树节点，中左右
 void preorderPrint(pNode head){
  if(head == nullptr){
   return;
  }
  cout<<head->data<<"\t";
  preorderPrint(head->left_child);
  preorderPrint(head->right_child);
  return;
 }

 //中序便利，左中右
 void inorderPrint(pNode head){
  if(head == nullptr){
   return;
  }
  inorderPrint(head->left_child);
  cout<<head->data<<"\t";
  inorderPrint(head->right_child);
  return;
 }

 //后序便利，左右中
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

 /*
	@params  根节点，左右区间
	@returns 查询区间最小值
 */

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
