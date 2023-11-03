/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    type="equal";
    num=0;
    id="";
    left=NULL;
    right=NULL;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    if(t.length()==1 && t[0]=='-'){
        type="SUB";
        id=t;
        num=0;
        left=NULL;
        right=NULL;
    }
    else if(t[0]=='+'){
        type="ADD";
        id=t;
        num=0;
        left=NULL;
        right=NULL;
    }
    else if(t[0]=='-' && t.length()>1){
        type="VAL";
        id=t;
        num=stoi(t);
        left=NULL;
        right=NULL;
    }
    else if(t[0]=='*'){
        type="MUL";
        id=t;
        num=0;
        left=NULL;
        right=NULL;
    }
    else if(t[0]=='/'){
        type="DIV";
        id=t;
        num=0;
        left=NULL;
        right=NULL;
    }
    else if(t[0]=='%'){
        type="MOD";
        id=t;
        num=0;
        left=NULL;
        right=NULL;
    }
    else if(t[0]>='0' && t[0]<='9'){
        type="VAL";
        id=t;
        num=stoi(t);
        left=NULL;
        right=NULL;
    }
    else if(t[0]==':' && t[1]=='='){
        type="equal";
        id=t;
        num=0;
        left=NULL;
        right=NULL;
    }
    else if(t[0]=='(' || t[0]==')'){
        return;
    }
    else if(t.compare("del")==0){
        type="DEL";
        id=t;
        num=0;
        left=NULL;
        right=NULL;
    }
    else if(t.compare("ret")==0){
        type="RET";
        id=t;
        num=0;
        left=NULL;
        right=NULL;
    }
    else{
        type="VAR";
        id=t;
        num=0;
        left=NULL;
        right=NULL;
    }
}

ExprTreeNode::~ExprTreeNode(){
    type="";
    id="";
    num=0;
    left=NULL;
    right=NULL;
}