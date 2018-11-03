
#ifndef POSTFIXVISITOR_H
#define POSTFIXVISITOR_H

#include "ast.h"

class PostFixVisitor: public ASTvisitor
{
  public:

    virtual void visit(ProgASTnode& node)
    {
        std::cout<<"prog"<<'\n';
        node.getDecl()->accept(*this);
    } 
    virtual void visit(DeclASTnode& node)
    {
        node.getFieldDecls()->accept(*this);
        node.getMethodDecls()->accept(*this);
        std::cout<<"decl\n";

    } 
    virtual void visit(FieldDeclsASTnode& node)
    {
        vector<ASTnode*> temp =node.getFieldDecls();
        for(int i=0;i<temp.size();i++)
            temp[i]->accept(*this);

        std::cout<<"fielddecls\n";
    } 
    virtual void visit(FieldDeclASTnode& node)
    {
        node.getType()->accept(*this);
        vector<ASTnode*> temp = node.getVariables();
        for(int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        std::cout<<"fielddecl\n";
    } 
    virtual void visit(VarstarASTnode& node) 
    {
        vector<ASTnode*> temp = node.getVars();
        for(int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        std::cout<<"vars\n";
    }
    virtual void visit(VarASTnode& node) 
    {
        node.getType();
        node.getID();
        if(node.getLit())
            node.getLit()->accept(*this);
        std::cout<<"var\n";

    }
    virtual void visit(TypeASTnode& node) 
    {
        node.getType();
        std::cout<<"type\n";
    }

    virtual void visit(BinaryASTnode& node)
    {
        node.getLeft()->accept(*this);
        node.getRight()->accept(*this);
        std::cout << node.getBinOperator() << " ";
    }

    virtual void visit(TernaryASTnode& node)
    {
        node.getFirst()->accept(*this);
        node.getSecond()->accept(*this);
        node.getThird()->accept(*this);
        std::cout << "? ";
    }

    virtual void visit(IntLitASTnode& node) 
    {
        std::cout << node.getType() << " ";
    }
};

#endif /* POSTFIXVISITOR_H */

