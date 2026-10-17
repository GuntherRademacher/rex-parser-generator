// This file was generated on Sat Oct 17, 2026 11:26 (UTC+02) by REx v6.3-SNAPSHOT which is Copyright (c) 1979-2026 by Gunther Rademacher <grd@gmx.net>
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
                                                            #line 26 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 51 "PrintJavascript.cpp"
  append(L");\n");
                                                            #line 28 "PrintJavascript.cpp.template"
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
                                                            #line 38 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 69 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    var ambiguousInput = false;");
                                                            #line 41 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 75 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    var ambiguityDescriptor;");
                                                            #line 44 "PrintJavascript.cpp.template"
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
                                                            #line 53 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 93 "PrintJavascript.cpp"
  append(L"ambiguousInput");
                                                            #line 56 "PrintJavascript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 99 "PrintJavascript.cpp"
  append(L"false");
                                                            #line 59 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 103 "PrintJavascript.cpp"
  append(L";};\n");
                                                            #line 61 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 108 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    this.setAmbiguousInput = function(a)\n");
  append(L"    {\n");
  append(L"      ambiguousInput = true;\n");
  append(L"      ambiguityDescriptor = a;\n");
  append(L"    };\n");
                                                            #line 69 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 117 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    this.getMessage = function()\n");
  append(L"    {\n");
  append(L"      return ");
                                                            #line 73 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 125 "PrintJavascript.cpp"
  append(L"ambiguousInput\n");
  append(L"           ? \"ambiguous input\"\n");
  append(L"           : ");
                                                            #line 77 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 131 "PrintJavascript.cpp"
  append(L"offending < 0\n");
  append(L"           ? \"lexical analysis failed\"\n");
  append(L"           : \"syntax error\";\n");
  append(L"    };");
                                                            #line 81 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 139 "PrintJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"    this.serialize = function(eventHandler)\n");
  append(L"    {\n");
  append(L"      ambiguityDescriptor.serialize(eventHandler);\n");
  append(L"    };");
                                                            #line 88 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 148 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  };\n");
                                                            #line 91 "PrintJavascript.cpp.template"
                                                            }

                                                            void PrintJavascript::printFlush(int i, bool withinThread)
                                                            {
                                                              increaseIndent(i);
                                                              if (trace)
                                                              {
                                                            #line 159 "PrintJavascript.cpp"
  append(L"\n");
  append(L"flushTrace();");
                                                            #line 99 "PrintJavascript.cpp.template"
                                                              }
                                                              decreaseIndent(i);
                                                            }

                                                            void PrintJavascript::openStackNode()
                                                            {
                                                            #line 169 "PrintJavascript.cpp"
  append(L"\n");
                                                            #line 106 "PrintJavascript.cpp.template"
                                                              print(className.c_str());
                                                            #line 173 "PrintJavascript.cpp"
  append(L".StackNode = function(state, ");
                                                            #line 107 "PrintJavascript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 178 "PrintJavascript.cpp"
  append(L"code, ");
                                                            #line 109 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 182 "PrintJavascript.cpp"
  append(L"pos, link)\n");
  append(L"{\n");
  append(L"  this.state = state;");
                                                            #line 112 "PrintJavascript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 189 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.code = code;");
                                                            #line 115 "PrintJavascript.cpp.template"
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
                                                            #line 127 "PrintJavascript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 210 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      if (lhs.code != rhs.code) return false;");
                                                            #line 130 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 215 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      if (lhs.pos != rhs.pos) return false;\n");
  append(L"      lhs = lhs.link;\n");
  append(L"      rhs = rhs.link;\n");
  append(L"    }\n");
  append(L"    return lhs == rhs;\n");
  append(L"  };\n");
                                                            #line 138 "PrintJavascript.cpp.template"
                                                              increaseIndent();
                                                            }

                                                            void PrintJavascript::closeStackNode()
                                                            {
                                                              decreaseIndent();
                                                            #line 230 "PrintJavascript.cpp"
  append(L"\n");
  append(L"};\n");
                                                            #line 146 "PrintJavascript.cpp.template"
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
                                                            #line 156 "PrintJavascript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 249 "PrintJavascript.cpp"
  append(L"\n");
                                                            #line 160 "PrintJavascript.cpp.template"
                                                                print(className.c_str());
                                                            #line 253 "PrintJavascript.cpp"
  append(L".DeferredEvent = function(link, name, begin, end, count)\n");
  append(L"{\n");
  append(L"  this.link = link;\n");
  append(L"\n");
  append(L"  this.execute = function(eventHandler)\n");
  append(L"  {\n");
  append(L"    ");
                                                            #line 167 "PrintJavascript.cpp.template"
                                                                if (minimalAmbiguity)
                                                                {
                                                            #line 264 "PrintJavascript.cpp"
  append(L"if (name == null)\n");
  append(L"    {\n");
  append(L"      eventHandler.ambiguity(begin, end);\n");
  append(L"    }\n");
  append(L"    else ");
                                                            #line 173 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 272 "PrintJavascript.cpp"
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
  append(L"      current.execute(eventHandler);\n");
  append(L"      current = current.link;\n");
  append(L"    }\n");
  append(L"    while (current != null);\n");
  append(L"  };\n");
                                                            #line 203 "PrintJavascript.cpp.template"
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 305 "PrintJavascript.cpp"
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
                                                            #line 218 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 321 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.toString = function()\n");
  append(L"  {\n");
  append(L"    if (count == null)\n");
  append(L"      return \"terminal(\" + name + \", \" + begin + \", \" + end + \")\";\n");
  append(L"    else\n");
  append(L"      return \"nonterminal(\" + name + \", \" + begin + \", \" + end + \", \" + count + \")\";\n");
  append(L"  };\n");
  append(L"};\n");
                                                            #line 228 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 333 "PrintJavascript.cpp"
  append(L"\n");
                                                            #line 230 "PrintJavascript.cpp.template"
                                                              print(className.c_str());
                                                            #line 337 "PrintJavascript.cpp"
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
                                                            #line 294 "PrintJavascript.cpp.template"
                                                            }

                                                            void PrintJavascript::printXmlSerializer()
                                                            {
                                                              if (tree)
                                                              {
                                                            #line 408 "PrintJavascript.cpp"
  append(L"\n");
                                                            #line 301 "PrintJavascript.cpp.template"
                                                                print(className.c_str());
                                                            #line 412 "PrintJavascript.cpp"
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
                                                            #line 400 "PrintJavascript.cpp.template"
                                                              }
                                                            }

                                                            void PrintJavascript::openThread()
                                                            {
                                                            #line 517 "PrintJavascript.cpp"
  append(L"\n");
  append(L"var PARSING = 0;\n");
  append(L"var ACCEPTED = 1;\n");
  append(L"var ERROR = 2;\n");
  append(L"\n");
  append(L"function parse(target, initialState, ");
                                                            #line 410 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 527 "PrintJavascript.cpp"
  append(L"eventHandler, ");
                                                            #line 413 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 531 "PrintJavascript.cpp"
  append(L"thread)\n");
  append(L"{\n");
  append(L"  var threads = thread.open(initialState");
                                                            #line 416 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 538 "PrintJavascript.cpp"
  append(L", eventHandler");
                                                            #line 418 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 542 "PrintJavascript.cpp"
  append(L", target);\n");
  append(L"  for (;;)\n");
  append(L"  {\n");
  append(L"    thread = threads.poll();\n");
  append(L"    if (thread.getAccepted())\n");
  append(L"    {");
                                                            #line 424 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 552 "PrintJavascript.cpp"
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
                                                            #line 440 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 570 "PrintJavascript.cpp"
  append(L", thread.getDeferredEvent(), other.getDeferredEvent()");
                                                            #line 443 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 574 "PrintJavascript.cpp"
  append(L");\n");
  append(L"      }");
                                                            #line 445 "PrintJavascript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 581 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      while (! threads.isEmpty())\n");
  append(L"      {\n");
  append(L"        var other = threads.poll();\n");
  append(L"        thread = thread.getE0() < other.getE0() ? other : resolve(thread, other);\n");
  append(L"      }");
                                                            #line 453 "PrintJavascript.cpp.template"
                                                              }
                                                              if (tree)
                                                               {
                                                            #line 592 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      thread.release();");
                                                            #line 457 "PrintJavascript.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 599 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 461 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 604 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      return thread;\n");
  append(L"    }\n");
  append(L"\n");
                                                            #line 466 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 612 "PrintJavascript.cpp"
  append(L"    if (! threads.isEmpty())\n");
  append(L"    {\n");
  append(L"      if (threads.peek().equals(thread))\n");
  append(L"      {\n");
  append(L"        rejectAmbiguity(thread.getStack().pos, thread.getE0()");
                                                            #line 473 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 621 "PrintJavascript.cpp"
  append(L", thread.getDeferredEvent(), threads.peek().getDeferredEvent()");
                                                            #line 476 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 625 "PrintJavascript.cpp"
  append(L");\n");
  append(L"      }\n");
  append(L"    }");
                                                            #line 479 "PrintJavascript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 633 "PrintJavascript.cpp"
  append(L"    while (! threads.isEmpty() && threads.peek().equals(thread))\n");
  append(L"    {\n");
  append(L"      thread = resolve(thread, threads.poll());\n");
  append(L"    }");
                                                            #line 485 "PrintJavascript.cpp.template"
                                                              }
                                                              if (tree || hasCustomCode)
                                                              {
                                                                if (rejectsAmbiguity())
                                                                {
                                                            #line 644 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    else\n");
  append(L"    {");
                                                            #line 492 "PrintJavascript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 652 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    if (threads.isEmpty())\n");
  append(L"    {");
                                                            #line 497 "PrintJavascript.cpp.template"
                                                                }
                                                                if (tree)
                                                                {
                                                            #line 660 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      thread.release();");
                                                            #line 501 "PrintJavascript.cpp.template"
                                                                }
                                                                if (hasCustomCode)
                                                                {
                                                            #line 667 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      thread.executeDeferredCode();");
                                                            #line 505 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 672 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    }");
                                                            #line 507 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 677 "PrintJavascript.cpp"
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
                                                            #line 525 "PrintJavascript.cpp.template"
                                                              print(staticPrefix());
                                                            #line 698 "PrintJavascript.cpp"
  append(L"TOKENSET[thread.getState()] + 1,\n");
  append(L"                                          thread.getL1(),\n");
  append(L"                                          -1\n");
  append(L"                                         );\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
                                                            #line 533 "PrintJavascript.cpp.template"
                                                              if (rejectsAmbiguity())
                                                              {
                                                            #line 709 "PrintJavascript.cpp"
  append(L"\n");
  append(L"function rejectAmbiguity(begin, end");
                                                            #line 536 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 715 "PrintJavascript.cpp"
  append(L", first, second");
                                                            #line 538 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 719 "PrintJavascript.cpp"
  append(L")\n");
  append(L"{");
                                                            #line 540 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 725 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var treeBuilder = new ");
                                                            #line 543 "PrintJavascript.cpp.template"
                                                                  print(className.c_str());
                                                            #line 730 "PrintJavascript.cpp"
  append(L".ParseTreeBuilder();\n");
  append(L"  treeBuilder.reset(input);\n");
  append(L"  second.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, treeBuilder.getTop() + 1);\n");
  append(L"  var secondTree = treeBuilder.pop(1)[0];\n");
  append(L"  first.show(treeBuilder);\n");
  append(L"  treeBuilder.nonterminal(\"ALTERNATIVE\", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, treeBuilder.getTop() + 1);\n");
  append(L"  treeBuilder.push(secondTree);\n");
  append(L"  treeBuilder.nonterminal(\"AMBIGUOUS\", treeBuilder.getStack()[0].begin, treeBuilder.getStack()[treeBuilder.getTop()].end, 2);");
                                                            #line 553 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 742 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var exception = new thisParser.ParseException(begin, end, -1, -1, -1);\n");
  append(L"  exception.setAmbiguousInput(");
                                                            #line 556 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 749 "PrintJavascript.cpp"
  append(L"treeBuilder");
                                                            #line 558 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 753 "PrintJavascript.cpp"
  append(L");\n");
  append(L"  throw exception;\n");
  append(L"}");
                                                            #line 561 "PrintJavascript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 761 "PrintJavascript.cpp"
  append(L"\n");
  append(L"function resolve(thread, other)\n");
  append(L"{");
                                                            #line 566 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 768 "PrintJavascript.cpp"
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
                                                            #line 577 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 781 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  if (other.getEventCount() < thread.getEventCount())\n");
  append(L"    thread = other;");
                                                            #line 580 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 788 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  thread.addAmbiguity(begin, thread.getE0());");
                                                            #line 583 "PrintJavascript.cpp.template"
                                                                                                            }
                                                            #line 793 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  return thread;\n");
  append(L"}");
                                                            #line 586 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 799 "PrintJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"var thread;");
                                                            #line 589 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 806 "PrintJavascript.cpp"
  append(L"\n");
  append(L"var eventHandler;");
                                                            #line 592 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 811 "PrintJavascript.cpp"
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
                                                            #line 605 "PrintJavascript.cpp.template"
                                                              if (tree || useGlr)
                                                              {
                                                            #line 828 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var target;");
                                                            #line 608 "PrintJavascript.cpp.template"
                                                              }                                                if (tree)
                                                              {
                                                            #line 834 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var deferredEvent;");
                                                            #line 611 "PrintJavascript.cpp.template"
                                                                if (useGlr)
                                                                {
                                                            #line 840 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var es;");
                                                            #line 614 "PrintJavascript.cpp.template"
                                                                }
                                                              }
                                                              if (useGlr)
                                                              {
                                                            #line 848 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var bw, bs;");
                                                            #line 619 "PrintJavascript.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 855 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var deferredCode;");
                                                            #line 623 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 860 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var id;");
                                                            #line 625 "PrintJavascript.cpp.template"
                                                              if (minimalAmbiguity)
                                                              {
                                                            #line 866 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var eventCount;");
                                                            #line 628 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 871 "PrintJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  this.getId = function() {return id;};");
                                                            #line 631 "PrintJavascript.cpp.template"
                                                              if (minimalAmbiguity)
                                                              {
                                                            #line 878 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.getEventCount = function() {return eventCount;};");
                                                            #line 634 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 883 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.getAction = function() {return action;};\n");
  append(L"  this.getAccepted = function() {return accepted;};\n");
  append(L"  this.getThreads = function() {return threads};\n");
  append(L"  this.getState = function() {return state};\n");
  append(L"  this.getStack = function() {return stack};\n");
  append(L"  this.getEnd = function() {return end;};\n");
  append(L"  this.getB0 = function() {return b0;};\n");
  append(L"  this.getE0 = function() {return e0;};");
                                                            #line 643 "PrintJavascript.cpp.template"
                                                              for (size_t i = 1; i <= grammar->k; ++i)
                                                              {
                                                                const wchar_t *iString = format.toString<wchar_t>(i);
                                                            #line 897 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.getB");
                                                            #line 647 "PrintJavascript.cpp.template"
                                                                print(iString);
                                                            #line 902 "PrintJavascript.cpp"
  append(L" = function() {return b");
                                                            #line 648 "PrintJavascript.cpp.template"
                                                                print(iString);
                                                            #line 906 "PrintJavascript.cpp"
  append(L";};\n");
  append(L"  this.getE");
                                                            #line 650 "PrintJavascript.cpp.template"
                                                                print(iString);
                                                            #line 911 "PrintJavascript.cpp"
  append(L" = function() {return e");
                                                            #line 651 "PrintJavascript.cpp.template"
                                                                print(iString);
                                                            #line 915 "PrintJavascript.cpp"
  append(L";};\n");
  append(L"  this.getL");
                                                            #line 653 "PrintJavascript.cpp.template"
                                                                print(iString);
                                                            #line 920 "PrintJavascript.cpp"
  append(L" = function() {return l");
                                                            #line 654 "PrintJavascript.cpp.template"
                                                                print(iString);
                                                            #line 924 "PrintJavascript.cpp"
  append(L";};");
                                                            #line 655 "PrintJavascript.cpp.template"
                                                              }
                                                              if (complexWhitespace)
                                                              {
                                                            #line 930 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.setB1 = function(b) {b1 = b;};\n");
  append(L"  this.setE1 = function(e) {e1 = e;};\n");
  append(L"  this.setL1 = function(l) {l1 = l;};");
                                                            #line 661 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 937 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.getBs = function() {return bs;};\n");
  append(L"  this.getBw = function() {return bw;};\n");
  append(L"  this.getTarget = function() {return target;};");
                                                            #line 665 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 945 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.getEs = function() {return es;};\n");
  append(L"  this.getEventHandler = function() {return eventHandler;};\n");
  append(L"  this.getDeferredEvent = function() {return deferredEvent;};");
                                                            #line 670 "PrintJavascript.cpp.template"
                                                                if (minimalAmbiguity)
                                                                {
                                                            #line 953 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.addAmbiguity = function(begin, end)\n");
  append(L"  {\n");
  append(L"    if (eventHandler != null)\n");
  append(L"      deferredEvent = new ");
                                                            #line 676 "PrintJavascript.cpp.template"
                                                                  print(className.c_str());
                                                            #line 961 "PrintJavascript.cpp"
  append(L".DeferredEvent(deferredEvent, null, begin, end);\n");
  append(L"  };");
                                                            #line 678 "PrintJavascript.cpp.template"
                                                                }

                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 970 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.getDeferredCode = function() {return deferredCode};");
                                                            #line 684 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 975 "PrintJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  this.open = function(initialState");
                                                            #line 687 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 982 "PrintJavascript.cpp"
  append(L", eh");
                                                            #line 689 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 986 "PrintJavascript.cpp"
  append(L", t)\n");
  append(L"  {\n");
  append(L"    accepted = false;\n");
  append(L"    target = t;");
                                                            #line 693 "PrintJavascript.cpp.template"
                                                              if (minimalAmbiguity)
                                                              {
                                                            #line 994 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    eventCount = 0;");
                                                            #line 696 "PrintJavascript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1001 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    if (eh != null)\n");
  append(L"    {\n");
  append(L"      eh.reset(input);\n");
  append(L"    }\n");
  append(L"    eventHandler = eh;\n");
  append(L"    deferredEvent = null;");
                                                            #line 705 "PrintJavascript.cpp.template"
                                                              }
                                                              if (hasCustomCode && useGlr)
                                                              {
                                                            #line 1013 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    deferredCode = null;");
                                                            #line 709 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1018 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    stack = new ");
                                                            #line 711 "PrintJavascript.cpp.template"
                                                              print(className.c_str());
                                                            #line 1023 "PrintJavascript.cpp"
  append(L".StackNode(-1, ");
                                                            #line 712 "PrintJavascript.cpp.template"
                                                              if (grammar->states->hasLookback)
                                                              {
                                                            #line 1028 "PrintJavascript.cpp"
  append(L"0, ");
                                                            #line 714 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1032 "PrintJavascript.cpp"
  append(L"e0, null);\n");
  append(L"    state = initialState;\n");
  append(L"    action = predict(initialState);\n");
  append(L"    bw = e0;\n");
  append(L"    bs = e0;");
                                                            #line 719 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1041 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    es = e0;");
                                                            #line 722 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1046 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    threads = new ");
                                                            #line 724 "PrintJavascript.cpp.template"
                                                              print(className.c_str());
                                                            #line 1051 "PrintJavascript.cpp"
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
                                                            #line 740 "PrintJavascript.cpp.template"
                                                              if (minimalAmbiguity)
                                                              {
                                                            #line 1071 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    eventCount = other.getEventCount();");
                                                            #line 743 "PrintJavascript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1078 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    es = other.getEs();\n");
  append(L"    eventHandler = other.getEventHandler();\n");
  append(L"    deferredEvent = other.getDeferredEvent();");
                                                            #line 749 "PrintJavascript.cpp.template"
                                                              }
                                                              if (hasCustomCode)
                                                              {
                                                            #line 1087 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    deferredCode = other.getDeferredCode();");
                                                            #line 753 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1092 "PrintJavascript.cpp"
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
                                                            #line 783 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1125 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.release = function()\n");
  append(L"  {\n");
  append(L"    if (deferredEvent != null)\n");
  append(L"    {\n");
  append(L"      deferredEvent.release(eventHandler);\n");
  append(L"      deferredEvent = null;\n");
  append(L"    }\n");
  append(L"  };\n");
                                                            #line 794 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1137 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  this.parse = function()\n");
  append(L"  {");
                                                            #line 797 "PrintJavascript.cpp.template"
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
                                                            #line 1154 "PrintJavascript.cpp"
  append(L"\n");
  append(L"this.");
                                                            #line 810 "PrintJavascript.cpp.template"
                                                                print(name);
                                                            #line 1159 "PrintJavascript.cpp"
  append(L" = function");
                                                            #line 811 "PrintJavascript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1165 "PrintJavascript.cpp"
  append(L"\n");
  append(L"function ");
                                                            #line 815 "PrintJavascript.cpp.template"
                                                                print(name);
                                                              }
                                                            #line 1171 "PrintJavascript.cpp"
  append(L"(");
                                                            #line 817 "PrintJavascript.cpp.template"
                                                              printArgNamesOnly(args);
                                                            #line 1175 "PrintJavascript.cpp"
  append(L")");
                                                            #line 818 "PrintJavascript.cpp.template"
                                                            }

                                                            void PrintJavascript::privateVars()
                                                            {
                                                              if (trace)
                                                              {
                                                            #line 1184 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  function lookaheadString()\n");
  append(L"  {\n");
  append(L"    var result = \"\";\n");
  append(L"    if (l1 > 0)\n");
  append(L"    {\n");
  append(L"      result += ");
                                                            #line 830 "PrintJavascript.cpp.template"
                                                                print(staticPrefix());
                                                            #line 1194 "PrintJavascript.cpp"
  append(L"TOKEN[l1];");
                                                            #line 831 "PrintJavascript.cpp.template"
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                            #line 1199 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      if (l");
                                                            #line 834 "PrintJavascript.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1204 "PrintJavascript.cpp"
  append(L" > 0)\n");
  append(L"      {\n");
  append(L"        result += \" \" + ");
                                                            #line 837 "PrintJavascript.cpp.template"
                                                                  print(staticPrefix());
                                                            #line 1210 "PrintJavascript.cpp"
  append(L"TOKEN[l");
                                                            #line 838 "PrintJavascript.cpp.template"
                                                                  print(format.toString<wchar_t>(i));
                                                            #line 1214 "PrintJavascript.cpp"
  append(L"];");
                                                            #line 839 "PrintJavascript.cpp.template"
                                                                  increaseIndent();
                                                                }
                                                                for (size_t i = 2; i <= grammar->k; ++i)
                                                                {
                                                                  decreaseIndent();
                                                            #line 1222 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      }");
                                                            #line 845 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1227 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    }\n");
  append(L"    return result;\n");
  append(L"  }\n");
                                                            #line 850 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1234 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var ");
                                                            #line 852 "PrintJavascript.cpp.template"
                                                              if (! isLrParser && (grammar->k > 1 ||
                                                                                   memoization ||
                                                                                   ! grammar->decisionPoints.empty()))
                                                              {
                                                            #line 1242 "PrintJavascript.cpp"
  append(L"lk,");
                                                            #line 856 "PrintJavascript.cpp.template"
                                                              }
                                                              else
                                                              {
                                                            #line 1248 "PrintJavascript.cpp"
  append(L"   ");
                                                            #line 859 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1252 "PrintJavascript.cpp"
  append(L" b0, e0;");
                                                            #line 860 "PrintJavascript.cpp.template"
                                                              for (size_t k = 1; k <= grammar->k; ++k)
                                                              {
                                                                Format format;
                                                                wchar_t *asString = format.toString<wchar_t>(k);
                                                            #line 1259 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var l");
                                                            #line 865 "PrintJavascript.cpp.template"
                                                                print(asString);
                                                            #line 1264 "PrintJavascript.cpp"
  append(L", b");
                                                            #line 866 "PrintJavascript.cpp.template"
                                                                print(asString);
                                                            #line 1268 "PrintJavascript.cpp"
  append(L", e");
                                                            #line 867 "PrintJavascript.cpp.template"
                                                                print(asString);
                                                            #line 1272 "PrintJavascript.cpp"
  append(L";");
                                                            #line 868 "PrintJavascript.cpp.template"
                                                              }
                                                              if (hasBacktracking)
                                                              {
                                                            #line 1278 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var bx, ex, sx, lx, tx;");
                                                            #line 872 "PrintJavascript.cpp.template"
                                                              }
                                                              if (isLrParser && ! useGlr)
                                                              {
                                                            #line 1285 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var iStack = [];\n");
  append(L"  var top = -1;");
                                                            #line 877 "PrintJavascript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                            #line 1293 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var eventHandler;");
                                                            #line 881 "PrintJavascript.cpp.template"
                                                              }
                                                              if (memoization)
                                                              {
                                                                int bits = Math::bits(grammar->conflictCount);
                                                            #line 1301 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var memo;");
                                                            #line 886 "PrintJavascript.cpp.template"
                                                                if (grammar->noThrow)
                                                                {
                                                            #line 1307 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  var viable;");
                                                            #line 889 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1312 "PrintJavascript.cpp"
  append(L"\n");
  append(L"\n");
  append(L"  function memoize(i, e, v)\n");
  append(L"  {\n");
  append(L"    memo[(e << ");
                                                            #line 894 "PrintJavascript.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1320 "PrintJavascript.cpp"
  append(L") + i] = v;\n");
  append(L"  }\n");
  append(L"\n");
  append(L"  function memoized(i, e)\n");
  append(L"  {\n");
  append(L"    var v = memo[(e << ");
                                                            #line 900 "PrintJavascript.cpp.template"
                                                                print(format.toString<wchar_t>(bits));
                                                            #line 1329 "PrintJavascript.cpp"
  append(L") + i];\n");
  append(L"    return typeof v != \"undefined\" ? v : 0;\n");
  append(L"  }");
                                                            #line 903 "PrintJavascript.cpp.template"
                                                              }
                                                              if (useGlr)
                                                              {
                                                                decreaseIndent();
                                                              }
                                                            }

                                                            void PrintJavascript::printPlatformSpecific()
                                                            {
                                                            #line 1343 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  if (typeof process !== \"undefined\")   // assume node.js\n");
  append(L"  {\n");
  append(L"    var command = \"node\";\n");
  append(L"    var arguments = process.argv.slice(2);\n");
  append(L"    var log = function(string) {process.stdout.write(string);};\n");
  append(L"    var fs = require(\"fs\");\n");
  append(L"    var readTextFile = fs.readFileSync;");
                                                            #line 919 "PrintJavascript.cpp.template"
                                                              if (performanceTest)
                                                              {
                                                            #line 1355 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    var readDir = fs.readdirSync;\n");
  append(L"    var isDirectory = function(filename) {return fs.statSync(filename).isDirectory();};");
                                                            #line 924 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1361 "PrintJavascript.cpp"
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
                                                            #line 937 "PrintJavascript.cpp.template"
                                                              if (performanceTest)
                                                              {
                                                            #line 1378 "PrintJavascript.cpp"
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
                                                            #line 951 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1393 "PrintJavascript.cpp"
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
                                                            #line 973 "PrintJavascript.cpp.template"
                                                            }

                                                            void PrintJavascript::printFileProcessor()
                                                            {
                                                            #line 1420 "PrintJavascript.cpp"
  append(L"\n");
  append(L"// performance test main program for use with node.js, rhino, or jrunscript\n");
  append(L"\n");
  append(L"function main(args)\n");
  append(L"{");
                                                            #line 981 "PrintJavascript.cpp.template"
                                                              printPlatformSpecific();
                                                            #line 1428 "PrintJavascript.cpp"
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
                                                            #line 991 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1442 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    this.contentCounter = new ContentCounter();");
                                                            #line 994 "PrintJavascript.cpp.template"
                                                                if (isLrParser)
                                                                {
                                                            #line 1448 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    this.parseTreeBuilder = new ");
                                                            #line 997 "PrintJavascript.cpp.template"
                                                                  print(className.c_str());
                                                            #line 1453 "PrintJavascript.cpp"
  append(L".ParseTreeBuilder();");
                                                            #line 998 "PrintJavascript.cpp.template"
                                                                }
                                                              }
                                                            #line 1458 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    this.parser = new ");
                                                            #line 1001 "PrintJavascript.cpp.template"
                                                              print(className.c_str());
                                                            #line 1463 "PrintJavascript.cpp"
  append(L"(i");
                                                            #line 1002 "PrintJavascript.cpp.template"
                                                              if (noLexer)
                                                              {
                                                            #line 1468 "PrintJavascript.cpp"
  append(L", null");
                                                            #line 1004 "PrintJavascript.cpp.template"
                                                              }
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1476 "PrintJavascript.cpp"
  append(L", this.parseTreeBuilder");
                                                            #line 1009 "PrintJavascript.cpp.template"
                                                                }
                                                                else
                                                                {
                                                            #line 1482 "PrintJavascript.cpp"
  append(L", this.contentCounter");
                                                            #line 1012 "PrintJavascript.cpp.template"
                                                                }
                                                              }
                                                            #line 1487 "PrintJavascript.cpp"
  append(L");\n");
  append(L"  }\n");
                                                            #line 1016 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                            #line 1493 "PrintJavascript.cpp"
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
                                                            #line 1029 "PrintJavascript.cpp.template"
                                                              }
                                                              printReadMethod();
                                                            #line 1508 "PrintJavascript.cpp"
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
                                                            #line 1056 "PrintJavascript.cpp.template"
                                                                    print(className.c_str());
                                                            #line 1537 "PrintJavascript.cpp"
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
                                                            #line 1129 "PrintJavascript.cpp.template"
                                                              print(methodPrefixParse);
                                                              print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1614 "PrintJavascript.cpp"
  append(L"();\n");
  append(L"              if (! quiet) log(\"\\n\");");
                                                            #line 1132 "PrintJavascript.cpp.template"
                                                              if (tree)
                                                              {
                                                                if (isLrParser)
                                                                {
                                                            #line 1622 "PrintJavascript.cpp"
  append(L"\n");
  append(L"              job.parseTreeBuilder.serialize(job.contentCounter);");
                                                            #line 1138 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1627 "PrintJavascript.cpp"
  append(L"\n");
  append(L"              if (job.contentCounter.getLength() != job.input.length)\n");
  append(L"              {\n");
  append(L"                throw \"content counter saw \" + job.contentCounter.getLength() +\n");
  append(L"                      \", but input length is \" + job.input.length;\n");
  append(L"              }");
                                                            #line 1144 "PrintJavascript.cpp.template"
                                                              }
                                                            #line 1636 "PrintJavascript.cpp"
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
                                                            #line 1183 "PrintJavascript.cpp.template"
                                                            }

                                                            void PrintJavascript::printReadMethod()
                                                            {
                                                            #line 1680 "PrintJavascript.cpp"
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
                                                            #line 1202 "PrintJavascript.cpp.template"
                                                            }

                                                            void PrintJavascript::close(Grammar *node)
                                                            {
                                                              if (lexerInstanceCode == 0 || lexerStaticCode == 0)
                                                              {
                                                                internalerr();
                                                              }

                                                              print(L"\n");
                                                              print(lexerInstanceCode);
                                                            #line 1710 "PrintJavascript.cpp"
  append(L"\n");
  append(L"}\n");
                                                            #line 1215 "PrintJavascript.cpp.template"
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
                                                            #line 1726 "PrintJavascript.cpp"
  append(L"\n");
  append(L"// main program for use with node.js, rhino, or jrunscript\n");
  append(L"\n");
  append(L"function main(args)\n");
  append(L"{");
                                                            #line 1231 "PrintJavascript.cpp.template"
                                                                printPlatformSpecific();
                                                                printReadMethod();
                                                            #line 1735 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  if (arguments.length == 0)\n");
  append(L"  {\n");
  append(L"    log(\"Usage: \" + command + \" ");
                                                            #line 1237 "PrintJavascript.cpp.template"
                                                                print(className.c_str());
                                                            #line 1742 "PrintJavascript.cpp"
  append(L".js ");
                                                            #line 1238 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1747 "PrintJavascript.cpp"
  append(L"[-i] ");
                                                            #line 1240 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1751 "PrintJavascript.cpp"
  append(L"INPUT...\\n\");\n");
  append(L"    log(\"\\n\");\n");
  append(L"    log(\"  parse INPUT, which is either a filename or literal text enclosed in curly braces\\n\");");
                                                            #line 1244 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1758 "PrintJavascript.cpp"
  append(L"\n");
  append(L"    log(\"\\n\");\n");
  append(L"    log(\"  Option:\\n\");\n");
  append(L"    log(\"    -i     indented parse tree\\n\");");
                                                            #line 1249 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1765 "PrintJavascript.cpp"
  append(L"\n");
  append(L"  }\n");
  append(L"  else\n");
  append(L"  {\n");
  append(L"    var indent = false;\n");
  append(L"    for (var i = 0; i < arguments.length; ++i)\n");
  append(L"    {");
                                                            #line 1256 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1776 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      if (arguments[i] === \"-i\")\n");
  append(L"      {\n");
  append(L"        indent = true;\n");
  append(L"        continue;\n");
  append(L"      }");
                                                            #line 1263 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1785 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      var input = read(String(arguments[i]));");
                                                            #line 1265 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                            #line 1791 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      var s = new ");
                                                            #line 1268 "PrintJavascript.cpp.template"
                                                                  print(staticPrefix());
                                                            #line 1796 "PrintJavascript.cpp"
  append(L"XmlSerializer(log, indent);");
                                                            #line 1269 "PrintJavascript.cpp.template"
                                                                  if (isLrParser)
                                                                  {
                                                            #line 1801 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      var b = new ");
                                                            #line 1272 "PrintJavascript.cpp.template"
                                                                    print(staticPrefix());
                                                            #line 1806 "PrintJavascript.cpp"
  append(L"ParseTreeBuilder();");
                                                            #line 1273 "PrintJavascript.cpp.template"
                                                                  }
                                                                }
                                                            #line 1811 "PrintJavascript.cpp"
  append(L"\n");
  append(L"      var parser = new ");
                                                            #line 1276 "PrintJavascript.cpp.template"
                                                                print(className.c_str());
                                                            #line 1816 "PrintJavascript.cpp"
  append(L"(input");
                                                            #line 1277 "PrintJavascript.cpp.template"
                                                                if (tree)
                                                                {
                                                                  if (isLrParser)
                                                                  {
                                                            #line 1823 "PrintJavascript.cpp"
  append(L", b");
                                                            #line 1281 "PrintJavascript.cpp.template"
                                                                  }
                                                                  else
                                                                  {
                                                            #line 1829 "PrintJavascript.cpp"
  append(L", s");
                                                            #line 1284 "PrintJavascript.cpp.template"
                                                                  }
                                                                }
                                                            #line 1834 "PrintJavascript.cpp"
  append(L");\n");
  append(L"      try\n");
  append(L"      {");
                                                            #line 1288 "PrintJavascript.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1841 "PrintJavascript.cpp"
  append(L"\n");
  append(L"        parser.writeTrace(\"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?\" + \">\\n<trace>\\n\");");
                                                            #line 1292 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1846 "PrintJavascript.cpp"
  append(L"\n");
  append(L"        parser.");
                                                            #line 1294 "PrintJavascript.cpp.template"
                                                                print(methodPrefixParse);
                                                                print(Format::acceptableName<WString>(grammar->startSymbol()->name).c_str());
                                                            #line 1852 "PrintJavascript.cpp"
  append(L"();");
                                                            #line 1296 "PrintJavascript.cpp.template"
                                                                if (trace)
                                                                {
                                                            #line 1857 "PrintJavascript.cpp"
  append(L"\n");
  append(L"        parser.writeTrace(\"</trace>\\n\");\n");
  append(L"        parser.flushTrace();");
                                                            #line 1300 "PrintJavascript.cpp.template"
                                                                }
                                                                if (tree && isLrParser)
                                                                {
                                                            #line 1865 "PrintJavascript.cpp"
  append(L"\n");
  append(L"        b.serialize(s);");
                                                            #line 1304 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1870 "PrintJavascript.cpp"
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
                                                            #line 1314 "PrintJavascript.cpp.template"
                                                                if (rejectsAmbiguity() && tree)
                                                                {
                                                            #line 1884 "PrintJavascript.cpp"
  append(L"\n");
  append(L"          if (pe.isAmbiguousInput())\n");
  append(L"          {\n");
  append(L"            pe.serialize(s);\n");
  append(L"            log(\"\\n\");\n");
  append(L"          }");
                                                            #line 1321 "PrintJavascript.cpp.template"
                                                                }
                                                            #line 1893 "PrintJavascript.cpp"
  append(L"\n");
  append(L"          throw parser.getErrorMessage(pe);\n");
  append(L"        }\n");
  append(L"      }\n");
  append(L"    }\n");
  append(L"  }\n");
  append(L"}\n");
  append(L"\n");
  append(L"main(arguments);\n");
                                                            #line 1332 "PrintJavascript.cpp.template"
                                                              }
                                                              if (performanceTest)
                                                              {
                                                                printFileProcessor();
                                                              }
                                                            }

// End
