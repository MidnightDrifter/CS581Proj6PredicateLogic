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


	//bool out = true;

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






	//ASSUMES THAT:
	//If KB size doesn't change after we merge it with temp, then we'll have no solution

	std::set<Clause> temp, temp2;

//	auto kbFirstNegative = kb.begin();
//	auto kbFirstPositive = kb.begin();
	
//	while(kbFirstPositive->)


	if(kb.clauses.empty())
	{
		return true;
	}


	auto kbIter = kb.begin();
	auto kbEndIter = kb.end();
	auto kbIter2 = kb.begin();
	auto kbBeforeEndIter = kb.begin();
	if (kb.size() > 0)
	{
		kbBeforeEndIter = --kb.end();
	}
	else
	{
		kbBeforeEndIter = kb.end();
	}




	//Initial pass over kb
	while (kbIter != kbBeforeEndIter)
	{
		kbIter2 = kbIter;
		kbIter2++;
		if (kbIter->literals.empty())
		{
			return true;
		}

		while (kbIter2 != kbEndIter)
		{
			if (kbIter2->literals.empty())
			{
				return true;
			}

			auto testPair = kbIter->CanResolve(*kbIter2);
			if (testPair.first)
			{
				if (testPair.second.literals.empty())
				{
					return true;
				}


				temp.insert(testPair.second);
			}

			if (kbIter2 != kbEndIter)
			{
				kbIter2++;
			}
		
		
		
		}
		
		if (kbIter != kbBeforeEndIter)
		{
			kbIter++;
		}
		
	} 


	int kbSize = kb.size();  //Keep track of starting vs. ending size--if they're the same, we've checked everything we can
	bool keepGoing = true;

	auto tempBaseIter = temp.begin();
	auto tempPairIter = temp.begin();
	auto tempEndIter = temp.end();
	auto tempBeforeEndIter = temp.end();
	if(temp.size() >0)
	{ tempBeforeEndIter--; }
	//kbIter = kb.begin();
	//kbEndIter = kb.end();


	
	while (keepGoing)
	{

		kbIter = kb.begin();
		kbEndIter = kb.end();
		

		while (tempBaseIter != tempBeforeEndIter)
		{
			while (kbIter != kbEndIter)
			{
				auto pair1 = tempBaseIter->CanResolve(*kbIter);
				if (pair1.first)
				{
					if (pair1.second.literals.empty())
					{
						return true; 
					}
					
					temp2.insert(pair1.second);
				}
				kbIter++;
			}


			tempPairIter = tempBaseIter;
			tempPairIter++;
			while (tempPairIter != tempEndIter)
			{
				//tempPairIter++;
				
				auto pair2 = tempBaseIter->CanResolve(*tempPairIter);
				if (pair2.first)
				{
					if (pair2.second.literals.empty())
					{
						return true;
					}
					temp2.insert(pair2.second);
				}

				tempPairIter++;
			}

			if (tempBaseIter != tempBeforeEndIter)
			{
				tempBaseIter++;
			}
			

		}

	
	
		//Insert all temp clauses into KB
		for (auto x = temp.begin(); x != temp.end(); x++)
		{
			kb.clauses.insert(*x);
		}

		if (kbSize == kb.size())
		{
			//No change in size, return FALSE
		//	return false;
			keepGoing = false;
		}

		else {
			kbSize = kb.size();
			std::swap(temp, temp2);
			temp2.clear();

			tempBaseIter = temp.begin();
			tempPairIter = temp.begin();
			tempEndIter = temp.end();
			if(temp.size()>0)
			{tempBeforeEndIter = --temp.end(); }
			else
			{
				tempBeforeEndIter = tempEndIter;
			}

			}
	}
	return false;
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
