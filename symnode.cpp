/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    key="";
    height=-1;
    address=-1;
    left=NULL;
    right=NULL;
    par=NULL;
}

SymNode::SymNode(string k){
    key=k;
    height=0;
    address=-1;
    left=NULL;
    right=NULL;
    par=NULL;
}

int getheight(SymNode* root){
    if(root==NULL){
        return -1;
    }
    return root->height;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* lefty = this->left;
    this->left=lefty->right;
    if(lefty->right){
        lefty->right->par=this;
    }
    lefty->right=this;
    lefty->par=this->par;
    this->par=lefty;
    this->height=1+std::max(getheight(this->left),getheight(this->right));
    lefty->height=1+std::max(getheight(lefty->left),getheight(lefty->right));
    return lefty;
}

SymNode* SymNode::RightRightRotation(){
    SymNode* righty = this->right;
    this->right=righty->left;
    if(righty->left){
        righty->left->par=this;
    }
    righty->left=this;
    righty->par=this->par;
    this->par=righty;
    this->height=1+std::max(getheight(this->left),getheight(this->right));
    righty->height=1+std::max(getheight(righty->left),getheight(righty->right));
    return righty;
}

SymNode* SymNode::LeftRightRotation(){
    this->left=this->left->RightRightRotation();
    return this->LeftLeftRotation();
}

SymNode* SymNode::RightLeftRotation(){
    this->right=this->right->LeftLeftRotation();
    return this->RightRightRotation();
}

SymNode::~SymNode(){
    key="";
    height=-1;
    address=-2;
    left=NULL;
    right=NULL;
    par=NULL;
}
