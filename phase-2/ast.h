
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


    FieldDeclASTnode (ASTnode* typo,
                       VarstarASTnode* variable_str) {
        typ = typo;
        variables = variable_str->getVars();
    }



    ASTnode* getType()
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
    ASTnode* typ;
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

    private:
    
}








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
