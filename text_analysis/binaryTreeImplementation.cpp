/************************************************************************/
/*                                                                      */
/* Interface file for a BINARY_TREE ADT                                 */
/*                                                                      */
/* Refer to lecture notes for details.                                  */
/*                                                                      */
/* David Vernon                                                         */
/* 5/3/2017 Added function to initialize the tree                       */
/*                                                                      */
/************************************************************************/

#include "binaryTree.h"

/*** initialize a tree ***/

void initialize(BINARY_TREE_TYPE *tree)
{

	static bool first_call = true;

	/* we don't know what value *tree has when the program is launched      */
	/* so we have to be careful not to dereference it                       */
	/* if it's the first call to initialize, there is no tree to be deleted */
	/* and we just set *tree to NULL                                        */

	if (first_call)
	{
		first_call = false;
		*tree = NULL;
	}
	else
	{
		if (*tree != NULL) postorder_delete_nodes(*tree);
		*tree = NULL;
	}
}


/*** insert an element in a tree ***/

BINARY_TREE_TYPE *insert(ELEMENT_TYPE e, BINARY_TREE_TYPE *tree)
{

	WINDOW_TYPE temp;

	if (*tree == NULL)
	{

		/* we are at an external node: create a new node and insert it */

		if ((temp = (NODE_TYPE)malloc(sizeof(NODE))) == NULL)
			error("function insert: unable to allocate memory");
		else
		{
			temp->element = e;
			temp->left = NULL;
			temp->right = NULL;
			*tree = temp;
		}
	}
	else if (strcmp(e.word, (*tree)->element.word) == -1)

	{ /* assume the string/word field is the key */
		insert(e, &((*tree)->left));
	}
	else if (strcmp(e.word, (*tree)->element.word) == 1)
	{
		insert(e, &((*tree)->right));
		
	}

	/* if e.word == (*tree)->element.word, e already is in the tree so add the frequency  */

	else if (strcmp(e.word, (*tree)->element.word) == 0)
	{
		(*tree)->element.frequency++;
	}

	return(tree);
}


/*** returns & deletes the smallest node in a tree (i.e. the left-most node) */

ELEMENT_TYPE delete_min(BINARY_TREE_TYPE *tree)
{

	ELEMENT_TYPE e;
	BINARY_TREE_TYPE p;

	if ((*tree)->left == NULL)
	{

		/* tree points to the smallest element */

		e = (*tree)->element;

		/* replace the node pointed to by tree by its right child */

		p = *tree;
		*tree = (*tree)->right;
		free(p);

		return(e);
	}
	else
	{

		/* the node pointed to by tree has a left child */

		return(delete_min(&((*tree)->left)));
	}

}

/*** delete an element in a tree ***/

BINARY_TREE_TYPE *delete_element(ELEMENT_TYPE e, BINARY_TREE_TYPE *tree)
{

	BINARY_TREE_TYPE p;

	if (*tree != NULL)
	{

		if (e.frequency < (*tree)->element.frequency)  /* assume element.number is the */
			delete_element(e, &((*tree)->left));          /* key                          */

		else if (e.frequency > (*tree)->element.frequency)
			delete_element(e, &((*tree)->right));

		else if (((*tree)->left == NULL) && ((*tree)->right == NULL))
		{

			/* leaf node containing e - delete it */

			p = *tree;
			free(p);
			*tree = NULL;
		}
		else if ((*tree)->left == NULL)
		{

			/* internal node containing e and it has only a right child */
			/* delete it and make treepoint to the right child          */

			p = *tree;
			*tree = (*tree)->right;
			free(p);
		}
		else if ((*tree)->right == NULL)
		{

			/* internal node containing e and it has only a left child */
			/* delete it and make treepoint to the left child          */

			p = *tree;
			*tree = (*tree)->left;
			free(p);
		}
		else
		{

			/* internal node containing e and it has both left and right child */
			/* replace it with leftmost node of right sub-tree                 */
			(*tree)->element = delete_min(&((*tree)->right));
		}
	}
	return(tree);
}


/*** inorder traversal of a tree, printing node elements **/

int inorder(BINARY_TREE_TYPE tree, int n)
{

	int i;

	if (tree != NULL)
	{
		inorder(tree->right, n + 1);

		for (i = 0; i < n; i++) printf("        ");
		printf("%s %d\n", tree->element.word, tree->element.frequency);

		inorder(tree->left, n + 1);
	}
	return(0);
}



/*** inorder traversal of a tree, deleting node elements **/

int postorder_delete_nodes(BINARY_TREE_TYPE tree)
{

	if (tree != NULL)
	{
		postorder_delete_nodes(tree->left);
		postorder_delete_nodes(tree->right);
		free(tree);
	}
	return(0);
}



/*** print all elements in a tree by traversing inorder ***/

int print(BINARY_TREE_TYPE tree)
{

	printf("Contents of tree by inorder traversal: \n");

	inorder(tree, 0);

	printf("--- \n");

	return(0);
}


/*** error handler:
	 print message passed as argument and take appropriate action ***/

int error(char *s)
{

	printf("Error: %s\n", s);

	exit(0);
}

/*** assign values to an element ***/

int assign_element_values(ELEMENT_TYPE *e, int number, char s[])
{

	e->word = (char *)malloc(sizeof(char) * (strlen(s) + 1));
	strcpy(e->word, s);
	e->frequency = number;
	return(0);
}

