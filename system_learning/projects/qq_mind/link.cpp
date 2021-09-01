#include "mylink.h"

void mylink_init(mylink *head)	//struct node **head = &head
{
	*head = NULL;
}

mylink make_node(char *item, int fd)
{
	//mylink p = (mylink)malloc(sizeof(struct node));
	mylink p = new node;
	strcpy(p->item,item);		//(*p).itme = item;
 	p->fifo_fd = fd;

	p->next = NULL;				//#define NULL (void *)0
	return p;
}

void mylink_insert(mylink *head, mylink p)	// 头插	
{
	p->next = *head;
	*head = p;
}

mylink mylink_search(mylink *head, char *keyname)
{
	for (mylink p = *head; p != NULL; p = p->next)
		if (strcmp(p->item,keyname) == 0)
			return p;
	return NULL;
}

void mylink_delete(mylink *head, mylink q)
{
    if (q == *head) {//如果要删除的节点是头结点
		*head = q->next;
		return;
	}
	for (mylink p = *head; p != NULL; p = p->next)
		if (p->next == q) {
			p->next = q->next;
			delete q; //释放q的空间
			return;
		}
}

/*
void free_node(mylink p)
{
	//free(p);
	delete p;
}
*/

void mylink_destory(mylink *head)
{
	mylink p= *head, tmp;
	while (p != NULL) {
		tmp = p->next;
		//free(p);
		delete p;
		p = tmp;
	}
	*head = NULL;
}

void mylink_travel(mylink *head, void (*vist)(mylink)) // 调用函数
{
	std::cout << "当前在线用户:";
	for (mylink p = *head; p != NULL; p = p->next)
		vist(p);
	std::cout << std::endl;
}
void vist(mylink p){
	std::cout << p->item << ",";	
}
