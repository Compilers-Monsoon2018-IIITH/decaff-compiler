#ifndef CODEGEN_H
#define CODEGEN_H

#include "ClassDefs.h"

class Codegen : public Codegenerator{
public:
	static AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, const std::string &VarName, string type) {
	  /* Allocates memory for local variables  on the stack of the function */

	  /* Get the builder for current context */
	  IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
	  AllocaInst* Alloca;
	  if(type == "int"){
	    Alloca = TmpB.CreateAlloca(Type::getInt32Ty(getGlobalContext()), 0, VarName.c_str());
	  }
	  else if (type == "boolean"){
	    Alloca = TmpB.CreateAlloca(Type::getInt1Ty(getGlobalContext()), 0, VarName.c_str());
	  }
	  return Alloca;
	}



	Value* FieldDeclASTnode::codegen(){
	  for(int i = 0; i < variables.size(); i++)
	  {
	    class Var* var = variables[i];
	    llvm::Type *ty;
	    if(typ == "int"){
	      ty = Type::getInt32Ty(Context);
	    }
	    else if(typ == "boolean"){
	      ty = Type::getInt1Ty(Context);
	    }
	    if(var->getType() == 'Array'){
	      PointerType* PointerTy_1 = PointerType::get(ArrayType::get(ty,var->getVal()),0);
	      GlobalVariable* gv = new GlobalVariable(*TheModule,ArrayType::get(ty,var->getVal()),false,GlobalValue::CommonLinkage,0,var->getID());
	    }
	    else{
	      PointerType* ptrTy = PointerType::get(ty,0);
	      GlobalVariable* gv = new GlobalVariable(*TheModule,ptrTy , false,GlobalValue::ExternalLinkage, 0, var->getID());
	    }
	  }
	  Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
	  return v;
	}

	Value* FieldDeclsASTnode::codegen(){
	  for(int i = 0; i < field_decls.size(); i++){
	    field_decls[i]->codegen();
	  }
	  Value* v = ConstantInt::get(getGlobalContext(), APInt(32,1));
	  return v;
	}

	Value* ProgASTnode::codegen(){
	  Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	  V = declare->codegen();
	  return V;
	}

	void ProgASTnode::generateCode(){
	  cout << "Generating LLVM IR Code\n";
      TheModule->dump();
    }

	Value* DeclASTnode::codegen(){
	  Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	  V = field_decls->codegen();
	  return V;
	}

	Value* VarASTnode::codegen(){
	  Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	  return V;
	}

	Value* VarstarASTnode::codegen(){
	  Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	  return V;
	}


};

#endif /* CODEGEN_H */