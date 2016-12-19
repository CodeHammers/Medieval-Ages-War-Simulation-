#include"utility.h"

bool IsEmpty(Queue &queue)
{
	return((queue.bounds.front == NULL&&queue.bounds.rear == NULL) ? true : false);
}


void Enqueue(Queue &queue, enemy* &data,Statistics &stats)
{
	if (IsEmpty(queue))   //handling the case of an empty queue.
		queue.bounds.front = queue.bounds.rear = data;
	else {
		queue.bounds.rear->next = data;  
		queue.bounds.rear = data;
	}
	data->next = NULL;
	stats.Total_inactive++;
}