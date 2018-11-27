#ifndef AST_H
#define AST_H

#include <bits/stdc++.h>
#include <stack>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Support/IRBuilder.h>
//#include <llvm/ModuleProvider.h>
#include <llvm/Target/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/raw_ostream.h>

using namespace std;

union Node
{
	int integerVal;
	std::string* stringVal;
    class ASTnode* astnode;
    class ProgASTnode* progastnode;
    class DeclASTnode* declastnode;
    class FieldDeclsASTnode* fildeclsastnode;
    class FieldDeclASTnode* fildeclastnode;
    class VarstarASTnode* varstrastnode;
    class VarASTnode* varastnode;
   
};

typedef union Node YYSTYPE;

#define YYSTYPE_IS_DECLARED 1

class ProgASTnode;
class DeclASTnode;
class FieldDeclsASTnode;
class FieldDeclASTnode;
class VarstarASTnode;
class VarASTnode;
class ASTnode;

class ASTvisitor
{
  public:
    virtual void visit(ProgASTnode& node) = 0;
    virtual void visit(DeclASTnode& node) = 0;
    virtual void visit(FieldDeclsASTnode& node) = 0;
    virtual void visit(FieldDeclASTnode& node) = 0;
    virtual void visit(VarstarASTnode& node) = 0;
    virtual void visit(VarASTnode& node) = 0;
    virtual void visit(ASTnode& node) = 0;

};


class Codegen
{
	public:

    virtual Value* codegen() = 0;   

}


class ASTnode
{
  public :
    virtual ~ASTnode()
    {
    }

    virtual void accept(ASTvisitor& V) = 0;
    virtual Value* codegen();
};

class ProgASTnode : public ASTnode
{
    public:

    ProgASTnode (ASTnode* decl)
    :declare(decl)
    {      
    }

    ASTnode* getDecl()
    {
        return declare;
    }

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }
    
    virtual Value* codegen();

    private:

    ASTnode* declare;

};


class DeclASTnode : public ASTnode
{
    public:

    DeclASTnode (ASTnode* fielddecls)
    :field_decls(fielddecls)
    {    
    }

    ASTnode* getFieldDecls()
    {
        return field_decls;
    }





    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }     

    virtual Value* codegen();  

    private:
    ASTnode* field_decls;


};


class FieldDeclsASTnode : public ASTnode
{
    public:

    FieldDeclsASTnode(){   
    }

    void push_back(ASTnode* field_decl)
    {
        field_decls.push_back(field_decl);
    }

    vector<ASTnode*> getFieldDecls()
    {
        return field_decls;
    }


    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }  

    virtual Value* codegen();



    private:
    vector<ASTnode*> field_decls;    



};

class VarstarASTnode : public ASTnode
{
    public:

    VarstarASTnode()
    {   
    }

    void push_back(ASTnode* variable)
    {
        vars.push_back(variable);
    }

    vector<ASTnode*> getVars()
    {
        return vars;
    }

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    virtual Value* codegen();


    private:
    vector<ASTnode*> vars;    

};


class FieldDeclASTnode : public ASTnode
{
    public:


    FieldDeclASTnode (string typo,
                       VarstarASTnode* variable_str) {
        typ = typo;
        variables = variable_str->getVars();
    }



    string getType()
    {
        return typ;
    }

    vector<ASTnode*> getVariables()
    {
        return variables;
    }                    

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    } 

    virtual Value* codegen();


    private:
    string typ;
    vector<ASTnode*> variables;

};




class VarASTnode : public ASTnode
{
    public:

    VarASTnode(string type
              ,string name)
    :typ(type)
    ,nam(name)
    {   
    }

    VarASTnode(string typo
              ,string name
              ,unsigned int value)
    :typ(typo)
    ,nam(name)
    ,val(value)
    {   
    }

    string getType()
    {
        return typ;
    }

    string getID()
    {
        return nam;
    }

    unsigned int getLit()
    {
        return val;
    }

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    virtual Value* codegen();

    private:

    string typ;
    string nam;
    unsigned int val;    

};



#endif /* End of AST_H */