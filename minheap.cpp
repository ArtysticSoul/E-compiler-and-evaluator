/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
//Write your code below this line

MinHeap::MinHeap(){
    root=NULL;
    size=0;
}

int calc(int n){
    int ans=1;
    while(ans<=n){
        ans*=2;
    }
    if((ans-n)==1){
        ans*=2;
    }
    return ans;
}

void hpfyup(HeapNode* temp){
    if(temp->par){
        if(temp->par->val>temp->val){
            swap(temp->par->val,temp->val);
            hpfyup(temp->par);
        }
    }
}

HeapNode* inserting(HeapNode* temp,int num,int count,int lc,int rc){
    if(count==1){
        HeapNode* lefty=new HeapNode(num);
        temp->left=lefty;
        lefty->par=temp;
        hpfyup(lefty);
        return temp;
    }
    else if(count==2){
        HeapNode* righty=new HeapNode(num);
        temp->right=righty;
        righty->par=temp;
        hpfyup(righty);
        return temp;
    }
    int x=count-lc;
    int y=rc-count;
    lc=(lc-1)/2;
    rc=(rc-1)/2;
    if(x<y){
        count-=(lc+1);
        temp->left=inserting(temp->left,num,count,lc,rc);
    }
    else{
        count-=(rc+1);
        temp->right=inserting(temp->right,num,count,lc,rc);
    }
    return temp;
}

void MinHeap::push_heap(int num){
    if(root==NULL){
        HeapNode* head=new HeapNode(num);
        root=head;
        size++;
        return;
    }
    int rc=calc(size);
    int lc=rc/2;
    lc--;
    rc--;
    root=inserting(root,num,size,lc,rc);
    size++;
}

int MinHeap::get_min(){
    if(root==NULL){
        return -1;
    }
    return root->val;
}

int deleting(HeapNode* temp,int count,int lc,int rc){
    if(count==2){
        int ans=temp->left->val;
        delete temp->left;
        temp->left=NULL;
        return ans;
    }
    else if(count==3){
        int ans=temp->right->val;
        delete temp->right;
        temp->right=NULL;
        return ans;
    }
    int x=count-lc;
    int y=rc-count;
    lc=(lc-1)/2;
    rc=(rc-1)/2;
    int ans;
    if(x<=y){
        count-=(lc+1);
        ans=deleting(temp->left,count,lc,rc);
    }
    else{
        count-=(rc+1);
        ans=deleting(temp->right,count,lc,rc);
    }
    return ans;
}

void hpfydn(HeapNode* temp){
    if(temp->left==NULL){
        return;
    }
    HeapNode* t=temp;
    if(t->val>temp->left->val){
        t=temp->left;
    }
    if((temp->right)!=NULL && t->val>temp->right->val){
        t=temp->right;
    }
    if(t!=temp){
        swap(t->val,temp->val);
        hpfydn(t);
    }
}

void MinHeap::pop(){
    if(root==NULL){
        return;
    }
    if(size==1){
        root=NULL;
        size--;
        return;
    }
    int rc=calc(size);
    int lc=rc/2;
    if((lc-size)==1){
        lc/=2;
        rc/=2;
    }
    lc--;
    rc--;
    int ans=deleting(root,size,lc,rc);
    root->val=ans;
    size--;
    hpfydn(root);
}

HeapNode* Burst(HeapNode* temp){
    if(temp==NULL){
        return temp;
    }
    temp->left=Burst(temp->left);
    temp->right=Burst(temp->right);
    delete temp;
    return NULL;
}

MinHeap::~MinHeap(){
    size=0;
    root=Burst(root);
}
