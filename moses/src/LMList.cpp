// $Id: LMList.cpp 158 2007-10-22 00:47:01Z hieu $

/***********************************************************************
Moses - factored phrase-based language decoder
Copyright (C) 2006 University of Edinburgh

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
***********************************************************************/

#include "LMList.h"
#include "Phrase.h"
#include "LanguageModelSingleFactor.h"
#include "ScoreComponentCollection.h"

using namespace std;

void LMList::CalcScore(const FactorMask &mask, const Phrase &phrase, float &retFullScore, float &retNGramScore, ScoreComponentCollection* breakdown) const
{ 
	const_iterator lmIter;
	for (lmIter = begin(); lmIter != end(); ++lmIter)
	{
		const LanguageModel &lm = **lmIter;
		const float weightLM = lm.GetWeight();

		float fullScore, nGramScore;

		// do not process, if factors not defined yet (happens in partial translation options)
		if (!lm.Useable(mask))
			continue;

		lm.CalcScore(phrase, fullScore, nGramScore);

		breakdown->Assign(&lm, nGramScore);  // I'm not sure why += doesn't work here- it should be 0.0 right?
		retFullScore   += fullScore * weightLM;
		retNGramScore	+= nGramScore * weightLM;
	}	
}
