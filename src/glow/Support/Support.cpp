// Copyright 2017 Facebook Inc.  All Rights Reserved.

#include "glow/Support/Support.h"

#include <sstream>

using namespace glow;

std::string glow::pointerToString(void *ptr) {
  std::ostringstream oss;
  oss << ptr;
  return oss.str();
}

std::string glow::escapeDottyString(const std::string &str) {
  std::string out;
  out += "\"";
  for (unsigned char c : str) {
    if (std::isprint(c) && c != '\\' && c != '"' && c != '<' && c != '>') {
      out += c;
    } else {
      out += "\\";
      switch (c) {
      case '"':
        out += "\"";
        break;
      case '<':
        out += "<";
        break;
      case '>':
        out += ">";
        break;
      case '\\':
        out += "\\";
        break;
      case '\t':
        out += 't';
        break;
      case '\r':
        out += 'r';
        break;
      case '\n':
        // The marker '\l' means left-justify linebreak.
        out += 'l';
        break;
      default:
        char const *const hexdig = "0123456789ABCDEF";
        out += 'x';
        out += hexdig[c >> 4];
        out += hexdig[c & 0xF];
      }
    }
  }
  out += "\"";
  return out;
}

DescriptionBuilder &DescriptionBuilder::addDim(const std::string &name,
                                               llvm::ArrayRef<size_t> dims) {
  assert(!dims.empty() && "Invalid dimensions");
  repr_ << name << " : (" << dims[0];
  for (unsigned int i = 1; i < dims.size(); i++) {
    repr_ << " x " << dims[i];
  }
  repr_ << ")\n";
  return *this;
}

