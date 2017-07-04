/* https://www.reddit.com/r/dailyprogrammer/comments/2kpnky/10292014_challenge_186_intermediate_syzygyfication/ */

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

const double PI2 = 6.28318530718;
const double ALIGN_THRESHOLD = 0.00125;  // radians

class orbital_body
{
public:
    string name;
    double orbit_radius, orbit_period, x_pos, y_pos;

    orbital_body::orbital_body(const string n, const double or, const double op) :
        name(n),
        orbit_radius(or),
        orbit_period(op),
        x_pos(0.0),
        y_pos(0.0)
    {}

    friend bool   operator< (orbital_body &x, orbital_body &y) { return (x.name < y.name); }

    double orbital_body::calc_angle(orbital_body &a)
    {
        double rel_a_x = a.x_pos - x_pos;
        double rel_a_y = a.y_pos - y_pos;
        return fmod(PI2 + atan2(rel_a_y, rel_a_x), PI2); // map to circle in radians
    }

    void orbital_body::adv_orbit(double years)
    {
        if (orbit_period != 0.0)
        {
            double orbit_pos = fmod(years, orbit_period) / orbit_period; // % of orbital period traversed.
            double orbit_theta = PI2 * orbit_pos;   // convert % to angle traversed in radians.
            x_pos = orbit_radius * cos(orbit_theta);
            y_pos = orbit_radius * sin(orbit_theta);
        }
    }
};

class syzygy_calculator 
{
public:
    void syzygy_calculator::do_calc(double years)
    {
        vector<orbital_body> ss{
                { "Sun",      0.000,   0.000 },
                { "Mercury",  0.387,   0.241 },
                { "Venus",    0.723,   0.615 },
                { "Earth",    1.000,   1.000 },
                { "Mars",     1.524,   1.881 },
                { "Jupiter",  5.204,  11.862 },
                { "Saturn",   9.582,  29.457 },
                { "Uranus",  19.189,  84.017 },
                { "Neptune", 30.071, 164.795 } };

        sort(ss.begin(), ss.end());

        cout << "calculating for " << years << " years..." << endl;
        for (auto i = ss.begin(); i != ss.end(); ++i)
            i->adv_orbit(years); // advance all planets in their orbits

        set<string> final_align;

        do {
            double benchmark = ss[0].calc_angle(ss[1]);
            set<string> test_align;
            test_align.insert(ss[0].name);
            test_align.insert(ss[1].name);

            for (unsigned int i = 2; i < ss.size(); ++i)
            {
                double contender = ss[0].calc_angle(ss[i]);
                if (abs(benchmark - contender) < ALIGN_THRESHOLD)
                    test_align.insert(ss[i].name);
                else
                    break;
            }

            if (test_align.size() > 2)
            {
                string planet_list;
                for each (auto s in test_align)
                    planet_list += " " + s;
                final_align.insert(planet_list);
            }

        } while (next_permutation(ss.begin(), ss.end()));

        for each (auto s in final_align)
            cout << " " << s << endl;
    }
};

int main()
{
    syzygy_calculator calc;

    calc.do_calc(3.30085);  // Mercury - Earth - Mars - Jupiter
    calc.do_calc(9.12162);  // Sun - Mercury - Mars, Mercury - Venus - Saturn
    calc.do_calc(18.0852);  // Sun - Mars - Saturn, Mercury - Earth - Saturn - Neptune
    calc.do_calc(31.0531);  // Sun - Earth - Saturn, Venus - Earth - Mars (no)
    calc.do_calc(40.2048);  // Sun - Venus - Mars (no), Mercury - Mars - Saturn (no), Earth - Mars - Uranus
    calc.do_calc(66.2900);  // Sun - Venus - Earth - Uranus
    calc.do_calc(151.234);  // nothing...

    system("pause");
    return 0;
}