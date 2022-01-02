#include <iostream>
using namespace std;
struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};
int minPathSum(TreeNode *root)
{
    if (root == NULL)
        return 0;
    int sum = root->data;
    int leftSum = INT_MAX;
    int rightSum = INT_MAX;
    if (root->right == NULL && root->left == NULL)
    {
        return sum;
    }
    else
    {

        if (root->left != NULL)
        {
            leftSum = minPathSum(root->left);
        }
        if (root->right != NULL)
        {
            rightSum = minPathSum(root->right);
        }
        if (leftSum < rightSum)
        {
            sum += leftSum;
        }
        else
        {
            sum += rightSum;
        }
    }

    return sum;
}

int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->right->right = new TreeNode(-1);

    cout << minPathSum(root);

    return 0;
}

