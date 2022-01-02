#include<iostream>
#include<stdio.h>
using namespace std;
#define MaxSize 100
typedef char ElemType;
typedef struct node
{
    ElemType data;//数据类型
    struct node *lchild;//指向左孩子
    struct node *rchild;//指向右孩子
}BTNode;
void CreateBTNode(BTNode *&b,char *str)//由str串创建二叉链
{
    BTNode *St[MaxSize],*p=NULL;
    int top=-1,k,j=0;
    char ch;
    b=NULL;//建立二叉链初始时为空
    ch=str[j];
    while(ch!='\0')//str未扫描完时循环
    {
        switch(ch)
        {
        case'(':top++;St[top]=p;k=1;break;//为左结点
        case')':top--;break;
        case',':k=2;break;//为右结点
        default:p=(BTNode *)malloc(sizeof(BTNode));
            p->data=ch;
            p->lchild=p->rchild=NULL;
            if(b==NULL)//p指向二叉树的根结点
                b=p;
            else//已建立二叉树根结点
            {
                switch(k)
                {
                case 1:St[top]->lchild=p;break;
                case 2:St[top]->rchild=p;break;
                }
            }
        }
        j++;
        ch=str[j];
    }
}
void DispBTNode(BTNode *b)//以括号表示法输出二叉树
{
    if(b!=NULL)
    {
        printf(" %c",b->data);
        if(b->lchild!=NULL||b->rchild!=NULL)
        {
            printf("(");
            DispBTNode(b->lchild);
            if(b->rchild!=NULL) printf(",");
            DispBTNode(b->rchild);
            printf(")");
        }
    }
}
void PerOrder(BTNode *b)//先序遍历的递归算法
{
    if(b!=NULL)
    {

        printf(" %c ",b->data);//访问根结点
        PerOrder(b->lchild);//递归访问左子树
        PerOrder(b->rchild);//递归访问右子树
    }
}
void PerOrder1(BTNode *b)//先序遍历的非递归算法
{
    BTNode *St[MaxSize],*p;
    int top=-1;
    if(b!=NULL)
    {
        top++;//根结点入栈
        St[top]=b;
        while(top>-1)//桟不为空时循环
        {
            p=St[top];//退桟并访问该结点
            top--;
            printf(" %c ",p->data);
            if(p->rchild!=NULL)//右孩子入桟
            {
                top++;
                St[top]=p->rchild;
            }
            if(p->lchild!=NULL)//左孩子入桟
            {
                top++;
                St[top]=p->lchild;
            }
        }
        printf("\n");
    }
}
void InOrder(BTNode *b)//中序遍历的递归算法
{
    if(b!=NULL)
    {
        InOrder(b->lchild);//递归访问左子树
        printf(" %c ",b->data);//访问根结点
        InOrder(b->rchild);//递归访问右子树
    }
}
void InOrder1(BTNode *b)//中序遍历的非递归算法
{
    BTNode *St[MaxSize],*p;
    int top=-1;
    if(b!=NULL)
    {
        p=b;
        while(top>-1||p!=NULL)
        {
            while(p!=NULL)
            {
                top++;
                St[top]=p;
                p=p->lchild;
            }
            if(top>-1)
            {
                p=St[top];
                top--;
                printf(" %c ",p->data);
                p=p->rchild;
            }
        }
        printf("\n");
    }
}
void PostOrder(BTNode *b)//后序遍历的递归算法
{
    if(b!=NULL)
    {
        PostOrder(b->lchild);//递归访问左子树
        PostOrder(b->rchild);//递归访问右子树
        printf(" %c ",b->data);//访问根结点
    }
}
void PostOrder1(BTNode *b)//后序遍历的非递归算法
{
    BTNode *St[MaxSize],*p;
    int flag,top=-1;//桟指针初值
    if(b!=NULL)
    {
        do
        {
            while(b!=NULL)//将b的所有左结点入桟
            {
                top++;
                St[top]=b;
                b=b->lchild;
            }
            p=NULL;//p指向当前结点的前一个访问的结点
            flag=1;//设置b的访问标记为已访问过
            while(top!=-1&&flag)
            {
                b=St[top];//取出当前的桟顶元素
                if(b->rchild==p)//右子树不存在或已被访问,访问之
                {
                    printf(" %c ",b->data);//访问*b结点
                    top--;
                    p=b;//p指向刚被访问的结点
                }
                else
                {
                    b=b->rchild;//指向右子树
                    flag=0;//设置未被访问的标记
                }
            }
        }while(top!=-1);
        printf("\n");
    }
}
void TravLevel(BTNode *b)//层次遍历
{
    BTNode *Qu[MaxSize];//定义顺序循环队列
    int front,rear;//定义队首和队尾指针
    front=rear=0;//置队列为空队列
    if(b!=NULL)
        printf(" %c ",b->data);
    rear++;//结点指针进入队列
    Qu[rear]=b;
    while(rear!=front)//队列不为空
    {
        front=(front+1)%MaxSize;
        b=Qu[front];
        if(b->lchild!=NULL)//队头出队列
        {
            printf(" %c ",b->lchild->data);//输出左孩子，并入队列
            rear=(rear+1)%MaxSize;
            Qu[rear]=b->lchild;
        }
        if(b->rchild!=NULL)//输出右孩子，并入队列
        {
            printf(" %c ",b->rchild->data);
            rear=(rear+1)%MaxSize;
            Qu[rear]=b->rchild;
        }
    }
    printf("\n");
}
int main()
{
    BTNode *b;
    CreateBTNode(b,"A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
    printf(" 二叉树 b:");DispBTNode(b);printf("\n\n");
    printf(" 层次遍历序列:");
    TravLevel(b);
    printf("\n");
    printf(" 先序遍历序列:\n");
    printf("     递归算法:");PerOrder(b);printf("\n");
    printf("   非递归算法:");PerOrder1(b);printf("\n");
    printf(" 中序遍历序列:\n");
    printf("     递归算法:");InOrder(b);printf("\n");
    printf("   非递归算法:");InOrder1(b);printf("\n");
    printf(" 后序遍历序列:\n");
    printf("     递归算法:");PostOrder(b);printf("\n");
    printf("   非递归算法:");PostOrder1(b);printf("\n");

}
