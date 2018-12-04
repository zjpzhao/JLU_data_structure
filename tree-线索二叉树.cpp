#include <stdio.h>
#include <stdlib.h>

#define ERROR  0
#define OK  1

typedef enum{Link, Thread} PointerTag;      //link = 0表示指向左右孩子指针
                                            //Thread = 1表示指向前驱或后继的线索
typedef struct BitNode
{
    char data;                              //结点数据
    struct BitNode *lchild;                 //左右孩子指针
    struct BitNode *rchild;
    PointerTag ltag;                        //左右标志
    PointerTag rtag;
}BitNode, *BiTree;

BiTree pre;                                 //全局变量，始终指向刚刚访问过的结点

//前序创建二叉树
void CreateTree(BiTree *t)
{
    char ch;
    scanf("%c", &ch);

    if(ch == '#')
    {
        *t = NULL;
    }
    else
    {
        (*t) = (BiTree)malloc(sizeof(BitNode));
        if((*t) == NULL)
        {
            return;
        }
        (*t)->data = ch;
        CreateTree(&((*t)->lchild));
        CreateTree(&((*t)->rchild));
    }
}


//t指向头结点，头结点左链lchild指向根结点，头结点右链rchild指向中序遍历的最后一个结点。
//中序遍历二叉线索树表示的二叉树t
int InOrderThraverse_Thr(BiTree t)
{
    BiTree p;
    p = t->lchild;           //p指向根结点
    while(p != t)
    {
        while(p->ltag == Link)   //当ltag = 0时循环到中序序列的第一个结点
        {
            p = p->lchild;
        }
        printf("%c ", p->data);  //显示结点数据，可以更改为其他对结点的操作
        while(p->rtag == Thread && p->rchild != t)
        {
            p = p->rchild;
            printf("%c ", p->data);
        }

        p = p->rchild;           //p进入其右子树
    }

    return OK;
}

//中序遍历进行中序线索化
void InThreading(BiTree p)
{
    if(p)
    {
        InThreading(p->lchild);              //递归左子树线索化
        if(!p->lchild)                       //没有左孩子
        {
            p->ltag = Thread;                //前驱线索
            p->lchild = pre;             //左孩子指针指向前驱,这里是第3步
        }
        if(!pre->rchild)                 //没有右孩子
        {
            pre->rtag = Thread;              //后继线索
            pre->rchild = p;             //前驱右孩子指针指向后继(当前结点p)
        }
        pre = p;

        InThreading(p->rchild);              //递归右子树线索化
    }
}
//建立头结点，中序线索二叉树
int InOrderThread_Head(BiTree *h, BiTree t)
{
    (*h) = (BiTree)malloc(sizeof(BitNode));
    if((*h) == NULL)
    {
        return ERROR;
    }

    (*h)->rchild = *h;
    (*h)->rtag = Link;

    if(!t)      //如果为NULL
    {
        (*h)->lchild = *h;
        (*h)->ltag = Link;
    }
    else
    {
        pre = *h;
        (*h)->lchild = t;        //第一步
        (*h)->ltag = Link;
        InThreading(t);         //找到最后一个结点
        pre->rchild = *h;        //第四步
        pre->rtag = Thread;
        (*h)->rchild = pre;      //第二步
    }
}

int main()
{
    BiTree t;
    BiTree temp;

    printf("请输入前序二叉树的内容:\n");
    CreateTree(&t);                 //建立二叉树
    InOrderThread_Head(&temp, t);       //加入头结点，并线索化
    printf("输出中序二叉树的内容:\n");
    InOrderThraverse_Thr(temp);

    printf("\n");
    return 0;
}
