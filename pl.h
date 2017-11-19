#ifndef PL4_H
#define PL4_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

class Literal {
    public:
        Literal( std::string const& _name ) : name(_name), negated(false) { }
        Literal( ) : name(""), negated(false) { } // just for map.operator[]
        ////////////////////////////////////////////////////////////////////////
        Literal& Negate() { negated=!negated; }
        bool IsPositive() const { return !negated; }
        ////////////////////////////////////////////////////////////////////////
        bool operator==( Literal const& op2 ) const {
            Literal const& op1 = *this;
            return ( op1.negated == op2.negated ) && ( op1.name == op2.name );
        }
        ////////////////////////////////////////////////////////////////////////
        bool operator<( Literal const& op2 ) const {
            Literal const& op1 = *this;
            //negated infront
            if ( op1.negated && !op2.negated ) {
                return true;
            }
            if ( !op1.negated && op2.negated ) {
                return false;
            }
            return ( op1.name < op2.name );
        }
        ////////////////////////////////////////////////////////////////////////
        Literal operator~() const { 
Literal result(*this);
result.Negate();
return result;
		}
		////////////////////////////////////////////////////////////////////////
		bool Complementary(Literal const& op2) const {
			return (name == op2.name) && (negated != op2.negated);
		}
		////////////////////////////////////////////////////////////////////////
		friend std::ostream& operator<<(std::ostream& os, Literal const& literal) {
			os << (literal.negated ? "~" : "") << literal.name;
			return os;
		}
	private:
		std::string name;
		bool negated;
};

class Clause {   //Bunch of Literals OR'd together
public:
	// ..........
	// ..........
	// ..........
	// ..........
	////////////////////////////////////////////////////////////////////////
	Clause() : literals() {}
	Clause( Literal const& l) : literals() { literals.insert(l); }
	//Change this to bool maybe?  idk
	void Insert( Literal const& l) { literals.insert(l); }
	bool operator<( Clause const& other) const
	{
		//for(auto myIt = literals.begin())

		if (*(literals.end()) < (*(other.literals.begin() )))
		{
			return true;
		}

		else if(*(other.literals.end()) < (*(literals.begin())))
		{
			return false;
		}

		else
		{
			int iterOffset = 0;
			for (auto myIter = literals.begin(); myIter != literals.end();)  //myIter++
			{

				auto otherIter = other.literals.begin();
				for (int i = 0; i < iterOffset; i++)
				{
					if (otherIter != other.literals.end())
					{
						otherIter++;// iterOffset;
					}
					else {
						otherIter = other.literals.end();
						i = iterOffset;
					}
				}


				//Thing at position iterOffset in THIS clause is strictly less than thing at position iterOffset in OTHER clause
				if (*myIter < *otherIter)
				{
					return true;
				}

				//Thing at position iterOffset in OTHER clause is strictly less than thing at position iterOffset in THIS clause
				else if (*myIter < *otherIter)
				{
					return false;
				}


				if (myIter != literals.end())
				{
					iterOffset++;
					myIter++;
				}



			}


			return false;
		}

	}

		

	/*
	Clause const operator>(Clause const& other) const
	{

	}

	Clause const operator&(Clause const& other) const
	{

	}

	Clause const operator|(Clause const& other) const
	{

	}

	Clause const operator~() const
	{

	}
	*/


	std::pair<bool,Clause> CanResolve(const Clause& other) const
	{
		//Returns true & resolves clauses if possible
		//False otherwise
		Clause outClause;
		Clause c1(*this);
		Clause c2(other);
		int complimentaryClauses = 0;
		auto myIter = c1.literals.begin();
		auto otherIter = c2.literals.begin();

	//	auto myCurrPos = literals.begin();
	//	auto otherCurrPos = other.literals.begin();

		auto myCompIter = c1.literals.begin();
		auto otherCompIter = c2.literals.begin();

		while (myIter != c1.literals.end())
		{
			while (otherIter != c2.literals.end())
			{
				if ((*myIter) == ~(*otherIter))
				{
					complimentaryClauses++;
					
					if(complimentaryClauses>=2)
					{
						return std::make_pair(false,outClause);
					}

					myCompIter = myIter;
					otherCompIter = otherIter;


				}



				if (otherIter != c2.literals.end())
				{
					otherIter++;
				}
			}

			if(myIter != c1.literals.end())
			{
				myIter++;
			}



		}


		//If we get out of the loops successfully, we know there's exactly ONE complimentary pair &
		//we have the iterators that point to the values


		c1.literals.erase(myCompIter);
		c2.literals.erase(otherCompIter);

		for (auto x = c1.literals.begin(); x != c1.literals.end(); x++)
		{
			outClause.Insert(*x);
		}


		for (auto x = c2.literals.begin(); x != c2.literals.end(); x++)
		{
			outClause.Insert(*x);
		}

		return std::make_pair(true, outClause);

	}



	friend std::ostream& operator<<(std::ostream& os, Clause const& clause) {
		unsigned size = clause.literals.size();

		if (size == 0) {
			os << " FALSE ";
		}
		else {
			std::set< Literal >::const_iterator it = clause.literals.begin();
			os << "( " << *it;
			++it;
			for (; it != clause.literals.end(); ++it) {
				os << " | " << *it;
			}
			os << " ) ";
		}
		return os;
	}
//private:
	std::set< Literal > literals;
};

class CNF {   //Bunch of Clauses AND'd together
public:
	// ..........
	// ..........
	// ..........
	// ..........
	////////////////////////////////////////////////////////////////////////
	
	CNF( Clause const& c) : clauses() { clauses.insert(c); }
	CNF( Literal const& l) : clauses() { clauses.insert(Clause(l)); }
	CNF() : clauses() {}

	
	
	std::pair<bool,CNF>  CanResolve(const CNF& other)
	{
		//Returns true if there exists exactly 1 complimentary pair, resolves on it
		//False otherwise
		CNF out;
		bool outBool = false;
		auto myClauseIter = clauses.begin();
		auto otherClauseIter = other.clauses.begin();

	//	int numClausesCount = 0;

	//	auto complimentaryClauseIter1 = clauses.begin(); 
	//	auto complimentaryClauseIter2 = other.clauses.begin();//	clauses.begin()
	
	
		while (myClauseIter != clauses.end())
		{
			otherClauseIter = other.clauses.begin();
			while (otherClauseIter != other.clauses.end())
			{
				auto t = myClauseIter->CanResolve(*otherClauseIter);
				
				if (t.first)
				{
					out.clauses.insert(t.second);
					outBool = true;
				}


			}

		}

		return std::make_pair(outBool,out);

	}


	// not
	CNF const operator~() const {   //Aren't all of these supposed to act on the current, given CNF?
		//if CNF is made of a single clause: A | B | ~C,
		//negating it gives ~A & ~B & C (3 clauses)
		//otherwise
		//CNF = clause1 & clause2 & clause3,
		//~CNF = ~clause1 | ~clause2 | ~clause3 
		//"or" is defined later 

		CNF & op1 = CNF(*this);  //Add or remove const from this?   

		if (0==clauses.size())  //SOMETHING HAS GONE HORRIBLY HORRIBLY WRONG
		{
			return op1;
		}


		else if (clauses.size() == 1)  //
		{
			auto myLiterals = op1.clauses.begin();
			for (auto literalsIter = myLiterals->literals.begin(); literalsIter != myLiterals->literals.end(); literalsIter++)
			{
			//	Literal l(*literalsIter);
			//	Clause c(~(l));
			//	Clause c(~(*literalsIter));
			//	clauses.insert(c);


			//	clauses.insert(const_cast<Clause&>(Clause(~(*literalsIter))));
				op1.clauses.emplace(~(*literalsIter));
			
				//clauses.insert(const_cast<Literal&>(*literalsIter));
			
				//Literal l(*literalsIter);
				//clauses.emplace(l);
			
			
			}
			return op1;
		}

		

		else
		{
			//CNF out;
			auto opClauses = clauses.begin();
			CNF out(~ CNF(*opClauses));
			opClauses++;
			for ( ;opClauses != op1.clauses.end(); opClauses++)
			{
				out = out | (~ CNF(*opClauses));
			}

			return out;
		}






	}
	////////////////////////////////////////////////////////////////////////
	// =>
	CNF const operator>(CNF const& op2) const {
		CNF const& op1 = *this;
		return ~(op1) | op2;
	}
	////////////////////////////////////////////////////////////////////////
	// and
	CNF const operator&(CNF const& op2) const {   //Gotta check this, CONFUSED
		//CNF1 = clause1 & clause2 & clause3,
		//CNF2 = clause4 & clause5 & clause6,
		//CNF1 & CNF2 = clause1 & clause2 & clause3 & clause4 & clause5 & clause6


		CNF out(*this);
		for (auto otherClausesIter = op2.clauses.begin(); otherClausesIter != op2.clauses.end(); otherClausesIter++)
		{
			out.clauses.insert(*otherClausesIter);
		}

		return out;


	}
	///////////////////////////////////////////////////////////////////////
	// or
	CNF const operator|(CNF const& op2) const {
		//CNF1 = clause1 & clause2 & clause3,
		//CNF2 = clause4 & clause5 & clause6,
		//CNF1 | CNF2 = 
		//              c1|c4 & c1|c5 & c1|c6    &
		//              c2|c4 & c2|c5 & c2|c6    &
		//              c3|c4 & c3|c5 & c3|c6

		//output CNF out = this
		//for each literal in THIS = i
			//for each literal in op2 = j
				// out +=  i|j


		CNF out;

		for (auto thisIter = this->clauses.begin(); thisIter != clauses.end(); thisIter++)
		{
			for (auto otherIter = op2.clauses.begin(); otherIter != op2.clauses.end(); otherIter++)
			{
				//out.clauses.emplace((*thisIter) | (*otherIter));

				
				for (auto thisClauseIter = (*thisIter).literals.begin(); thisClauseIter != (*thisIter).literals.end(); thisClauseIter++)
					{
						for (auto otherClauseIter = (*otherIter).literals.begin(); otherClauseIter != (*otherIter).literals.end(); otherClauseIter++)
							{
								out.clauses.emplace((*thisClauseIter) | (*otherClauseIter));
							}

					}

					

				}
			}
			
		return out;

        }

        /////////////////////////////////////////////////////////////////////////////////
        CNF const operator>( Literal const& op2 ) const { return operator>( CNF(op2) ); }
        CNF const operator&( Literal const& op2 ) const { return operator&( CNF(op2) ); }
        CNF const operator|( Literal const& op2 ) const { return operator|( CNF(op2) ); }

        ////////////////////////////////////////////////////////////////////////
        bool Empty() const { return clauses.size()==0; }
        ////////////////////////////////////////////////////////////////////////
        std::set< Clause >::const_iterator begin() const { return clauses.begin(); }
        std::set< Clause >::const_iterator end()   const { return clauses.end(); }
        unsigned                           size()  const { return clauses.size(); }
        ////////////////////////////////////////////////////////////////////////
        friend std::ostream& operator<<( std::ostream& os, CNF const& cnf ) {
            unsigned size = cnf.clauses.size();
            for( std::set< Clause >::const_iterator it1 = cnf.clauses.begin(); it1 != cnf.clauses.end(); ++it1) { 
                os << *it1 << ", ";
            }
            return os;
        }
    private:
        std::set< Clause > clauses;
};

CNF const operator|( Literal const& op1, Literal const& op2 );
CNF const operator|( Literal const& op1, CNF     const& op2 );
CNF const operator&( Literal const& op1, Literal const& op2 );
CNF const operator&( Literal const& op1, CNF     const& op2 );
CNF const operator>( Literal const& op1, Literal const& op2 );
CNF const operator>( Literal const& op1, CNF     const& op2 );

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class KnowledgeBase {
    public:
        ////////////////////////////////////////////////////////////////////////////
        KnowledgeBase();
        ////////////////////////////////////////////////////////////////////////////
        KnowledgeBase& operator+=( CNF const& cnf );
        ////////////////////////////////////////////////////////////////////////
        std::set< Clause >::const_iterator begin() const;
        std::set< Clause >::const_iterator end()   const;
        unsigned                           size()  const;
        ////////////////////////////////////////////////////////////////////////////
        bool ProveByRefutation( CNF const& alpha ) const;
        ////////////////////////////////////////////////////////////////////////////
        friend std::ostream& operator<<( std::ostream& os, KnowledgeBase const& kb );
    private:
        std::set< Clause > clauses;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#endif
