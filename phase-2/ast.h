
#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
using namespace std;


class ProgASTnode;
class DeclASTnode;
class FieldDeclsASTnode;
class FieldDeclASTnode;
class VarstarASTnode;
class VarASTnode;
class TypeASTnode;
class BinaryASTnode;
class TernaryASTnode;
class IntLitASTnode;

class MethDeclsASTnode;
class MethDeclASTnode;
class MethodsASTnode;
class MethodASTnode;
class BlockASTnode;
class VarDeclsASTnode; 
class VarDeclASTnode;
class IdsASTnode;
class StatstarASTnode;
class StatASTnode;

class LocationASTnode;
class MethodCallASTnode;
class ExprPlusASTnode;
class CallPlusASTnode;
class CallArgASTnode;
class ExprASTnode;
class LitASTnode;
class BoolLitASTnode;
class ArthOpASTnode;
class BinOpASTnode;
class EqOpASTnode;
class RelOpASTnode;
class CondOpASTnode;


class ASTvisitor
{
  public:
    virtual void visit(BinaryASTnode& node) = 0;
    virtual void visit(TernaryASTnode& node) = 0;
    virtual void visit(IntLitASTnode& node) = 0;
    virtual void visit(ProgASTnode& node) = 0;
    virtual void visit(DeclASTnode& node) = 0;
    virtual void visit(FieldDeclsASTnode& node) = 0;
    virtual void visit(FieldDeclASTnode& node) = 0;
    virtual void visit(VarstarASTnode& node) = 0;
    virtual void visit(VarASTnode& node) = 0;
    virtual void visit(TypeASTnode& node) = 0;
    virtual void visit(MethDeclsASTnode& node) = 0;
    virtual void visit(MethDeclASTnode& node) = 0;
    virtual void visit(MethodsASTnode& node) = 0;
    virtual void visit(MethodASTnode& node) = 0;
    virtual void visit(BlockASTnode& node) = 0;
    virtual void visit(VarDeclsASTnode& node) = 0;
    virtual void visit(VarDeclASTnode& node) = 0;
    virtual void visit(IdsASTnode& node) = 0;
    virtual void visit(StatstarASTnode& node) = 0;
    virtual void visit(StatASTnode& node) = 0;
    virtual void visit(LocationASTnode& node) = 0;
    virtual void visit(MethodCallASTnode& node) = 0;
    virtual void visit(ExprPlusASTnode& node) = 0;
    virtual void visit(CallPlusASTnode& node) = 0;
    virtual void visit(CallArgASTnode& node) = 0;
    virtual void visit(ExprASTnode& node) = 0;
    virtual void visit(LitASTnode& node) = 0;
    virtual void visit(BoolLitASTnode& node) = 0;
    virtual void visit(ArthOpASTnode& node) = 0;
    virtual void visit(BinOpASTnode& node) = 0;
    virtual void visit(EqOpASTnode& node) = 0;
    virtual void visit(RelOpASTnode& node) = 0;
    virtual void visit(CondOpASTnode& node) = 0;

};


class ASTnode
{
  public :
    virtual ~ASTnode()
    {
    }

    //  virtual void printPostFix() const = 0;
    virtual void accept(ASTvisitor& V) = 0;
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

    private:

    ASTnode* declare;

};


class DeclASTnode : public ASTnode
{
    public:

    DeclASTnode (ASTnode* fielddecls
                ,ASTnode* methoddecls)
    :field_decls(fielddecls)
    ,method_decls(methoddecls)
    {    
    }

    ASTnode* getFieldDecls()
    {
        return field_decls;
    }

    ASTnode* getMethodDecls()
    {
        return method_decls;
    }



    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }       

    private:
    ASTnode* field_decls;
    ASTnode* method_decls;

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
              ,ASTnode* value)
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

    ASTnode* getLit()
    {
        return val;
    }

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    private:

    string typ;
    string nam;
    ASTnode* val;    

};

class IntLitASTnode : public ASTnode
{

    public:
    IntLitASTnode(string type
                  ,int value)
    :typ(type)
    ,val(value)
    {   
    }

    string getType()
    {
        return typ;
    }

    int getValue()
    {
        return val;
    }


    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    


    private:

    string typ;
    int val;    
};


class TypeASTnode : public ASTnode
{
    public: 

    TypeASTnode(string typo)
    :typ(typo)
    {   
    }

    string getType()
    {
        return typ;
    }

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }


    private:    
    string typ;
};


class MethDeclsASTnode : public ASTnode
{
    public:

    MethDeclsASTnode(){   
    }

    void push_back(ASTnode* method_decl)
    {
        method_decls.push_back(method_decl);
    }

    vector<ASTnode*> getMethDecls()
    {
        return method_decls;
    }


    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }  




    private:
    vector<ASTnode*> method_decls;
};

class MethodsASTnode : public ASTnode
{
    public:

    MethodsASTnode()
    {   
    }

    void push_back(ASTnode* method)
    {
        methods.push_back(method);
    }

    vector<ASTnode*> getMethods()
    {
        return methods;
    }

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }




    private:
    vector<ASTnode*> methods;   
};
class MethDeclASTnode : public ASTnode
{
    public:

    MethDeclASTnode(string voidi
                   ,string idi
                   ,MethodsASTnode* methods
                   ,ASTnode* block)
    {vod=voidi;
     id=idi;
     metds=methods->getMethods();
     bloc=block;
    
    }

    ASTnode* getType()
    {
        return typ;
    }

    string getID()
    {
        return id;
    }

    string getVoid()
    {
        return vod;
    }

    vector<ASTnode*> getMethods()
    {
        return metds;
    }

    ASTnode* getBlock()
     {
        return bloc;            
     }


    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }  

    private:
    ASTnode* typ;
    string vod;
    string id;
    vector<ASTnode*> metds;
    ASTnode* bloc;    

};




class MethodASTnode : public ASTnode
{
    public:
    MethodASTnode(string typo
                  ,string idis)
    :typ(typo)
    ,ids(idis)
    {
    }

    string getType()
    {
        return typ;
    }

    string getIDs()
    {
        return ids;
    }

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    private:
    string typ;
    string ids;    

};
class BlockASTnode : public ASTnode 
{
    public:

    BlockASTnode(ASTnode* vardecls 
                ,ASTnode* statements)
    :var_decls(vardecls)
    ,statement_star(statements)
    {
    }


    ASTnode* getVarDecls()
    {
        return var_decls;
    }

    ASTnode* getStatstar()
    {
        return statement_star;
    }


    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }


    private:

    ASTnode* var_decls;
    ASTnode* statement_star;                

} ;

class VarDeclsASTnode : public ASTnode 
{
    public:
    VarDeclsASTnode()
    {
    }

    void push_back(ASTnode* var_decl)
    {
        var_decls.push_back(var_decl);
    }

    vector<ASTnode*> getVarDecls()
    {
        return var_decls;
    }

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }       

    private: 
    vector<ASTnode*> var_decls;    
};


class VarDeclASTnode : public ASTnode
{
    public:

    VarDeclASTnode(string typo
                   ,ASTnode* idis)
    :typ(typo)
    ,ids(idis)
    {
    }

    string getType()
    {
        return typ;
    }

    ASTnode* getIDs()
    {
        return ids;
    }

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }    


    private:
    string typ;
    ASTnode* ids;    

};


class IdsASTnode : public ASTnode 
{
    public:
    IdsASTnode()
    {
    }

    void push_back(string id)
    {
        ids.push_back(id);
    }

    vector<string> getIds()
    {
        return ids;
    }

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }     

    private:
    vector<string> ids;   

};

class StatstarASTnode : public ASTnode 
{
    public:

    StatstarASTnode()
    {
    }

    void push_back(ASTnode* statement)
    {
        statements.push_back(statement);
    }

    vector<ASTnode*> getStatements()
    {
        return statements;
    }


    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }         

    private:
    vector<ASTnode*> statements; 

};
class StatASTnode  : public ASTnode
{
    public:

    StatASTnode(ASTnode* location
                ,ASTnode* expr)
    :loc(location)
    ,exp(expr)
    {
    }


    StatASTnode(string ifcon
               ,ASTnode* expr
               ,ASTnode* block)
    :str1(ifcon)
    ,exp(expr)
    ,bloc(block)
    {
    }



    StatASTnode(string forcon
                ,string idi
               ,ASTnode* expr
               ,ASTnode* expr1
               ,ASTnode* block)
    :str1(forcon)
    ,str2(idi)
    ,exp(expr)
    ,exp1(expr1)
    ,bloc(block)
    {
    }

    StatASTnode(string stat)
    :str1(stat)
    {
    }

    StatASTnode(string retcon
               ,ASTnode* expr)
    :str1(retcon)
    ,exp(expr)
    {
    }

    StatASTnode(ASTnode* block)
    :bloc(block)
    {
    }   

    ASTnode* getLocation()
    {
        return loc;
    }



    ASTnode* getExpr()
    {
        return exp;
    }

    ASTnode* getBlock()
    {
        return bloc;
    }

   

    string getStr1()
    {
        return str1;
    }

    string getStr2()
    {
        return str2;
    }

    ASTnode* getExpr1()
    {
        return exp1;
    }


    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }
    
    private:
    ASTnode* loc;
    string str1;
    string str2;
    ASTnode* exp;
    ASTnode* exp1;
    ASTnode* bloc;    
   

};


class LocationASTnode : public ASTnode
{
    public:

    LocationASTnode(string idi)
    :id(idi)
    {
    }

    LocationASTnode(string idi
                    ,ASTnode* expr)
    :id(idi)
    ,exp(expr)
    {
    }

    string getID()
    {
        return id;
    }

    ASTnode* getExpr()
    {
        return exp;
    }

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    private:

    string id;
    ASTnode* exp;   
};


class MethodCallASTnode : public ASTnode
{
    public:

    MethodCallASTnode(string idi
                    ,ASTnode* exprplus)
    :id(idi)
    ,exp(exprplus)
    {}

    MethodCallASTnode(string call_out
                      ,string idi
                     ,ASTnode* expr)
    :callout(call_out)
    ,id(idi)
    ,exp(expr)
    {}

    string getCallOut()
    {
        return callout;
    }
    string getID()
    {
        return id;
    }

    ASTnode* getExpr()
    {
        return exp;
    }

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }


    private: 
    string callout;
    string id;
    ASTnode* exp;   
};

class ExprPlusASTnode : public ASTnode
{
    public:

    ExprPlusASTnode()
    {}

    void push_back(ASTnode* expr)
    {
        exprs.push_back(expr);
    }

    vector<ASTnode*> getExprs()
    {
        return exprs;
    }

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    private:
    vector<ASTnode*> exprs;    
};

class CallPlusASTnode : public ASTnode
{
    public:

    CallPlusASTnode()
    {}

    void push_back(ASTnode* callooutarg)
    {
        callargs.push_back(callooutarg);
    }

    vector<ASTnode*> getCalloutArgs()
    {
        return callargs;
    }

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    private:
    vector<ASTnode*> callargs;
};

class CallArgASTnode : public ASTnode
{
    public:

    CallArgASTnode(ASTnode* expr)
    :exp(expr)
    {}

    CallArgASTnode(string strlit)
    :stringlit(strlit)
    {}

    string getStringLit()
    {
        return stringlit;
    }

    ASTnode* getExpr()
    {
        return exp;
    }

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    private:

    ASTnode* exp;
    string stringlit;    
};


class ExprASTnode : public ASTnode
{
    public:
    
    ExprASTnode(ASTnode* rule)
    :rl(rule)
    {}

    ExprASTnode(ASTnode* expr
                ,ASTnode* oper
                ,ASTnode* expr1)
    :rl(expr)
    ,op(oper)
    ,rl1(expr1)
    {}

    ASTnode* getExpr()
    {return rl;}

    ASTnode* getOp()
    {return op;}

    ASTnode* getExpr1()
    {return rl1;}
    
    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    private:

    ASTnode* rl;
    ASTnode* op;
    ASTnode* rl1;
        
};

class LitASTnode : public ASTnode
{
    public:

    LitASTnode(ASTnode* literal)
    :lit(literal)
    {}

    LitASTnode(string char_lit)
    :charlit(char_lit)
    {}

    ASTnode* getLit()
    {return lit;}

    string getChar()
    {return charlit;}

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    private:
    ASTnode* lit;
    string charlit;    
};

class BoolLitASTnode : public ASTnode
{
    public:

    BoolLitASTnode(string boolean)
    :bol(boolean)    
    {}

    string  getBool()
    {return bol;}

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    private:
    string bol;    
};

class ArthOpASTnode : public ASTnode
{
    public:

    ArthOpASTnode(char oper)
    :op(oper)
    {}

    char getOp()
    {return op;}
    
    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }    


    private:

    char op;    
};

class BinOpASTnode : public ASTnode
{
    public:

    BinOpASTnode(ASTnode* bin_operator)
    :binop(bin_operator)
    {}

    ASTnode* getBinOp()
    {return binop;}

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    private:    
    ASTnode* binop;
};

class EqOpASTnode : public ASTnode
{
    public:

    EqOpASTnode(char str1
                ,char str2)
    :op1(str1)
    ,op2(str2)
    {}

    char getOp1()
    {return op1;}

    char getOp2()
    {return op2;}    

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    private:

    char op1;
    char op2;     
};

class RelOpASTnode : public ASTnode
{
    public:

    RelOpASTnode(char str1)
    :op1(str1)
    {}

    RelOpASTnode(char str1
                ,char str2)
    :op1(str1)
    ,op2(str2)
    {}

    char getOp1()
    {return op1;}

    char getOp2()
    {return op2;}

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    private:

    char op1;
    char op2;    
};

class CondOpASTnode : public ASTnode
{
    public:

    CondOpASTnode(char str1
                ,char str2)
    :op1(str1)
    ,op2(str2)
    {}

    char getOp1()
    {return op1;}

    char getOp2()
    {return op2;}    

    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

    private:

    char op1;
    char op2;
};








class BinaryASTnode : public ASTnode
{
    public:
    // Constructor to initialize binary operator, 
    // left node and right node of the binary expression.
    BinaryASTnode (string binOperatorParm,
                   ASTnode* pLeftParm,
                   ASTnode* pRightParm)
    :pLeft(pLeftParm)
    ,pRight(pRightParm)
    ,mBinaryOperator(binOperatorParm)
    {
    }  

    /*  virtual void printPostFix() const 
    {
    	lhs->printPostFix();
    	rhs->printPostFix();
    	std::cout << bin_operator << " "; 
    } */

    ASTnode* getLeft()
    {
        return pLeft;
    }

    ASTnode* getRight()
    {
        return pRight;
    }

    string getBinOperator()
    {
        return mBinaryOperator;
    }
    
    virtual void accept(ASTvisitor& v)
    {
        v.visit(*this);
    }

  private:
    // left node and right node can be of any type. 
    // So we need to use Base ASTnode type
    ASTnode* pLeft;
    ASTnode* pRight;
    string   mBinaryOperator;
};


class TernaryASTnode : public ASTnode
{
    public:

    TernaryASTnode (ASTnode* pFirstParm,
                    ASTnode* pSecondParm,
                    ASTnode* pThirdParm)
    :pFirst(pFirstParm)
    ,pSecond(pSecondParm)
    ,pThird(pThirdParm)
    {
    }

    /*
    virtual void printPostFix() const
    {
     	first->printPostFix();
     	second->printPostFix();
     	third->printPostFix();
     	std::cout << "? " << std::endl; 
    }
    */

    ASTnode* getFirst()
    {
        return pFirst;
    }

    ASTnode* getSecond()
    {
        return pSecond;
    }

    ASTnode* getThird()
    {
        return pThird;
    }

     virtual void accept(ASTvisitor& v) 
    {
      v.visit(*this);
    }

  private:
    ASTnode* pFirst;
    ASTnode* pSecond;
    ASTnode* pThird;
};


// class IntLitASTnode: public ASTnode
// {
// 	public:
// 	IntLitASTnode(int intlit)
//     : intlit(intlit)
//     {
//     }

//     int getIntLit()
//     {
//         return intlit;
//     }

//     virtual void accept(ASTvisitor& v) 
//     {
//         v.visit(*this);
//     }
    
// 	/*
//     virtual void printPostFix() const
// 	{
// 		std::cout << intlit << " " ;
// 	}
//     */

//   private:
// 	int intlit;
// };


class ASTContext
{
  public:
    ASTnode* pRoot;
    ~ASTContext()
    {
	    clearAST();
    }

    // free all saved expression trees
    void clearAST()
    {
        delete pRoot;
    }
};

#endif /* End of AST_H */
