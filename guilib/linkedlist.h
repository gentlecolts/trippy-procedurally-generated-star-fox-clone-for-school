#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include <iostream>
using namespace std;

/**
this is a templated linked list class, it has some fancy features that makes using linked lists easier
*/

template<typename T>
struct node{
	T data;
	node* next;
	node(T d,node* next=NULL){
		data=d;
		this->next=next;
		//cout<<"made a node with the value = "<<data<<endl;
		//printf("made a node with value %p\n",data);
	}
};
template<typename T>
class linkedlist{
public:
	node<T>* head;
	node<T>* last;
	linkedlist<T>(){
		head=NULL;
		last=head;
		//printf("hi");
		//cout<<"made a list"<<endl;
		//printf("made a list\n");
	}
	linkedlist<T>(T data){
		head=new node<T>(data);
		last=head;
		//cout<<"made a list with the value "<<data<<endl;
		//printf("made a list with the value %p\n",data);
	}

	virtual void addToFront(T value){
		node<T>* tmp=new node<T>(value,head);
		head=tmp;
	}
	virtual void addToBack(T value){
		if(head==NULL){
			head=new node<T>(value);
			last=head;
			return;
		}
		last->next=new node<T>(value);
		last=last->next;
	}

	virtual void deletfront(){
		if(head==NULL){
			return;
		}
		node<T>* tmp=head;
		head=head->next;
		delete tmp;
	}
	virtual void deletend(){
		if(head==NULL){
			return;
		}
		node<T>* tmp=head;
		if(head->next==NULL){
			head=NULL;
			last=head;
			delete tmp;
		}

		while(tmp->next!=last){
			tmp=tmp->next;
		}
		delete last;
		last=tmp;
		last->next=NULL;
	}
};

#endif // LINKEDLIST_H_INCLUDED
