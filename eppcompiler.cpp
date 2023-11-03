/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
//Write your code below this line

ofstream finally;
EPPCompiler::EPPCompiler(){
    memory_size=100000000;
    output_file="";
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    memory_size=mem_limit;
    output_file=out_file;
    for(int i=0 ; i<mem_limit ; i++){
        least_mem_loc.push_heap(i);

    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    finally.open(output_file);
    int i=0;
    for(; i<code.size() ; i++){
        string k=code[i][0];
        if(k.compare("del")==0){
            targ.last_deleted=targ.symtable->search(code[i][2]);
            least_mem_loc.push_heap(targ.last_deleted);
            targ.parse(code[i]);
            write_to_file(generate_targ_commands());
        }
        else if(k.compare("ret")==0){
            targ.parse(code[i]);
            write_to_file(generate_targ_commands());
        }
        else{
            targ.parse(code[i]);
            int id=targ.symtable->search(code[i][0]);
            if(id==-1){
                int poppy=least_mem_loc.get_min();
                least_mem_loc.pop();
                targ.symtable->assign_address(code[i][0],poppy);
            }
            write_to_file(generate_targ_commands());
        }
        finally<<endl;
    }
    finally.close();
}

void calculate(ExprTreeNode* temp,vector<string> &str,SymbolTable* symtable){
    if(temp==NULL){
        return;
    }
    calculate(temp->right,str,symtable);
    calculate(temp->left,str,symtable);
    if(temp->type=="VAR"){
        int idx=symtable->search(temp->id);
        string finally="PUSH mem[";
        string s2=to_string(idx);
        finally+=s2;
        finally+="]";
        str.push_back(finally);
    }
    else if(temp->type=="VAL"){
        int idx=temp->num;
        string finally="PUSH ";
        string s2=to_string(idx);
        finally+=s2;
        str.push_back(finally);
    }
    else{
        str.push_back(temp->type);
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string>stackcmnd={};
    ExprTreeNode* temp=targ.expr_trees[targ.expr_trees.size()-1];
    if(temp->left->type=="DEL"){
        int idx=targ.last_deleted;
        string finally="PUSH mem[";
        string s2=to_string(idx);
        finally+=s2;
        finally+="]";
        stackcmnd.push_back(finally);
        finally="DEL = mem[";
        s2=to_string(idx);
        finally+=s2;
        finally+="]";
        stackcmnd.push_back(finally);
        return stackcmnd;
    }
    calculate(temp->right,stackcmnd,targ.symtable);
    if(temp->left->type=="RET"){
        string finally="RET = POP";
        stackcmnd.push_back(finally);
        return stackcmnd;
    }
    string finally="mem[";
    int idx=targ.symtable->search(temp->left->id);
    string s2=to_string(idx);
    finally+=s2;
    finally+="] = POP";
    stackcmnd.push_back(finally);
    return stackcmnd;
}

void EPPCompiler::write_to_file(vector<string> commands){
    for(int i=0 ; i<commands.size() ; i++){
        finally<<commands[i]<<endl;
    }
}

EPPCompiler::~EPPCompiler(){
    
}