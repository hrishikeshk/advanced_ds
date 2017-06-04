#include <iostream>
struct Node{
    int data;
    Node *left;
    Node *right;
    int height;
    int count;
};

Node* rotate_left(Node* y){
    Node* w = y->right;
    Node* b = w->left;
    y->right = b;
    w->left = y;
    
    int yleft = 0, ylcount = 0;
    if(y->left){
        yleft = y->left->height + 1;
        ylcount = y->left->count;
    }
    int bheight = 0, bcount = 0;
    if(b){
        bheight = b->height + 1;
        bcount = b->count;
    }
    y->count = ylcount + bcount + 1;
    y->height = yleft;
    if(bheight > yleft)
        y->height = bheight;
    
    w->height = y->height + 1;
    if(w->right){
        if(w->right->height + 1 > w->height){
            w->height = w->right->height + 1;
        }
    }
    w->count = y->count + 1;
    if(w->right)
        w->count += w->right->count;
    return w;
}

Node* rotate_right(Node* z){
    Node* w = z->left;
    Node* c = w->right;
    z->left = c;
    w->right = z;
    
    int zright = 0, zrcount = 0;
    if(z->right){
        zright = z->right->height + 1;
        zrcount = z->right->count;
    }
    int cheight = 0, ccount = 0;
    if(c){
        cheight = c->height + 1;
        ccount = c->count;
    }
    z->count = ccount + zrcount + 1;
    z->height = zright;
    if(cheight > zright)
        z->height = cheight;
    
    w->height = z->height + 1;
    if(w->left){
        if(w->left->height + 1 > w->height){
            w->height = w->left->height + 1;
        }
    }
    w->count = z->count + 1;
    if(w->left)
        w->count += w->left->count;
    return w;
}

bool is_right_heavy(Node* y){
    if(!y)
        return false;
    Node* yr = y->right;
    if(!yr)
        return false;
    Node* yl = y->left;
    if(!yl)
        return true;
    if(yr->height > yl->height)
        return true;
    return false;
}

bool is_left_heavy(Node* y){
    if(!y)
        return false;
    Node* yl = y->left;
    if(!yl)
        return false;
    Node* yr = y->right;
    if(!yr)
        return true;
    if(yl->height > yr->height)
        return true;
    return false;
}

Node* balance(Node* z){
    if(!z)
        return z;
    Node* to_return = z;
    int left_height = 0;
    if(z->left)
        left_height = z->left->height + 1;
    int right_height = 0;
    if(z->right)
        right_height = z->right->height + 1;
    if(left_height - right_height > 1){
        Node* y = z->left;
        bool right_heavy = is_right_heavy(y);
        if(right_heavy){
            Node* x = rotate_left(y);
            z->left = x;
            z->count = x->count + 1;
            z->height = x->height + 1;
            int zright = 0;
            if(z->right){
                z->count += z->right->count;
                zright = z->right->height + 1;
                if(zright > z->height)
                    z->height = zright;
            }
        }
        to_return = rotate_right(z);
    }
    else if(right_height - left_height > 1){
        Node* y = z->right;
        bool left_heavy = is_left_heavy(y);
        if(left_heavy){
            Node* x = rotate_right(y);
            z->right = x;
            z->count = x->count + 1;
            z->height = x->height + 1;
            int zleft = 0;
            if(z->left){
                z->count += z->left->count;
                zleft = z->left->height + 1;
                if(zleft > z->height)
                    z->height = zleft;
            }
        }
        to_return = rotate_left(z);
    }
    return to_return;
}

Node* insert(Node* root, Node* new_node){
    Node* to_return = root;
    if(root->data == new_node->data){
        return root;
    }
    root->count++;
    if(root->data < new_node->data){
        if(root->right){
            root->right = insert(root->right, new_node);
            root->height = root->right->height + 1;
            if(root->left){
                if(root->left->height + 1 > root->height)
                    root->height = root->left->height + 1;
            }
            to_return = balance(root);
        }
        else{
            root->right = new_node;
            root->height = 1;
        }
    }
    else{
        if(root->left){
            root->left = insert(root->left, new_node);
            root->height = root->left->height + 1;
            if(root->right){
                if(root->right->height + 1 > root->height)
                    root->height = root->right->height + 1;
            }
            to_return = balance(root);
        }
        else{
            root->left = new_node;
            root->height = 1;
        }
    }
    return to_return;
}

Node* insertToAVL( Node* node, int data){
    Node* new_node = new Node();
    new_node->data = data;
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->height = 0;
    new_node->count = 1;
    if(!node)
        return new_node;
    return insert(node, new_node);
}

void prt(Node* root){
  std::cout << root->data << " ";
  if(root->left){
      prt(root->left);
  }
  if(root->right){
      prt(root->right);
  }
}

/*
int main(){
    int T;
    std::cin >> T;
    while(T){
        int N;
        std::cin >> N;
        int n;
        Node* root = nullptr;
        while(N){
            std::cin >> n;
            root = insertToAVL(root, n);
            prt(root); std::cout << "\n";
            --N;
        }
        --T;
    }
    return 0;
}
*/

