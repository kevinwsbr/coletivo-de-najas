#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _binary_tree bt;
typedef struct _avl_tree avl;

//                 ######################
//                 ####     ABB      ####
//                 ######################

struct _binary_tree
{
	int item;
	bt *left;
	bt *right;
};

bt *create_empty_bt()
{
	return NULL;
}

bt *create_bt(int item, bt *left, bt *right)
{
	bt *new_tree = (bt*) malloc(sizeof(bt));
	new_tree->item = item;
	new_tree->left = left;
	new_tree->right = right;

	return new_tree;
}

void print_bt_inorder(bt *bt)
{
	if(bt != NULL)
	{
		print_bt_inorder(bt->left);
		printf("%d ", bt->item);
		print_bt_inorder(bt->right);
	}
}

void print_bt_preorder(bt *bt)
{
	if(bt != NULL)
	{
		printf("%d ", bt->item);
		print_bt_preorder(bt->left);
		print_bt_preorder(bt->right);
	}
}

void print_bt_postorder(bt *bt)
{
	if(bt != NULL)
	{
		print_bt_postorder(bt->left);
		print_bt_postorder(bt->right);
		printf("%d ", bt->item);
	}
}

int search_bt_counter(bt *bt, int item)
{
	if(bt == NULL || bt->item == item)
	{
		return 1;
	}
	else if(bt->item > item)
	{
		return 1 + search_bt_counter(bt->left, item);
	}
	else
	{
		return 1 + search_bt_counter(bt->right, item);
	}
}

bt *add_node_bt(bt *bt, int item)
{
	if(bt == NULL)
	{
		bt = create_bt(item, NULL, NULL);
	}
	else if(bt->item > item)
	{
		bt->left = add_node_bt(bt->left, item);
	}
	else
	{
		bt->right = add_node_bt(bt->right, item);
	}

	return bt;
}

//                 ###################
//                 ####    AVL    ####
//                 ###################       

struct _avl_tree {
    int item;
    int h;
    avl* left;
    avl* right;
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int h(avl* bt)
{
    if (bt == NULL) {
        return -1;
    } else {
        return 1 + max(h(bt->left), h(bt->right));
    }
}

avl* create_empty_avl()
{
	return NULL;
}

avl* create_avl(int item, avl* left, avl* right)
{
    avl* new_tree = malloc(sizeof(avl));
    new_tree->item = item;
    new_tree->left = left;
    new_tree->right = right;
    new_tree->h = h(new_tree);
    
    return new_tree;
}

avl* rotate_left(avl* bt)
{
    avl *subtree_root = NULL;
    if (bt != NULL && bt->right != NULL)
    {
        subtree_root = bt->right;
        bt->right = subtree_root->left;
        subtree_root->left = bt;
    }
    subtree_root->h = h(subtree_root);
    bt->h = h(bt);
    
    return subtree_root;
}

avl* rotate_right(avl* bt)
{
    avl *subtree_root = NULL;
    if (bt != NULL && bt->left != NULL)
    {
        subtree_root = bt->left;
        bt->left = subtree_root->right;
        subtree_root->right = bt;
    }
    subtree_root->h = h(subtree_root);
    bt->h = h(bt);
    
    return subtree_root;
}

int balance_factor(avl *bt)
{
    if (bt == NULL) {
        return 0;
    } else {
        return (h(bt->left) - h(bt->right));
    } 
}

avl* avl_add(avl* bt, int item)
{
    if (bt == NULL) {
        return create_avl(item, NULL, NULL);
    } else if (bt->item > item) {
        bt->left = avl_add(bt->left, item);
    } else {
        bt->right = avl_add(bt->right, item);
    }
        bt->h = h(bt);
        avl* child;
    if (balance_factor(bt) == 2 || balance_factor(bt) == -2) {
        if (balance_factor(bt) == 2) {
            child = bt->left;
            if (balance_factor(child) == -1) {
                bt->left = rotate_left(child);
            }
            bt = rotate_right(bt);
        } else if (balance_factor(bt) == -2) {
        child = bt->right;
            if (balance_factor(child) == 1) {
                bt->right = rotate_right(child);
            }
            bt = rotate_left(bt);
        }
    }
    return bt;
}

int search_avl_counter(avl *bt, int item)
{
	if(bt == NULL || bt->item == item)
	{
		return 1;
	}
	else if(bt->item > item)
	{
		return 1 + search_avl_counter(bt->left, item);
	}
	else
	{
		return 1 + search_avl_counter(bt->right, item);
	}
}

//-------------------------------------------

void print_array(int *array, int size)
{
	for(int i = 0; i < size; i++)
	{
		printf("{%d} -> %d\n", i, array[i]);
	}
}

int main()
{
	bt *arvore = create_empty_bt();
	avl *avl = create_empty_avl();

	FILE *list_data_comp = NULL;


	list_data_comp= fopen("list_data_comp.txt", "w");

	fprintf(list_data_comp, "%s\t%s\t%s\t%s\n",  "comparacoesAVL", "tamanhoAVL", "comparacoesABB", "tamanhoABB");

	char command;
	int x, index;
	int array_size;
	int sorted_counter;
	int countAVL = 0, countABB = 0;
	srand(time(NULL));

	printf("INSERT ARRAY SIZE:\t");
	scanf("%d", &array_size);
	printf("INSERT HOW MANY SEARCHES WE SHOULD DO:\t");
	scanf("%d", &sorted_counter);

	int *array = (int*)malloc(sizeof(int) * array_size);
	int *array_visited = (int*)calloc(array_size, sizeof(int));

	for(int i = 0; i < array_size; i++)
	{
		x = rand();
		array[i] = x;
		arvore = add_node_bt(arvore, x);
		avl = avl_add(avl, x);

	}

	for(int i = 0; i < sorted_counter; i++)
	{
		index = rand() % array_size;
		if(!array_visited[index])
		{			
			countAVL = search_avl_counter(avl, array[index]);
			countABB = search_bt_counter(arvore, array[index]);
			array_visited[index] = 1;			

			fprintf(list_data_comp, "%d\t%d\t%d\t%d\n", countAVL, array_size-index, countABB, index+1);
		}
	}
	free(array);
	free(array_visited);

	return 0;
}
