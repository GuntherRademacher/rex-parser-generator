// This file was generated on Tue Oct 20, 2026 19:55 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
// REx command line: PrintJavascript.cpp.template
                                                            #line 1 "PrintJavascript.cpp.template"
                                                            #include "../common/Memory.hpp"

                                                            #include "PrintJavascript.hpp"
                                                            #include "ItemSet.hpp"

                                                            void PrintJavascript::openClass()
                                                            {
                                                              if (! hasProlog)
                                                              {
                                                            #line 14 "PrintJavascript.cpp"
  append(L"\n");
  append(L"function ");
                                                            #line 11 "PrintJavascript.cpp.template"
                                                                print(className.c_str());
                                                            #line 19 "PrintJavascript.cpp"
  append(L"(string");
                                                            #line 12 "PrintJavascript.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 24 "PrintJavascript.cpp"
  append(L", lexer");
                                                            #line 14 "PrintJavascript.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 30 "PrintJavascript.cpp"
  append(L", parsingEventHandler");
                                                            #line 17 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 34 "PrintJavascript.cpp"
  append(L")\n");
  append(L"{\n");
  append(L"  init(string");
                                                            #line 20 "PrintJavascript.cpp.template"
                                                                if (noLexer)
                                                                {
                                                            #line 41 "PrintJavascript.cpp"
  append(L", lexer");
                                                            #line 22 "PrintJavascript.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 47 "PrintJavascript.cpp"
  append(L", parsingEventHandler");
                                                            #line 25 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 51 "PrintJavascript.cpp"
  append(L");\n");
                                                            #line 27 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 55 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var thisParser = this;\n");
  append(L"\n");
  append(L"  this.ParseException = function(b, e, s, o, x)\n");
  append(L"  {\n");
  append(L"    var begin = b;\n");
  append(L"    var end = e;\n");
  append(L"    var state = s;\n");
  append(L"    var offending = o;\n");
  append(L"    var expected = x;");
                                                            #line 37 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 69 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    var ambiguousInput = false;");
                                                            #line 40 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 75 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    var ambiguityDescriptor;");
                                                            #line 43 "PrintJavascript.cpp.template"
                                                                }
                                                              }
                                                            #line 81 "PrintJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    this.getBegin = function() {return begin;};\n");
  append(L"    this.getEnd = function() {return end;};\n");
  append(L"    this.getState = function() {return state;};\n");
  append(L"    this.getExpected = function() {return expected;};\n");
  append(L"    this.getOffending = function() {return offending;};\n");
  append(L"    this.isAmbiguousInput = function() {return ");
                                                            #line 52 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 93 "PrintJavascript.cpp"
  append(L"ambiguousInput");
                                                            #line 55 "PrintJavascript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 99 "PrintJavascript.cpp"
  append(L"false");
                                                            #line 58 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 103 "PrintJavascript.cpp"
  append(L";};\n");
                                                            #line 60 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 108 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    this.setAmbiguousInput = function(a)\n");
  append(L"    {\n");
  append(L"      ambiguousInput = true;\n");
  append(L"      ambiguityDescriptor = a;\n");
  append(L"    };\n");
                                                            #line 68 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 117 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    this.getMessage = function()\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 72 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 125 "PrintJavascript.cpp"
  append(L"ambiguousInput\n");
  append(L"           ? \"ambiguous input\"\n");
  append(L"           : ");
                                                            #line 76 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 131 "PrintJavascript.cpp"
  append(L"offending < 0\n");
  append(L"           ? \"lexical analysis failed\"\n");
  append(L"           : \"syntax error\";\n");
  append(L"    };");
                                                            #line 80 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 139 "PrintJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    this.serialize = function(eventHandler)\n");
  append(L"    {\n");
  append(L"      ambiguityDescriptor.serialize(eventHandler);\n");
  append(L"    };");
                                                            #line 87 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 148 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  };\n");
                                                            #line 90 "PrintJavascript.cpp.template"
                                                            }

                                                            void PrintJavascript::printFlush(int i, bool withinThread)
                                                            {
                                                              increaseIndent(i);
                                                              if (trace)
                                                              {
                                                            #line 159 "PrintJavascript.cpp"
  append(L"\n");
  append(L"flushTrace();");
                                                            #line 98 "PrintJavascript.cpp.template"
                                                              }
                                                              decreaseIndent(i);
                                                            }

                                                            void PrintJavascript::openStackNode()
                                                            {
                                                            #line 169 "PrintJavascript.cpp"
  append(L"\n");
                                                            #line 105 "PrintJavascript.cpp.template"
                                                              print(className.c_str());
                                                            #line 173 "PrintJavascript.cpp"
  append(L".StackNode = function(state, ");
                                                            #line 106 "PrintJavascript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 178 "PrintJavascript.cpp"
  append(L"code, ");
                                                            #line 108 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 182 "PrintJavascript.cpp"
  append(L"pos, link)\n");
  append(L"{\n");
  append(L"  this.state = state;");
                                                            #line 111 "PrintJavascript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 189 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.code = code;");
                                                            #line 114 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 194 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.pos = pos;\n");
  append(L"  this.link = link;\n");
  append(L"\n");
  append(L"  this.equals = function(obj)\n");
  append(L"  {\n");
  append(L"    var lhs = this;\n");
  append(L"    var rhs = obj;\n");
  append(L"    while (lhs != null && rhs != null)\n");
  append(L"    {\n");
  append(L"      if (lhs == rhs) return true;\n");
  append(L"      if (lhs.state != rhs.state) return false;");
                                                            #line 126 "PrintJavascript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 210 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      if (lhs.code != rhs.code) return false;");
                                                            #line 129 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 215 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      if (lhs.pos != rhs.pos) return false;\n");
  append(L"      lhs = lhs.link;\n");
  append(L"      rhs = rhs.link;\n");
  append(L"    }\n");
  append(L"    return lhs == rhs;\n");
  append(L"  };\n");
                                                            #line 137 "PrintJavascript.cpp.template"
                                                              increaseIndent();
                                                            }

                                                            void PrintJavascript::closeStackNode()
                                                            {
                                                              decreaseIndent();
                                                            #line 230 "PrintJavascript.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 145 "PrintJavascript.cpp.template"
                                                              if (hasCustomCode)
                                                              {
                                                                print(className.c_str());
                                                            #line 237 "PrintJavascript.cpp"
  append(L".DeferredCode = function(link, codeId, b0, e0)\n");
  append(L"{\n");
  append(L"  this.link = link;\n");
  append(L"  this.codeId = codeId;\n");
  append(L"  this.b0 = b0;\n");
  append(L"  this.e0 = e0;\n");
  append(L"};\n");
                                                            #line 155 "PrintJavascript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 249 "PrintJavascript.cpp"
  append(L"\n");
                                                            #line 159 "PrintJavascript.cpp.template"
                                                                print(className.c_str());
                                                            #line 253 "PrintJavascript.cpp"
  append(L".DeferredEvent = function(link, name, begin, end, count)\n");
  append(L"{\n");
  append(L"  this.link = link;");
                                                            #line 162 "PrintJavascript.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 260 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.depth = link == null ? 1 : link.depth + 1;\n");
  append(L"\n");
  append(L"  this.isTerminal = function() {return name != null && count == null;};");
                                                            #line 168 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 267 "PrintJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  this.execute = function(eventHandler)\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 173 "PrintJavascript.cpp.template"
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 276 "PrintJavascript.cpp"
  append(L"if (name == null)\n");
  append(L"    {\n");
  append(L"      eventHandler.ambiguity(begin, end);\n");
  append(L"    }\n");
  append(L"    else ");
                                                            #line 179 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 284 "PrintJavascript.cpp"
  append(L"if (count == null)\n");
  append(L"    {\n");
  append(L"      eventHandler.terminal(name, begin, end);\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      eventHandler.nonterminal(name, begin, end, count);\n");
  append(L"    }\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.release = function(eventHandler)\n");
  append(L"  {\n");
  append(L"    var current = this;\n");
  append(L"    var predecessor = current.link;\n");
  append(L"    current.link = null;\n");
  append(L"    while (predecessor != null)\n");
  append(L"    {\n");
  append(L"      var next = predecessor.link;\n");
  append(L"      predecessor.link = current;\n");
  append(L"      current = predecessor;\n");
  append(L"      predecessor = next;\n");
  append(L"    }\n");
  append(L"    do\n");
  append(L"    {\n");
  append(L"      ");
                                                            #line 204 "PrintJavascript.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 313 "PrintJavascript.cpp"
  append(L"if (eventHandler != null)\n");
  append(L"        ");
                                                            #line 207 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 318 "PrintJavascript.cpp"
  append(L"current.execute(eventHandler);\n");
  append(L"      current = current.link;\n");
  append(L"    }\n");
  append(L"    while (current != null);\n");
  append(L"  };\n");
                                                            #line 213 "PrintJavascript.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 327 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.show = function(eventHandler)\n");
  append(L"  {\n");
  append(L"    var stack = [];\n");
  append(L"    for (var current = this; current != null; current = current.link)\n");
  append(L"    {\n");
  append(L"      stack.push(current);\n");
  append(L"    }\n");
  append(L"    while (stack.length > 0)\n");
  append(L"    {\n");
  append(L"      stack.pop().execute(eventHandler);\n");
  append(L"    }\n");
  append(L"  };\n");
                                                            #line 228 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 343 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.toString = function()\n");
  append(L"  {\n");
  append(L"    if (count == null)\n");
  append(L"      return \"terminal(\" + name + \", \" + begin + \", \" + end + \")\";\n");
  append(L"    else\n");
  append(L"      return \"nonterminal(\" + name + \", \" + begin + \", \" + end + \", \" + count + \")\";\n");
  append(L"  };\n");
  append(L"};\n");
                                                            #line 238 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 355 "PrintJavascript.cpp"
  append(L"\n");
                                                            #line 240 "PrintJavascript.cpp.template"
                                                              print(className.c_str());
                                                            #line 359 "PrintJavascript.cpp"
  append(L".Heap = function()\n");
  append(L"{\n");
  append(L"  var array = [];\n");
  append(L"  var size = 0;\n");
  append(L"\n");
  append(L"  this.offer = function(value)\n");
  append(L"  {\n");
  append(L"    var index = size++;\n");
  append(L"    while (index != 0)\n");
  append(L"    {\n");
  append(L"      var parentIndex = (index - 1) >> 1;\n");
  append(L"      if (array[parentIndex].compareTo(value) <= 0)\n");
  append(L"        break;\n");
  append(L"      array[index] = array[parentIndex];\n");
  append(L"      index = parentIndex;\n");
  append(L"    }\n");
  append(L"    array[index] = value;\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.poll = function()\n");
  append(L"  {\n");
  append(L"    if (size == 0)\n");
  append(L"      return null;\n");
  append(L"    var min = array[0];\n");
  append(L"    if (--size > 0)\n");
  append(L"    {\n");
  append(L"      var value = array[size];\n");
  append(L"      var index = 0;\n");
  append(L"      for (var child;;)\n");
  append(L"      {\n");
  append(L"        child = (index << 1) + 2;\n");
  append(L"        if (child < size)\n");
  append(L"        {\n");
  append(L"          var otherChild = child - 1;\n");
  append(L"          if (otherChild < size && array[child].compareTo(array[otherChild]) > 0)\n");
  append(L"            child = otherChild;\n");
  append(L"        }\n");
  append(L"        else if (--child >= size)\n");
  append(L"        {\n");
  append(L"          break;\n");
  append(L"        }\n");
  append(L"        if (value.compareTo(array[child]) <= 0)\n");
  append(L"        {\n");
  append(L"          break;\n");
  append(L"        }\n");
  append(L"        array[index] = array[child];\n");
  append(L"        index = child;\n");
  append(L"      }\n");
  append(L"      array[index] = value;\n");
  append(L"    }\n");
  append(L"    return min;\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.peek = function()\n");
  append(L"  {\n");
  append(L"    return size == 0 ? null : array[0];\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.isEmpty = function()\n");
  append(L"  {\n");
  append(L"    return size == 0;\n");
  append(L"  };\n");
  append(L"};\n");
                                                            #line 304 "PrintJavascript.cpp.template"
                                                            }

                                                            void PrintJavascript::printXmlSerializer()
                                                            {
                                                              if (tree)
                                                              {
                                                            #line 430 "PrintJavascript.cpp"
  append(L"\n");
                                                            #line 311 "PrintJavascript.cpp.template"
                                                                print(className.c_str());
                                                            #line 434 "PrintJavascript.cpp"
  append(L".XmlSerializer = function(log, indent)\n");
  append(L"{\n");
  append(L"  var input = null;\n");
  append(L"  var delayedTag = null;\n");
  append(L"  var hasChildElement = false;\n");
  append(L"  var depth = 0;\n");
  append(L"\n");
  append(L"  this.reset = function(string)\n");
  append(L"  {\n");
  append(L"    log(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\");\n");
  append(L"    input = string;\n");
  append(L"    delayedTag = null;\n");
  append(L"    hasChildElement = false;\n");
  append(L"    depth = 0;\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.startNonterminal = function(tag, begin)\n");
  append(L"  {\n");
  append(L"    if (delayedTag != null)\n");
  append(L"    {\n");
  append(L"      log(\"<\");\n");
  append(L"      log(delayedTag);\n");
  append(L"      log(\">\");\n");
  append(L"    }\n");
  append(L"    delayedTag = tag;\n");
  append(L"    if (indent)\n");
  append(L"    {\n");
  append(L"      log(\"\\n\");\n");
  append(L"      for (var i = 0; i < depth; ++i)\n");
  append(L"      {\n");
  append(L"        log(\"  \");\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    hasChildElement = false;\n");
  append(L"    ++depth;\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.endNonterminal = function(tag, end)\n");
  append(L"  {\n");
  append(L"    --depth;\n");
  append(L"    if (delayedTag != null)\n");
  append(L"    {\n");
  append(L"      delayedTag = null;\n");
  append(L"      log(\"<\");\n");
  append(L"      log(tag);\n");
  append(L"      log(\"/>\");\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      if (indent)\n");
  append(L"      {\n");
  append(L"        if (hasChildElement)\n");
  append(L"        {\n");
  append(L"          log(\"\\n\");\n");
  append(L"          for (var i = 0; i < depth; ++i)\n");
  append(L"          {\n");
  append(L"            log(\"  \");\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      log(\"</\");\n");
  append(L"      log(tag);\n");
  append(L"      log(\">\");\n");
  append(L"    }\n");
  append(L"    hasChildElement = true;\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.terminal = function(tag, begin, end)\n");
  append(L"  {\n");
  append(L"    if (tag.charAt(0) == '\\'') tag = \"TOKEN\";\n");
  append(L"    this.startNonterminal(tag, begin);\n");
  append(L"    characters(begin, end);\n");
  append(L"    this.endNonterminal(tag, end);\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.whitespace = function(begin, end)\n");
  append(L"  {\n");
  append(L"    characters(begin, end);\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  function characters(begin, end)\n");
  append(L"  {\n");
  append(L"    if (begin < end)\n");
  append(L"    {\n");
  append(L"      if (delayedTag != null)\n");
  append(L"      {\n");
  append(L"        log(\"<\");\n");
  append(L"        log(delayedTag);\n");
  append(L"        log(\">\");\n");
  append(L"        delayedTag = null;\n");
  append(L"      }\n");
  append(L"      log(input.substring(begin, end)\n");
  append(L"               .replace(/&/g, \"&amp;\")\n");
  append(L"               .replace(/</g, \"&lt;\")\n");
  append(L"               .replace(/>/g, \"&gt;\"));\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"};\n");
                                                            #line 410 "PrintJavascript.cpp.template"
                                                              }
                                                            }

                                                            void PrintJavascript::openThread()
                                                            {
                                                            #line 539 "PrintJavascript.cpp"
  append(L"\n");
  append(L"var PARSING = 0;\n");
  append(L"var ACCEPTED = 1;\n");
  append(L"var ERROR = 2;\n");
  append(L"\n");
  append(L"function parse(target, initialState, ");
                                                            #line 420 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 549 "PrintJavascript.cpp"
  append(L"eventHandler, ");
                                                            #line 422 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 553 "PrintJavascript.cpp"
  append(L"thread)\n");
  append(L"{\n");
  append(L"  var threads = thread.open(initialState");
                                                            #line 425 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 560 "PrintJavascript.cpp"
  append(L", eventHandler");
                                                            #line 427 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 564 "PrintJavascript.cpp"
  append(L", target);\n");
  append(L"  for (;;)\n");
  append(L"  {\n");
  append(L"    thread = threads.poll();\n");
  append(L"    if (thread.getAccepted())\n");
  append(L"    {");
                                                            #line 433 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 574 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      var other = null;\n");
  append(L"      while (! threads.isEmpty())\n");
  append(L"      {\n");
  append(L"        other = threads.poll();\n");
  append(L"        if (thread.getE0() < other.getE0())\n");
  append(L"        {\n");
  append(L"          thread = other;\n");
  append(L"          other = null;\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"      if (other != null)\n");
  append(L"      {\n");
  append(L"        rejectAmbiguity(thread.getStack().pos, thread.getE0()");
                                                            #line 448 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 592 "PrintJavascript.cpp"
  append(L", thread.getDeferredEvent(), other.getDeferredEvent()");
                                                            #line 451 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 596 "PrintJavascript.cpp"
  append(L");\n");
  append(L"      }");
                                                            #line 453 "PrintJavascript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 603 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      while (! threads.isEmpty())\n");
  append(L"      {\n");
  append(L"        var other = threads.poll();\n");
  append(L"        thread = thread.getE0() < other.getE0() ? other : resolve(thread, other);\n");
  append(L"      }");
                                                            #line 461 "PrintJavascript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 614 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      thread.release();");
                                                            #line 465 "PrintJavascript.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 621 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 469 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 626 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      return thread;\n");
  append(L"    }\n");
  append(L"\n");
                                                            #line 474 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 634 "PrintJavascript.cpp"
  append(L"    if (! threads.isEmpty())\n");
  append(L"    {\n");
  append(L"      if (threads.peek().equals(thread))\n");
  append(L"      {\n");
  append(L"        rejectAmbiguity(thread.getStack().pos, thread.getE0()");
                                                            #line 480 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 643 "PrintJavascript.cpp"
  append(L", thread.getDeferredEvent(), threads.peek().getDeferredEvent()");
                                                            #line 483 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 647 "PrintJavascript.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 486 "PrintJavascript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 655 "PrintJavascript.cpp"
  append(L"    while (! threads.isEmpty() && threads.peek().equals(thread))\n");
  append(L"    {\n");
  append(L"      thread = resolve(thread, threads.poll());\n");
  append(L"    }");
                                                            #line 492 "PrintJavascript.cpp.template"
                                                              }
                                                              if (tree || hasCustomCode)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 666 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 499 "PrintJavascript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 674 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    if (threads.isEmpty())\n");
  append(L"    {");
                                                            #line 504 "PrintJavascript.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 682 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      thread.release();");
                                                            #line 508 "PrintJavascript.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 689 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 512 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 694 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 514 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 699 "PrintJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    var status;\n");
  append(L"    for (;;)\n");
  append(L"    {\n");
  append(L"      if ((status = thread.parse()) != PARSING) break;\n");
  append(L"      if (! threads.isEmpty()) break;\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    if (status != ERROR)\n");
  append(L"    {\n");
  append(L"      threads.offer(thread);\n");
  append(L"    }\n");
  append(L"    else if (threads.isEmpty())\n");
  append(L"    {\n");
  append(L"      throw new thisParser.ParseException(thread.getB1(),\n");
  append(L"                                          thread.getE1(),\n");
  append(L"                                          ");
                                                            #line 532 "PrintJavascript.cpp.template"
                                                              print(staticPrefix());
                                                            #line 720 "PrintJavascript.cpp"
  append(L"TOKENSET[thread.getState()] + 1,\n");
  append(L"                                          thread.getL1(),\n");
  append(L"                                          -1\n");
  append(L"                                         );\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 540 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 731 "PrintJavascript.cpp"
  append(L"\n");
  append(L"function rejectAmbiguity(begin, end");
                                                            #line 543 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 737 "PrintJavascript.cpp"
  append(L", first, second");
                                                            #line 545 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 741 "PrintJavascript.cpp"
  append(L")\n");
  append(L"{");
                                                            #line 547 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 747 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var treeBuilder = new ");
                                                            #line 550 "PrintJavascript.cpp.template"
                                                                  print(className.c_str());
                                                            #line 752 "PrintJavascript.cpp"
  append(L".ParseTreeBuilder();\n");
  append(L"  treeBuilder.reset(input);\n");
  append(L"  second.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, treeBuilder.getTop() + 1);\n");
  append(L"  var secondTree = treeBuilder.pop(1)[0];\n");
  append(L"  first.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, treeBuilder.getTop() + 1);\n");
  append(L"  treeBuilder.push(secondTree);\n");
  append(L"  treeBuilder.nonterminal(\"AMBIGUOUS\", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, 2);");
                                                            #line 560 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 764 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var exception = new thisParser.ParseException(begin, end, -1, -1, -1);\n");
  append(L"  exception.setAmbiguousInput(");
                                                            #line 563 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 771 "PrintJavascript.cpp"
  append(L"treeBuilder");
                                                            #line 565 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 775 "PrintJavascript.cpp"
  append(L");\n");
  append(L"  throw exception;\n");
  append(L"}");
                                                            #line 568 "PrintJavascript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 783 "PrintJavascript.cpp"
  append(L"\n");
  append(L"function resolve(thread, other)\n");
  append(L"{");
                                                            #line 573 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 790 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var a = thread.getStack();\n");
  append(L"  var b = other.getStack();\n");
  append(L"  var begin = a.pos;\n");
  append(L"  while (a !== b && a != null && b != null)\n");
  append(L"  {\n");
  append(L"    begin = a.pos;\n");
  append(L"    a = a.link;\n");
  append(L"    b = b.link;\n");
  append(L"  }");
                                                            #line 584 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 803 "PrintJavascript.cpp"
  append(L"\n");
                                                            #line 586 "PrintJavascript.cpp.template"
                                                                if (shiftAmbiguity)
                                                                {
                                                            #line 808 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var ea = thread.getDeferredEvent();\n");
  append(L"  var eb = other.getDeferredEvent();\n");
  append(L"  var ua = null;\n");
  append(L"  var ub = null;\n");
  append(L"  while (ea !== eb)\n");
  append(L"  {\n");
  append(L"    if ((ea == null ? 0 : ea.depth) >= (eb == null ? 0 : eb.depth))\n");
  append(L"    {\n");
  append(L"      ua = ea;\n");
  append(L"      ea = ea.link;\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      ub = eb;\n");
  append(L"      eb = eb.link;\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"  var sa = ua != null && ua.isTerminal();\n");
  append(L"  var sb = ub != null && ub.isTerminal();\n");
  append(L"  if (sa != sb)\n");
  append(L"  {\n");
  append(L"    if (sb)\n");
  append(L"      thread = other;\n");
  append(L"  }\n");
  append(L"  else if (other.getEventCount() < thread.getEventCount())\n");
  append(L"    thread = other;");
                                                            #line 614 "PrintJavascript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 840 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  if (other.getEventCount() < thread.getEventCount())\n");
  append(L"    thread = other;");
                                                            #line 619 "PrintJavascript.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 848 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  thread.addAmbiguity(begin, thread.getE0());");
                                                            #line 623 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 853 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  return thread;\n");
  append(L"}");
                                                            #line 626 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 859 "PrintJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"var thread;");
                                                            #line 629 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 866 "PrintJavascript.cpp"
  append(L"\n");
  append(L"var eventHandler;");
                                                            #line 632 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 871 "PrintJavascript.cpp"
  append(L"\n");
  append(L"var input;\n");
  append(L"var size;\n");
  append(L"var maxId = 0;\n");
  append(L"\n");
  append(L"function ParsingThread()\n");
  append(L"{\n");
  append(L"  var thisThread = this;\n");
  append(L"  var threads;\n");
  append(L"  var accepted;\n");
  append(L"  var stack;\n");
  append(L"  var state;\n");
  append(L"  var action;");
                                                            #line 645 "PrintJavascript.cpp.template"
                                                              if (tree || useGlr)
                                                              {
                                                            #line 888 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var target;");
                                                            #line 648 "PrintJavascript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 895 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var deferredEvent;");
                                                            #line 652 "PrintJavascript.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 901 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var es;");
                                                            #line 655 "PrintJavascript.cpp.template"
                                                                }
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 909 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var bw, bs;");
                                                            #line 660 "PrintJavascript.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 916 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var deferredCode;");
                                                            #line 664 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 921 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var id;");
                                                            #line 666 "PrintJavascript.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 927 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var eventCount;");
                                                            #line 669 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 932 "PrintJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  this.getId = function() {return id;};");
                                                            #line 672 "PrintJavascript.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 939 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.getEventCount = function() {return eventCount;};");
                                                            #line 675 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 944 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.getAction = function() {return action;};\n");
  append(L"  this.getAccepted = function() {return accepted;};\n");
  append(L"  this.getThreads = function() {return threads};\n");
  append(L"  this.getState = function() {return state};\n");
  append(L"  this.getStack = function() {return stack};\n");
  append(L"  this.getEnd = function() {return end;};\n");
  append(L"  this.getB0 = function() {return b0;};\n");
  append(L"  this.getE0 = function() {return e0;};");
                                                            #line 684 "PrintJavascript.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 958 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.getB");
                                                            #line 688 "PrintJavascript.cpp.template"
                                                                print(iString);
                                                            #line 963 "PrintJavascript.cpp"
  append(L" = function() {return b");
                                                            #line 689 "PrintJavascript.cpp.template"
                                                                print(iString);
                                                            #line 967 "PrintJavascript.cpp"
  append(L";};\n");
  append(L"  this.getE");
                                                            #line 691 "PrintJavascript.cpp.template"
                                                                print(iString);
                                                            #line 972 "PrintJavascript.cpp"
  append(L" = function() {return e");
                                                            #line 692 "PrintJavascript.cpp.template"
                                                                print(iString);
                                                            #line 976 "PrintJavascript.cpp"
  append(L";};\n");
  append(L"  this.getL");
                                                            #line 694 "PrintJavascript.cpp.template"
                                                                print(iString);
                                                            #line 981 "PrintJavascript.cpp"
  append(L" = function() {return l");
                                                            #line 695 "PrintJavascript.cpp.template"
                                                                print(iString);
                                                            #line 985 "PrintJavascript.cpp"
  append(L";};");
                                                            #line 696 "PrintJavascript.cpp.template"
                                                              }
                                                              if (complexWhitespace)
                                                              {
                                                            #line 991 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.setB1 = function(b) {b1 = b;};\n");
  append(L"  this.setE1 = function(e) {e1 = e;};\n");
  append(L"  this.setL1 = function(l) {l1 = l;};");
                                                            #line 702 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 998 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.getBs = function() {return bs;};\n");
  append(L"  this.getBw = function() {return bw;};\n");
  append(L"  this.getTarget = function() {return target;};");
                                                            #line 706 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1006 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.getEs = function() {return es;};\n");
  append(L"  this.getEventHandler = function() {return eventHandler;};\n");
  append(L"  this.getDeferredEvent = function() {return deferredEvent;};");
                                                            #line 711 "PrintJavascript.cpp.template"
                                                                if (resolvesAmbiguity)
                                                                {
                                                            #line 1014 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.addAmbiguity = function(begin, end)\n");
  append(L"  {\n");
  append(L"    if (eventHandler != null)\n");
  append(L"      deferredEvent = new ");
                                                            #line 717 "PrintJavascript.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1022 "PrintJavascript.cpp"
  append(L".DeferredEvent(deferredEvent, null, begin, end);\n");
  append(L"  };");
                                                            #line 719 "PrintJavascript.cpp.template"
                                                                }

                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1031 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.getDeferredCode = function() {return deferredCode};");
                                                            #line 725 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1036 "PrintJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  this.open = function(initialState");
                                                            #line 728 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1043 "PrintJavascript.cpp"
  append(L", eh");
                                                            #line 730 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1047 "PrintJavascript.cpp"
  append(L", t)\n");
  append(L"  {\n");
  append(L"    accepted = false;\n");
  append(L"    target = t;");
                                                            #line 734 "PrintJavascript.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1055 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    eventCount = 0;");
                                                            #line 737 "PrintJavascript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1062 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    if (eh != null)\n");
  append(L"    {\n");
  append(L"      eh.reset(input);\n");
  append(L"    }\n");
  append(L"    eventHandler = eh;\n");
  append(L"    deferredEvent = null;");
                                                            #line 746 "PrintJavascript.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 1074 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    deferredCode = null;");
                                                            #line 750 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1079 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    stack = new ");
                                                            #line 752 "PrintJavascript.cpp.template"
                                                              print(className.c_str());
                                                            #line 1084 "PrintJavascript.cpp"
  append(L".StackNode(-1, ");
                                                            #line 753 "PrintJavascript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1089 "PrintJavascript.cpp"
  append(L"0, ");
                                                            #line 755 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1093 "PrintJavascript.cpp"
  append(L"e0, null);\n");
  append(L"    state = initialState;\n");
  append(L"    action = predict(initialState);\n");
  append(L"    bw = e0;\n");
  append(L"    bs = e0;");
                                                            #line 760 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1102 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    es = e0;");
                                                            #line 763 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1107 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    threads = new ");
                                                            #line 765 "PrintJavascript.cpp.template"
                                                              print(className.c_str());
                                                            #line 1112 "PrintJavascript.cpp"
  append(L".Heap();\n");
  append(L"    threads.offer(this);\n");
  append(L"    return threads;\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.copy = function(other, a)\n");
  append(L"  {\n");
  append(L"    action = a;\n");
  append(L"    accepted = other.getAccepted();\n");
  append(L"    threads = other.getThreads();\n");
  append(L"    state = other.getState();\n");
  append(L"    stack = other.getStack();\n");
  append(L"    end = other.getEnd();\n");
  append(L"    target = other.getTarget();\n");
  append(L"    bs = other.getBs();\n");
  append(L"    bw = other.getBw();");
                                                            #line 781 "PrintJavascript.cpp.template"
                                                              if (resolvesAmbiguity)
                                                              {
                                                            #line 1132 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    eventCount = other.getEventCount();");
                                                            #line 784 "PrintJavascript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1139 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    es = other.getEs();\n");
  append(L"    eventHandler = other.getEventHandler();\n");
  append(L"    deferredEvent = other.getDeferredEvent();");
                                                            #line 790 "PrintJavascript.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1148 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    deferredCode = other.getDeferredCode();");
                                                            #line 794 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1153 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    id = ++maxId;\n");
  append(L"    b0 = other.getB0();\n");
  append(L"    e0 = other.getE0();\n");
  append(L"    l1 = other.getL1();\n");
  append(L"    b1 = other.getB1();\n");
  append(L"    e1 = other.getE1();\n");
  append(L"    return this;\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.compareTo = function(other)\n");
  append(L"  {\n");
  append(L"    if (accepted != other.getAccepted())\n");
  append(L"      return accepted ? 1 : -1;\n");
  append(L"    var comp = e0 - other.getE0();\n");
  append(L"    return comp == 0 ? id - other.getId() : comp;\n");
  append(L"  };\n");
  append(L"\n");
  append(L"  this.equals = function(other)\n");
  append(L"  {\n");
  append(L"    if (accepted != other.getAccepted()) return false;\n");
  append(L"    if (b1 != other.getB1()) return false;\n");
  append(L"    if (e1 != other.getE1()) return false;\n");
  append(L"    if (l1 != other.getL1()) return false;\n");
  append(L"    if (state != other.getState()) return false;\n");
  append(L"    if (action != other.getAction()) return false;\n");
  append(L"    if (! stack.equals(other.getStack())) return false;\n");
  append(L"    return true;\n");
  append(L"  };\n");
                                                            #line 824 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1186 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.release = function()\n");
  append(L"  {\n");
  append(L"    if (deferredEvent != null)\n");
  append(L"    {\n");
  append(L"      deferredEvent.release(eventHandler);\n");
  append(L"      deferredEvent = null;\n");
  append(L"    }\n");
  append(L"  };\n");
                                                            #line 835 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1198 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.parse = function()\n");
  append(L"  {");
                                                            #line 838 "PrintJavascript.cpp.template"
                                                              increaseIndent();
                                                            }

                                                            void PrintJavascript::openMethod(const wchar_t *type,
                                                                                             const wchar_t *prefix,
                                                                                             const wchar_t *name,
                                                                                             const wchar_t *args,
                                                                                             bool constant,
                                                                                             const wchar_t *clazz)
                                                            {
                                                              if (isPublic)
                                                              {
                                                            #line 1215 "PrintJavascript.cpp"
  append(L"\n");
  append(L"this.");
                                                            #line 851 "PrintJavascript.cpp.template"
                                                                print(name);
                                                            #line 1220 "PrintJavascript.cpp"
  append(L" = function");
                                                            #line 852 "PrintJavascript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1226 "PrintJavascript.cpp"
  append(L"\n");
  append(L"function ");
                                                            #line 856 "PrintJavascript.cpp.template"
                                                                print(name);
                                                              }
                                                            #line 1232 "PrintJavascript.cpp"
  append(L"(");
                                                            #line 858 "PrintJavascript.cpp.template"
                                                              printArgNamesOnly(args);
                                                            #line 1236 "PrintJavascript.cpp"
  append(L")");
                                                            #line 859 "PrintJavascript.cpp.template"
                                                            }

                                                            void PrintJavascript::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                            #line 1245 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  function lookaheadString()\n");
  append(L"  {\n");
  append(L"    var result = \"\";\n");
  append(L"    if (l1 > 0)\n");
  append(L"    {\n");
  append(L"      result += ");
                                                            #line 871 "PrintJavascript.cpp.template"
                                                                print(staticPrefix());
                                                            #line 1255 "PrintJavascript.cpp"
  append(L"TOKEN[l1];");
                                                            #line 872 "PrintJavascript.cpp.template"
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                            #line 1260 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      if (l");
                                                            #line 875 "PrintJavascript.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1265 "PrintJavascript.cpp"
  append(L" > 0)\n");
  append(L"      {\n");
  append(L"        result += \" \" + ");
                                                            #line 878 "PrintJavascript.cpp.template"
                                                                  print(staticPrefix());
                                                            #line 1271 "PrintJavascript.cpp"
  append(L"TOKEN[l");
                                                            #line 879 "PrintJavascript.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1275 "PrintJavascript.cpp"
  append(L"];");
                                                            #line 880 "PrintJavascript.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 1283 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 886 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1288 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    return result;\n");
  append(L"  }\n");
                                                            #line 891 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1295 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var ");
                                                            #line 893 "PrintJavascript.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 1303 "PrintJavascript.cpp"
  append(L"lk,");
                                                            #line 897 "PrintJavascript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1309 "PrintJavascript.cpp"
  append(L"   ");
                                                            #line 900 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1313 "PrintJavascript.cpp"
  append(L" b0, e0;");
                                                            #line 901 "PrintJavascript.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 1320 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var l");
                                                            #line 906 "PrintJavascript.cpp.template"
                                                                print(asString);
                                                            #line 1325 "PrintJavascript.cpp"
  append(L", b");
                                                            #line 907 "PrintJavascript.cpp.template"
                                                                print(asString);
                                                            #line 1329 "PrintJavascript.cpp"
  append(L", e");
                                                            #line 908 "PrintJavascript.cpp.template"
                                                                print(asString);
                                                            #line 1333 "PrintJavascript.cpp"
  append(L";");
                                                            #line 909 "PrintJavascript.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 1339 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var bx, ex, sx, lx, tx;");
                                                            #line 913 "PrintJavascript.cpp.template"
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                            #line 1346 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var iStack = [];\n");
  append(L"  var top = -1;");
                                                            #line 918 "PrintJavascript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1354 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var eventHandler;");
                                                            #line 922 "PrintJavascript.cpp.template"
                                                              }
                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 1362 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var memo;");
                                                            #line 927 "PrintJavascript.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 1368 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var viable;");
                                                            #line 930 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1373 "PrintJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  function memoize(i, e, v)\n");
  append(L"  {\n");
  append(L"    memo[(e << ");
                                                            #line 935 "PrintJavascript.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1381 "PrintJavascript.cpp"
  append(L") + i] = v;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  function memoized(i, e)\n");
  append(L"  {\n");
  append(L"    var v = memo[(e << ");
                                                            #line 941 "PrintJavascript.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1390 "PrintJavascript.cpp"
  append(L") + i];\n");
  append(L"    return typeof v != \"undefined\" ? v : 0;\n");
  append(L"  }");
                                                            #line 944 "PrintJavascript.cpp.template"
                                                              }
                                                              if (useGlr)
                                                              {
                                                                decreaseIndent();
                                                              }
                                                            }

                                                            void PrintJavascript::printPlatformSpecific()
                                                            {
                                                            #line 1404 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  if (typeof process !== \"undefined\")   // assume node.js\n");
  append(L"  {\n");
  append(L"    var command = \"node\";\n");
  append(L"    var arguments = process.argv.slice(2);\n");
  append(L"    var log = function(string) {process.stdout.write(string);};\n");
  append(L"    var fs = require(\"fs\");\n");
  append(L"    var readTextFile = fs.readFileSync;");
                                                            #line 960 "PrintJavascript.cpp.template"
                                                              if (performanceTest)
                                                              {
                                                            #line 1416 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    var readDir = fs.readdirSync;\n");
  append(L"    var isDirectory = function(filename) {return fs.statSync(filename).isDirectory();};");
                                                            #line 965 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1422 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  }\n");
  append(L"  else                                  // assume rhino or jrunscript\n");
  append(L"  {\n");
  append(L"    var arguments = function()\n");
  append(L"                    {\n");
  append(L"                      var strings = [];\n");
  append(L"                      for (var i = 0; i < args.length; ++i)\n");
  append(L"                      {\n");
  append(L"                        strings[i] = String(args[i]);\n");
  append(L"                      }\n");
  append(L"                      return strings;\n");
  append(L"                    }();");
                                                            #line 978 "PrintJavascript.cpp.template"
                                                              if (performanceTest)
                                                              {
                                                            #line 1439 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    var readDir = function(dirName)\n");
  append(L"                  {\n");
  append(L"                    var files = new java.io.File(dirName).listFiles();\n");
  append(L"                    var names = [];\n");
  append(L"                    for (var i = 0; i < files.length; ++i)\n");
  append(L"                    {\n");
  append(L"                      names[names.length] = files[i].getName();\n");
  append(L"                    }\n");
  append(L"                    return names;\n");
  append(L"                  };\n");
  append(L"    var isDirectory = function(filename) {return new java.io.File(filename).isDirectory();};");
                                                            #line 992 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1454 "PrintJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    if (typeof println == \"undefined\")  // assume rhino\n");
  append(L"    {\n");
  append(L"      var command = \"java -jar js.jar\";\n");
  append(L"      var log = function(string) {java.lang.System.out.write(java.lang.String(string).getBytes(\"utf-8\"));};\n");
  append(L"      var readTextFile = readFile;\n");
  append(L"    }\n");
  append(L"    else                                // assume jrunscript\n");
  append(L"    {\n");
  append(L"      var command = \"jrunscript\";\n");
  append(L"      var log = function(string) {java.lang.System.out.print(string);};\n");
  append(L"      var readTextFile = function(filename, encoding)\n");
  append(L"                         {\n");
  append(L"                           var file = new java.io.File(filename);\n");
  append(L"                           var buffer = javaByteArray(file.length());\n");
  append(L"                           new java.io.FileInputStream(file).read(buffer);\n");
  append(L"                           return String(new java.lang.String(buffer, encoding));\n");
  append(L"                         };\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1014 "PrintJavascript.cpp.template"
                                                            }

                                                            void PrintJavascript::printFileProcessor()
                                                            {
                                                            #line 1481 "PrintJavascript.cpp"
  append(L"\n");
  append(L"// performance test main program for use with node.js, rhino, or jrunscript\n");
  append(L"\n");
  append(L"function main(args)\n");
  append(L"{");
                                                            #line 1022 "PrintJavascript.cpp.template"
                                                              printPlatformSpecific();
                                                            #line 1489 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var quiet = false;\n");
  append(L"  var parsed = 0;\n");
  append(L"  var errorCount = 0;\n");
  append(L"  var parsers = [];\n");
  append(L"\n");
  append(L"  function ParseJob(s, i)\n");
  append(L"  {\n");
  append(L"    this.name = s;\n");
  append(L"    this.input = i;");
                                                            #line 1032 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1503 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    this.contentCounter = new ContentCounter();");
                                                            #line 1035 "PrintJavascript.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1509 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    this.parseTreeBuilder = new ");
                                                            #line 1038 "PrintJavascript.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1514 "PrintJavascript.cpp"
  append(L".ParseTreeBuilder();");
                                                            #line 1039 "PrintJavascript.cpp.template"
                                                                }
                                                              }
                                                            #line 1519 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    this.parser = new ");
                                                            #line 1042 "PrintJavascript.cpp.template"
                                                              print(className.c_str());
                                                            #line 1524 "PrintJavascript.cpp"
  append(L"(i");
                                                            #line 1043 "PrintJavascript.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1529 "PrintJavascript.cpp"
  append(L", null");
                                                            #line 1045 "PrintJavascript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1537 "PrintJavascript.cpp"
  append(L", this.parseTreeBuilder");
                                                            #line 1050 "PrintJavascript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1543 "PrintJavascript.cpp"
  append(L", this.contentCounter");
                                                            #line 1053 "PrintJavascript.cpp.template"
                                                                }
                                                              }
                                                            #line 1548 "PrintJavascript.cpp"
  append(L");\n");
  append(L"  }\n");
                                                            #line 1057 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1554 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  function ContentCounter()\n");
  append(L"  {\n");
  append(L"    var length = 0;\n");
  append(L"    this.getLength = function() {return length;};\n");
  append(L"    this.reset = function(string) {length = 0;};\n");
  append(L"    this.startNonterminal = function(name, begin) {};\n");
  append(L"    this.endNonterminal = function(name, end) {};\n");
  append(L"    this.terminal = function(name, begin, end) {length += end - begin;};\n");
  append(L"    this.whitespace = function(begin, end) {length += end - begin;};\n");
  append(L"  }\n");
                                                            #line 1070 "PrintJavascript.cpp.template"
                                                              }
                                                              printReadMethod();
                                                            #line 1569 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  function findFiles(f, filter)\n");
  append(L"  {\n");
  append(L"    if (isDirectory(f))\n");
  append(L"    {\n");
  append(L"      var files = readDir(f);\n");
  append(L"      for (var i = 0; i < files.length; ++i)\n");
  append(L"      {\n");
  append(L"        findFiles(f + \"/\" + files[i], filter);\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"    else if (f.substring(f.length - filter.length).toLowerCase() == filter.toLowerCase())\n");
  append(L"    {\n");
  append(L"      collectInput(f, read(f));\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  function collectInput(name, content)\n");
  append(L"  {\n");
  append(L"    if (! quiet) log(\"loading \" + name + \"\\n\");\n");
  append(L"    parsers[parsers.length] = new ParseJob(name, content);\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  if (arguments.length == 0)\n");
  append(L"  {\n");
  append(L"    log(\"Usage: \" + command + \" ");
                                                            #line 1097 "PrintJavascript.cpp.template"
                                                              print(className.c_str());
                                                            #line 1598 "PrintJavascript.cpp"
  append(L".js [-q] [-r N] [-t N] ENDING...\\n\");\n");
  append(L"    log(\"\\n\");\n");
  append(L"    log(\"  parse all files that have names ending with ENDING, in current dir and below,\\n\");\n");
  append(L"    log(\"  and display performance summary.\\n\");\n");
  append(L"    log(\"\\n\");\n");
  append(L"    log(\"  -q     do not show file names\\n\");\n");
  append(L"    log(\"  -r N   repeat N times\\n\");\n");
  append(L"    log(\"  -t N   repeat until N seconds have elapsed\\n\");\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {\n");
  append(L"    var repeat = 1;\n");
  append(L"    var timeout = 0;\n");
  append(L"    var i;\n");
  append(L"    for (i = 0; i < arguments.length; ++i)\n");
  append(L"    {\n");
  append(L"      if (arguments[i] == \"-q\")\n");
  append(L"      {\n");
  append(L"        quiet = true;\n");
  append(L"      }\n");
  append(L"      else if (arguments[i] == \"-r\")\n");
  append(L"      {\n");
  append(L"        repeat = parseInt(arguments[++i]);\n");
  append(L"        timeout = 0;\n");
  append(L"      }\n");
  append(L"      else if (arguments[i] == \"-t\")\n");
  append(L"      {\n");
  append(L"        repeat = 0;\n");
  append(L"        timeout = 1000 * parseInt(arguments[++i]);\n");
  append(L"      }\n");
  append(L"      else if (arguments[i].substring(0, 1) !== \"-\")\n");
  append(L"      {\n");
  append(L"        break;\n");
  append(L"      }\n");
  append(L"      else\n");
  append(L"      {\n");
  append(L"        throw \"invalid option: \" + arguments[i];\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    var start = Date.now();\n");
  append(L"\n");
  append(L"    for (; i < arguments.length; ++i)\n");
  append(L"    {\n");
  append(L"      findFiles(\".\", arguments[i]);\n");
  append(L"    }\n");
  append(L"\n");
  append(L"    if (parsers.length != 0)\n");
  append(L"    {\n");
  append(L"      var msec = Date.now() - start;\n");
  append(L"\n");
  append(L"      if (! quiet) log(\"\\n\");\n");
  append(L"      log(\"loaded \" + parsers.length + \" file\" +\n");
  append(L"          (parsers.length == 1 ? \"\" : \"s\") + \" in \" +\n");
  append(L"          msec + \" msec\\n\");\n");
  append(L"      if (! quiet) log(\"\\n\");\n");
  append(L"\n");
  append(L"      start = Date.now();\n");
  append(L"      for (i = 0; ; ++i)\n");
  append(L"      {\n");
  append(L"        if (repeat != 0 && i >= repeat) break;\n");
  append(L"        if (timeout != 0 && Date.now() - start >= timeout) break;\n");
  append(L"\n");
  append(L"        for (var j = 0; j < parsers.length; ++j)\n");
  append(L"        {\n");
  append(L"          var job = parsers[j];\n");
  append(L"          if (job.parser != null)\n");
  append(L"          {\n");
  append(L"            try\n");
  append(L"            {\n");
  append(L"              if (! quiet) log(\"parsing \" + job.name);\n");
  append(L"              job.parser.reset(0, 0, 0);\n");
  append(L"              job.parser.");
                                                            #line 1170 "PrintJavascript.cpp.template"
                                                              print(methodPrefixParse);
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1675 "PrintJavascript.cpp"
  append(L"();\n");
  append(L"              if (! quiet) log(\"\\n\");");
                                                            #line 1173 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1683 "PrintJavascript.cpp"
  append(L"\n");
  append(L"              job.parseTreeBuilder.serialize(job.contentCounter);");
                                                            #line 1179 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1688 "PrintJavascript.cpp"
  append(L"\n");
  append(L"              if (job.contentCounter.getLength() != job.input.length)\n");
  append(L"              {\n");
  append(L"                throw \"content counter saw \" + job.contentCounter.getLength() +\n");
  append(L"                      \", but input length is \" + job.input.length;\n");
  append(L"              }");
                                                            #line 1185 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1697 "PrintJavascript.cpp"
  append(L"\n");
  append(L"              parsed += job.input.length;\n");
  append(L"            }\n");
  append(L"            catch (pe)\n");
  append(L"            {\n");
  append(L"              if (pe instanceof job.parser.ParseException)\n");
  append(L"              {\n");
  append(L"                ++errorCount;\n");
  append(L"                log((quiet ? (\"parsing \" + job.name) : \"\") +\n");
  append(L"                    \": error: \" + job.parser.getErrorMessage(pe) + \"\\n\");\n");
  append(L"                job.parser = null;\n");
  append(L"              }\n");
  append(L"              else\n");
  append(L"              {\n");
  append(L"                throw pe;\n");
  append(L"              }\n");
  append(L"            }\n");
  append(L"          }\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"\n");
  append(L"      msec = Date.now() - start;\n");
  append(L"      var sec = msec / 1000e0;\n");
  append(L"      var perSec = msec == 0\n");
  append(L"                   ? \"\"\n");
  append(L"                   : parsed / sec > 1024 * 1024\n");
  append(L"                   ? (\" (\"  + (parsed / 1024 / 1024 /sec).toFixed(2) + \" MB/sec)\")\n");
  append(L"                   : (\" (\"  + (parsed / 1024        /sec).toFixed(2) + \" KB/sec)\");\n");
  append(L"\n");
  append(L"      if (! quiet) log(\"\\n\");\n");
  append(L"      log(\"parsed \" + parsed + \" byte\" + (parsed == 1 ? \"\" : \"s\") +\n");
  append(L"          \" in \" + msec + \" msec\" + perSec + \"\\n\");\n");
  append(L"      log(errorCount + \" error\" + (errorCount == 1 ? \"\" : \"s\") + \"\\n\");\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"main(arguments);\n");
                                                            #line 1224 "PrintJavascript.cpp.template"
                                                            }

                                                            void PrintJavascript::printReadMethod()
                                                            {
                                                            #line 1741 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  function read(input)\n");
  append(L"  {\n");
  append(L"    if (/");
  append(L"^");
  append(L"{.*}$/.test(input))\n");
  append(L"    {\n");
  append(L"      return input.substring(1, input.length - 1);\n");
  append(L"    }\n");
  append(L"    else\n");
  append(L"    {\n");
  append(L"      var content = readTextFile(input, \"utf-8\");\n");
  append(L"      return content.length > 0 && content.charCodeAt(0) == 0xFEFF\n");
  append(L"           ? content.substring(1)\n");
  append(L"           : content;\n");
  append(L"    }\n");
  append(L"  }\n");
                                                            #line 1243 "PrintJavascript.cpp.template"
                                                            }

                                                            void PrintJavascript::close(Grammar *node)
                                                            {
                                                              if (lexerInstanceCode == 0 || lexerStaticCode == 0)
                                                              {
                                                                internalerr();
                                                              }

                                                              print(L"\n");
                                                              print(lexerInstanceCode);
                                                            #line 1771 "PrintJavascript.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 1256 "PrintJavascript.cpp.template"
                                                              if (useGlr)
                                                              {
                                                                openStackNode();
                                                                printCountMethod();
                                                                closeStackNode();
                                                              }
                                                              printXmlSerializer();
                                                              print(lexerStaticCode);
                                                              visitEpilog();

                                                              if (main)
                                                              {
                                                            #line 1787 "PrintJavascript.cpp"
  append(L"\n");
  append(L"// main program for use with node.js, rhino, or jrunscript\n");
  append(L"\n");
  append(L"function main(args)\n");
  append(L"{");
                                                            #line 1272 "PrintJavascript.cpp.template"
                                                                printPlatformSpecific();
                                                                printReadMethod();
                                                            #line 1796 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  if (arguments.length == 0)\n");
  append(L"  {\n");
  append(L"    log(\"Usage: \" + command + \" ");
                                                            #line 1278 "PrintJavascript.cpp.template"
                                                                print(className.c_str());
                                                            #line 1803 "PrintJavascript.cpp"
  append(L".js ");
                                                            #line 1279 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1808 "PrintJavascript.cpp"
  append(L"[-i] ");
                                                            #line 1281 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1812 "PrintJavascript.cpp"
  append(L"INPUT...\\n\");\n");
  append(L"    log(\"\\n\");\n");
  append(L"    log(\"  parse INPUT, which is either a filename or literal text enclosed in curly braces\\n\");");
                                                            #line 1285 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1819 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    log(\"\\n\");\n");
  append(L"    log(\"  Option:\\n\");\n");
  append(L"    log(\"    -i     indented parse tree\\n\");");
                                                            #line 1290 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1826 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {\n");
  append(L"    var indent = false;\n");
  append(L"    for (var i = 0; i < arguments.length; ++i)\n");
  append(L"    {");
                                                            #line 1297 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1837 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      if (arguments[i] === \"-i\")\n");
  append(L"      {\n");
  append(L"        indent = true;\n");
  append(L"        continue;\n");
  append(L"      }");
                                                            #line 1304 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1846 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      var input = read(String(arguments[i]));");
                                                            #line 1306 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1852 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      var s = new ");
                                                            #line 1309 "PrintJavascript.cpp.template"
                                                                  print(staticPrefix());
                                                            #line 1857 "PrintJavascript.cpp"
  append(L"XmlSerializer(log, indent);");
                                                            #line 1310 "PrintJavascript.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 1862 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      var b = new ");
                                                            #line 1313 "PrintJavascript.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 1867 "PrintJavascript.cpp"
  append(L"ParseTreeBuilder();");
                                                            #line 1314 "PrintJavascript.cpp.template"
                                                                  }
                                                                }
                                                            #line 1872 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      var parser = new ");
                                                            #line 1317 "PrintJavascript.cpp.template"
                                                                print(className.c_str());
                                                            #line 1877 "PrintJavascript.cpp"
  append(L"(input");
                                                            #line 1318 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                                  if (isLrParser)
                                                                  {
                                                            #line 1884 "PrintJavascript.cpp"
  append(L", b");
                                                            #line 1322 "PrintJavascript.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1890 "PrintJavascript.cpp"
  append(L", s");
                                                            #line 1325 "PrintJavascript.cpp.template"
                                                                  }
                                                                }
                                                            #line 1895 "PrintJavascript.cpp"
  append(L");\n");
  append(L"      try\n");
  append(L"      {");
                                                            #line 1329 "PrintJavascript.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1902 "PrintJavascript.cpp"
  append(L"\n");
  append(L"        parser.writeTrace(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\\n<trace>\\n\");");
                                                            #line 1333 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1907 "PrintJavascript.cpp"
  append(L"\n");
  append(L"        parser.");
                                                            #line 1335 "PrintJavascript.cpp.template"
                                                                print(methodPrefixParse);
                                                                print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1913 "PrintJavascript.cpp"
  append(L"();");
                                                            #line 1337 "PrintJavascript.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1918 "PrintJavascript.cpp"
  append(L"\n");
  append(L"        parser.writeTrace(\"</trace>\\n\");\n");
  append(L"        parser.flushTrace();");
                                                            #line 1341 "PrintJavascript.cpp.template"
                                                                }
                                                                if (tree && isLrParser)
                                                                {
                                                            #line 1926 "PrintJavascript.cpp"
  append(L"\n");
  append(L"        b.serialize(s);");
                                                            #line 1345 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1931 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      }\n");
  append(L"      catch (pe)\n");
  append(L"      {\n");
  append(L"        if (! (pe instanceof parser.ParseException))\n");
  append(L"        {\n");
  append(L"          throw pe;\n");
  append(L"        }\n");
  append(L"        else\n");
  append(L"        {");
                                                            #line 1355 "PrintJavascript.cpp.template"
                                                                if (rejectsAmbiguity() && tree)
                                                                {
                                                            #line 1945 "PrintJavascript.cpp"
  append(L"\n");
  append(L"          if (pe.isAmbiguousInput())\n");
  append(L"          {\n");
  append(L"            pe.serialize(s);\n");
  append(L"            log(\"\\n\");\n");
  append(L"          }");
                                                            #line 1362 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1954 "PrintJavascript.cpp"
  append(L"\n");
  append(L"          throw parser.getErrorMessage(pe);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"main(arguments);\n");
                                                            #line 1372 "PrintJavascript.cpp.template"
                                                              }
                                                              if (performanceTest)
                                                              {
                                                                printFileProcessor();
                                                              }
                                                            }

// End
