#include "pl.h"

CNF const operator|( Literal const& op1, Literal const& op2 ) { return CNF(op1)|CNF(op2); }
CNF const operator|( Literal const& op1, CNF     const& op2 ) { return CNF(op1)|op2; }
CNF const operator&( Literal const& op1, Literal const& op2 ) { return CNF(op1)&CNF(op2); }
CNF const operator&( Literal const& op1, CNF     const& op2 ) { return CNF(op1)&op2; }
CNF const operator>( Literal const& op1, Literal const& op2 ) { return CNF(op1)>CNF(op2); }
CNF const operator>( Literal const& op1, CNF     const& op2 ) { return CNF(op1)>op2; }


KnowledgeBase::KnowledgeBase() : clauses() {}
////////////////////////////////////////////////////////////////////////////
KnowledgeBase& KnowledgeBase::operator+=( CNF const& cnf ) {
    for ( std::set< Clause >::const_iterator it = cnf.begin(); it != cnf.end(); ++it ) {
        clauses.insert( *it );
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////
std::set< Clause >::const_iterator KnowledgeBase::begin() const { return clauses.begin(); }
std::set< Clause >::const_iterator KnowledgeBase::end()   const { return clauses.end(); }
unsigned                           KnowledgeBase::size()  const { return clauses.size(); }
////////////////////////////////////////////////////////////////////////////
bool KnowledgeBase::ProveByRefutation( CNF const& alpha ) const {


	KnowledgeBase kb(*this);

	kb += ~alpha;


	bool out = true;

	//Push ~alpha into new kb


	//Make new set of CNFs to push stuff into - temp1, temp2
	
	//For each CNF in KB
		//Go through positive terms
		//Go through negative terms
			//If exactly 1 complimentary pair
				//Resolve & OR them together, push back into temp1
			//Get to end of KB	
			//For each in temp1
				//Go through + terms of temp1 & KB
				//Go through neg terms of temp1 & KB
					//If exactly 1 complimentary pair
						//Resolve & push  into temp2
					//Get to end of temp1
					//Merge temp1 with KB
			//Repeat process w/ temp2




	std::set<Clause> temp;

//	auto kbFirstNegative = kb.begin();
//	auto kbFirstPositive = kb.begin();
	
//	while(kbFirstPositive->)

	auto kbIter = kb.begin();
	auto kbEndIter = kb.end();
	auto kbIter2 = kb.begin();


	while (kbIter != kbEndIter)
	{

		


	}


	//auto tempIter = temp.begin();
//	auto tempEndIter = temp.end();
//	auto tempIter2 = temp.begin();
	//auto firstIter = kb.begin();
	//auto secondIter = kb.begin();



//	for (; kbIter != kb.end();)
//	{
		//secondIter = kbIter;
		//for (; secondIter != kb.end();
//		int iter2Count = 0;
//		kbIter2 = kbIter;
//		for(;kbIter2 != kbEndIter;)
//		{
			

//			auto clauseIter1 = kbIter->literals.begin();
//			auto clauseIter2 = kbIter2->literals.begin();

			






				






			
//		}


//	}


}
////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<( std::ostream& os, KnowledgeBase const& kb ) {
    unsigned size = kb.clauses.size();
    for( std::set< Clause >::const_iterator it1 = kb.clauses.begin(); it1 != kb.clauses.end(); ++it1) { 
        os << *it1 << ", ";
    }
    return os;
}
