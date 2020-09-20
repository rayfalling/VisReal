//
// Created by rayfalling on 2020/8/29.
//

#include "TString.h"

using namespace Engine::Core::Types;

TString::TString() {
    string = nullptr;
};

TString::~TString() {
    delete string;
}

TString::TString(std::string &str) {
    string = TString::string2wstring(str).data();
}
