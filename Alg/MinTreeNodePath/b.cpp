#include <stdio.h>
#include <stack>
using namespace std;
 
typedef struct Node
{
	int value;
	int left_len;//左子树的最长距离
	int right_len;//右子树的最长距离
	struct Node *left;
	struct Node *right;
}Node,*pNode;
 
int max_len = 0;//二叉树节点的最大距离
 
void find_maxlen_recursion(pNode root)//防止节点被重复访问，采用后序遍历，从下到上依次计算每个子树的节点最长距离
{
	if(root==NULL)//遍历到叶子节点，返回
		return;
	if(root->left==NULL)//节点左子树为空，那么该节点左子树的最大距离为0
		root->left_len=0;
	if(root->right==NULL)//节点右子树为空，那么该节点右子树的最大距离为0
		root->right_len=0;
	if(root->left!=NULL)//如果左子树不为空，继续递归寻找左子树最长距离
		find_maxlen_recursion(root->left);
	if(root->right!=NULL)//如果右子树不为空，继续递归寻找右子树最长距离
		find_maxlen_recursion(root->right);
	if(root->left!=NULL)//计算左子树最长节点的距离
	{
		int temp;
		if(root->left->left_len > root->left->right_len)
		{
			temp = root->left->left_len;
		}
		else
		{
			temp = root->left->right_len;
		}
		root->left_len = temp + 1;
	}
	if(root->right!=NULL)//计算右子树最长节点的距离
	{
		int temp;
		if(root->right->left_len > root->right->right_len)
		{
			temp = root->right->left_len;
		}
		else
		{
			temp = root->right->right_len;
		}
		root->right_len = temp + 1;
	}
	if(max_len < root->left_len+root->right_len)//更新二叉树节点的最大距离
	{
		max_len = root->left_len + root->right_len;
	}
}
 
void find_maxlen(pNode root)//引用后续非递归模板即可，模板详见http://blog.csdn.net/xc889078/article/details/9194403
{
	stack<pNode> stack1;
	pNode curr = NULL;
	pNode pre = NULL;
	stack1.push(root);
	while(!stack1.empty())
	{
		curr = stack1.top();
		if((curr->left==NULL && curr->right==NULL) ||
			(pre!=NULL && (pre==curr->left || pre==curr->right)))
		{
			if(curr->left==NULL)
				curr->left_len=0;
			if(curr->right==NULL)
				curr->right_len=0;
			if(curr->left!=NULL)
			{
				int temp = curr->left->left_len < curr->left->right_len ? curr->left->left_len : curr->left->right_len;
				curr->left_len = temp + 1;
			}
			if(curr->right!=NULL)
			{
				int temp = curr->right->left_len < curr->right->right_len ? curr->right->left_len : curr->right->right_len;
				curr->right_len = temp + 1;
			}
			if(max_len < curr->left_len + curr->right_len)
			{
				max_len = curr->left_len + curr->right_len;
			}
			stack1.pop();
			pre = curr;
		}
		else
		{
			if(curr->right!=NULL)
				stack1.push(curr->right);
			if(curr->left!=NULL)
				stack1.push(curr->left);
		}
	}
}
 
void inorder_traversal(pNode root)//中序遍历打印
{
	if(root==NULL)
		return;
	if(root->left!=NULL)
		inorder_traversal(root->left);
	printf("%d\t",root->value);
	if(root->right!=NULL)
		inorder_traversal(root->right);
}
 
void postorder_traversal(pNode root)//后续遍历打印
{
	if(root==NULL)
		return;
	if(root->left!=NULL)
		postorder_traversal(root->left);
	if(root->right!=NULL)
		postorder_traversal(root->right);
	printf("%d\t",root->value);
}
 
pNode init()//创建节点
{
	pNode node[10];
	int i;
	for(i=0;i<10;i++)
	{
		node[i] = (pNode)malloc(sizeof(Node));
		node[i]->value = i;
		node[i]->left_len = 0;
		node[i]->right_len = 0;
		node[i]->left = NULL;
		node[i]->right = NULL;
	}
	for(i=0;i<=2;i++)
	{
		node[i]->left = node[2*i+1];
		node[i]->right = node[2*i+2];
	}
	node[3]->left = node[7];
	node[5]->right = node[8];
	node[7]->right = node[9];
	return node[0];
}
 
int main()
{
	pNode root_recursion = init();
	pNode root = init();
	printf("中序遍历:\n");
	inorder_traversal(root);
	printf("\n");
	printf("后续遍历:\n");
	postorder_traversal(root);
	printf("\n");
	find_maxlen_recursion(root_recursion);
	printf("二叉树中节点的最大距离为(递归):\n%d\n",max_len);
	max_len=0;
	find_maxlen(root);
	printf("二叉树中节点的最大距离为(非递归):\n%d\n",max_len);
	return 0;
}
