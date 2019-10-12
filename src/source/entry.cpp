#include <windows.h>

// #include <gdiplus.h>
#include <node.h>
#include <v8.h>
#include <Windows10Colours.h>

#include <objidl.h>
#include <gdiplus.h>

#include <memory>

v8::Local<v8::Object> getColourObj(v8::Isolate *isolate, DWORD DColour) {
    // v8::Local<v8::Context> context = isolate->GetCurrentContext()->Global();
    // v8::Local<v8::Context> context = isolate->GetCurrentContext()->Global();
    
    v8::Local<v8::Object> colour = v8::Object::New(isolate);

    colour->Set(v8::String::NewFromUtf8(isolate, "red"), v8::Number::New(isolate, GetRValue(DColour)));
    colour->Set(v8::String::NewFromUtf8(isolate, "green"), v8::Number::New(isolate, GetGValue(DColour)));
    colour->Set(v8::String::NewFromUtf8(isolate, "blue"), v8::Number::New(isolate, GetBValue(DColour)));

    return colour;
}

void getColour(const v8::FunctionCallbackInfo<v8::Value> &args) {
    v8::Isolate *isolate = args.GetIsolate();
    // v8::Local<v8::Context> context = isolate->GetCurrentContext()->Global();

    windows10colors::AccentColor accents;
    bool accents_valid = SUCCEEDED (windows10colors::GetAccentColor (accents));

    v8::Local<v8::Object> colours = v8::Object::New(isolate);
    
    colours->Set(v8::String::NewFromUtf8(isolate, "lightest"), getColourObj(isolate, accents.lightest));
    colours->Set(v8::String::NewFromUtf8(isolate, "lighter"), getColourObj(isolate, accents.lighter));
    colours->Set(v8::String::NewFromUtf8(isolate, "light"), getColourObj(isolate, accents.light));
    colours->Set(v8::String::NewFromUtf8(isolate, "accent"), getColourObj(isolate, accents.accent));
    colours->Set(v8::String::NewFromUtf8(isolate, "dark"), getColourObj(isolate, accents.dark));
    colours->Set(v8::String::NewFromUtf8(isolate, "darker"), getColourObj(isolate, accents.darker));
    colours->Set(v8::String::NewFromUtf8(isolate, "darkest"), getColourObj(isolate, accents.darkest));

    args.GetReturnValue().Set(colours);
}

void init(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "getColour", getColour);
}

NODE_MODULE(getColour, init)