/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

SymbolTable::SymbolTable(){
    root=NULL;
    size=0;
}

int nodehit(SymNode* temp){
    if(temp==NULL){
        return -1;
    }
    return temp->height;
}

int difrnc(SymNode* check){  
    if(check==NULL){
        return 0;
    } 
    return ((nodehit(check->left))-(nodehit(check->right)));  
}

SymNode* ins(SymNode* temp,string k){
    string a=temp->key;
    int result=k.compare(a);
    if(result<0){
        if(temp->left==NULL){
            SymNode* ans=new SymNode(k);
            temp->left=ans;
            ans->par=temp;
        }
        else{
            temp->left=ins(temp->left,k);
        }
    }
    else{
        if(temp->right==NULL){
            SymNode* ans=new SymNode(k);
            temp->right=ans;
            ans->par=temp;
        }
        else{
            temp->right=ins(temp->right,k);
        }
    }
    temp->height=1+max(nodehit(temp->left),nodehit(temp->right));
    int prblm=difrnc(temp);
    if (prblm>1 && (k.compare(temp->left->key)<0)){
        return temp->LeftLeftRotation();
    }
    if (prblm<-1 && (k.compare(temp->right->key)>0)){
        return temp->RightRightRotation();
    } 
    if (prblm>1 && (k.compare(temp->left->key)>0)){  
        return temp->LeftRightRotation();
    }
    if (prblm<-1 && (k.compare(temp->right->key)<0)){  
        return temp->RightLeftRotation();
    }
    return temp;
}

void SymbolTable::insert(string k){
    if(root==NULL){
        SymNode* head=new SymNode(k);
        size++;
        root=head;
        return;
    }
    size++;
    root=ins(root,k);
}

SymNode* Rightmin(SymNode* temp){
    SymNode* temp2=temp;
    while(temp2->left!=NULL){
        temp2=temp2->left;
    }
    return temp2;
}

SymNode* Leftmax(SymNode* temp){
    SymNode* temp2=temp;
    while(temp2->right!=NULL){
        temp2=temp2->right;
    }
    return temp2;
}

SymNode* deleteNode(SymNode* temp, string k) {
    if(temp==NULL){
        return NULL;
    }
    string a=temp->key;
    int result=k.compare(a);
    if(result==0){
        if(temp->left==NULL && temp->right==NULL){
            delete temp;
            return NULL;
        }
        else if(temp->left==NULL){
            SymNode* x=Rightmin(temp->right);
            temp->address=x->address;
            temp->key=x->key;
            string s=x->key;
            temp->right=deleteNode(temp->right,s);
        }
        else{
            SymNode* x=Leftmax(temp->left);
            temp->address=x->address;
            temp->key=x->key;
            string s=x->key;
            temp->left=deleteNode(temp->left,s);
        }
    }
    else if(result<0){
        temp->left=deleteNode(temp->left,k);
    }
    else{
        temp->right=deleteNode(temp->right,k);
    }
    temp->height=1+max(nodehit(temp->left),nodehit(temp->right));
    int prblm=difrnc(temp);
    if (prblm>1){
        int prblm2=difrnc(temp->left);
        if(prblm2>=0){
            return temp->LeftLeftRotation();
        }
        if(prblm2<0){
            return temp->LeftRightRotation();
        }
    }
    if (prblm<-1){
        int prblm2=difrnc(temp->right);
        if(prblm2>0){
            return temp->RightLeftRotation();
        }
        if(prblm2<=0){
            return temp->RightRightRotation();
        }
    }
    return temp;
}

void SymbolTable::remove(string k){
    int ans=search(k);
    if(ans==-2){
        return;
    }
    size--;
    root=deleteNode(root,k);
}

int srch(SymNode* temp,string k){
    if(temp==NULL){
        return -2;
    }
    string a=temp->key;
    int result=k.compare(a);
    if(result==0){
        return temp->address;
    }
    if(result<0){
        return srch(temp->left,k);
    }
    return srch(temp->right,k);
}

int SymbolTable::search(string k){
    return srch(root,k);
}

void giveAddress(SymNode* temp,string k,int idx){
    if(temp==NULL){
        return;
    }
    string a=temp->key;
    int result=k.compare(a);
    if(result==0){
        temp->address=idx;
        return;
    }
    if(result<0){
        giveAddress(temp->left,k,idx);
        return;
    }
    giveAddress(temp->right,k,idx);
    return;
}

void SymbolTable::assign_address(string k,int idx){
    giveAddress(root,k,idx);
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymNode* Burn(SymNode* temp){
    if(temp==NULL){
        return temp;
    }
    temp->left=Burn(temp->left);
    temp->right=Burn(temp->right);
    delete temp;
    return NULL;
}

SymbolTable::~SymbolTable(){
    size=0;
    root=Burn(root);
}
