#include "LexiconUnit.h"

#include <cassert>
#include <sstream>

using std::string;
using std::set;
using std::vector;
using std::ostream;
using std::ostringstream;

LexiconUnit::LexiconUnit(LexiconUnitType type_) : type(type_) {}

LexiconUnit::LexiconUnit(const string& symbol_)
  : type(Symbol), symbol(symbol_) {}

LexiconUnit::LexiconUnit(const set<unsigned int>& equivalence_)
  : type(EC), equivalence(equivalence_) {}

LexiconUnit::LexiconUnit(const vector<unsigned int>& sequence_)
  : type(SP), sequence(sequence_) {}

LexiconUnit::~LexiconUnit() {}

LexiconUnit*
LexiconUnit::makeCopy() const
{
  LexiconUnit* ret = new LexiconUnit(this->type);
  switch(this->type) {
    case Symbol:
      ret->symbol = this->symbol;
      break;
    case EC:
      ret->equivalence = this->equivalence;
      break;
    case SP:
      ret->sequence = this->sequence;
      break;
  }
  return ret;
}

string
LexiconUnit::toString() const
{
  switch(type) {
    case Start:
      return "START";
    case End:
      return "END";
    case Symbol:
      return symbol;
    case EC:
    {
      ostringstream sout;
      sout << "E[";
      bool first = true;
      for(auto& it : equivalence) {
        if(!first) { sout << " | "; }
        first = false;
        sout << "P" << it;
      }
      sout << "]";
      return sout.str();
    }
    case SP:
    {
      ostringstream sout;
      sout << "P[";
      bool first = true;
      for(auto& it : sequence) {
        if(!first) { sout << " - "; }
        first = false;
        sout << "P" << it;
      }
      sout << "]";
      return sout.str();
    }
    default:
      assert(false);
  }
}

unsigned int
LexiconUnit::size() const
{
  switch(type) {
    case SP:
      return sequence.size();
    case EC:
      return equivalence.size();
    default:
      return 1;
  }
}

unsigned int
LexiconUnit::find(unsigned int unit) const
{
  assert(type == SP);
  for(unsigned int i = 0; i < sequence.size(); i++) {
    if(sequence[i] == unit) {
      return i;
    }
  }
  assert(false);
}

LexiconUnit
LexiconUnit::computeOverlapEC(const LexiconUnit& other) const
{
  assert(type == EC);
  assert(other.type == EC);

  LexiconUnit overlap(EC);
  for(auto it : other.equivalence) {
    if(has(it)) {
      overlap.add(it);
    }
  }
  return overlap;
}

unsigned int
LexiconUnit::computeOverlapECSize(const LexiconUnit& other) const
{
  assert(type == EC);
  assert(other.type == EC);

  unsigned int count = 0;
  for(auto it : other.equivalence) {
    if(has(it)) {
      count++;
    }
  }
  return count;
}

bool
LexiconUnit::has(unsigned int unit) const
{
  return equivalence.find(unit) != equivalence.end();
}

bool
LexiconUnit::add(unsigned int unit)
{
  assert(type == EC);
  return equivalence.insert(unit).second;
}
