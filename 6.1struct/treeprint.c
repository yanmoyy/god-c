#include "tnode.c"
#include <stdio.h>
#include <string.h>

/* treeprint: in-order print of tree p */
void treeprint(struct tnode* p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}
