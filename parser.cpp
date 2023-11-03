/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
//Write your code below this line

Parser::Parser(){
    expr_trees={};
    symtable=new SymbolTable();
    last_deleted=-1;
}

int fndClsPrntss(vector<string> &expression, int index) {
    int count = 0;
    for (int i = index + 1; i < expression.size(); i++) {
        if (expression[i] == "(") {
            count++;
        } else if (expression[i] == ")") {
            if (count == 0) {
                return i;
            } else {
                count--;
            }
        }
    }
    return -1;
}

ExprTreeNode* bildExprsnTree(vector<string> &expression, int start, int end) {
    if(start>end){
        return NULL;
    }
    if (start == end) {
        ExprTreeNode* result=new ExprTreeNode(expression[start],0);
        return result;
    }
    if(expression[start]=="("){
        int j=fndClsPrntss(expression, start);
        if(j==end){
            return bildExprsnTree(expression,start+1,end-1);
        }
        else{
            ExprTreeNode* node = new ExprTreeNode(expression[j+1],0);
            node->left=bildExprsnTree(expression, start,j);
            node->right=bildExprsnTree(expression, j+2,end);
            return node;
        }
    }
    ExprTreeNode* node = new ExprTreeNode(expression[start+1],0);
    node->left=bildExprsnTree(expression, start,start);
    node->right=bildExprsnTree(expression, start+2,end);
    return node;
}

void Parser::parse(vector<string> expression){
    ExprTreeNode* head=bildExprsnTree(expression,2,expression.size()-1);
    ExprTreeNode* result=new ExprTreeNode();
    result->left=new ExprTreeNode(expression[0],0);
    result->right=head;
    expr_trees.push_back(result);
    if((result->left->type).compare("VAR")==0){
        if(symtable->search(result->left->id)==-2){
            symtable->insert(result->left->id);
        }
    }
    else if((result->left->type).compare("DEL")==0){
        symtable->remove(result->left->id);
    }
}

ExprTreeNode* Blow(ExprTreeNode* temp){
    if(temp==NULL){
        return temp;
    }
    temp->left=Blow(temp->left);
    temp->right=Blow(temp->right);
    delete temp;
    return NULL;
}

Parser::~Parser(){
    long long n=expr_trees.size();
    for(long long i=0 ; i<n ; i++){
        expr_trees[i]=Blow(expr_trees[i]);
    }
    expr_trees.resize(0);
    delete symtable;
}