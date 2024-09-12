//说实话这应该是目前以来最难理解最难实现的一个代码了。
//这是一个平衡排序二叉树的插入算法，就目前而言我自己不能独立解决这个问题
//平衡二叉树，是一种二叉排序树，其中每个结点的左子树和右子树的高度差至多等于1。它是一种高度平衡的二叉排序树。现二叉平衡树结点定义如下：
typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
    struct node *parent;
    int height;
} node_t;
请实现平衡二叉树的插入算法：

//向根为 root 的平衡二叉树插入新元素 val，成功后返回新平衡二叉树根结点
node_t *avl_insert(node_t *root, int val);


#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

//S首先要获取结点高度来判断二叉树能否平衡
int get_height(node_t* node)
{
    if(node==0)
    {
        return 0;
    }
    return node->height;
}

//计算平衡因子，即该节点的左右子树的高度差
int get_balance_factor(node_t *node)
{
    if (node==NULL)
    {
        /* code */
        return 0;//最为严谨的地方，每次遇到这种情况都需要去检查一下是否合理
    }
    return get_height(node->left)-get_height(node->right);    
}

//更新节点高度，当使用左旋或者右旋的时候，新的根节点的高度可能会发生改变
void update_height(node_t* node)
{
    int left_height=get_height(node->left);
    int right_height=get_height(node->right);
    //节点高度为左右子树的最大高度加一
    node->height= (left_height > right_height ? left_height : right_height) + 1;
    //比较函数 a>b?a:b
}
//创建新节点
node_t* creat_node(int val) 
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    //此处个人认为应该添加检查分配成功的问题，但是有点不想写
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    new_node->height = 1;//此处是为了后续更新结点高度用
    return new_node;
}

//重头戏
//左旋操作（RR型）将根节点的右子节点作为中心结点进行左旋
//这个版本写的其实不是很详细，关于新的根节点的parent是什么样的并没有明说
node_t *left_rotate(node_t* root)
{
   node_t* pivot=root->right;//新的根结点
   node_t* subtree=pivot->left;//新的根节点的左子树成为旧结点的右子树
   //左旋
   pivot->right=root;
   root->right=subtree;
   //更新高度
   update_height(root);
    update_height(pivot);

    // 返回旋转后的根节点
    return pivot;
}
/*plus
public AVLNode leftRotate(AVLNode root) {
        AVLNode oldRoot = root;
        AVLNode newRoot = root.right;
        AVLNode parent = root.parent;
        //1.newRoot 替换 oldRoot 位置
        if (null != parent ) {
            if (oldRoot.parent.data > oldRoot.data) {
                parent.left = newRoot;
            }else  {
                parent.right = newRoot;
            }
        }
        newRoot.parent = parent;
        //2.重新组装 oldRoot (将 newRoot 的左子树 给 oldRoot 的右子树)
        oldRoot.right = newRoot.left;
        if (newRoot.left != null) {
            newRoot.left.parent = oldRoot;
        }
        //3. oldRoot 为 newRoot 的左子树
        newRoot.left = oldRoot;
        oldRoot.parent = newRoot;
        //刷新高度
        oldRoot.height = calcHeight(oldRoot);
        newRoot.height = calcHeight(newRoot);
        return newRoot;
    }


    public AVLNode rightRotate(AVLNode root) {
        AVLNode oldRoot = root;
        AVLNode newRoot = root.left;
        AVLNode parent = root.parent;
        //1.newRoot 替换 oldRoot 位置
        if (null != parent ) {
            if (oldRoot.parent.data > oldRoot.data) {
                parent.left = newRoot;
            }else {
                parent.right = newRoot;
            }
        }
        newRoot.parent = parent;
        //2.重新组装 oldRoot (将 newRoot 的右子树 给 oldRoot 的左子树)
        oldRoot.left = newRoot.right;
        if (newRoot.right != null) {
            newRoot.right.parent = oldRoot;
        }
        //3. oldRoot 为 newRoot 的左子树
        newRoot.right = oldRoot;
        oldRoot.parent = newRoot;
        //刷新高度
        oldRoot.height = calcHeight(oldRoot);
        newRoot.height = calcHeight(newRoot);
        return newRoot;
    }
*/
//右旋
node_t* right_rotate(node_t* root)
{
    node_t *pivot=root->left;
    node_t *subtree=pivot->left;

    pivot->right=root;
    pivot->left=subtree;

     // 更新节点的高度
    update_height(root);
    update_height(pivot);

    // 返回旋转后的根节点
    return pivot; 
}

//插入节点
node_t* avl_insert(node_t *root,int val)
{
    //这是一个递归公式
    if(root==NULL)
    {
        return creat_node(val);//一定会递归到此处然后插入结点
    }
    if(val<root->val)
    {
        //插入左子树，这是排序二叉树的性质
        root->left=avl_insert(root->left,val);
        root->right->parent=root;//不懂
    }
    else if(val > root->val)
    {
        /* code */
        // 递归进入右子树
        root->right = avl_insert(root->right, val);
        root->right->parent = root;
    }
    else
        return root;
    
    //更新结点的高度
    update_heighet(root);
    //检查节点的平衡因子
    int balance=get_height(root);
    // 平衡树
    // 左-左情况：插入节点在左子树的左子树中
    if (balance > 1 && val < root->left->val)
        return right_rotate(root);

    // 右-右情况：插入节点在右子树的右子树中
    if (balance < -1 && val > root->right->val)
        return left_rotate(root);

    // 左-右情况：插入节点在左子树的右子树中
    if (balance > 1 && val > root->left->val) {
        // 先对左子树进行左旋操作，再对根节点进行右旋操作
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // 右-左情况：插入节点在右子树的左子树中
    if (balance < -1 && val < root->right->val) {
        // 先对右子树进行右旋操作，再对根节点进行左旋操作
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    // 如果树已经平衡，直接返回根节点
    return root;

}