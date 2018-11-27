
#ifndef POSTFIXVISITOR_H
#define POSTFIXVISITOR_H

#include "ast.h"

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
        node.getMethodDecls()->accept(*this);
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
        node.getType();
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
        node.getType();
        node.getID();
        if(node.getLit())
            node.getLit()->accept(*this);
        std::cout<<"</var>\n";

    }
    virtual void visit(TypeASTnode& node) 
    {
        std::cout<<"<type>\n";
        node.getType();
        std::cout<<"</type>\n";
    }



    virtual void visit(MethDeclsASTnode& node)
    {
        std::cout<<"<methoddecls>\n";
        vector<ASTnode*> temp =node.getMethDecls();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        std::cout<<"</methoddecls>\n";

    } 
    
    virtual void visit(MethDeclASTnode& node) 
    {
        std::cout<<"<methoddecl>\n";
        if(node.getType())
            node.getType()->accept(*this);
        if(node.getVoid() != "")
            node.getVoid();
        node.getID();
        vector<ASTnode*> temp =node.getMethods();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        node.getBlock()->accept(*this);
        std::cout<<"</methoddecl>\n";
    }
    virtual void visit(MethodsASTnode& node) 
    {
        std::cout<<"<methods>\n";
        vector<ASTnode*> temp =node.getMethods();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        std::cout<<"</methods>\n";   
    }
    virtual void visit(MethodASTnode& node) 
    {
        std::cout<<"<method>\n";
        node.getType();
        node.getIDs();
        std::cout<<"</method>\n";
    }
    virtual void visit(BlockASTnode& node) 
    {
        std::cout<<"<block>\n";
        node.getVarDecls()->accept(*this);
        node.getStatstar()->accept(*this);
        std::cout<<"</block>\n";

    }
    virtual void visit(VarDeclsASTnode& node)
    {
        std::cout<<"<vardecls>\n";
        vector<ASTnode*> temp =node.getVarDecls();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        std::cout<<"</vardecls>\n"; 

    }
    virtual void visit(VarDeclASTnode& node) 
    {
        std::cout<<"<vardecl>\n";
        node.getType();
        node.getIDs()->accept(*this);
        std::cout<<"</vardecl>\n";

    }
    virtual void visit(IdsASTnode& node) 
    {
        std::cout<<"<ids>\n";
        vector<string> temp =node.getIds();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i];
        std::cout<<"</ids>\n";

    }
    virtual void visit(StatstarASTnode& node)
    {
        std::cout<<"<statements>\n";
        vector<ASTnode*> temp =node.getStatements();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i]->accept(*this);
        std::cout<<"</statements>\n";
    }
    virtual void visit(StatASTnode& node) 
    {   
        std::cout<<"<statement>\n";
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
        std::cout<<"</statement>\n";
    }

    virtual void visit(LocationASTnode& node) 
    {
        std::cout<<"<location>\n";
        node.getID();
        if(node.getExpr())
            node.getExpr()->accept(*this);
        std::cout<<"</location>\n";
    }
    virtual void visit(MethodCallASTnode& node) 
    {
        std::cout<<"<methodcall>\n";
        if(node.getCallOut() != "")
            node.getCallOut();
        node.getID();
        node.getExpr()->accept(*this);
        std::cout<<"</methodcall>\n";

    }
    virtual void visit(ExprPlusASTnode& node) 
    {
        std::cout<<"<exprs>\n";
        vector<ASTnode*> temp =node.getExprs();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i];
        std::cout<<"</exprs>\n";
    }
    virtual void visit(CallPlusASTnode& node) 
    {
        std::cout<<"<calloutargs>\n";
        vector<ASTnode*> temp =node.getCalloutArgs();
        for(unsigned int i=0;i<temp.size();i++)
            temp[i];
        std::cout<<"</calloutargs>\n";
    }
    virtual void visit(CallArgASTnode& node) 
    {
        std::cout<<"<calloutarg>\n";
        if(node.getExpr())
            node.getExpr()->accept(*this);
        if(node.getStringLit() != "")
            node.getStringLit();
        std::cout<<"</calloutarg>\n";
    }
    virtual void visit(ExprASTnode& node) 
    {
        std::cout<<"<expr>\n";
        node.getExpr()->accept(*this);
        if(node.getOp())
            node.getOp()->accept(*this);
        if(node.getExpr1())
            node.getExpr1()->accept(*this);
        std::cout<<"</expr>\n";
    }
    virtual void visit(LitASTnode& node) 
    {
        std::cout<<"<literal>\n";
        if(node.getLit())
            node.getLit()->accept(*this);
        if(node.getChar() != "")
            node.getChar();
        std::cout<<"</literal>\n";
    }
    virtual void visit(BoolLitASTnode& node) 
    {
        std::cout<<"<bool_literal>\n";
        node.getBool();
        std::cout<<"</bool_literal>\n";
    }
    virtual void visit(ArthOpASTnode& node) 
    {
        std::cout<<"<arth_op>\n";
        node.getOp();
        std::cout<<"</arth_op>\n";
    }
    virtual void visit(BinOpASTnode& node) 
    {
        std::cout<<"<bin_op>\n";
        node.getBinOp()->accept(*this);
        std::cout<<"</bin_op>\n";
    }
    virtual void visit(EqOpASTnode& node) 
    {
        
        std::cout<<"<eq_op>\n";
        node.getOp1();
        node.getOp2();
        std::cout<<"</eq_op>\n";


    }
    virtual void visit(RelOpASTnode& node) 
    {
        std::cout<<"<rel_op>\n";
        node.getOp1();
        if(node.getOp2())
           node.getOp2();
        std::cout<<"</rel_op>\n";

    }
    virtual void visit(CondOpASTnode& node) 
    {
        std::cout<<"<cond_op>\n";
        node.getOp1();
        node.getOp2();
        std::cout<<"</cond_op>\n";
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

