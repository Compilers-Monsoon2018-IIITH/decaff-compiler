
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
        std::cout<<"decl\n";
        node.getFieldDecls()->accept(*this);
        node.getMethodDecls()->accept(*this);
        std::cout<<"</decl>\n";

    } 
    virtual void visit(FieldDeclsASTnode& node)
    {
        std::cout<<"fielddecls\n";
        vector<ASTnode*> temp =node.getFieldDecls();
        if(temp.size())
            for(unsigned int i=0;i<temp.size();i++)
                temp[i]->accept(*this);

        std::cout<<"fielddecls\n";
    } 
    virtual void visit(FieldDeclASTnode& node)
    {
         std::cout<<"fielddecl\n";
        node.getType();
        vector<ASTnode*> temp = node.getVariables();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        std::cout<<"fielddecl\n";
    } 
    virtual void visit(VarstarASTnode& node) 
    {
        std::cout<<"vars\n";
        vector<ASTnode*> temp = node.getVars();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        std::cout<<"vars\n";
    }
    virtual void visit(VarASTnode& node) 
    {
        std::cout<<"var\n";
        node.getType();
        node.getID();
        if(node.getLit())
            node.getLit()->accept(*this);
        std::cout<<"var\n";

    }
    virtual void visit(TypeASTnode& node) 
    {
        std::cout<<"type\n";
        node.getType();
        std::cout<<"type\n";
    }



    virtual void visit(MethDeclsASTnode& node)
    {
        std::cout<<"methoddecls\n";
        vector<ASTnode*> temp =node.getMethDecls();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        std::cout<<"methoddecls\n";

    } 
    
    virtual void visit(MethDeclASTnode& node) 
    {
        if(node.getType())
            node.getType()->accept(*this);
        if(node.getVoid() != "")
            node.getVoid();
        node.getID();
        vector<ASTnode*> temp =node.getMethods();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        node.getBlock()->accept(*this);
        std::cout<<"methoddecl\n";
    }
    virtual void visit(MethodsASTnode& node) 
    {
        vector<ASTnode*> temp =node.getMethods();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        std::cout<<"methods\n";   
    }
    virtual void visit(MethodASTnode& node) 
    {
        node.getType();
        node.getIDs();
        std::cout<<"method\n";
    }
    virtual void visit(BlockASTnode& node) 
    {
        node.getVarDecls()->accept(*this);
        node.getStatstar()->accept(*this);
        std::cout<<"block\n";

    }
    virtual void visit(VarDeclsASTnode& node)
    {
        vector<ASTnode*> temp =node.getVarDecls();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        std::cout<<"vardecls\n"; 

    }
    virtual void visit(VarDeclASTnode& node) 
    {
        node.getType();
        node.getIDs()->accept(*this);
        std::cout<<"vardecl\n";

    }
    virtual void visit(IdsASTnode& node) 
    {
        vector<string> temp =node.getIds();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i];
        std::cout<<"ids\n";

    }
    virtual void visit(StatstarASTnode& node)
    {
        vector<ASTnode*> temp =node.getStatements();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        std::cout<<"statements\n";
    }
    virtual void visit(StatASTnode& node) 
    {   
        if(node.getLocation())
            node.getLocation()->accept(*this);
        if(node.getExpr())
            node.getExpr()->accept(*this);
        if(node.getStr1() != "")
            node.getStr1();
        if(node.getStr2() != "")
            node.getStr2();
        if(node.getBlock())
            node.getBlock()->accept(*this);

    }

    virtual void visit(LocationASTnode& node) 
    {
        node.getID();
        if(node.getExpr())
            node.getExpr()->accept(*this);
    }
    virtual void visit(MethodCallASTnode& node) 
    {
        if(node.getCallOut() != "")
            node.getCallOut();
        node.getID();
        node.getExpr()->accept(*this);

    }
    virtual void visit(ExprPlusASTnode& node) 
    {
        vector<ASTnode*> temp =node.getExprs();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i];
        std::cout<<"exprs\n";
    }
    virtual void visit(CallPlusASTnode& node) 
    {
        vector<ASTnode*> temp =node.getCalloutArgs();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i];
        std::cout<<"calloutargss\n";
    }
    virtual void visit(CallArgASTnode& node) 
    {
        if(node.getExpr())
            node.getExpr()->accept(*this);
        if(node.getStringLit() != "")
            node.getStringLit();
    }
    virtual void visit(ExprASTnode& node) 
    {
        node.getExpr()->accept(*this);
        if(node.getOp())
            node.getOp()->accept(*this);
        if(node.getExpr1())
            node.getExpr1()->accept(*this);
    }
    virtual void visit(LitASTnode& node) 
    {
        if(node.getLit())
            node.getLit()->accept(*this);
        if(node.getChar() != "")
            node.getChar();
    }
    virtual void visit(BoolLitASTnode& node) 
    {
        node.getBool();
    }
    virtual void visit(ArthOpASTnode& node) 
    {
        node.getOp();
    }
    virtual void visit(BinOpASTnode& node) 
    {
        node.getBinOp()->accept(*this);
    }
    virtual void visit(EqOpASTnode& node) 
    {
        
        node.getOp1();
        node.getOp2();


    }
    virtual void visit(RelOpASTnode& node) 
    {
        
        node.getOp1();
        if(node.getOp2())
            node.getOp2();

    }
    virtual void visit(CondOpASTnode& node) 
    {
        node.getOp1();
        node.getOp2();
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

