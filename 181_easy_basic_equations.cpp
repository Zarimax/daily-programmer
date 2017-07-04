/* https://www.reddit.com/r/dailyprogrammer/comments/2h5b2k/09222014_challenge_181_easy_basic_equations/ */

#include <iostream>
#include <string>

using namespace std;

class equation_solver 
{
  public:
          void solve(const string &, const string &);

  private:
          void parse_equation(const string &, double &, double &);
};

// parse equations, do math, and print results
void equation_solver::solve(const string &eq1, const string &eq2) 
{
      double eq1_x = 1.0, eq1_c = 0.0;
      double eq2_x = 1.0, eq2_c = 0.0;

      parse_equation(eq1, eq1_x, eq1_c);
      parse_equation(eq2, eq2_x, eq2_c);

      double tot_x = eq1_x - eq2_x;
      double tot_c = eq2_c - eq1_c;
      double fin_x = tot_c / tot_x;
      double fin_y = (eq1_x * fin_x) + eq1_c;

      cout << eq1 << " and " << eq2 << endl;
      cout << " intersection: (" << fin_x << "," << fin_y << ")" << endl << endl;
}

// extract a and b from form y=ax+b
void equation_solver::parse_equation(const string &eq, double &a, double &b)
{
      size_t prev = 0, pos;
      while ((pos = eq.find_first_of("x=", prev)) != string::npos)
      {
           if (pos > prev && prev != 0)
                a = stod(eq.substr(prev, pos - prev));
           prev = pos + 1;
      }
      if (prev < eq.length())
           b = stod(eq.substr(prev, string::npos));
}

// test main
int main(int argc, char * argv[])
{
      equation_solver eqs;                  // can only solve form y=ax+b
      eqs.solve("y=2x+2", "y=5x-4");            // solves to (2,6)
      eqs.solve("y=-5x", "y=-4x+1");            // solves to (-1,5)
      eqs.solve("y=0.5x+1.3", "y=-1.4x-0.2"); // solves to (-0.789474,0.905263)
      eqs.solve("y=x", "y=3x+1");               // solves to (-0.5,-0.5)
      eqs.solve("y=x", "y=x+1");                // solves to (1.#INF,1.#INF) - no intersection
      eqs.solve("y=2x+2", "y=2x+2");            // solves to (-1.#IND,-1.#IND) - infinite intersection

      system("pause"); // warning: not portable off Windows
      return 0;
}