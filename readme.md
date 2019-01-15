# Statements to Clauses
## Authors
2003:
Daniel Johnson

## About
	My final project was to create a computer program that could take a logical statement as input and output an equivalent list of clauses. This has relevance, because many automated theorem provers use such clauses as their input. As opposed to a brute force method, in which a the program would formulate a truth table for each input statement and compare it with the tables of many different clause lists, I decided to utilize equivalence rules. This, in my opinion, is a far more practical route, as it will most often complete its task in a shorter period of time.
	Using the program is pretty self-explanatory. As noted in a key that appears every time the program is run, the only connectives used are the biconditional (“<->”), the conditional (“->”), conjunctions  (“^”), disjunctions (“V”), and negations (“~”). Literals can be pretty much any combination of letters and numbers as long as they do not include capital “V” (as this is the symbol for a disjunction). There is also a possibility of error if there is a single literal surround by parenthesis. One such example of this is for a statement like “~(A)” which returns “{~,A,}.”Also, when inputting a statement, avoid putting spaces in the logical statement. Be sure to check that an input has the correct use of parenthesis, as an error may cause problems. 
	The first few steps of the algorithm are mainly to format the statement. The very first thing the program does is put enclose the statement by parenthesis, which may help later in the process. Then the biconditionals are dealt with. Any statement of the form, “(…(A<->B)…)” is changed to “(…((A->B)^(B->A))…),” and this process is repeated until there are no remaining biconditionals. Then conditionals are attacked in a similar fashion. Statements in the form, “(…(A->B)…)” and replaces them with “(…(~AVB)…),” also until the rule can no longer be applied. The remaining statement was then termed exclusively in conjunctions, disjunctions, and negations: a much easier format to work with.
	The rest of the algorithm was coded in the form of a recursive function with five different steps, or rules to be applied. In order, these steps were, double negation, DeMorgans, the base case, splitting of conjuncted statements and distribution of disjunctions. The function would run sequentially: attempting to apply a rule and only moving to the next one if the current one could not be applied. In other words if a specific step was applied it meant that no step before it was applicable. This makes more sense in practice. 
First the program would check for any double negations. As soon as one was found, the function would call itself with the double negation fixed. For example if the phrase “(…~~A…)” was in the original phrase parameterized in the function, the function would call itself with “(…A…)” as its parameter. This would reoccur until there were no remaining double negations. At this point the program would move to the next step. 
In the DeMorgans step, the function would search through the statement until it found a statement of the form “(…~(AVB)…)” or “(…~(A^B)…)” and would then call the function with “(…(~A^~B)…)” or “(…(~AV~B)…)” respectively as its parameter. Such an application could potentially cause a double negation to form. This would be quickly rectified, as the function would then check for double negations before it could move on. 
	Then at a point when the first two rules are not applicable, the program would check to see if there were any conjunctions left in the statement. If there were none, the statement could be immediately put into clausal form. A statement like “(AV(BVC))” would be written to the command window as “{A,B,C,}.” This is called the base case, as it is the scenario which the function reaches its goal and can end. However, if this rule cannot be applied the function moves on to its next step.
	The algorithm then calls for the statement to be checked to see if it is actually the conjunction of two smaller statements. If so the function calls itself twice: once for each substatement. The phrase “A^(BVC)” would call the function once with “A” as its parameter, and again with “(BVC)” as its parameter. 
	If the function gets to the final step, it must be true that it is the disjunction of two smaller statements since it is not the conjunction. It is also known that there is at least one conjunction somewhere in the statement since it was not taken car of by the base case. Using this knowledge the program performs distribution by taking the disjuncted statement and making it into the conjunction of two disjunctions. An example of such an application is as follows, “(AV(B^C))” would be split into “(AVB)” and “(AVC),” and each would be ran through the function separately.
	Barring any errors in the input, this algorithm should always succeed in taking the logical statement and putting it into clausal form. Besides such situations, there should never be any case in which the function cannot apply any of the five steps, as all non-literal statements must either, after removing conditionals, be in the form of a conjunction of two statements, the disjunction of two statements, or the negation there of. As for any statements that are composed of a literal; there cannot be a conjunction in such a statement and thus qualify for the base case. 
	Though functional, there are a number of features that would greatly improve the quality of the program. One such improvement would be a more user-friendly, more beautiful interface. The text would be easier to read in a different font, and the connectives would be clearer if they were not improvised from plain text. Also, error checking would add a lot, as it is not too difficult to make a mistake when inputting a statement. The inclusion of quantifiers and the whole resolution algorithm would greatly expand the program’s capabilities. Though this program essentially converts statements into conjunctive normal form, allowing users to convert to other normal forms would take much more than a few lines of code, though it would be a nice capability. It is possible for a given clause to contain an element more than once, which though not ideal, will not affect the validity of the results. This can be fixed with further work.