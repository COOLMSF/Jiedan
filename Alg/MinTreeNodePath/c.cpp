#include<iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Node {
    public:
    int data;
    Node* left;
    Node* right;
    Node(int d) {
        data = d;
        left = NULL;
        right = NULL;
    }
};

class Pair {
    public:
    Node* node;
    int child;
    Pair(Node* n, int i) {
        node = n;
        child = i;
    }
};

void display(Node* root) {
    if(root == NULL) return;
    
    if(root->left !=NULL) {
        cout << root->left->data;
    } else {
        cout << ".";
    }
    cout << "<-" << root->data<< "->";
    if(root->right != NULL) {
        cout <<root->right->data;
    } else {
        cout << ".";
    }
    cout << endl;

    display(root->left);
    display(root->right);
}

void sizeHeightMaxSum(Node* root, int depth, int& size, int& height, int& max, int& sum) {
    if(root == NULL) return;
    size++;
    if(root->data > max) max = root->data;
    if(depth > height) height = depth;
    sum += root->data;
    sizeHeightMaxSum(root->left, depth + 1, size, height, max, sum);
    sizeHeightMaxSum(root->right, depth + 1, size, height, max, sum);
}

void traverse(Node* root) {
    if(root == NULL) return;
    cout << root->data << " in preorder" << endl;
    traverse(root->left);
    cout << root->data << " in inorder" << endl;
    traverse(root->right);
    cout << root->data << " in postorder" << endl;
}

void levelOrder1(Node* root) {
    queue<Node*> q;
    queue<Node*> hq;
    q.push(root);
    while(!q.empty()) {
        Node* node = q.front();
        q.pop();
        cout << node->data << " ";
        if(node->left) {
            hq.push(node->left);
        }
        if(node->right) {
            hq.push(node->right);
        }
        if(q.empty()) {
            cout << endl;
            q = hq; //copying will take some time 
            hq = queue<Node*>();
        }
    }
}

void levelOrder2(Node* root) {
    queue<Node*> q;
    q.push(root);
    while(!q.empty()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            Node* node = q.front();
            q.pop();
            cout << node->data << " ";
            if(node->left) {
                q.push(node->left);
            }
            if(node->right) {
                q.push(node->right);
            }
        }
        cout << endl;
    }
}

void levelOrder3(Node* root) {
    queue<Node*> q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()) {
        Node* node = q.front();
        q.pop();
        if(node == NULL) {
            cout << endl;
            if(q.empty()) {
                break;
            }
            q.push(NULL);
            continue;
        }
        cout << node->data << " ";
        if(node->left) {
            q.push(node->left);
        }
        if(node->right) {
            q.push(node->right);
        }
    }
}

class PairNodeState {
    public:
    Node* node;
    int state;
    PairNodeState(Node* n, int s) {
        node = n;
        state = s;
    }
};

void traversalIterative(Node* root) {
    stack<PairNodeState> st;
    st.push(PairNodeState(root, 1));
    while(!st.empty()) {
        PairNodeState &p = st.top();
        if(p.state == 1) { // pre, s++, left
            cout << p.node->data << " in Preoder" << endl;
            p.state++;
            if(p.node->left) {
                st.push(PairNodeState(p.node->left, 1));
            }
        } else if(p.state == 2) { // in, s++, right
            cout << p.node->data << " in inorder" << endl;
            p.state++;
            if(p.node->right) {
                st.push(PairNodeState(p.node->right, 1));
            }
        } else if(p.state == 3){ // post, pop
            cout << p.node->data << " in Postorder" << endl;
            st.pop();
        }
    }
}

vector<int> nodeToRoot(Node* root, int val) {
    if(root == NULL) {
        return vector<int>();
    }
    if(root->data == val) {
        return vector<int>(1, val);
    }
    if(root->left) {
        vector<int> ntrLeft = nodeToRoot(root->left, val);
        if(!ntrLeft.empty()) {
            ntrLeft.push_back(root->data);
            return ntrLeft;
        }
    }
    if(root->right) {
        vector<int> ntrRight = nodeToRoot(root->right, val);
        if(!ntrRight.empty()) {
            ntrRight.push_back(root->data);
            return ntrRight;
        }
    }
    return vector<int>();
}

void printLevelK(Node* root, int k) {
    if(root == NULL || k < 0) return;
    if(k == 0) {
        cout << root->data << " ";
    }
    printLevelK(root->left, k-1);
    printLevelK(root->right, k-1);
}

vector<Node*> nodeToRootNodes(Node* root, int val) {
    if(root == NULL) {
        return vector<Node*>();
    }
    if(root->data == val) {
        return vector<Node*>(1, root);
    }
    if(root->left) {
        vector<Node*> ntrLeft = nodeToRootNodes(root->left, val);
        if(!ntrLeft.empty()) {
            ntrLeft.push_back(root);
            return ntrLeft;
        }
    }
    if(root->right) {
        vector<Node*> ntrRight = nodeToRootNodes(root->right, val);
        if(!ntrRight.empty()) {
            ntrRight.push_back(root);
            return ntrRight;
        }
    }
    return vector<Node*>();
}
void printLevelK2(Node* root, int k, Node* node) {
    if(root == NULL || k < 0 || root == node) return;
    if(k == 0) {
        cout << root->data << " ";
    }
    printLevelK2(root->left, k-1, node);
    printLevelK2(root->right, k-1, node);
}

void pritnNodesKDistanceAway(Node* root, int val, int k) {
    vector<Node*> ntr = nodeToRootNodes(root, val);
    for(int i = 0; i < ntr.size() && k >=0; i++,k--) {
        printLevelK2(ntr[i], k, (i == 0) ? NULL : ntr[i-1]);
    }
}

void printPathbetwenLowAndHigh(Node* root, string psf, int sum, int& low, int& high) {
    if(root == NULL) return;
    if(!root->left && !root->right) {
        sum += root->data;
        if(sum < high && sum > low) {
            cout << psf + " " +to_string(root->data)  << endl;
        }
        return;
    }
    printPathbetwenLowAndHigh(root->left, psf + " " +to_string(root->data), sum + root->data, low, high);
    printPathbetwenLowAndHigh(root->right, psf + " " +to_string(root->data), sum + root->data, low, high);
}

void leftCloneTree(Node* root) {
    if(root == NULL) return;
    leftCloneTree(root->left);
    leftCloneTree(root->right);

    Node* node = new Node(root->data);
    node->left = root->left;
    node->right = NULL;
    root->left = node;
}

void revertLeftClone(Node* root) {
    if(root == NULL) return;
    revertLeftClone(root->left->left);
    revertLeftClone(root->right);

    Node* toRemove = root->left;
    root->left = toRemove->left;
    delete toRemove;
}

void pritnSingleChildParent(Node* root) {
    if(root == NULL) return;
    if(!root->left && root->right) {
        cout << root->data << " ";
    } else if(root->left && !root->right) {
        cout << root->data << " ";
    }
    pritnSingleChildParent(root->left);
    pritnSingleChildParent(root->right);
}

Node* removeLeafs(Node* root) {
    if(root == NULL) return root;
    if(!root->left && !root->right) {
        delete root;
        return NULL;
    }
    root->left = removeLeafs(root->left);
    root->right = removeLeafs(root->right);
    return root;
}

int heightTree(Node* root) {
    if(root == NULL) return -1; // becoz null is one edge below than baseline
    return max(heightTree(root->left), heightTree(root->right)) + 1;
}

//bad approach
int diameter1(Node* root) {
    if(root == NULL) return 0;
    int ld = diameter1(root->left);
    int rd = diameter1(root->right);
    int cd = heightTree(root->left) + heightTree(root->right) + 2;
    return max(max(ld,rd), cd);
}
//good approach1
class PairHtDia {
    public:
    int ht;
    int dia;
};
PairHtDia diameter2(Node* root) {
    if(root == NULL) {
        PairHtDia mp;
        mp.dia = -2;
        mp.ht = -1;
        return mp;
    }
    PairHtDia lp = diameter2(root->left);
    PairHtDia rp = diameter2(root->right);
    PairHtDia mp;
    int dia = lp.ht + rp.ht + 2;
    mp.dia = max(max(lp.dia, rp.dia), dia);
    mp.ht = max(lp.ht, rp.ht) + 1;
    return mp;
}
//good approach2
int diameterAndReturnheight(Node* root, int& dia) {
    if(root == NULL) return -1;
    int lh = diameterAndReturnheight(root->left, dia);
    int rh = diameterAndReturnheight(root->right, dia);
    if(dia < lh + rh + 2) {
        dia = lh + rh + 2;
    }
    return max(lh, rh) + 1;
}

int tiltOfBinaryTreeReturnSum(Node* root, int& tilt) {
    if(root == NULL) return 0;
    int ls = tiltOfBinaryTreeReturnSum(root->left, tilt);
    int rs = tiltOfBinaryTreeReturnSum(root->right, tilt);
    int t = abs(ls-rs);
    tilt += t;
    return ls + rs + root->data;
}  
//we can solve this question also by inorder traversal as it should always be increasing
//we add a possible range for every node.
bool isBinarySearchTree(Node* root, int min, int max) {
    if(root == NULL) return true;
    if(root->data < min || root->data > max) {
        return false;
    }
    //the left node should lie in range (min, root->data)
    int lbst = isBinarySearchTree(root->left, min, root->data);
    //the right node should lie in range (root->data, max)
    int rbst = isBinarySearchTree(root->right, root->data, max);
    if(lbst && rbst) {
        return true;
    } else {
        return false;
    }
}
//we also Solve this while we are returning the max and min from bottom subtree
class PairBst {
    public:
    bool isBST;
    int min;
    int max;
};

PairBst isBinarySearchTree(Node* root) {
    if(root == NULL) {
        PairBst mp;
        mp.isBST = true;
        mp.min = INT_MAX;
        mp.max = INT_MIN;
        return mp;
    }
    PairBst lp = isBinarySearchTree(root->left);
    PairBst rp = isBinarySearchTree(root->right);
    PairBst mp;
    mp.isBST = lp.isBST && rp.isBST && (root->data > lp.max && root->data < rp.min);
    mp.min = min(root->data, min(lp.min,rp.min));
    mp.max = max(root->data, max(lp.max,rp.max));
    return mp;
}

int isbalancedTreeReturnHeight(Node* root, bool& isBal) {
    if(root == NULL) return -1;
    int lh = isbalancedTreeReturnHeight(root->left, isBal);
    int rh = isbalancedTreeReturnHeight(root->right, isBal);
    if(abs(lh - rh) > 1) {
        isBal = false;
    }
    return lh + rh + 2;
}
class PairLargestBst {
    public:
    bool isBST;
    int size;
    int max;
    int min;
};

PairLargestBst largestBst(Node* root, int& sizeBST, Node*& nodeBST) {
    if(root == NULL) {
        PairLargestBst mp;
        mp.isBST = true;
        mp.size = 0;
        mp.max = INT_MIN;
        mp.min = INT_MAX;
        return mp;
    }
    PairLargestBst lp = largestBst(root->left, sizeBST, nodeBST);
    PairLargestBst rp = largestBst(root->right, sizeBST, nodeBST);
    PairLargestBst mp;
    mp.isBST = lp.isBST && rp.isBST && (root->data > lp.max && root->data < rp.min);
    mp.min = min(root->data, min(lp.min,rp.min));
    mp.max = max(root->data, max(lp.max,rp.max));
    mp.size = lp.size + rp.size + 1;
    if(mp.isBST) {
        if(mp.size > sizeBST) {
             sizeBST = mp.size;
             nodeBST = root;
        }
    }
    return mp;
}

class PairLargestBST {
    public:
    bool isBST;
    int sizeBST;
    Node* nodeBST;
    int max;
    int min;
};

//using no static var
PairLargestBST largestBst(Node* root) {
    if(root == NULL) {
        PairLargestBST mp;
        mp.isBST = true;
        mp.sizeBST = 0;
        mp.nodeBST = NULL;
        mp.max = INT_MIN;
        mp.min = INT_MAX;
        return mp;
    }
    PairLargestBST lp = largestBst(root->left); //mereko pair lakar do left se
    PairLargestBST rp = largestBst(root->right); //aur right se
    PairLargestBST mp;
    //process pairs
    mp.isBST = lp.isBST && rp.isBST && (root->data > lp.max && root->data < rp.min);
    mp.min = min(root->data, min(lp.min,rp.min));
    mp.max = max(root->data, max(lp.max,rp.max));
    if(mp.isBST) { //agar bst hai toh update bstsize and nodes 
        mp.nodeBST = root;
        mp.sizeBST = lp.sizeBST + rp.sizeBST + 1;
    } else if(lp.sizeBST > rp.sizeBST) { //else purana vala ko hi age bhej do jo bda ha left ya right mai
        mp.nodeBST = lp.nodeBST;
        mp.sizeBST = lp.sizeBST;
    } else {
        mp.nodeBST = rp.nodeBST;
        mp.sizeBST = rp.sizeBST;
    }
    return mp;
}

int main() {
    //int a[] = {50, 25, 12, -1, -1, 37, 30, -1, -1, -1, 75, 62, -1, 70, -1, -1, 87, -1, -1};
    //int a[] = {50,25,12,-1,-1, 51,-1, -1,75,62,-1,-1,87,-1,-1};
    int a[] = {50,25,12,-1,-1,37,30,-1,-1,40,-1,-1,75,62,60,-1,-1,77,-1,-1,87,-1,-1};
    int n = sizeof(a)/sizeof(a[0]);

    stack<Pair> st;
    Node* root;
    for(int i = 0; i < n; i++) {
        if(a[i] == -1) { // when null
            //hmlog stack se nikalkar update krenge childIndex
            // ko aur agar index mai 2 hogaya matlab no all child traversed pop krdo parent ko
            Pair &p = st.top();
            if(p.child == 0) {
                p.node->left = NULL;
                p.child++;
            } else if(p.child == 1){
                p.node->right = NULL;
                p.child++;
                st.pop();
            }
        } else { 
            Node* node = new Node(a[i]);
            if(st.empty()) {
                root = node;
            } else {
                Pair &p = st.top();
                if(p.child == 0) {
                    p.node->left = node;
                    p.child++;
                } else if(p.child == 1){ 
                    p.node->right = node;
                    p.child++;
                    st.pop();
                }
            }
            st.push(Pair(node, 0));
        }
    }
    Node* nodeBST = NULL;
    int sizeBST = 0;
    largestBst(root, sizeBST, nodeBST);
    cout << nodeBST->data << "@" << sizeBST << endl;
    PairLargestBST p = largestBst(root);
    cout << p.nodeBST->data << "@" << p.sizeBST << endl;
    return 0;
}
