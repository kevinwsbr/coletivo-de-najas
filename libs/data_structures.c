#include "compact.h"

/*
 * Priority queue
 */

queue *create_queue()                         
{                                             
    queue *new_queue = malloc(sizeof(queue)); 
    new_queue->head = NULL;
    return new_queue;
}

void enqueue(queue *pq, void *i, int p)
{
    node *new_node = malloc(sizeof(node));
    

    (new_node->item) = i;
    new_node->frequency = p;
    new_node->left = NULL;
    new_node->right = NULL;
    if ((is_empty(pq)) || (p <= pq->head->frequency))
    {                                                 
        new_node->next = pq->head;
        pq->head = new_node;
    }
    else
    {
        node *current = pq->head;         
        while ((current->next != NULL) && (current->next->frequency < p))
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}
void enqueue_node(node *new_node, queue *pq) 
{
    if ((is_empty(pq)) || (new_node->frequency <= pq->head->frequency))
    {
        new_node->next = pq->head;
        pq->head = new_node;
    }
    else
    {
        node *current = pq->head;
        while ((current->next != NULL) &&
               (current->next->frequency < new_node->frequency))
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}
node *dequeue(queue *pq)
{
    if (is_empty(pq)) 
    {
        printf("Priority Queue underflow");
        return NULL;
    }
    else 
    {
        node *node = pq->head;     
        pq->head = pq->head->next; 
        node->next = NULL;         
        return node;               
    }
}

void print_q(queue *queue) //função que imprime fila
{
    if (!is_empty(queue)) // se a fila não estiver vazia a função segue
    {
        node *current = queue->head; //cria um ponteiro pra nó, para  poder se navegar na fila
        while (current != NULL)      //enquanto o ponteiro não chega no fim da fila
        {
            printf("%c ", *(unsigned char *)current->item); //printa o item do ponteiro
            current = current->next;                        //atualiza o ponteiro
        }
        printf("\n");
    }
}

int is_empty(queue *queue)
{
    return (queue->head == NULL);
}

void frequency_enqueue(int *frequency, queue *queue)
{
    int i;
    for (i = 0; i < 256; i++)
    {
        if (frequency[i] != 0)
        {
            unsigned char *aux = (unsigned char *)malloc(sizeof(unsigned char));
            *aux = i;
            enqueue(queue, aux, frequency[i]);
        }
    }
}

/*
 * Binary tree
 */

void print_tree(node *root) 
{
    if (root != NULL) 
    {
        printf("node: %c %d\n", *(unsigned char *)root->item, root->frequency); 
        print_tree(root->left);                                                 
        print_tree(root->right);                                                
    }
}

node *merge_nodes(queue *queue) 
{
    if (queue->head->next != NULL) 
    {
        unsigned char *aux = (unsigned char *)malloc(sizeof(unsigned char));
        *aux = '*';
        node *new_node = malloc(sizeof(node));                                        
        new_node->left = dequeue(queue);                                              
        new_node->right = dequeue(queue);                                             
        new_node->item = aux;                                                         
        new_node->frequency = new_node->left->frequency + new_node->right->frequency; 
        enqueue_node(new_node, queue);                                                        

        merge_nodes(queue); 
    }
    else 
    {
        return queue->head;
    }
}

int tree_size(node *root)
{
    if (root->left == NULL && root->right == NULL)
    {
        if (comparing(root->item, '*') || comparing(root->item, (char)SLASH))
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1 + tree_size(root->left) + tree_size(root->right);
    }
}

void fprint_tree(node *root, FILE *compact_file)
{
    if (root != NULL)
    {
        if (root->left == NULL && root->right == NULL && (comparing(root->item, '*') || comparing(root->item, (char)SLASH)))
        {
            fprintf(compact_file, "%c", (char)SLASH);
        }
        fprintf(compact_file, "%c", *(unsigned char *)root->item);
        fprint_tree(root->left, compact_file);
        fprint_tree(root->right, compact_file);
    }
}

/*
 * Hash table
 */


hash_table *create_hash_table()
{
    int i;
    hash_table *new_hash = (hash_table *)malloc(sizeof(hash_table));
    for (i = 0; i < 256; i++)
    {
        new_hash->table[i] = NULL;
    }
    return new_hash;
}

element *create_element()
{
    element *new_ele = (element *)malloc(sizeof(element));
    new_ele->n = 0;

    return new_ele;
}

void add_hash(hash_table *ht, void *character, char bit[], int n)
{
    int h = *(unsigned char *)character;

    element *new_ele = create_element();
    new_ele->n = n;
    int i;
    
    for (i = 0; i < n; i++)
    {
        new_ele->str[i] = bit[i];
    }
    
    ht->table[h] = new_ele;

    return;
}

void print_hash(hash_table *ht) //printa a hash, ou seja, os elementos e suas respectivas frequências
{
    int i, j;
    for (i = 0; i < 256; i++)
    {
        if (ht->table[i] != NULL)
        {
            printf("%d ->", i);
            for (j = 0; j < ht->table[i]->n; j++)
            {
                printf("%c", ht->table[i]->str[j]);
            }
            printf(" [%d]\n", ht->table[i]->n);
        }
    }
}