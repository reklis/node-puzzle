#include <stddef.h>

extern "C" {
#include <puzzle.h>
}

#include <node.h>
#include <v8.h>
using namespace v8;

#include <iostream>
using namespace std;

class PuzzleContextWrapper : public node::ObjectWrap {
 public:
	static void Init(v8::Handle<v8::Object> target);

 private:
	PuzzleContextWrapper();
	~PuzzleContextWrapper();

	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	static v8::Handle<v8::Value> Compare(const v8::Arguments& args);
	
	PuzzleContext context;
};

PuzzleContextWrapper::PuzzleContextWrapper() {
	puzzle_init_context(&context);

	// TODO:
	// puzzle_set_contrast_barrier_for_cropping(context, atof(optarg));
	// puzzle_set_autocrop(context, 0);
	// puzzle_set_max_cropping_ratio(context, atof(optarg));
	// puzzle_set_max_height(context, strtoul(optarg, NULL, 10));
	// puzzle_set_lambdas(context, strtoul(optarg, NULL, 10));
	// puzzle_set_noise_cutoff(context, atof(optarg));
	// puzzle_set_p_ratio(context, atof(optarg));
	// puzzle_set_max_width(context, strtoul(optarg, NULL, 10));
};

PuzzleContextWrapper::~PuzzleContextWrapper() {
	puzzle_free_context(&context);
};

void PuzzleContextWrapper::Init(Handle<Object> target) {
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("PuzzleContextWrapper"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->PrototypeTemplate()->Set(String::NewSymbol("compare"), FunctionTemplate::New(Compare)->GetFunction());

	Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
	target->Set(String::NewSymbol("PuzzleContextWrapper"), constructor);
}

Handle<Value> PuzzleContextWrapper::New(const Arguments& args) {
	HandleScope scope;

	PuzzleContextWrapper* obj = new PuzzleContextWrapper();
	obj->Wrap(args.This());

	return args.This();
}

Handle<Value> PuzzleContextWrapper::Compare(const Arguments& args) {
	HandleScope scope;

	PuzzleContextWrapper* obj = ObjectWrap::Unwrap<PuzzleContextWrapper>(args.This());
	PuzzleContext context = obj->context;

	PuzzleCvec cvec1, cvec2;
	puzzle_init_cvec(&context, &cvec1);
	puzzle_init_cvec(&context, &cvec2);

	if (args.Length() < 2) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}

	if ((args.Length() > 2) && !args[3]->IsBoolean()) {
		ThrowException(Exception::TypeError(String::New("fix_for_texts parameter must be true or false")));
		return scope.Close(Undefined());
	}

	if (!args[0]->IsString()) {
		ThrowException(Exception::TypeError(String::New("file1 must be a string path to a file")));
		return scope.Close(Undefined());
	}

	if (!args[1]->IsString()) {
		ThrowException(Exception::TypeError(String::New("file2 must be a string path to a file")));
		return scope.Close(Undefined());
	}

	Local<v8::String> file1 = args[0]->ToString();
	Local<v8::String> file2 = args[1]->ToString();
	bool fix_for_texts = args[2]->IsUndefined() ? true : args[2]->BooleanValue(); // default to ON

	String::AsciiValue f1_ascii(file1);
	String::AsciiValue f2_ascii(file2);
	const int S_OK = 0;
	double distance = -1;

	int vec1_result = puzzle_fill_cvec_from_file(&context, &cvec1, *f1_ascii);
	if (S_OK != vec1_result) {
		ThrowException(Exception::TypeError(String::New("error loading file 1")));
	} else {
		int vec2_result = puzzle_fill_cvec_from_file(&context, &cvec2, *f2_ascii);
		if (S_OK != vec2_result) {
			ThrowException(Exception::TypeError(String::New("error loading file 2")));
		} else {
			distance = puzzle_vector_normalized_distance(&context, &cvec1, &cvec2, fix_for_texts ? 1 : 0);
			puzzle_free_cvec(&context, &cvec2);
		}
		puzzle_free_cvec(&context, &cvec1);
	}

	return scope.Close(Number::New(distance));
}

void InitAll(Handle<Object> target) {
	PuzzleContextWrapper::Init(target);
}

NODE_MODULE(puzzle, InitAll)
