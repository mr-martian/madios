#ifndef LEXICONUNIT_H
#define LEXICONUNIT_H

#include "utils/Stringable.h"

#include <set>
#include <vector>

enum LexiconUnitType {
  Start,
  End,
  Symbol,
  SP,
  EC
};

std::set<unsigned int> intersectSet(const std::set<unsigned int>& a, const std::set<unsigned int>& b);
unsigned int intersectSetSize(const std::set<unsigned int>& a, const std::set<unsigned int>& b);
bool isSubset(const std::set<unsigned int>& a, const std::set<unsigned int>& b);

class LexiconUnit: public Stringable
{
public:
  LexiconUnitType type;

  std::string symbol;
  std::set<unsigned int> equivalence;
  std::vector<unsigned int> sequence;

  LexiconUnit(LexiconUnitType type_);
  LexiconUnit(const std::string& symbol_);
  LexiconUnit(const std::set<unsigned int>& equivalence_);
  LexiconUnit(const std::vector<unsigned int>& sequence_);
  ~LexiconUnit();

  LexiconUnit* makeCopy() const;
  std::string toString() const;
  unsigned int size() const;

  bool has(unsigned int unit) const;
  bool add(unsigned int unit);

  unsigned int find(unsigned int unit) const;
};

#endif
