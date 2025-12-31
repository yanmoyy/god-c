struct tnode {
    char *word;          /* points to the next */
    int count;           /* number of occurrences */
    struct tnode *left;  /* left child */
    struct tnode *right; /* right child */
};
