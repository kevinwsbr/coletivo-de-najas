#include <stdio.h>
#include <stdlib.h>
#include "src/libs/compact.h"
#include "src/libs/descompact.h"
#include "src/libs/data_structures.h"
#include "src/libs/utils.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>


FILE *input = NULL;
//---- --- - - -- -
int opening()
{
    input = fopen("entrada.txt", "rb");   
    if(input == NULL)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int closing()
{
    if(fclose(input))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}



// ---------------------

void test_frequency_saving()
{
    int *frequencies = save_frequency(input);
    //input = "aaaaabbbbccccddeef" (a->[5], b->[4], c->[4], d->[2], e->[2], f->[1])
    int a = 'a', b = 'b', c = 'c', d = 'd', e = 'e', f = 'f';
    CU_ASSERT_EQUAL(frequencies[a], 5);
    CU_ASSERT_EQUAL(frequencies[b], 4);
    CU_ASSERT_EQUAL(frequencies[c], 4);
    CU_ASSERT_EQUAL(frequencies[d], 2);
    CU_ASSERT_EQUAL(frequencies[e], 2);
    CU_ASSERT_EQUAL(frequencies[f], 1);  
}
void test_frequency_enqueue()
{
    queue *queue1 = create_queue();
    rewind(input);
    int *frequencies = save_frequency(input);
    frequency_enqueue(frequencies, queue1);
    //input = "aaaaabbbbccccddeef" (a->[5], b->[4], c->[4], d->[2], e->[2], f->[1])
    node *current = queue1->head;
    CU_ASSERT_EQUAL(*((int*)current->item), 'f');
    current = current->next;
    CU_ASSERT_EQUAL(*((int*)current->item), 'e');
    current = current->next;
    CU_ASSERT_EQUAL(*((int*)current->item), 'd');
    current = current->next;
    CU_ASSERT_EQUAL(*((int*)current->item), 'c');
    current = current->next;
    CU_ASSERT_EQUAL(*((int*)current->item), 'b');
    current = current->next;
    CU_ASSERT_EQUAL(*((int*)current->item), 'a');
}
void test_enqueue()
{
	queue *queue1 = create_queue();
	int a = 1, b = 2, c = 3, d = 4;
	//Priority of 1 is 100
	enqueue(queue1, &a, 100);
	//Priority of 2 is 120
	enqueue(queue1, &b, 120);
	//Priority of 3 is 50
	enqueue(queue1, &c, 50);
	//Priority of 4 is 120
	enqueue(queue1, &d, 120);


	node *current = queue1->head;
	CU_ASSERT_EQUAL(*((int*)current->item), 3);
	current = current->next;
	CU_ASSERT_EQUAL(*((int*)current->item), 1);
	current = current->next;
	CU_ASSERT_EQUAL(*((int*)current->item), 4);
	current = current->next;
	CU_ASSERT_EQUAL(*((int*)current->item), 2);
}

void test_dequeue()
{
	queue *queue1 = create_queue();
	int a = 1, b = 2, c = 3, d = 4;
	//Priority of 1 is 100
	enqueue(queue1, &a, 100);
	//Priority of 2 is 120
	enqueue(queue1, &b, 120);
	//Priority of 3 is 50
	enqueue(queue1, &c, 50);
	//Priority of 4 is 120
	enqueue(queue1, &d, 120);

	node *current = dequeue(queue1);
	CU_ASSERT_EQUAL(*((int*)current->item), 3);
	current = dequeue(queue1);
	CU_ASSERT_EQUAL(*((int*)current->item), 1);
	current = dequeue(queue1);
	CU_ASSERT_EQUAL(*((int*)current->item), 4);
	current = dequeue(queue1);
	CU_ASSERT_EQUAL(*((int*)current->item), 2);

	CU_ASSERT_EQUAL(is_empty(queue1), 1);
}

// --------- - - - - - -  TREE

// ************
node *create_test_tree()
{
	node *root = create_node('*');
	root->left = create_node('A');
	root->right = create_node('B');

	return root;
}

void writing_pre_order(node *root, char *string, int* count)
{
    if (root != NULL)
    {
        if (root->left == NULL && root->right == NULL && (comparing(root->item, '*') || comparing(root->item, '\\')))
        {
            string[*count] = '\\';
            *count += 1;
        }
        string[*count] = *(unsigned char *)root->item;
        *count += 1;

        writing_pre_order(root->left, string, count);
        writing_pre_order(root->right, string, count);
    }
}
// ****************
void test_tree()
{
	node *root = create_test_tree();

	CU_ASSERT_EQUAL(*((unsigned char*)root->item), '*');
	CU_ASSERT_EQUAL(*((unsigned char*)root->left->item), 'A');
	CU_ASSERT_EQUAL(*((unsigned char*)root->right->item), 'B');
	CU_ASSERT_EQUAL(tree_size(root), 3);
}

void test_merge_nodes()
{
    queue* queue1 = create_queue();
    int *frequencies = save_frequency(input);
    frequency_enqueue(frequencies, queue1);
    node *root = merge_nodes(queue1);

    CU_ASSERT_PTR_NULL(queue1->head->next);
    CU_ASSERT_EQUAL(*((unsigned char*)queue1->head->item), '*');
}

void test_tree_size()
{
    rewind(input);
    queue* queue1 = create_queue();
    int *frequencies = save_frequency(input);
    frequency_enqueue(frequencies, queue1);
    node *root = merge_nodes(queue1);

    CU_ASSERT_EQUAL(tree_size(root), 11);
}

void test_preorder_tree()
{
    rewind(input);
    queue* queue1 = create_queue();
    int *frequencies = save_frequency(input);
    frequency_enqueue(frequencies, queue1);
    node *root = merge_nodes(queue1);

    char p_order[15] = "**cb**d*fea";
    char w_p_order[15];
    int *i = (int*)malloc(sizeof(int));
    *i = 0;    
    writing_pre_order(root, w_p_order, i);

    CU_ASSERT_NSTRING_EQUAL(p_order, w_p_order, 11);
    CU_ASSERT_EQUAL(*i, 11);


}
//---------------- HASH -----------

void test_huff_code()
{
    rewind(input);
    char compacted_byte[50];
    hash_table *hash_table1 = create_hash_table();
    queue* queue1 = create_queue();
    int *frequencies = save_frequency(input);
    frequency_enqueue(frequencies, queue1);
    node *root = merge_nodes(queue1);
    generate_huffman_tree(root, 0, hash_table1, compacted_byte);
    int a = 'a', b = 'b', c = 'c', d = 'd', e = 'e', f = 'f';

    CU_ASSERT_EQUAL(hash_table1->table[a]->n, 2);
    CU_ASSERT_STRING_EQUAL(hash_table1->table[a]->str, "11");

    CU_ASSERT_EQUAL(hash_table1->table[b]->n, 2);
    CU_ASSERT_STRING_EQUAL(hash_table1->table[b]->str, "01");

    CU_ASSERT_EQUAL(hash_table1->table[c]->n, 2);
    CU_ASSERT_STRING_EQUAL(hash_table1->table[c]->str, "00");

    CU_ASSERT_EQUAL(hash_table1->table[d]->n, 3);
    CU_ASSERT_STRING_EQUAL(hash_table1->table[d]->str, "100");

    CU_ASSERT_EQUAL(hash_table1->table[e]->n, 4);
    CU_ASSERT_STRING_EQUAL(hash_table1->table[e]->str, "1011");

    CU_ASSERT_EQUAL(hash_table1->table[f]->n, 4);
    CU_ASSERT_STRING_EQUAL(hash_table1->table[f]->str, "1010");
}

int main() {


   // Init the CUnit
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

    // FIRST SUITE
        CU_pSuite ps_queue = NULL;

        ps_queue = CU_add_suite("test_queue", opening, closing);

        if(ps_queue == NULL)
        {
          CU_cleanup_registry();
          return CU_get_error();
        }

        //Adding test to the suite
        if (NULL == CU_add_test(ps_queue, "test_enqueue", test_enqueue)) {
          CU_cleanup_registry();
          return CU_get_error();
        }

        if (NULL == CU_add_test(ps_queue, "test_dequeue", test_dequeue)) {
          CU_cleanup_registry();
          return CU_get_error();
        }
        if(NULL == CU_add_test(ps_queue, "test_frequency_saving", test_frequency_saving))
        {
            CU_cleanup_registry();
            return CU_get_error();
        }
        if(NULL == CU_add_test(ps_queue, "test_frequency_enqueue", test_frequency_enqueue))
        {
            CU_cleanup_registry();
            return CU_get_error();
        }

    // SECOND SUITE
        CU_pSuite ps_tree = NULL;

        ps_tree = CU_add_suite("test_tree", opening, closing);

        if(ps_tree == NULL)
        {
          CU_cleanup_registry();
          return CU_get_error();
        }

        //Adding test to the suite
        if (NULL == CU_add_test(ps_tree, "test_merge_nodes", test_merge_nodes))
        {
          CU_cleanup_registry();
          return CU_get_error();
        }
        if (NULL == CU_add_test(ps_tree, "test_tree", test_tree))
        {
          CU_cleanup_registry();
          return CU_get_error();
        }
        if (NULL == CU_add_test(ps_tree, "test_tree_size", test_tree_size))
        {
          CU_cleanup_registry();
          return CU_get_error();
        }
        if (NULL == CU_add_test(ps_tree, "test_preorder_tree", test_preorder_tree))
        {
          CU_cleanup_registry();
          return CU_get_error();
        }
    // THIRD SUITE
        CU_pSuite ps_hash = NULL;

        ps_hash = CU_add_suite("test_hash_table", opening, closing);

        if(ps_hash == NULL)
        {
          CU_cleanup_registry();
          return CU_get_error();
        }

        //Adding test to the suite
        
        if (NULL == CU_add_test(ps_hash, "test_huff_code", test_huff_code))
        {
          CU_cleanup_registry();
          return CU_get_error();
        }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   

   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
