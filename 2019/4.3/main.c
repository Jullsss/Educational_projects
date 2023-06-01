#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int field;           // ���� ������
    struct tnode *left;  // ����� �������
    struct tnode *right; // ������ �������
};

int size(struct tnode* temp)
{
    if (temp == NULL) {
        return (0);
    } else {
        return (size (temp -> left) + 1 + size (temp -> right));
    }
}

void treeprint(struct tnode *tree) {
    if (tree != NULL) { //���� �� ���������� ������ ����
        printf("%d\n", tree->field); //���������� ������ ������
        treeprint(tree->left); //����������� ������� ��� ������ ���������
        treeprint(tree->right); //����������� ������� ��� ������� ���������
    }
}

struct tnode * addnode(int x, struct tnode *tree) {
    if (tree == NULL) { // ���� ������ ���, �� ��������� ������
        tree = (struct tnode *) malloc (sizeof(struct tnode)); // ������ ��� ����
        tree->field = x;   // ���� ������
        tree->left =  NULL;
        tree->right = NULL; // ����� �������������� ��������
    }else  if (x < tree->field)   // ������� ���������� ������ �������
        tree->left = addnode(x,tree->left);
    else    // ������� ���������� ������� �������
        tree->right = addnode(x,tree->right);
    return(tree);
}

void freemem(struct tnode *tree) {
    if (tree != NULL) {
        freemem(tree->left);
        freemem(tree->right);
        free(tree);
    }
}

int main(void)
{

    return 0;
}
