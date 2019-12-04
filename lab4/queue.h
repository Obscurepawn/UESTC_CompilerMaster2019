#ifndef QUEUE_H
#define QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Elemtype char*

struct Queue
{
    int len;
    Elemtype *pdata;
    int front;
    int rear;
};

typedef struct Queue queue;
typedef struct Queue *pqe;

bool init_queue(pqe *que, int size);
bool is_que_full(queue que);
bool is_que_empty(queue que);
bool que_push(pqe que, Elemtype data);
Elemtype que_pop(pqe que);
bool Destroy_que(pqe *que);
bool outputQue(queue que);
bool que_pop_all(pqe que);

bool init_queue(pqe *que, int size)
{
    (*que) = (pqe)malloc(sizeof(queue));
    if (!(*que))
        return false;
    (*que)->len = size;
    (*que)->front = (*que)->rear = 0;
    (*que)->pdata = (Elemtype *)malloc(sizeof(sizeof(Elemtype) * (size + 1)));
    return true;
}

bool is_que_full(queue que)
{
    if ((que.rear + 1) % (que.len + 1) == que.front) //有一个空余空间是不可用的，用于判断队列满空
        return true;
    else
        return false;
}

bool is_que_empty(queue que)
{
    if (que.rear == que.front)
        return true;
    else
        return false;
}

bool que_push(pqe que, Elemtype data)
{
    if (is_que_full(*que))
    {
        printf("this queue is already full!\n");
        return false;
    }
    else
    {
        que->pdata[que->rear] = data;
        que->rear = (que->rear + 1) % (que->len + 1);
        return true;
    }
    return false;
}

Elemtype que_pop(pqe que)
{
    if (is_que_empty(*que))
    {
        printf("this queue is empty!\n");
        return NULL;
    }
    else
    {
        Elemtype tmp = que->pdata[que->front];
        que->front = (que->front + 1) % (que->len + 1);
        return tmp;
    }
    return NULL;
}

bool Destroy_que(pqe *que)
{
    if (!(*que))
    {
        printf("the queue doesn't exit!\n");
        return false;
    }
    else
    {
        if ((*que)->pdata)
            free((*que)->pdata);
        free(*que);
        *que = NULL;
        return true;
    }
    return false;
}

bool outputQue(queue que)
{
    if (is_que_empty(que))
        return false;
    int tmp = que.front;
    while (tmp != que.rear)
    {
        printf("%s\t", que.pdata[tmp]);
        tmp = (tmp + 1) % (que.len + 1);
    }
    puts("");
    return true;
}

bool que_pop_all(pqe que)
{
    if (!que)
        return false;
    while (!is_que_empty(*que))
        printf("%s\t", que_pop(que));
    puts("");
    return true;
}

#endif