#include "LoopHeader.h"
#include <iostream>
#include <ctime>


LoopHeader::LoopHeader(LetterList * letterList, int difficulty) {

	// randomly generate all for loop variables and operators
	int modifier = difficulty < 2 ? 5 : 1;
	int middleRand = rand() % (50 / modifier) - (25 / modifier);

	conditionOperator = rand() % 4 + 1;
	A.num = rand() % (50 / modifier) + middleRand;
	B.num = rand() % (50 / modifier) + middleRand;
	C.num = difficulty < 2 ? 1 : rand() % 4 + 2;

	A.letter = letterList->grabLetter();
	B.letter = letterList->grabLetter();
	C.letter = letterList->grabLetter();
	firstIteration = true;

	if (conditionOperator % 2 == 0) {

		// 10 percent chance to make an infinite loop
		counterOperator = rand() % 10 < 9 ? 0 : 1;

		if (rand() % 10 < 9)
			B.num -= (50 / modifier);
		else
			A.num -= (50 / modifier);

	}

	else {

		counterOperator = rand() % 10 < 9 ? 1 : 0;

		if (rand() % 10 < 9)
			A.num -= (50 / modifier);
		else
			B.num -= (50 / modifier);

	} // end if

} // end constructor


// determines if the loop will be infinite
bool LoopHeader::isInfinite() const {

	return (
		
		conditionOperator % 2 != counterOperator && (
		(conditionOperator == 1 && A.num < B.num) ||
		(conditionOperator == 2 && A.num > B.num) ||
		(conditionOperator == 3 && A.num <= B.num) ||
		(conditionOperator == 4 && A.num >= B.num))

	); // end return

} // end isInfinite


// display all variables at the top of the question associated with the for loop
void LoopHeader::showVariables() const {

	cout << ", " << B.letter << " = " << B.num;

	if (C.num > 1)
		cout << ", " << C.letter << " = " << C.num;

} // end showVariables


// display for loop header
void LoopHeader::showLine() const {

	cout << "for (" << A.letter << " = " << A.num << "; " << A.letter;

	switch (conditionOperator)
	{
	case 1:
		cout << " < ";
		break;
	case 2:
		cout << " > ";
		break;
	case 3:
		cout << " <= ";
		break;
	default:
		cout << " >= ";
	}

	cout << B.letter << "; " << A.letter;

	if (counterOperator == 1)
		if (C.num == 1)
			cout << "++)";
		else
			cout << " += " << C.letter << ")";
	else
		if (C.num == 1)
			cout << "--)";
		else
			cout << " -= " << C.letter << ")";

} // end showLine


// used for determining the answer to the question. iterates the value of A and returns true/false based on if the for loop condition is met.
bool LoopHeader::iterate() {

	if (firstIteration)
		firstIteration = false;
	else
		if (counterOperator == 1)
			A.num += C.num;
		else
			A.num -= C.num;

	return (

		(conditionOperator == 1 && A.num < B.num) ||
		(conditionOperator == 2 && A.num > B.num) ||
		(conditionOperator == 3 && A.num <= B.num) ||
		(conditionOperator == 4 && A.num >= B.num)

	); // end return

} // end iterate