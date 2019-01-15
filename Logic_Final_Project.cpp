//DAN JOHSNON
#include <string>
#include <vector>
#include <iostream>
using namespace std;


bool char_find(char a, string phrase)
{
	for(int i = 0; i < phrase.size(); i++)
		if (phrase[i] == a)
			return true;

	return false;
}

void Clausitize(string phrase)						// recursive function with a single string as a parameter
{
	for(int i = 0; i < phrase.size() - 1; i++)		// Double Negation
	{
		if(phrase[i] == '~' && phrase[i+1] == '~')
		{
			string dn_phrase = string();

			for(int j = 0; j < phrase.size(); j++)
			{
				if(j == i)
					continue;

				if(j == i + 1)
					continue;

				dn_phrase += phrase[j];
			}

			Clausitize(dn_phrase);

			return;
		}
	}												// END


	for(int k = 0; k < phrase.size() - 1; k++)		// DeMorgans
	{
		if(phrase[k] == '~' && phrase[k + 1] == '(')
		{
			int lp_open = 1;

			for(int l = k + 2; l < phrase.size(); l++)
			{
				if(phrase[l] == '(')
					lp_open++;

				if(phrase[l] == ')')
					lp_open--;

				if(lp_open == 1 && phrase[l] == 'V')
				{
					string newphrase = string();

					for(int x = 0; x < phrase.size(); x++)
					{
						if(x == k)
							continue;

						if(x == k + 2)
							newphrase += '~';

						if(x == l)
						{
							newphrase += "^~";

							continue;
						}

						newphrase += phrase[x];
					}

					Clausitize(newphrase);

					return;
				}

				if(lp_open == 1 && phrase[l] == '^')
				{
					string newphrase1 = string();

					for(int y = 0; y < phrase.size(); y++)
					{
						if(y == k)
							continue;

						if(y == k + 2)
							newphrase1 += '~';

						if(y == l)
						{
							newphrase1 += "V~";

							continue;
						}

						newphrase1 += phrase[y];
					}

					Clausitize(newphrase1);

					return;
				}
			}
		}
	}												// END

	if(!char_find('^',phrase))						// Base Case
	{
		cout << "{";

		vector<string> clauses;

		string clause_1 = string();

		for(int w = 0; w < phrase.size(); w++)
		{
			if(phrase[w] == '(')
			{
				if(clause_1.size() != 0)
				{
	//				clauses.push_back(clause_1);

					cout << clause_1 << ",";

					clause_1 = string();
				}

				continue;
			}

			if(phrase[w] == ')')
			{
				if(clause_1.size() != 0)
				{
	//				clauses.push_back(clause_1);

					cout << clause_1 << ",";

					clause_1 = string();
				}

				continue;
			}

			if(phrase[w] == 'V')
			{
				if(clause_1.size() != 0)
				{
	//				clauses.push_back(clause_1);

					cout << clause_1 << ",";

					clause_1 = string();
				}

				continue;
			}

			clause_1 += phrase[w];
		}

	//	for(vector<string>::iterator itr = clauses.begin(); itr != clauses.end(); itr++)
	//	{
	//		cout << '{' << *itr << '}' << endl;
	//	}

		cout << "}" << endl;

		return;
	}												// END


	int and_level_min = phrase.size();
	int or_level_min = phrase.size();
	int and_low_ind, or_low_ind;
	for(int r = 0; r < phrase.size(); r++)			// conjunction split
	{
		if(phrase[r] == '^')
		{
			int lp_level = 0;
			int rp_level = 0;

			for(int f = r; f >= 0; f--)
			{
				if(phrase[f] == ')')
					lp_level--;
				if(phrase[f] == '(')
					lp_level++;
			}

			if(lp_level < and_level_min)
			{
				and_level_min = lp_level;
				and_low_ind = r;
			}
		}
		if(phrase[r] == 'V')
		{
			int lp1_level = 0;

			for(int f = r; f >= 0; f--)
			{
				if(phrase[f] == ')')
					lp1_level--;
				if(phrase[f] == '(')
					lp1_level++;
			}

			if(lp1_level < or_level_min)
			{
				or_level_min = lp1_level;
				or_low_ind = r;
			}

		}

	}										

	if(or_level_min > and_level_min)
	{
		string phrase1 = string();
		string phrase2 = string();

		for(int u = 1; u < and_low_ind; u++)
		{
			phrase1 += phrase[u];
		}

		int l_side = 0;
		int r_side = 0;

		for(int aa = phrase1.size()/2; aa >= 0; aa--)
		{
			if(phrase1[aa] == ')')
				l_side--;
			if(phrase1[aa] == '(')
				l_side++;
		}

		for(int bb = phrase1.size()/2 + 1; bb < phrase1.size(); bb++)
		{
			if(phrase1[bb] == ')')
				r_side++;
			if(phrase1[bb] == '(')
				r_side--;
		}

		if(r_side < l_side)
		{
			for(int cc = 0; cc < l_side - r_side; cc++)
				phrase1 += ')';
		}
		
		if(r_side > l_side)
		{
			for(int dd = 0; dd < r_side - l_side; dd++)
				phrase1 += '(';
		}

		phrase1 = '(' + phrase1 + ')';

		l_side = 0;
		r_side = 0;
		
		for(int v = and_low_ind + 1; v < phrase.size() - 1; v++)
		{
			phrase2 += phrase[v];
		}

		for(int ee = phrase2.size()/2; ee >= 0; ee--)
		{
			if(phrase2[ee] == ')')
				l_side--;
			if(phrase2[ee] == '(')
				l_side++;
		}

		for(int ff = phrase2.size()/2 + 1; ff < phrase2.size(); ff++)
		{
			if(phrase2[ff] == ')')
				r_side++;
			if(phrase2[ff] == '(')
				r_side--;
		}

		if(r_side < l_side)
		{
			for(int gg = 0; gg < l_side - r_side; gg++)
				phrase2 += ')';
		}
		
		if(r_side > l_side)
		{
			for(int hh = 0; hh < r_side - l_side; hh++)
				phrase2 += '(';
		}

		phrase2 = '(' + phrase2 + ')';

		Clausitize(phrase1);
		Clausitize(phrase2);

		return;
	}												//END

	int low_and_ind;								// disjunction split
	int min_and_level = phrase.size();
	int and_level = 0;

/*	for(int c = 0; c < phrase.size(); c++)
	{
		if(phrase[c] == '(')
			and_level++;

		if(phrase[c] == ')')
			and_level--;

		if(phrase[c] == '^')
		{
			if(and_level < min_and_level)
			{
				low_and_ind = c;
				min_and_level = and_level;
			}
		}
	}
*/

	min_and_level = and_level_min;
	low_and_ind = and_low_ind;

	string or_phrase = string();

	int l_bound, r_bound;
	int right_count = 0;
	int left_count = 0;

	int check = 0;
	for(int d = low_and_ind; d >= 0; d--)
	{		
		
		if(left_count == 0 && phrase[d] == '(')
		{
			l_bound = d;
			check++;

			break;
		}

		if(phrase[d] == ')')
			left_count++;

		if(phrase[d] == '(')
			left_count--;	
		

	}

	if(check == 0)
		l_bound=0;

	check = 0;
		
	for(int e = low_and_ind; e < phrase.size() ; e++)
	{		
		if(right_count == 0 && phrase[e] == ')')
		{
			r_bound = e;

			check++;

			break;
		}

		if(phrase[e] == '(')
			right_count++;

		if(phrase[e] == ')')
			right_count--;

	}

	if(check == 0)
		r_bound = phrase.size() - 1;

	int left_stop, right_stop;
	int p_ct = 0;

	string or_phrase1 = string();

	string mini_phrase = string();
	for(int a = 0; a < l_bound - 1; a++)
	{
		or_phrase1 += phrase[a];
	}

	if(phrase[l_bound - 1] != 'V')
	{
		or_phrase1 += phrase[l_bound - 1];
	}

	if(phrase[r_bound + 1] != 'V')
	{
		or_phrase1 += phrase[r_bound + 1];
	}

	for(int qq = r_bound + 2; qq < phrase.size(); qq++)
	{
		or_phrase1 += phrase[qq];
	}


/*
	else
	{
		left_stop = l_bound;
	
		for(int o = r_bound; o < phrase.size(); o++)
		{
			if(p_ct == 0 && phrase[o] == ')')
			{
				right_stop = o;

				break;
			}

			if(phrase[o] == ')')
				p_ct--;

			if(phrase[o] == '(')
				p_ct++;
		}
	}

	for(int h = r_bound + 1; h < phrase.size(); h++)
	{
		if(h == right_stop)
			continue;

		or_phrase1 += phrase[h];
	}
*/
	string one_clause = string();
	string two_clause = string();
	string l_and = string();
	string r_and = string();
	
	for(int z = l_bound + 1; z < low_and_ind; z++)
	{
		l_and += phrase[z];
	}

	for(int tt = low_and_ind + 1; tt < r_bound; tt++)
	{
		r_and += phrase[tt];
	}

	one_clause = '(' + or_phrase1 + 'V' + l_and + ')';
	two_clause = '(' + or_phrase1 + 'V' + r_and + ')';

	Clausitize(one_clause);
	Clausitize(two_clause);

	return;
}

string DeConditional(string phrase)
{
	while(char_find('>',phrase))
	{
		int m;
		for(m = 0; m < phrase.size(); m++)
		{
			if (phrase[m] == '>')
				break;
		}


		int left_parenthesis, right_parenthesis;
		int rp_count = 0;
		int lp_count = 0;
		int j;
		for(j = m; j >= 0; j--)
		{
			if(phrase[j] == ')')
				rp_count++;
			if(phrase[j] == '(' && rp_count == 0)
				break;
			if(phrase[j] == '(')
				rp_count--;
		}

		left_parenthesis = j;
		int k;
		for(k = m; k < phrase.size(); k++)
		{
			if(phrase[k] == '(')
				lp_count++;
			if(phrase[k] == ')' && lp_count == 0)
				break;
			if(phrase[k] == ')')
				lp_count--;
		}

		right_parenthesis = k;
		
		string first_term = string();
		string second_term = string();
		
		for(int r = left_parenthesis + 1; r < m - 1; r++)
			first_term += phrase[r];

		for(int t = m + 1; t < right_parenthesis; t++)
			second_term += phrase[t];

		string phrase2 = string();

		for(int w = 0; w <=  left_parenthesis; w++)
			phrase2 += phrase[w];

		phrase2 = phrase2 + '~' + first_term + "V" + second_term;

		for(int v = right_parenthesis; v < phrase.size(); v++)
			phrase2 += phrase[v];

		phrase = phrase2;

	}

	return phrase;
}

string DeBiconditional(string phrase)
{
	while(char_find('<',phrase))
	{
		int m;
		for(m = 0; m < phrase.size(); m++)
			if (phrase[m] == '<')
				break;

		int left_parenthesis, right_parenthesis;
		int rp_count = 0;
		int lp_count = 0;
		int j;
		for(j = m; j >= 0; j--)
		{
			if(phrase[j] == ')')
				rp_count++;
			if(phrase[j] == '(' && rp_count == 0)
				break;
			if(phrase[j] == '(')
				rp_count--;
		}

		left_parenthesis = j;
		int k;
		for(k = m; k < phrase.size(); k++)
		{
			if(phrase[k] == '(')
				lp_count++;
			if(phrase[k] == ')' && lp_count == 0)
				break;
			if(phrase[k] == ')')
				lp_count--;
		}

		right_parenthesis = k;
		
		string first_term = string();
		string second_term = string();
		
		for(int r = left_parenthesis + 1; r < m; r++)
			first_term += phrase[r];

		for(int t = m + 3; t < right_parenthesis; t++)
			second_term += phrase[t];

		string phrase2 = string();

		for(int w = 0; w <=  left_parenthesis; w++)
			phrase2 += phrase[w];

		phrase2 = phrase2 + '(' + first_term + "->" + second_term + ")^(" + second_term + "->" + first_term + ')';

		for(int v = right_parenthesis; v < phrase.size(); v++)
			phrase2 += phrase[v];

		phrase = phrase2;

	}

	return phrase;
}

string ReplaceVs(string phrase)
{
	for(int i = 0; i < phrase.size(); i++)
	{
		if(phrase[i] == 'V')
		{
			string phrase2;

			for(int j = 0; j < i; j++)
			{
				phrase2 += phrase[j];
			}

			phrase2 += '|';

			for(int k = i + 1; k < phrase.size(); k++)
			{
				phrase2 += phrase[k];
			}

			phrase = phrase2;
		}
	}

	return phrase;
}

void clausitize(string phrase)
{
	//phrase = ReplaceVs(phrase);

	phrase = '(' + phrase + ')';

	phrase = DeBiconditional(phrase);

	phrase = DeConditional(phrase);

	//cout << phrase << endl;

	Clausitize(phrase);
}

int main()
{
	string more = "1";

	while(more == "1")
	{
		string phrase;

		cout << "Key:" << endl << endl
			<< "Literals	Any alphanumeric phrase not containing 'V'" << endl
			<< "^		Conjunction" << endl << "V		Disjunction" << endl 
			<< "~		Negation" << endl << "->		Conditional" << endl 
			<< "<->		Biconditional" << endl << endl;

		cout << "Enter a logical statement (no spaces):" << endl << "Type 'exit' to exit " << endl << endl << endl;
		cin >> phrase;

		if(phrase == "exit")
			break;

		clausitize(phrase);

	}

	return 0;
}
