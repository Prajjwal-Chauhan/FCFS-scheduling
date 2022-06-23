#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int burst_time;
    int arrival_time;
    struct node *next;
    struct node *prev;
} node;

node *createLinkedList(int n)
{
    node *head = NULL;
    node *tail = NULL;
    node *temp = NULL;

    for (int i = 0; i < n; i++)
    {
        tail = (node *)malloc(sizeof(node));
        printf("\n\nPROCESS %d : ", i + 1);
        printf("\nEnter the Arrival Time of Process %d ('0' RECOMMENDED) : ", i + 1);
        scanf("%d", &(tail->arrival_time));
        printf("Enter the Burst Time of Process %d : ", i + 1);
        scanf("%d", &(tail->burst_time));
        tail->prev = NULL;
        tail->next = NULL;

        if (head == NULL)
        {
            head = tail;
            temp = tail;
        }
        else
        {
            temp->next = tail;
            tail->prev = temp;

            while (temp->next != NULL)
            {
                temp = tail;
            }
        }
    }
    return head;
}

void display(node *head)
{
    node *temp = head;
    int i = 0;
    printf("\nTraversing the list now :\n");
    printf("\n  Processes\t\t  Arrival Time\t\t    Burst Time\n");
    while (temp != NULL)
    {
        printf("Process: %d \t\t\t %d \t\t\t %d\n", i + 1, temp->arrival_time, temp->burst_time);
        i++;
        temp = temp->next;
    }
    printf("\n");
}

int waiting_time(node *temp, int i)
{

    if (i == 1)
    {
        return 0;
    }
    else
    {
        return temp->burst_time + waiting_time(temp->prev, i - 1);
    }
}

void all(node *head, int n)
{
    node *temp = head;
    int total_TAT = 0;
    int total_WT = 0;
    int wt;
    printf("\n\n\t\t   SHOWING CHART OF DIFFERENT CALCULATED TIMES\n");
    printf("\n  Processes\t\t  Waiting Time\t\tTurnAround Time\t\tCompletion Time\n");
    for (int i = 1; i <= n; i++)
    {
        wt = waiting_time(temp, i);
        printf("Process: %d \t\t\t %d ", i, wt);

        if (i > 1)
        {
            temp = temp->next;
        }

        int TAT = wt + temp->burst_time;
        printf("\t\t\t %d ", TAT);
        printf("\t\t\t %d\n", TAT + temp->arrival_time);
        total_WT += wt;
        total_TAT += TAT;
    }
    float avg_WT = (float)total_WT / n;
    float avg_TAT = (float)total_TAT / n;

    printf("\nAverage Waiting Time    =\t%.2f", avg_WT);
    printf("\nAverage Turnaround Time =\t\t\t\t%.2f\n\n", avg_TAT);
}

node *enqueue(node *head, int n, int k)
{

    for (int i = 0; i < k; i++)
    {
        node *tail = (node *)malloc(sizeof(node));
        node *temp = head;
        tail->prev = NULL;
        tail->next = NULL;
        printf("\n\nPROCESS %d : ", n + i + 1);
        printf("\nEnter the Arrival Time of Process %d ('0' RECOMMENDED) : ", n + i + 1);
        scanf("%d", &(tail->arrival_time));
        printf("Enter the Burst Time of Process %d : ", n + i + 1);
        scanf("%d", &(tail->burst_time));

        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        tail->prev = temp;
        temp->next = tail;
    }

    return head;
}

int main()
{
    node *head = NULL;
    int n;

    printf("\n\n\n\n//////////**********    Implementation of the FCFS scheduling algorithm    **********//////////\n");
    printf("//////////**********                       using                           **********//////////\n");
    printf("//////////**********             Queue in Doubly Linked List               **********//////////\n");
    printf("\nEnter the number of Processes : ");
    scanf("%d", &n);
    head = createLinkedList(n);
    display(head);
    all(head, n);
    int choice;
    do
    {
        printf("Want to Enqueue more processes \n('1' Proceed  ||  '0' Reject): ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            int k;
            printf("Enter the number of Processes to Enqueue more : ");
            scanf("%d", &k);
            head = enqueue(head, n, k);
            display(head);
            n = n + k;
            all(head, n);
        }
        else if (choice != 1 && choice != 0)
        {
            printf("Invalid option !!");
        }
    } while (choice != 0);
    printf("\n\n");

    return 0;
}
