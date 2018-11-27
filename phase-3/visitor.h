#ifndef POSTFIXVISITOR_H
#define POSTFIXVISITOR_H

#include "ClassDefs.h"

class PostFixVisitor: public ASTvisitor
{
  public:

    virtual void visit(ProgASTnode& node)
    {
        std::cout<<"<prog>"<<'\n';
        node.getDecl()->accept(*this);
        std::cout<<"</prog>"<<'>\n';
    } 
    virtual void visit(DeclASTnode& node)
    {
        std::cout<<"<decl>\n";
        node.getFieldDecls()->accept(*this);
        std::cout<<"</decl>\n";

    } 
    virtual void visit(FieldDeclsASTnode& node)
    {
        std::cout<<"<fielddecls>\n";
        vector<ASTnode*> temp =node.getFieldDecls();
        if(temp.size())
            for(unsigned int i=0;i<temp.size();i++)
                temp[i]->accept(*this);

        std::cout<<"</fielddecls>\n";
    } 
    virtual void visit(FieldDeclASTnode& node)
    {
        std::cout<<"<fielddecl>\n";
        std::cout << node.getType();
        vector<ASTnode*> temp = node.getVariables();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        std::cout<<"</fielddecl>\n";
    } 
    virtual void visit(VarstarASTnode& node) 
    {
        std::cout<<"<vars>\n";
        vector<ASTnode*> temp = node.getVars();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        std::cout<<"</vars>\n";
    }
    virtual void visit(VarASTnode& node) 
    {
        std::cout<<"<var>\n";
        std::cout<<node.getType();
        std::cout<<node.getID();
        if(node.getLit())
            std::cout<< node.getLit();
        std::cout<<"</var>\n";

    }

};

#endif /* POSTFIXVISITOR_H */