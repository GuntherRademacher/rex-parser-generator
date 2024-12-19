/*
 * LookaheadCompressor.cpp
 *
 *  Created on: 10.11.2012
 *      Author: Gunther
 */

#include "../common/Memory.hpp"
#include "LookaheadCompressor.hpp"
#include "PredictionBuilder.hpp"

void LookaheadCompressor::visitGrammar(Grammar *node)
{
  grammar = node;

  grammar->k = 0;

  MarkLookaheadAvailability ml;
  grammar->accept(ml);

  if (grammar->whitespace)
  {
    determineWhitespaceIntroducers(grammar);

    if (! grammar->complexWhitespaceIntroducers.empty())
    {
      grammar->whitespace->runOffLoad = true;
      grammar->whitespace->accept(rop);
    }
  }

  section = NONTERMINALS;
  visitNodeList(grammar->nonTerminals);

  grammar->renumber();

  for (Node *n = grammar->nonTerminals; n; n = n->followingSibling)
  {
    Production *p = static_cast <Production *> (n);
    if (   ! p->runPayload
        && ! p->runOffLoad
        && p != grammar->whitespace)
    {
      printf("-Warning- Nonterminal %ls not used\n", p->name);
    }
  }

  PredictionBuilder pb(grammar);
  pb.collectInput();
  pb.build();

  if (grammar->verbose)
  {
    fprintf(stdout, "number of lookahead sets: %d\n", (int) grammar->lookaheadSets.size());
    fflush(stdout);
  }
}
