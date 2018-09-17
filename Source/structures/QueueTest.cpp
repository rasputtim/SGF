#include "structures\SGF_Queue.h"
#include <stdio.h>
#include <stddef.h>
#include <iostream> 

typedef struct pathNode_s {
	int					dir;
	float				dist;
	int					obstacle;
	int					edgeNum;
	int					numNodes;
	struct pathNode_s *	parent;
	struct pathNode_s *	children[2];
	struct pathNode_s *	next;
	void				pathNode_t(){
	dir = 0;
	obstacle = -1;
	edgeNum = -1;
	numNodes = 0;
	parent = children[0] = children[1] = next = 0;
	}
} pathNode_t;


static void teste() {
pathNode_t *root, *node, *child;

SGF::CQueue<pathNode_t> pathNodeQueue, treeQueue;
SGF::CQueueConcurrent<int> concurrentqueue(100);
SGF::CQueueConcurrent<pathNode_t> concurrentqueue2; //just for 10 elements
root = new pathNode_t();
node = new pathNode_t();
child = new pathNode_t();
pathNodeQueue.addItem( *root );
pathNodeQueue.addItem( *node );
pathNodeQueue.addItem( *child );
concurrentqueue.addItem(10);
concurrentqueue.addItem(10);
concurrentqueue.addItem(10);
concurrentqueue2.addItem(*root);
concurrentqueue2.addItem(*node);
concurrentqueue2.addItem(*child);

int kk;
if (concurrentqueue.getItem_try(kk)) {}
else { exit; }//error or queue empty
concurrentqueue.getItem_after_wait(kk);
SGF::CQueue<int> intQueue1(10), intQueue2(10);  // create two integer queues 
 
  intQueue1.addItem(1); 
  intQueue1.addItem(2); 
  intQueue1.addItem(3); 
 
  intQueue2.addItem(10); 
  intQueue2.addItem(20); 
  intQueue2.addItem(30); 
 
  cout << "Contents of integer queue intQueue1: "; 
  int y;
  for(int i=0; i < 3; i++) 
   intQueue2.getItem(y);
    cout << y << " ";
  cout << endl; 
 
  cout << "Contents of integer queue intQueue2: "; 
  int z;
  for(int i=0; i < 3; i++) 
	intQueue2.getItem(z);
    cout << z << " "; 
  cout << endl; 
 
  SGF::CQueue<double> doubleQueue1(10), doubleQueue(10);  // create two double queues
 
 
  doubleQueue1.addItem(1.01); 
  doubleQueue1.addItem(2.02); 
  doubleQueue1.addItem(3.03); 
 
  doubleQueue.addItem(10.01); 
  doubleQueue.addItem(20.02); 
  doubleQueue.addItem(30.03); 
 
  cout << "Contents of double queue doubleQueue1: "; 
  double x;
  for(int i=0; i < 3; i++) 
	doubleQueue1.getItem(x);
    cout << x << " ";
  cout << endl; 
 
  cout << "Contents of double queue doubleQueue: "; 
  for(int i=0; i < 3; i++) 
  doubleQueue1.getItem(x);
  cout << x << " ";
  cout << endl; 
}