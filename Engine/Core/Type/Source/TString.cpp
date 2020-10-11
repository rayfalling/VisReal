/**
 * Created by rayfalling on 2020/8/29.
 * 
 * This file is an alternative string header for project.
 * Not use std::string in project because it not support utf-8.
 * Base type is WCHAR.
 * */
#include "TString.h"

using namespace Engine::Core::Types;

TString::TString() {
    string = nullptr;
    length = 0;
};

TString::~TString() {
    delete string;
}

TString::TString(std::string &str) {
    string = TString::string2wstring(str).data();
}

uint32 TString::Length() const {
    return length;
}
