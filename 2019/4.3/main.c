#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int field;           // поле данных
    struct tnode *left;  // левый потомок
    struct tnode *right; // правый потомок
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
    if (tree != NULL) { //Пока не встретится пустой узел
        printf("%d\n", tree->field); //Отображаем корень дерева
        treeprint(tree->left); //Рекурсивная функция для левого поддерева
        treeprint(tree->right); //Рекурсивная функция для правого поддерева
    }
}

struct tnode * addnode(int x, struct tnode *tree) {
    if (tree == NULL) { // Если дерева нет, то формируем корень
        tree = (struct tnode *) malloc (sizeof(struct tnode)); // память под узел
        tree->field = x;   // поле данных
        tree->left =  NULL;
        tree->right = NULL; // ветви инициализируем пустотой
    }else  if (x < tree->field)   // условие добавление левого потомка
        tree->left = addnode(x,tree->left);
    else    // условие добавление правого потомка
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
