#include <node.h>
#include <node_buffer.h>
#include <v8.h>
#include <stdint.h>

extern "C" {
    #include "bcrypt.h"
    #include "keccak.h"
    #include "quark.h"
    #include "scryptjane.h"
    #include "scryptn.h"
    #include "skein.h"
    #include "x11.h"
    #include "groestl.h"
    #include "blake.h"
    #include "fugue.h"
    #include "qubit.h"
    #include "hefty1.h"
    #include "shavite3.h"
    #include "cryptonight.h"
    #include "x13.h"
    #include "nist5.h"
    #include "sha1.h"
    #include "x15.h"
	#include "fresh.h"
}

#include "boolberry.h"

using namespace node;
using namespace v8;










void quark(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   quark_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
  
}



void x11(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   x11_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}


void keccak(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   unsigned int input_len = Buffer::Length(target);
   
   keccak_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}




void scrypt(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 3) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide buffer to hash, N value, and R value")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   if (!args[1]->IsNumber() || !args[2]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
   }   
    
   Local<Number> numn = args[1]->ToNumber();
   unsigned int nValue = numn->Value();
   Local<Number> numr = args[2]->ToNumber();
   unsigned int rValue = numr->Value();
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   scrypt_N_R_1_256(input, output, nValue, rValue, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
  
}



void scryptn(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 2) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide buffer to hash and N factor.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   if (!args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong argument")));
    return;
   }   
    
   Local<Number> numn = args[1]->ToNumber();
   unsigned int nValue = numn->Value();
   
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   //unsigned int N = 1 << (getNfactor(input) + 1);
   unsigned int N = 1 << nValue;
   
   scrypt_N_R_1_256(input, output, N, 1, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
  
}





void scryptjane(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 5) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide two argument: buffer, timestamp as number, and nChainStarTime as number, nMin, and nMax")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   if (!args[1]->IsNumber() 
     || !args[2]->IsNumber()
     || !args[3]->IsNumber()
     || !args[4]->IsNumber()) {     
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
   }   
    
   Local<Number> num = args[1]->ToNumber();
    int timestamp = num->Value();

    Local<Number> num2 = args[2]->ToNumber();
    int nChainStartTime = num2->Value();

    Local<Number> num3 = args[3]->ToNumber();
    int nMin = num3->Value();

    Local<Number> num4 = args[4]->ToNumber();
    int nMax = num4->Value();
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   scryptjane_hash(input, input_len, (uint32_t *)output, GetNfactorJane(timestamp, nChainStartTime, nMin, nMax));

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
  
}





void cryptonight(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();
  bool fast = false;

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }
  
  if (args.Length() >= 2) {
        if(!args[1]->IsBoolean()) {
          isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Argument 2 should be a boolean.")));
          return;
        }
        fast = args[1]->ToBoolean()->BooleanValue();
  }
  

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   
   if(fast)
        cryptonight_fast_hash(input, output, input_len);
   else
        cryptonight_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
  
}


void boolberry(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 2) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide two arguments.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();
   Local<Object> target_spad = args[1]->ToObject();
   uint32_t height = 1;
   

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument 1 should be a buffer object.")));
    return;
   }

   if(!Buffer::HasInstance(target_spad)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument 2 should be a buffer object.")));
    return;
   }
   if (args.Length() >= 3) {
        if(args[2]->IsUint32())
            height = args[2]->ToUint32()->Uint32Value();
        else {
          isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "Argument 3 should be an unsigned integer.")));
          return;
        }
   }
   
   char * input = Buffer::Data(target);
   char * scratchpad = Buffer::Data(target_spad);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   uint64_t spad_len = Buffer::Length(target_spad);

   boolberry_hash(input, input_len, scratchpad, spad_len, output, height);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
  
}


void bcrypt(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   bcrypt_hash(input, output);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}


void skein(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   skein_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}


void groestl(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   groestl_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}



void groestlmyriad(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   groestlmyriad_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}




void blake(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   blake_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}



void fugue(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   fugue_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}


void qubit(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   qubit_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}


void hefty1(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   hefty1_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}


void shavite3(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   shavite3_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}


void x13(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   x13_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}







void nist5(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   nist5_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}





void sha1(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   sha1_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}



void x15(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   x15_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}


void fresh(const v8::FunctionCallbackInfo<v8::Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "You must provide one argument.")));
    return;
  }

   Local<Object> target = args[0]->ToObject();

   if(!Buffer::HasInstance(target)) {
     isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Argument should be a buffer object.")));
    return;
   }
   
   char * input = Buffer::Data(target);
   char output[32];

   uint32_t input_len = Buffer::Length(target);
   
   fresh_hash(input, output, input_len);

   Local<Object> buff = Buffer::New(output, 32);
   args.GetReturnValue().Set(buff);
}


void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "quark", quark);
  NODE_SET_METHOD(exports, "x11", x11);
  NODE_SET_METHOD(exports, "scrypt", scrypt);
  NODE_SET_METHOD(exports, "scryptn", scryptn);
  NODE_SET_METHOD(exports, "scryptjane", scryptjane);
  NODE_SET_METHOD(exports, "keccak", keccak);
  NODE_SET_METHOD(exports, "bcrypt", bcrypt);
  NODE_SET_METHOD(exports, "skein", skein);
  NODE_SET_METHOD(exports, "groestl", groestl);
  NODE_SET_METHOD(exports, "groestlmyriad", groestlmyriad);
  NODE_SET_METHOD(exports, "blake", blake);
  NODE_SET_METHOD(exports, "fugue", fugue);
  NODE_SET_METHOD(exports, "qubit", qubit);
  NODE_SET_METHOD(exports, "hefty1", hefty1);
  NODE_SET_METHOD(exports, "shavite3", shavite3);
  NODE_SET_METHOD(exports, "cryptonight", cryptonight);
  NODE_SET_METHOD(exports, "x13", x13);
  NODE_SET_METHOD(exports, "boolberry", boolberry);
  NODE_SET_METHOD(exports, "nist5", nist5);
  NODE_SET_METHOD(exports, "sha1", sha1);
  NODE_SET_METHOD(exports, "x15", x15);
  NODE_SET_METHOD(exports, "fresh", fresh);
}



NODE_MODULE(multihashing, init)
